#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>


namespace utils
{
    std::vector <std::string> split(const std::string & strValue, const std::string & separator);
    std::string remove(const std::string & strValue, const std::string & separator);
    std::string str_join(std::vector <std::string>  strlist, const std::string & separator);

    std::string int_to_str(int integer);
    int str_to_int(std::string str);
    int include_chinese(std::string word);
    std::vector <std::string> readlines(char * filename);
}



#endif /* _UTILS_H_ */
