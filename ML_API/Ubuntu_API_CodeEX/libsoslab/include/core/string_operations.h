/*
 * string_operations.h
 *
 *  Created on: Dec 7, 2018
 *      Author: gnohead
 */

#ifndef INCLUDE_STRING_OPERATIONS_H_
#define INCLUDE_STRING_OPERATIONS_H_

#include "soslab_typedef.h"

#include <string>
#include <vector>

namespace SOSLAB
{
    namespace STR_OP
    {
        /**
         * @brief String spliter
         * @param str [in]
         * @param delimeter [in]
         * @return splitted string list
         */
        SOSLAB_EXPORTS std::vector<std::string> str_split(std::string str, char delimeter);

        /**
         * @brief Remove the spaces character in string
         * @param str [in]
         * @return space character removed string
         */
        SOSLAB_EXPORTS std::string str_remove_spaces(std::string str);

        /**
         * @brief remove after target_str's first character
         * @param str [in]
         * @param target_str [in]
         * @return string of before target_str
         */
        SOSLAB_EXPORTS std::string str_strip(std::string str, std::string target_str);

        /**
         * @brief remove before target_str's last character
         * @param str [in]
         * @param target_str [in]
         * @return string of after target_str
         */
        SOSLAB_EXPORTS std::string str_strip_front(std::string str, std::string target_str);


        /**
         * @brief string to number
         */
        template<typename T> SOSLAB_EXPORTS T str_to_num(std::string str);

    }   /* namespace STR_OP */

}   /* namespace SOSLAB */



#endif /* INCLUDE_STRING_OPERATIONS_H_ */
