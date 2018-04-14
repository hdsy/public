#include "boost/regex.hpp"


#include <string>
#include <iostream>

using namespace std;

const char* re = "(人)|(a)";   
boost::regex expression(re, boost::regex_constants::normal);
const char* re1 = "([$]{1})([a-zA-Z:0-9]+)([$]{1})";   
boost::regex expression1(re1, boost::regex_constants::normal);

typedef std::pair<std::string, int> pair_type;  
typedef std::vector<pair_type> vec_type;        

void MySearch(const std::string & file,vec_type & res)
{
	std::string::const_iterator start, end;
	start = file.begin();
	end = file.end();
	boost::match_results<std::string::const_iterator> what;
	boost::match_flag_type flags = boost::match_default | boost::match_any;

	vec_type v1;	//full
       vec_type v2;     // contain $
       vec_type v3;     // contain a-zA-Z0-9
       vec_type v4;     // contain $

	pair_type a;
	a.first = "___________________";
	a.second = 0;

	while (boost::regex_search(start, end, what, expression1, flags))
       {
             pair_type r;
             std::string::const_iterator temp = end;
             if (what[0].matched)
             {
                     r.first = std::string(what[0].first, what[0].second);
                     r.second = what[0].first - file.begin();
                     v1.push_back(r);

                     temp = what[0].second;
              }
              if (what[1].matched)      // 
              {
                   r.first = string(what[1].first, what[1].second);
                   r.second = what[1].first - file.begin();
                   v2.push_back(r);
      
                   if (temp - what[1].second > 0)
                   temp = what[1].second;
              }
     
              if (what[2].matched)
              {
                     r.first = string(what[2].first, what[2].second);
                     r.second = what[2].first - file.begin();
                     v3.push_back(r);
     
                     if (temp - what[2].second > 0)
                     temp = what[2].second;
              }
              if (what[3].matched)
              {
                     r.first = string(what[3].first, what[3].second);
                     r.second = what[3].first - file.begin();
                     v4.push_back(r);
     
                     if (temp - what[3].second > 0)
                     temp = what[3].second;
              }


              start = temp;
              flags = boost::match_default | boost::match_any;
       }

       res.insert(res.end(),v1.begin(),v1.end());		
	res.push_back(a);
       res.insert(res.end(),v2.begin(),v2.end());		
	res.push_back(a);
       res.insert(res.end(),v3.begin(),v3.end());		
	res.push_back(a);
       res.insert(res.end(),v4.begin(),v4.end());		
}
void search(const std::string& file, vec_type& vv)
{
       std::string::const_iterator start, end;
       start = file.begin();
       end = file.end();   
       boost::match_results<std::string::const_iterator> what;
       boost::match_flag_type flags = boost::match_default | boost::match_any; 
 
       vec_type v1;     // contain full expression 
       vec_type v2;     // contain (人) sub expression
       vec_type v3;     // contain (a) sub expression
       while (boost::regex_search(start, end, what, expression, flags))   
       {
             pair_type r;
             std::string::const_iterator temp = end;
             if (what[0].matched)
             {
                     r.first = std::string(what[0].first, what[0].second);
                     r.second = what[0].first - file.begin();      
                     v1.push_back(r);
      
                     temp = what[0].second;
              }
  
              if (what[1].matched)      // 
              {
                   r.first = string(what[1].first, what[1].second);
                   r.second = what[1].first - file.begin();
                   v2.push_back(r);
      
                   if (temp - what[1].second > 0)
                   temp = what[1].second;
              }
     
              if (what[2].matched)
              {
                     r.first = string(what[2].first, what[2].second);
                     r.second = what[2].first - file.begin();
                     v3.push_back(r);
     
                     if (temp - what[2].second > 0)
                     temp = what[2].second;
              }
  
              start = temp;
              flags = boost::match_default | boost::match_any;
       }

       vv.insert(vv.end(),v1.begin(),v1.end());
       vv.insert(vv.end(),v2.begin(),v2.end());
       vv.insert(vv.end(),v3.begin(),v3.end());
      // vv.push_back(v2);
      // vv.push_back(v3);
}




// 验证卡号是否与正则表达式匹配
bool validate_card_format(const std::string& s)
{
       static const boost::regex e("(\\d{4}[- ]){3}\\d{4}");
       return boost::regex_match(s, e);
}

int test_main()
{
       std::string s[4] = { "0000111122223333", "0000 1111 2222 3333",
                   "0000-1111-2222-3333", "000-1111-2222-3333", };
       int i;
       for (i = 0; i < 4; ++i)
       {
              std::cout << "validate_card_format(\"" << s[i] << "\") returned " 
                   << validate_card_format(s[i]) << std::endl;
        }
        
        return 0;
}

int main(int argc,char ** argv)
{
/*

	string src="非常";
	string reg="([\x81-\xfe][\x40-\xfe])+";


	if(argc == 3)
	{
		src = argv[1];
		reg = argv[2];
	}


	boost::regex re(reg);

	if(!boost::regex_match(src,re))
	{				
		cout << "NOK" <<endl;	
	}	
	else
	{
		cout << "OK" << endl;
	}

	test_main();

//*/
	string str="人a 人  a 人a  aaaa";

	vec_type v;		
	search(str,v);


	cout << "\r\n...." << "0123456789012345678901234567890" << endl;
	cout << "...." << str << endl;
	for(int i=0;i<v.size();i++)
	{
		cout << v[i].first << " : " << v[i].second << endl;	
	}
	cout << "\r\n...." << endl;


	string src = "select $fi:eld$ from $table$ where a=b limit $from$,$limit$ ";
	vec_type v1;
	MySearch(src,v1);
	cout << "\r\n...." << "01234567890123456789012345678901234567890123456789012345678901234567890123456789" << endl;
	cout << "...." << src << endl;
	for(int i=0;i<v1.size();i++)
	{
		cout << v1[i].first << " : " << v1[i].second << endl;	
	}
	cout << "\r\n...." << endl;


	return 0;
}

