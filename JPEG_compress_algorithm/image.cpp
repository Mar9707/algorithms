#include <iostream>
#include "image.h"
#include "decompress.cpp"



void JPEG::convertRGBtoYCbCr(std::vector<std::vector<int>>& img){
    for (auto& row : img) {
        for (auto& pixel : row) {
            int R = (pixel >> 16) & 0xFF;
            int G = (pixel >> 8) & 0xFF;
            int B = pixel & 0xFF;

            int Y = (int)(0.299 * R + 0.587 * G + 0.114 * B);
            int Cb = (int)(-0.1687 * R - 0.3313 * G + 0.5 * B + 128);
            int Cr = (int)(0.5 * R - 0.4187 * G - 0.0813 * B + 128);

            pixel = (Y << 16) | (Cb << 8) | Cr;
          }
      }
}
   

void JPEG::DCT(const std::vector<std::vector<int>>& block, std::vector<std::vector<int>>& dctMatrix) {
   int N = 8;
   double coefU, coefV, sum;

   for (int u = 0; u < N; ++u) {
      for (int v = 0; v < N; ++v) {
         sum = 0.0;                                                     
         for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
               if (i < block.size() && j < block[i].size()) { 
                  coefU = (u == 0) ? 1.0 / sqrt(2) : 1.0;
                  coefV = (v == 0) ? 1.0 / sqrt(2) : 1.0;
                  sum += coefU * coefV * block[i][j] * 
                     cos((2 * i + 1) * u * M_PI / (2.0 * N)) * 
                     cos((2 * j + 1) * v * M_PI / (2.0 * N));
               }
            }
         }
         dctMatrix[u][v] = round(0.25 * sum);
      }
   }

}





void JPEG::quantize(std::vector<std::vector<int>>& block) {
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
            block[i][j] = round(block[i][j] / (double)quantizationMatrix[i][j]);
          }
        }
    }
}


std::vector<int> JPEG::zigzagOrder(const std::vector<std::vector<int>>& block) {
    std::vector<int> zigzag;
    int N = block.size();

    for (int sum = 0; sum <= 2 * (N - 1); ++sum) {
        int start = std::max(0, sum - (N - 1));
        int end = std::min(N - 1, sum);

        if (sum % 2 == 0) {
            for (int i = start; i <= end; ++i) {
                int j = sum - i;
                if (i < N && j < N) {
                    zigzag.push_back(block[i][j]);
                }
            }
        } else {
            for (int i = end; i >= start; --i) {
                int j = sum - i;
                if (i < N && j < N) {
                    zigzag.push_back(block[i][j]);
                }
            }
        }
    }

    return zigzag;
}


std::vector<std::pair<int, int>> JPEG::encodeAC(const std::vector<int>& zigzagCoeffs) {
    std::vector<std::pair<int, int>> encodedCoeffs;

    int zeroCount = 0;

    for (int i = 0; i < zigzagCoeffs.size(); ++i) {
        int coeff = zigzagCoeffs[i];

        if (coeff == 0) {
            zeroCount++;
        } else {
            encodedCoeffs.push_back({zeroCount, coeff});
            zeroCount = 0;
        }
    }

    encodedCoeffs.push_back({0, 0});

    return encodedCoeffs;
}


void JPEG::saveCompressedImage(const std::string& filename, const std::vector<std::pair<int, int>>& encodedAC) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to create or open file " << filename << std::endl;
        return;
    }

    for (const auto& pair : encodedAC) {
        file << pair.first << " " << pair.second << std::endl;
    }

    file.close();

    std::cout << "Compressed image saved as: " << filename << std::endl;
}


void JPEG::JPEGdata(std::vector<std::vector<int>>& img, std::vector<std::pair<int, int>>& encodedAC){
   std::vector<std::vector<int>> imgYCbCr = img;
   convertRGBtoYCbCr(imgYCbCr);

   std::vector<std::vector<int>> dctMatrix(8, std::vector<int>(8));
   DCT(imgYCbCr, dctMatrix);

   quantize(dctMatrix);

   std::vector<int> zigzag = zigzagOrder(dctMatrix);

   encodedAC = encodeAC(zigzag);

}



JPEG::JPEG(std::vector<std::vector<int>>& img, std::string& filename) : DCTCoefficients(img.size()), quantizedCoefficients(img.size()) {
   JPEGdata(img, encodedAC);
   saveCompressedImage(filename, getEncodedAC());

}  


std::vector<std::pair<int, int>> JPEG::getEncodedAC() const {
    return encodedAC;
}



/*ImageSize readJpegImageSize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return {0, 0};
    }

    unsigned short segmentSize;
    unsigned char marker;
    unsigned char segment;

    while (file.read(reinterpret_cast<char*>(&marker), sizeof(marker))) {
        std::cout << "Marker: " << std::hex << +marker << std::endl;

        if (marker != 0xFF) {
            continue;
        }

        file.read(reinterpret_cast<char*>(&segment), sizeof(segment));
        std::cout << "Segment: " << std::hex << +segment << std::endl;

        if (segment == 0xC0) {
            file.read(reinterpret_cast<char*>(&segmentSize), sizeof(segmentSize));
            segmentSize = (segmentSize << 8) | (segmentSize >> 8); 
            int height, width;
            file.read(reinterpret_cast<char*>(&height), sizeof(height));
            file.read(reinterpret_cast<char*>(&width), sizeof(width));
            return {width, height};
        } else {
            file.read(reinterpret_cast<char*>(&segmentSize), sizeof(segmentSize));
            segmentSize = (segmentSize << 8) | (segmentSize >> 8); 
            std::cout << "Segment size: " << std::hex << segmentSize << std::endl;
            file.seekg(segmentSize - 2, std::ios_base::cur);
        }
    }

    std::cerr << "Error: SOF0 segment not found" << std::endl;
    return {0, 0};
}
*/
     


std::vector<std::vector<int>> read (const std::string& filename){
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::invalid_argument("Error");
    }

    std::vector<std::vector<int>> img;
    int width = 2048;
    int height = 1266;

     if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Invalid image dimensions");
    }

     img.resize(height, std::vector<int>(width * 3));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width * 3; ++x) {
            unsigned char pixelValue;
            file.read(reinterpret_cast<char*>(&pixelValue), sizeof(unsigned char));
            img[y][x] = pixelValue;

        }
    }

    file.close();

    return img;
}



int main() {
    std::string image;
    std::cout << "Enter the image filename: ";
    std::cin >> image;
    std::string compressedImageFilename = "compressed_" + image;

    try {
        std::vector<std::vector<int>> img = read(image);
        std::cout << "Image read successfully!" << std::endl;

        JPEG imageJpeg(img, compressedImageFilename);
        std::cout << "Image compressed successfully!" << std::endl;

        std::vector<std::vector<int>> decompressedImg = imageJpeg.decompressImage(compressedImageFilename);
        std::cout << "Image decompressed successfully!" << std::endl;

        std::string decompressedFilename = "decompressed_" + image ;
        saveImageToJPEG(decompressedFilename, decompressedImg);
        std::cout << "Decompressed image saved as " << decompressedFilename << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
