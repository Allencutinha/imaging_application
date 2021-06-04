#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

typedef struct{
    int rho;
    int theta;
}sLine;

void hough_buffer(uchar* inBuff, int height, int width, 
	sLine * lines, int &numLines, int minLinePixels);
int hough_custom(cv::Mat &image);