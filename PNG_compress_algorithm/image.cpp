#include "image.h"


PNG::Token PNG::findLongestMatch(const unsigned char* input, int pos, int input_len){
     Token token;
        token.length = 0;
        token.distance = 0;

        int max_distance = std::min(pos, 32768);

        for (int d = 1; d <= max_distance; ++d) {
            int len = 0;
            while (pos + len < input_len && input[pos + len] == input[pos - d + len] && len < MAX_MATCH_LEN) {
                ++len;
            }
            if (len > token.length) {
                token.length = len;
                token.distance = d;
            }
        }

        return token;
    }



std::vector<unsigned char> PNG::deflate(const std::string& file_path){
     std::vector<unsigned char> compressed_data;

        std::ifstream file(file_path, std::ios::binary);
        if (!file) {
            std::cerr << "Error opening file\n";
            return compressed_data;
        }

        std::vector<unsigned char> input_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        int pos = 0;
        while (pos < input_data.size()) {
            Token token = findLongestMatch(&input_data[0], pos, input_data.size());

            if (token.length >= 3) {
                compressed_data.push_back(0xFF);
                compressed_data.push_back((token.distance >> 8) & 0xFF);
                compressed_data.push_back(token.distance & 0xFF);

                compressed_data.push_back((token.length - 3) & 0xFF);

                pos += token.length;
            } else {
                compressed_data.push_back(input_data[pos]);
                ++pos;
            }
        }

    return compressed_data;
}