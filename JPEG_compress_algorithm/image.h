#ifndef IMAGE_H
#define IMAGE_H
#include <vector>
#include <cmath>
#include <fstream>


class JPEG {
    private:
    std::vector<std::vector<int>> DCTCoefficients;
    std::vector<std::vector<int>> quantizedCoefficients;
    std::vector<std::pair<int, int>> encodedAC;

    void convertRGBtoYCbCr(std::vector<std::vector<int>>& img);
    void DCT(const std::vector<std::vector<int>>& block, std::vector<std::vector<int>>& dctMatrix);
    void quantize(std::vector<std::vector<int>>& block);
    std::vector<int> zigzagOrder(const std::vector<std::vector<int>>& block);
    std::vector<std::pair<int, int>> encodeAC(const std::vector<int>& zigzagCoeffs);
    void saveCompressedImage(const std::string& filename, const std::vector<std::pair<int, int>>& encodedAC);
    std::vector<std::pair<int, int>> getEncodedAC() const;
    void JPEGdata(std::vector<std::vector<int>>& img, std::vector<std::pair<int, int>>& encodedAC);



    std::vector<int> decodeAC(const std::vector<std::pair<int, int>>& encodedAC);
    std::vector<std::vector<int>> decompressZigzag(const std::vector<int>& zigzag, int blockSize);
    void dequantize(std::vector<std::vector<int>>& block);
    void IDCT(const std::vector<std::vector<int>>& dctMatrix, std::vector<std::vector<int>>& block);
    void convertYCbCrtoRGB(std::vector<std::vector<int>>& img);
    std::vector<std::pair<int, int>> loadEncodedACFromFile(const std::string& filename);




    public:
    JPEG(std::vector<std::vector<int>>& img, std::string& filename);
    std::vector<std::vector<int>> decompressImage(const std::string& compressedFileName, int blockSize = 8);
};

#endif