#include <iostream>
#include "image.h"


std::vector<int> JPEG::decodeAC(const std::vector<std::pair<int, int>>& encodedAC) {
    std::vector<int> zigzag;

    for (const auto& pair : encodedAC) {
        int zeroCount = pair.first;
        int coeff = pair.second;

        if (zeroCount == 0 && coeff == 0) {
            break;
        }

        for (int i = 0; i < zeroCount; ++i) {
            zigzag.push_back(0);
        }

        zigzag.push_back(coeff);
    }

    return zigzag;
}


std::vector<std::vector<int>> JPEG::decompressZigzag(const std::vector<int>& zigzag, int blockSize) {
    std::vector<std::vector<int>> block(blockSize, std::vector<int>(blockSize));
    int N = blockSize;
    int index = 0;

    for (int sum = 0; sum <= 2 * (N - 1); ++sum) {
        int start = std::max(0, sum - (N - 1));
        int end = std::min(N - 1, sum);

        if (sum % 2 == 0) {
            for (int i = start; i <= end; ++i) {
                int j = sum - i;
                if (i < N && j < N) {
                    block[i][j] = zigzag[index++];
                }
            }
        } else {
            for (int i = end; i >= start; --i) {
                int j = sum - i;
                if (i < N && j < N) {
                    block[i][j] = zigzag[index++];
                }
            }
        }
    }

    return block;
}


void JPEG::dequantize(std::vector<std::vector<int>>& block) {
    int quantizationMatrix[8][8] = {
        {16, 11, 10, 16, 24, 40, 51, 61},
        {12, 12, 14, 19, 26, 58, 60, 55},
        {14, 13, 16, 24, 40, 57, 69, 56},
        {14, 17, 22, 29, 51, 87, 80, 62},
        {18, 22, 37, 56, 68, 109, 103, 77},
        {24, 35, 55, 64, 81, 104, 113, 92},
        {49, 64, 78, 87, 103, 121, 120, 101},
        {72, 92, 95, 98, 112, 100, 103, 99}
    };

    int height = block.size();
    int width = (height > 0) ? block[0].size() : 0;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i < height && j < width) {
                block[i][j] *= quantizationMatrix[i][j];
            }
        }
    }
}


void JPEG::IDCT(const std::vector<std::vector<int>>& dctMatrix, std::vector<std::vector<int>>& block) {
    int N = 8;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;

            for (int u = 0; u < N; ++u) {
                for (int v = 0; v < N; ++v) {
                    double coefU = (u == 0) ? 1.0 / sqrt(2) : 1.0;
                    double coefV = (v == 0) ? 1.0 / sqrt(2) : 1.0;
                    sum += coefU * coefV * dctMatrix[u][v] *
                           cos((2 * i + 1) * u * M_PI / (2.0 * N)) *
                           cos((2 * j + 1) * v * M_PI / (2.0 * N));
                }
            }

            block[i][j] = round(sum * 0.25);
        }
    }
}


void JPEG::convertYCbCrtoRGB(std::vector<std::vector<int>>& img) {
    for (auto& row : img) {
        for (auto& pixel : row) {
            int Y = (pixel >> 16) & 0xFF;
            int Cb = (pixel >> 8) & 0xFF;
            int Cr = pixel & 0xFF;

            int R = Y + 1.402 * (Cr - 128);
            int G = Y - 0.34414 * (Cb - 128) - 0.71414 * (Cr - 128);
            int B = Y + 1.772 * (Cb - 128);

            R = std::min(255, std::max(0, R));
            G = std::min(255, std::max(0, G));
            B = std::min(255, std::max(0, B));

            pixel = (R << 16) | (G << 8) | B;
        }
    }
}


void saveImageToJPEG(const std::string& filename, const std::vector<std::vector<int>>& img) {
       std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to create or open file " << filename << std::endl;
        return;
    }

    int width = 2048;
    int height = 1266;
    file << width << " " << height << std::endl;

      for (const auto& row : img) {
        for (const auto& pixel : row) {
            file << pixel << " ";
        }
        file << std::endl;
    }
  

    std::cout << "Image saved as JPEG: " << filename << std::endl;
}


std::vector<std::pair<int, int>> JPEG::loadEncodedACFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file for reading: " + filename);
    }

    std::vector<std::pair<int, int>> encodedAC;
    int zeroCount, coeff;

    while (file >> zeroCount >> coeff) {
        encodedAC.push_back({zeroCount, coeff});
    }

    file.close();

    return encodedAC;
}



std::vector<std::vector<int>> JPEG::decompressImage(const std::string& compressedFileName, int blockSize) {
    std::vector<std::pair<int, int>> encodedAC = loadEncodedACFromFile(compressedFileName);
    std::vector<int> decodedAC = decodeAC(encodedAC);
    std::vector<std::vector<int>> block = decompressZigzag(decodedAC, blockSize);
    dequantize(block);
    std::vector<std::vector<int>> idctMatrix(blockSize, std::vector<int>(blockSize));
    IDCT(block, idctMatrix);

    std::vector<std::vector<int>> img(idctMatrix);
    convertYCbCrtoRGB(img);
    
    return img;
}


        

