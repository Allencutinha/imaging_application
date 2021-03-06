#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

void canny_custom(cv::Mat &image);
void detectCannyEdges(uchar * inBuff, uchar* outBuff, uchar * intBuff, int height, int width);