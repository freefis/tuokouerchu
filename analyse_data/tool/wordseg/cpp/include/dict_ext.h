#ifndef _DICT_EXT_H_
#define _DICT_EXT_H_

#include <vector>
#include <iostream>
#include <string>
#include <ext/hash_map>

using namespace std;
using namespace __gnu_cxx;

// create data type
struct Word_info
{
    int index;
    int count;
    std::string text;
};
typedef struct Word_info create_word_info;

// create hash type
struct string_hash  
{  
   size_t operator()(const string& str) const  
   {  
       return __stl_hash_string(str.c_str());  
   }  
};  
struct string_compare  
{  
    bool operator()(string const& str1, string const& str2)  
    {  
        return str1 == str2;  
    }  
};  
typedef hash_map<const string , create_word_info *, string_hash, string_compare> init_str_hash; 


// declare class
namespace dict_ext
{
    class Cache_words
    {
        public:
            Cache_words(const char * filename);
            ~Cache_words();
            void add_word(const char * word_text_char);
            int write_file();
            int clean();
            const char * get_iter_cache_word();
            const char * get_cache_words();
        private:
            std::vector <std::string> words_list;
            const char * write_file_name;
            void filter_with_only_chinese_words();
            int has_filtered;
            std::vector <std::string>::iterator cache_word_iter;
    };

    class Update_words
    {
        public:
            Update_words(const char * filename);
            ~Update_words();
            int write_file();
            void incr_words_count_from_cache(const char * cache_filename);
        private:
            // variables
            std::vector <std::string> words_list;
            init_str_hash words_hash;
            const char * write_file_name;
            // functions 
            void _incr_word_count(std::string word_text_char);
            void _incr_words_count(std::vector <std::string> cache_words_list);
            std::vector <std::string> _get_words(const char * cache_filename);
    };
}




#endif /* _DICT_EXT_H_ */
