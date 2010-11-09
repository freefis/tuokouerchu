#include <iostream>
#include <cstring>
#include "dict_ext.h"
#include "utils.h"

using namespace std;

int main()
{
    const char *f = "test";
    dict_ext::Cache_words * dict_obj = new dict_ext::Cache_words(f);
    dict_obj->add_word("你好");
    dict_obj->add_word("吃饭d");
    const char * s = dict_obj->get_cache_words();
    cout<<strlen(s)<<endl;


    /*
    const char *m = "dict";
    dict_ext::Update_words * obj = new dict_ext::Update_words(m);
    obj->get_words(f);
    obj->incr_words_count();
    obj->write_file();
  */
}
