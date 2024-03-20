/*
 * file_io.h
 *
 *  Created on: Dec 7, 2018
 *      Author: gnohead
 */

#ifndef FILE_IO_H_
#define FILE_IO_H_

#include "soslab_typedef.h"
#include <fstream>
#include <sstream>
#include <iostream>


namespace SOSLAB
{
    namespace FILE_IO
    {
        /*
         * 파일의 크기를 반환한다.
         */
        std::size_t SOSLAB_EXPORTS get_file_size(const char* name);

        /*
         * 파일의 내용을 임의의 크기 단위로 나눠서 vector에 저장한다.
         *  - fill_ff : 마지막 조각을 0xFF로 채워넣을지 여부 결정
         */
        std::vector<std::vector<uint8_t> > SOSLAB_EXPORTS read_binary_file(const char* name, const std::size_t step_bytes, const bool fill_ff);

        /*
         * 임의의 데이터를 binary로 저장한다.
         *  - 기존에 파일이 있으면 지우고 다시 만듦
         */
        int SOSLAB_EXPORTS writeBinaryFile(const char* name, const uint8_t* binData, const std::size_t size, const char option);
        
        /*
         * 한 라인씩 ASCII 데이터로 얽어서 벡터로 출력한다.
         *  NOTE: 큰 용량의 파일을 읽지 않도록 주의할 것
         */
        std::vector<std::string> SOSLAB_EXPORTS read_ascii_file(const char* name, const std::size_t r_cnt = 0);

        /*
		 * 입력 문자열을 파일로 저장한다.
		 */
        bool SOSLAB_EXPORTS write_ascii_file(const char* name, const std::string& in_str, const bool is_append = false);

        /*
         * 파일 존재 여부를 확인.
         */
        bool SOSLAB_EXPORTS check_file_exists(const std::string& filename);

    }   /* namespace FILEIO */
}   /* namespace SOSLAB */

#endif /* FILE_IO_H_ */
