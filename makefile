all:
	make -C utility
	make -C http
	make -C html
	make -C fileconfig
	make -C linespm
	make -C logapi
	make -C bpml
	make -C demo
	make -C LPDD
	
clean:
	make -C utility	clean
	make -C http clean
	make -C html clean
	make -C fileconfig clean
	make -C linespm clean
	make -C logapi clean
	make -C bpml clean
	make -C demo clean
	make -C LPDD clean
