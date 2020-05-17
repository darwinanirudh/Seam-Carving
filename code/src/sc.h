#ifndef SEAMCARVINGCOMP665156
#define SEAMCARVINGCOMP665156

#include <opencv2/opencv.hpp>


cv::Mat contructEnergyMatrix(cv::Mat inImage);

cv::Mat contructEnergyMatrixHorizontal(cv::Mat inImage);

void remove_vertical(cv::Mat &inImage, int col);

void remove_horizontal(cv::Mat &inImage, int row);


#endif
