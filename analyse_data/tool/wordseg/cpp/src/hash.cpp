#include <iostream>
#include <string>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

struct string_hash  
{  
   size_t operator()(const string& str) const  
   {  
       return __stl_hash_string(str.c_str());  
   }  
};  
  
struct string_compare  
{  
    bool operator () (string const& str1, string const& str2)  
    {  
        return str1 == str2;  
    }  
};  


typedef hash_map<const string , int, string_hash, string_compare> Str_int_hash; 

int main()
{


  Str_int_hash months;
  
  months["january"] = 31;
  months["february"] = 28;
  months["march"] = 31;
  months["april"] = 30;
  months["may"] = 31;
  months["june"] = 30;
  months["july"] = 31;
  months["august"] = 31;
  months["september"] = 30;
  months["october"] = 31;
  months["november"] = 30;
  months["december"] = 31;
  
  cout << "september -> " << months["september"] << endl;
  cout << "april     -> " << months["april"] << endl;
  cout << "june      -> " << months["june"] << endl;
  cout << "november  -> " << months["november"] << endl;
}
