#include <stdio.h>
#include <zlib.h>
#include <string.h>
#include <stdlib.h>
#include "gzip_mem.h"

#define OF(args)    args

#define OS_CODE        3    // unix

#if MAX_MEM_LEVEL >= 8
#  define DEF_MEM_LEVEL 8
#else
#  define DEF_MEM_LEVEL  MAX_MEM_LEVEL
#endif
/* default memLevel */

#define Z_BUFSIZE    16384

#define ALLOC(size)         malloc( size )
#define TRYFREE(p)          free( p )

static int gz_magic[2] = {0x1f, 0x8b}; /* gzip magic header */

/* gzip flag byte */
#define ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#define HEAD_CRC     0x02 /* bit 1 set: header CRC present */
#define EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#define ORIG_NAME    0x08 /* bit 3 set: original file name present */
#define COMMENT      0x10 /* bit 4 set: file comment present */
#define RESERVED     0xE0 /* bits 5..7: reserved */

typedef int ( * XGZFILE_PROC_READ  )( void* user_cb , void*       , int len );
typedef int ( * XGZFILE_PROC_WRITE )( void* user_cb , const void* , int len );

typedef struct xmem_gzstream {
    z_stream stream;
    int      z_err;   /* error code for last stream operation */
    int      z_eof;   /* set if end of input file */
    XGZFILE_PROC_READ   proc_read ;
    XGZFILE_PROC_WRITE  proc_write;
    void*               user_cb   ;
    Byte     *inbuf;  /* input buffer */
    Byte     *outbuf; /* output buffer */
    uLong    crc;     /* crc32 of uncompressed data */
    char     *msg;    /* error message */
    int      transparent; /* 1 if input file is not a .gz file */
    char     mode;    /* 'w' or 'r' */
    long     startpos; /* start of compressed data in file (header skipped) */
} xmem_gzstream;

static int    get_byte     OF((xmem_gzstream *s));
static int    check_header OF((xmem_gzstream *s));    /*!    return bytes of read. */
static int    destroy      OF((xmem_gzstream *s));
static void   putLong      OF((xmem_gzstream *s , uLong x));
static uLong  getLong      OF((xmem_gzstream *s));

xmem_gzstream*   XGZFILE_open( 
               XGZFILE_PROC_READ    proc_read   ,
               XGZFILE_PROC_WRITE   proc_write  ,
               void*                user_cb     ,
               int                create_flag ,
               int                  level )
{
    int err;
    int strategy = Z_DEFAULT_STRATEGY; /* compression strategy */
    static Byte simpleheader[] = {
        0x1f, 0x8b,    Z_DEFLATED  , 0 , 0 , 0 , 0 , 0 ,    0 , OS_CODE    };

    xmem_gzstream *s;

    if( (create_flag&&!proc_write) ||
        (!create_flag&&!proc_read) )    
        return Z_NULL;

    s = (xmem_gzstream *)ALLOC( sizeof(xmem_gzstream) );
    if( !s ) return Z_NULL;

    s->stream.zalloc = (alloc_func)0;
    s->stream.zfree = (free_func)0;
    s->stream.opaque = (voidpf)0;
    s->stream.next_in = s->inbuf = Z_NULL;
    s->stream.next_out = s->outbuf = Z_NULL;
    s->stream.avail_in = s->stream.avail_out = 0;
    
    s->proc_read  = proc_read ;
    s->proc_write = proc_write;
    s->user_cb    = user_cb   ;
    
    s->z_err = Z_OK;
    s->z_eof = 0;
    s->crc = crc32(0L, Z_NULL, 0);
    s->msg = NULL;
    s->transparent = 0;

    s->mode = create_flag ? 'w' : 'r';
    if( create_flag )
    {
        err = deflateInit2(&(s->stream), level,
                            Z_DEFLATED, -MAX_WBITS, DEF_MEM_LEVEL, strategy);
        s->stream.next_out = s->outbuf = (Byte*)ALLOC(Z_BUFSIZE);
        if (err != Z_OK || s->outbuf == Z_NULL) {
            return destroy(s), (xmem_gzstream*)Z_NULL;
        }
    }
    else 
    {
        s->stream.next_in  = s->inbuf = (Byte*)ALLOC(Z_BUFSIZE);

        err = inflateInit2(&(s->stream), -MAX_WBITS);
        if (err != Z_OK || s->inbuf == Z_NULL) {
            return destroy(s), (xmem_gzstream*)Z_NULL;
        }
    }

    s->stream.avail_out = Z_BUFSIZE;

    if( create_flag )
    {
        s->proc_write( s->user_cb , simpleheader , 10 );
        s->startpos = 10L;
    }
    else
    {
        s->startpos = check_header(s);
    }

    return (xmem_gzstream*)s;
}
    
int    XGZFILE_read ( xmem_gzstream* file , void*   buf    , int len )
{
    xmem_gzstream *s = (xmem_gzstream*)file;
    Bytef *start = (Bytef*)buf; /* starting point for crc computation */
    Byte  *next_out; /* == stream.next_out but not forced far (for MSDOS) */

    if( !s || s->mode != 'r' )    return Z_STREAM_ERROR;
    if (s->z_err == Z_DATA_ERROR || s->z_err == Z_ERRNO) return -1;
    if (s->z_err == Z_STREAM_END) return 0;  /* -1 */

    next_out = (Byte*)buf;
    s->stream.next_out = (Bytef*)buf;
    s->stream.avail_out = len;

    while (s->stream.avail_out != 0) {
        if (s->transparent) {
            /* Copy first the lookahead bytes: */
            uInt n = s->stream.avail_in;
            if (n > s->stream.avail_out) n = s->stream.avail_out;
            if (n > 0) {
                memcpy(s->stream.next_out, s->stream.next_in, n);
                next_out += n;
                s->stream.next_out = next_out;
                s->stream.next_in   += n;
                s->stream.avail_out -= n;
                s->stream.avail_in  -= n;
            }
            if (s->stream.avail_out > 0) {        
                s->stream.avail_out -= s->proc_read( s->user_cb ,
                    next_out , s->stream.avail_out );

            }
            len -= s->stream.avail_out;
            s->stream.total_in  += (uLong)len;
            s->stream.total_out += (uLong)len;
                if (len == 0) s->z_eof = 1;
            return (int)len;
        }

        if (s->stream.avail_in == 0 && !s->z_eof) {            
            /* errno = 0; */
            s->stream.avail_in = s->proc_read( s->user_cb , 
                s->inbuf , Z_BUFSIZE );

            if (s->stream.avail_in == 0) {
                s->z_eof = 1;                
            }
            s->stream.next_in = s->inbuf;
        }

        s->z_err = inflate(&(s->stream), Z_NO_FLUSH);

        if (s->z_err == Z_STREAM_END) {
            /* Check CRC and original size */
            s->crc = crc32(s->crc, start, (uInt)(s->stream.next_out - start));
            start = s->stream.next_out;
            
            if (getLong(s) != s->crc) {
                s->z_err = Z_DATA_ERROR;
            } else {
                (void)getLong(s);
                /* The uncompressed length returned by above getlong() may
                * be different from s->stream.total_out) in case of
                * concatenated .gz files. Check for such files:
                */
                check_header(s);
                if (s->z_err == Z_OK) {
                    uLong total_in = s->stream.total_in;
                    uLong total_out = s->stream.total_out;
                    
                    inflateReset(&(s->stream));
                    s->stream.total_in = total_in;
                    s->stream.total_out = total_out;
                    s->crc = crc32(0L, Z_NULL, 0);
                }
            }            
        }
        if (s->z_err != Z_OK || s->z_eof) break;        
    }
    s->crc = crc32(s->crc, start, (uInt)(s->stream.next_out - start));

    return len - s->stream.avail_out ;
}

int   XGZFILE_write( xmem_gzstream* file , const void* buf , int len )
{
    xmem_gzstream *s = (xmem_gzstream*)file;
    if (s == NULL || s->mode != 'w') return Z_STREAM_ERROR;
  
    s->stream.next_in = (Bytef*)buf;
    s->stream.avail_in = len;

    while (s->stream.avail_in != 0) {
        if (s->stream.avail_out == 0) {
            s->stream.next_out = s->outbuf;
            if( s->proc_write( s->user_cb , s->outbuf , Z_BUFSIZE ) != Z_BUFSIZE ) {
                s->z_err = Z_ERRNO;
                break;
            }
            s->stream.avail_out = Z_BUFSIZE;
        }
        s->z_err = deflate(&(s->stream), Z_NO_FLUSH);
        if (s->z_err != Z_OK) break;
    }
    s->crc = crc32(s->crc, (const Bytef *)buf, len);

    return (int)(len - s->stream.avail_in);
}
int  XGZFILE_flush( xmem_gzstream* file , int flush )
{
    xmem_gzstream *s = (xmem_gzstream*)file;
    uInt len;
    int done = 0;
    if( !s || s->mode != 'w' )    return Z_STREAM_ERROR;

    s->stream.avail_in = 0; /* should be zero already anyway */
    
    for (;;) {
        len = Z_BUFSIZE - s->stream.avail_out;

        if (len != 0) {
            if( s->proc_write( s->user_cb , s->outbuf , len ) != (int)len ) {
                s->z_err = Z_ERRNO;
                return Z_ERRNO;
            }
            s->stream.next_out = s->outbuf;
            s->stream.avail_out = Z_BUFSIZE;
        }
        if (done) break;
        s->z_err = deflate(&(s->stream), flush);

    /* Ignore the second of two consecutive flushes: */
    if (len == 0 && s->z_err == Z_BUF_ERROR) s->z_err = Z_OK;

        /* deflate has finished flushing only when it hasn't used up
         * all the available space in the output buffer: 
         */
        done = (s->stream.avail_out != 0 || s->z_err == Z_STREAM_END);
 
        if (s->z_err != Z_OK && s->z_err != Z_STREAM_END) break;
    }
    return  s->z_err == Z_STREAM_END ? Z_OK : s->z_err;
}

int  XGZFILE_eof  ( xmem_gzstream* file )
{
    xmem_gzstream *s = (xmem_gzstream*)file;    
    return (s == NULL || s->mode != 'r') ? 0 : s->z_eof;
}

int  XGZFILE_close( xmem_gzstream* file )
{
    int err;
    xmem_gzstream *s = (xmem_gzstream*)file;

    if (s == NULL) return Z_STREAM_ERROR;
    if (s->mode == 'w') {
        err = XGZFILE_flush (file, Z_FINISH);
        if (err != Z_OK) return destroy((xmem_gzstream*)file);
        putLong (s , s->crc);
        putLong (s , s->stream.total_in);
    }
    return destroy((xmem_gzstream*)file);
}

static int    get_byte     (xmem_gzstream *s)
{
    if (s->z_eof) return -1;
    if (s->stream.avail_in == 0) {
        /* errno = 0; */
        s->stream.avail_in = s->proc_read( s->user_cb , s->inbuf , Z_BUFSIZE );
        if (s->stream.avail_in == 0) {
            s->z_eof = 1;
            return -1;
        }
        s->stream.next_in = s->inbuf;
    }
    s->stream.avail_in--;
    return *(s->stream.next_in)++;
}

static void   putLong      (xmem_gzstream *s, uLong x)
{
    int n;
    char ch;
    for (n = 0; n < 4; n++) {
        ch = (char)(x & 0xff);
        s->proc_write( s->user_cb , &ch , 1 );        
        x >>= 8;
    }
}
static uLong  getLong      (xmem_gzstream *s)
{
    uLong x = (uLong)get_byte(s);
    int c;

    x += ((uLong)get_byte(s))<<8;
    x += ((uLong)get_byte(s))<<16;
    c = get_byte(s);
    if (c == -1) s->z_err = Z_DATA_ERROR;
    x += ((uLong)c)<<24;
    return x;
}

static int    destroy      (xmem_gzstream *s)
{
    int err = Z_OK;    
    if (!s) return Z_STREAM_ERROR;    
    TRYFREE(s->msg);
    
    if (s->stream.state != NULL) {
        if (s->mode == 'w') {
            err = deflateEnd(&(s->stream));
        } else if (s->mode == 'r') {
            err = inflateEnd(&(s->stream));
        }
    }

    if (s->z_err < 0) err = s->z_err;    
    TRYFREE(s->inbuf);
    TRYFREE(s->outbuf);
    TRYFREE(s);
    return err;
}

static int   check_header (xmem_gzstream *s)    /*!    return bytes of read. */
{
    int method; /* method byte */
    int flags;  /* flags byte */
    uInt len;
    int c;
    int lenret;
    int ch;
    
    /* Check the gzip magic header */
    for (len = 0; len < 2; len++) {
        c = get_byte(s);
        if (c != gz_magic[len]) {
            if (len != 0) s->stream.avail_in++, s->stream.next_in--;
            if (c != -1) {
                s->stream.avail_in++, s->stream.next_in--;
                s->transparent = 1;
            }
            s->z_err = s->stream.avail_in != 0 ? Z_OK : Z_STREAM_END;
            return len;
        }
    }
    lenret = 2;
    method = get_byte(s);    if( method != -1 ) ++lenret;
    flags = get_byte(s);    if( flags != -1 ) ++lenret;
    if (method != Z_DEFLATED || (flags & RESERVED) != 0) {
        s->z_err = Z_DATA_ERROR;
        return lenret;
    }
    
    /* Discard time, xflags and OS code: */
    for (len = 0; len < 6; len++) 
    {
        ch = get_byte(s);
        if( ch != -1 ) ++lenret;
        else {
            s->z_err = Z_DATA_ERROR;
            return lenret;
        }
    }
    
    if ((flags & EXTRA_FIELD) != 0) { /* skip the extra field */
        ch = get_byte(s); if( ch != -1 ) ++lenret;
        len  =  ch;    
        ch = get_byte(s); if( ch != -1 ) ++lenret;
        len += ((uInt)ch)<<8;
        /* len is garbage if -1 but the loop below will quit anyway */
        while (len-- != 0 && get_byte(s) != -1) ++lenret;
    }
    if ((flags & ORIG_NAME) != 0) { /* skip the original file name */
        while ((c = get_byte(s)) != 0 && c != -1) ++lenret;
    }
    if ((flags & COMMENT) != 0) {   /* skip the .gz file comment */
        while ((c = get_byte(s)) != 0 && c != -1) ++lenret;
    }
    if ((flags & HEAD_CRC) != 0) {  /* skip the header crc */
        for (len = 0; len < 2; len++) if( get_byte(s) != -1 ) ++lenret;
    }
    s->z_err = s->z_eof ? Z_DATA_ERROR : Z_OK;
    return lenret;
}


typedef unsigned char XU8;

static XU8 z_input[] = {
    0x1F,0x8B,0x08,0x08,0x59,0x96,0x9C,0x46,0x00,0x03,0x74,0x35,0x00,0x2B,0xC9,0xC8
        ,0x2C,0x56,0x00,0xA2,0x44,0x85,0x92,0xD4,0xE2,0x12,0x85,0xB4,0xCC,0x9C,0x54,0x5E
        ,0xAE,0x12,0x4C,0x41,0x00,0x9A,0xA3,0x62,0x77,0x28,0x00,0x00,0x00
};

static XU8 x_text[] = {
    0x74,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x61,0x20,0x74,0x65,0x73,0x74,0x20,0x66
        ,0x69,0x6C,0x65,0x0D,0x0A,0x74,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x61,0x20,0x74
        ,0x65,0x73,0x74,0x20,0x66,0x69,0x6C,0x65
};

const static string * pstring = NULL;
/*
static int X_test_read( void* user_cb , void* buff , int len )
{
    if( *(int*)user_cb >= sizeof( z_input ) || len <= 0 )
        return 0;
    if( len > (int)(sizeof( z_input ) - *(int*)user_cb) )
        len = sizeof( z_input ) - *(int*)user_cb;
    memcpy( buff , z_input + *(int*)user_cb , len );
    *(int*)user_cb += len;
    return len;
}
//*/
static int X_test_read( void* user_cb , void* buff , int len )
{
	if(pstring == NULL)
		return 0;

	if( *(int*)user_cb >= pstring->size()  || len <= 0 )
		return 0;
	if( len > (int)(pstring->size() - *(int*)user_cb) )
		len = pstring->size() - *(int*)user_cb;

	memcpy( buff , pstring->data() + *(int*)user_cb , len );

	*(int*)user_cb += len;

	return len;
}
/*
int main()
{
    int    off = 0 , len;
    XU8       buff[100];            
    xmem_gzstream*    strm = XGZFILE_open( X_test_read , NULL , &off , 0 , -1 );
    len = XGZFILE_read( strm , buff , sizeof( buff ) );
    XGZFILE_close( strm );

    if( len != sizeof( x_text ) || memcmp( x_text , buff , len ) )
        printf( "error\n" );


return 0;
}
//*/

string GUnzip(const string & zip_mem)
{
	int    off = 0 , len;
	XU8       buff[1024] ;

	memset(buff,0,sizeof(buff));

	string res;

	pstring = &zip_mem;

	xmem_gzstream*    strm = XGZFILE_open( X_test_read , NULL , &off , 0 , -1 );
	
	while(len = XGZFILE_read( strm , buff , sizeof( buff ) ))
	{
		res.append((char *)buff,len);
		memset(buff,0,sizeof(buff));
	}
	XGZFILE_close( strm );		



	return res;
	
}

