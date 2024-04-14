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
    void JPEGdata(std::vector<std::vector<int>>& img, std::vector<std::pair<int, int>>& encodedAC);


    public:
    JPEG(std::vector<std::vector<int>>& img); 
};

#endif