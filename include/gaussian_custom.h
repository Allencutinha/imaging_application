#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

void gaussian_custom(cv::Mat &image);
int test_filter();

void gaussian_buffer_int(int* inBuff, int* outBuff,
                     int KernelSize, double sigma,
                     int height, int width, int channels);