#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <fstream>
#include "utils.h"

using namespace std;


namespace utils
{
    vector<string> split(const string& strValue, const string& separator)
    {
        vector<string> vecstrResult;
        int startpos=0;
        int endpos=0;

        endpos = strValue.find_first_of(separator, startpos);
        while (endpos != -1)
        {       
            vecstrResult.push_back(strValue.substr(startpos, endpos-startpos)); // add to vector
            startpos = endpos+1; //jump past sep
            endpos = strValue.find_first_of(separator, startpos); // find next
            if(endpos==-1)
            {
                //lastone, so no 2nd param required to go to end of string
                vecstrResult.push_back(strValue.substr(startpos));
            }
        }

        if(vecstrResult.empty())
            vecstrResult.push_back(strValue);

        return vecstrResult;
    }

    string str_join(vector <string> strList,const string & separator)
    {
        string temp = "";
        vector <string>::iterator it;
        
        if(strList.empty())
            return "";

        for(it=strList.begin();it!=strList.end();it++) {
            cout<<*it<<endl;
            if( it+1 == strList.end() )
                temp += *it;
            else
                temp += *it + separator;
        }
        return temp;
    }


    string remove(const string & strValue,const string & separator)
    {
        string temp = "";
        vector <string> _splitStr = split(strValue,separator);
        return str_join(_splitStr,"");
    }



    int str_to_int(string str)
    {
        char buf[str.size()];
        int i;

        strcpy(buf,str.c_str());
        sscanf(buf,"%d",&i);

        return i;
    }


    string int_to_str(int integer)
    {
        stringstream buf;
        buf<<integer;
        return buf.str();
    }

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  include_chinese
     *  Description:  check if Chinese words in string
     * =====================================================================================
     */
    int include_chinese(string word)//返回0：无中文，返回1：有中文
    {
        const char *str = word.c_str();
        char c;
        while(1)
        {
            c=*str++;
            if (c==0) 
                break;  //如果到字符串尾则说明该字符串没有中文字符
             
            if (c&0x80 & *str & 0x80) 
                return 1;//如果字符高位为1且下一字符高位也是1则有中文字符
        }
        return 0;
    }

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  readlines
     *  Description:  read file into array,seperate by "\n"
     * =====================================================================================
     */
    vector <string> readlines(char * filename)
    {
        ifstream fin(filename);  
        string line;  
        vector <string> list;
        while( getline(fin,line) )
        {    
            list.push_back(line);
        }
        return list;
    }




}
