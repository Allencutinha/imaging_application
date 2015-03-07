#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

int draw_custom(cv::Mat &image);

void draw_rectangle(uchar* inBuff, int height, int width,
               int x, int y, int rectHeight, int rectWidth, float theta = 0);