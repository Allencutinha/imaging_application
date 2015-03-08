#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

int draw_custom(cv::Mat &image);

void draw_rectangle(uchar* inBuff, int height, int width,
               int x, int y, int rectHeight, int rectWidth, float theta = 0);


void draw_line(uchar * inBuff, int height, int width,
	           int x0, int y0, int x1, int y1);