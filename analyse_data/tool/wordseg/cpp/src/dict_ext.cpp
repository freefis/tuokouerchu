/*
 * =====================================================================================
 *       Filename:  dict_ext.cpp
 *
 *    Description:  Extend dict.cpp fro mmseg
 *
 *        Version:  1.0
 *        Created:  2010/11/05 15时22分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wang.Shuo (free.wang), freefis@gmail.com
 *        Company:  tuokouerchu.com
 * =====================================================================================
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include "utils.h"
#include "dict_ext.h"


using namespace std;

namespace dict_ext
{
    Cache_words::Cache_words(const char *filename)
    {
        write_file_name = (char *)malloc(sizeof(char)*strlen(filename));
        write_file_name = filename;  
        has_filtered = 0;
    }

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  add_word
     *  Description:  push word into array,then will be write into cache file
     * =====================================================================================
     */
    void Cache_words::add_word(const char * word_text_char)
    {
        words_list.push_back(word_text_char);
    }


    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  write_file
     *  Description:  write append to cache
     *         Type:  Public
     * =====================================================================================
     */
    int Cache_words::write_file() 
    {
        if( !(this->has_filtered) ) 
            this->filter_with_only_chinese_words();

        if(words_list.empty())
            return 0;

        string write_content = utils::str_join(words_list,"\n");
        write_content += "\n";
        cout<<write_content<<endl;
        ofstream fp(write_file_name,ios_base::app);
        fp<<write_content;
        fp.close();
        return 1;
    }


    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  get_filter_words
     *  Description:  get words_list which after filtered
     * =====================================================================================
     */
    const char * Cache_words::get_iter_cache_word()
    {
        if( !(this->has_filtered) )  {
            this->filter_with_only_chinese_words();
            return this->get_iter_cache_word();
        }


        if(this->cache_word_iter!=this->words_list.end()) {
            const char * word = (char *)malloc(sizeof(char)*(*cache_word_iter).size());
            word =  (*cache_word_iter).c_str();
            this->cache_word_iter += 1;
            return word;
        }

    }		

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  clean
     *  Description:  flush cache file
     * =====================================================================================
     */
    const char * Cache_words::get_cache_words()
    {
        if( !(this->has_filtered) ) 
            this->filter_with_only_chinese_words();

        string stringResult = utils::str_join(words_list,"\n");
//        const char * charResult = (char *)malloc(sizeof(char)*stringResult.size());
        return stringResult.c_str();
    }




    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  clean
     *  Description:  flush cache file
     * =====================================================================================
     */
    int Cache_words::clean()
    {
        string write_content = "\0";
        ofstream fp(write_file_name,ios_base::binary);
        fp<<write_content;
        fp.close();
    }

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  Cache_words::filter_with_only_chinese_words
     *  Description:  remove the chars which is not Chinese
     *         Type:  Priavate
     * =====================================================================================
     */
    void Cache_words::filter_with_only_chinese_words()
    {
        vector <string> words_list_temp;
        vector <string>::iterator iter; 
        for(iter=words_list.begin();iter!=words_list.end();iter++) {

            const char * charWord = (*iter).c_str();
            int ascii = (int)(*charWord);

            // is charactor
            if( (ascii>=65&&ascii<=90) || (ascii>=97&&ascii<=122) ) 
                continue;

            // is int
            if( ascii>='0' && ascii<='9' ) 
                continue;

            // this can be commited  just for debug
            if(utils::include_chinese(*iter)==0)
                cout<<"what a fucking problem with the word not Chinese?"+*iter<<endl;

            // 2个字以上的次会被记录如cache
            if( (*iter).size()>=3*2 ) 
                words_list_temp.push_back(*iter); 

        }
        this->words_list = words_list_temp;
        this->has_filtered = 1;
        this->cache_word_iter = this->words_list.begin();
    }


    Cache_words::~Cache_words() {}


    /*-----------------------------------------------------------------------------
     *   this is class: Update_words
     *-----------------------------------------------------------------------------*/


    Update_words::Update_words(const char *filename)
    {
        // write_file_name : private variable
        write_file_name = (char *)malloc(sizeof(char)*strlen(filename));
        write_file_name = filename;

        FILE *fp = fopen(filename, "r");
        if (fp)
        {
            const int buf_len = 100;
            char buf[buf_len];
            char *ptr;
            vector <string> WordsList;
            init_str_hash WordsHash;
            int i=1;

            while(fgets(buf, buf_len, fp))
            {
                create_word_info * word_info = new create_word_info;

                /*
                 * buf      <- "1  sdfsd\n"
                 * textTemp <- "sdfsd"
                 */
                vector <string> splitStr = utils::split(buf," ");
                string _textTemp = splitStr[1];
                string textTemp = utils::remove(_textTemp,"\n");

                word_info->text  = textTemp;
                word_info->index = i;
                word_info->count = utils::str_to_int(splitStr[0]);

                // push into list
                WordsList.push_back(word_info->text);

                // push into hash
                WordsHash[word_info->text] = word_info;
                
                //
                i+=1;
            }

            fclose(fp);


            // private variables
            words_hash = WordsHash;
            words_list = WordsList;
        }
    }

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  Update_words::incr_words_count_from_cache
     *  Description:  1.get word from cache
     *                2.incr word count hash
     *         Type:  Public
     * =====================================================================================
     */
    void Update_words::incr_words_count_from_cache(const char * cache_filename)
    {
        vector <string> cache_words_list = this->_get_words(cache_filename);
        this->_incr_words_count(cache_words_list);
    }

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  Update_words::_get_words
     *  Description:  Open cache file with getting content as vector <string>
     *         Type:  Priavate
     * =====================================================================================
     */
    vector <string> Update_words::_get_words(const char * cache_filename)
    {
        if(cache_filename == write_file_name) {
            cout<<"You cannot get words from cache_filename"<<endl;
            exit(0);
        }

        vector <string> cache_words_list;

        FILE *fp = fopen(cache_filename, "r");
        if (fp) {
            const int buf_len = 100;
            char buf[buf_len];
            char *ptr;


            while(fgets(buf, buf_len, fp))
            {
                vector <string> splitStr = utils::split(buf," ");
                string _textTemp; 

                if(splitStr.size() == 1) {
                    _textTemp = splitStr[0];
                } else {
                    _textTemp = splitStr[1];
                }

                string textTemp = utils::remove(_textTemp,"\n");
                cache_words_list.push_back(textTemp);
            }
            fclose(fp);
        }
        return cache_words_list;
    }

    void Update_words::_incr_words_count(vector <string> cache_words_list)
    {
        vector <string>::iterator iter; 
        for(iter=cache_words_list.begin();iter!=cache_words_list.end();iter++)
            this->_incr_word_count(*iter); // word  type: string  not char
    }

    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  Update_words::_incr_word_count
     *  Description:  add word with count into Class Member:words_hash,words_list
     *         Type:  Priaate
     * =====================================================================================
     */
    void Update_words::_incr_word_count(string word_text)
    {
        // key does not exist
        if (words_hash.find(word_text) == words_hash.end()) {
            // add hash
            create_word_info * word_info = new create_word_info;
            words_hash[word_text] = word_info;
            (words_hash[word_text])->text = word_text;
            (words_hash[word_text])->count = 0;
            (words_hash[word_text])->index = 0;

            // add list
            words_list.push_back(word_text);
        }
        (words_hash[word_text])->count += 1;
    }

    int Update_words::write_file()
    {
        vector <string> content_list;

        vector <string>::iterator pText;
        for(pText=words_list.begin();pText!=words_list.end();pText++) {
            content_list.push_back(utils::int_to_str((words_hash[*pText])->count) + " " + *pText);
        }
        
        string write_content = utils::str_join(content_list,"\n");

        ofstream fp(write_file_name);
        //cout<<write_content<<endl;
        fp<<write_content;
        fp.close();

        return 1;
    }

    Update_words::~Update_words() {}    
}
