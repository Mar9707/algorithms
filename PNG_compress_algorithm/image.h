#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>



class PNG {
    private:
    const int MAX_MATCH_LEN = 258;
    struct Token {
        int length;
        int distance;
    };


    Token findLongestMatch(const unsigned char* input, int pos, int input_len);


    public:
    std::vector<unsigned char> deflate(const std::string& file_path);
};


#endif