#include "median_custom.h"

void sort_array(uchar * inBuff,int size)
{

	int flag = 1;    // set flag to 1 to start first pass
	int temp;             // holding variable
	for(int i = 1; (i <= size) && flag; i++){
	   flag = 0;
	   for (int j=0; j < (size -1); j++){
	       if (inBuff[j+1] > inBuff[j]){      // ascending order simply changes to <
	          temp = inBuff[j];             // swap elements
	          inBuff[j] = inBuff[j+1];
	          inBuff[j+1] = temp;
	          flag = 1;               // indicates that a swap occurred.
	       }
	   }
	}
}

void median_buffer(uchar* inBuff, uchar* outBuff,
	               int height, int width, int channels,
	               int kernelSize)
{
	int offset = kernelSize/2;
	uchar * sortBuff;
	int step = width * channels;
	sortBuff = new uchar[kernelSize * kernelSize];
	for (int row = offset; row <(height - offset); row++){
		for(int col = offset; col < (width-offset); col++){
			for (int ch = 0; ch < channels; ch++){
				int count = 0;
				for(int r = -offset; r <= offset; r++){
					for (int c = -offset; c <= offset; c++){
						sortBuff[count] = inBuff[(col+c)*channels + (row+r) * step + ch];
						count++; 
					}
				}
				sort_array(sortBuff,kernelSize * kernelSize);
				outBuff[(col* channels)+ (row * step) + ch] = sortBuff[(kernelSize * kernelSize )/2];
			}
		}
	}


}
void median_custom(cv::Mat & image)
{
  cv::Mat result;
  image.copyTo(result);
  uchar* inBuff = (uchar*) image.data;
  uchar* outBuff = (uchar*) result.data;
  median_buffer(inBuff, outBuff, image.rows, image.cols, image.channels(), 3);
  cv::namedWindow("median");
  cv::imshow("median", result);  
}