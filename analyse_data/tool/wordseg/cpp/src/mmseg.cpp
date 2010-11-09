/**
 * A C interface to mmseg-cpp. Will be compiled to a
 * shared library.
 */

#include "token.h"
#include "dict.h"
#include "dict_ext.h"
#include "algor.h"
#include  <iostream>

#if defined(_MSC_VER) // Microsoft compiler
#    define DLLEXPORT __declspec(dllexport)
#elif defined(__GNUC__) // GNU compiler
#    define DLLEXPORT
#else
#    error Unknown compiler, donot know how to process dllexport
#endif


extern "C" {
    
    struct Token
    {
        const char *text;
        int offset;
        int length;
    };

    /*
     * Load a character dictionary.
     */
    DLLEXPORT
    int mmseg_load_chars(const char *path)
    {
        if (rmmseg::dict::load_chars(path))
            return 1;
        return 0;
    }

    /*
     * Load a word dictionary.
     */ 
    DLLEXPORT
    int mmseg_load_words(const char *path)
    {
        if (rmmseg::dict::load_words(path))
            return 1;
        return 0;
    }
    
    /*
     * Add a word to the in-memory dictionary.
     *
     * - word is a String.
     * - length is number of characters (not number of bytes) of the
     *   word to be added.
     * - freq is the frequency of the word. This is only used when
     *   it is a one-character word.
     */
    DLLEXPORT
    void mmseg_dic_add(const char *word, int len, int freq)
    {
        rmmseg::Word *w = rmmseg::make_word(word, len, freq, strlen(word));
        rmmseg::dict::add(w);
    }

    /*
     * Create an Algorithm object.
     *
     * - text is the text to process. It is OK to contain NUL
     *   character.
     * - len is the length (number of bytes) of the text.
     */
    DLLEXPORT
    rmmseg::Algorithm *mmseg_algor_create(const char *text, int len)
    {
        return new rmmseg::Algorithm(text, len);
    }


    DLLEXPORT
    void mmseg_algor_destroy(rmmseg::Algorithm *algor)
    {
        delete algor;
    }

    DLLEXPORT
    Token mmseg_next_token(rmmseg::Algorithm *algor)
    {
        rmmseg::Token rtk = algor->next_token();
        Token tk;
        tk.text = rtk.text;
        tk.offset = rtk.text - algor->get_text();
        tk.length = rtk.length;
        return tk;
    }


    /*
     * Create an Update_words objct
     */
    DLLEXPORT
    dict_ext::Update_words *update_words_init(const char *path)
    {
        return new dict_ext::Update_words(path);
    }

    DLLEXPORT
    void update_words_incr_words_count_from_cache(dict_ext::Update_words * obj,const char *cache_filename)
    {
        obj->incr_words_count_from_cache(cache_filename);
    }


    DLLEXPORT
    int update_words_write_file(dict_ext::Update_words * obj)
    {
        if (obj->write_file())
            return 1; 
        return 0;
    }

    DLLEXPORT
    void update_words_destroy(dict_ext::Update_words * obj)
    {
        delete obj; 
    }

    /*
     * Create an Cache_words objct
     */
    DLLEXPORT
    dict_ext::Cache_words *cache_words_init(const char *path)
    {
        return new dict_ext::Cache_words(path);
    }

    DLLEXPORT
    int cache_words_write_file(dict_ext::Cache_words * obj)
    {
        if (obj->write_file())
            return 1; 
        return 0;
    }

    DLLEXPORT
    void cache_words_add_word(dict_ext::Cache_words * obj,const char *word)
    {
        obj->add_word(word);
    }

    DLLEXPORT
    const char * cache_words_get_iter_cache_word(dict_ext::Cache_words * obj)
    {
        return obj->get_iter_cache_word();
    }

    DLLEXPORT
    const char * cache_words_get_cache_words(dict_ext::Cache_words * obj)
    {
        return obj->get_cache_words();
    }

    DLLEXPORT
    void cache_words_clean(dict_ext::Cache_words * obj)
    {
        obj->clean();
    }

    DLLEXPORT
    void cache_words_destroy(dict_ext::Cache_words * obj)
    {
        delete obj; 
    }

}
