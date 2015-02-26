#include "sobel_custom.h"

using namespace cv;

int sobel_x[3][3] = {-1,0,1,-2, 0,2, -1, 0,1};
int sobel_y[3][3] = {-1,-2,-1,0,0,0,1,2,1};
// Sobel edge detection using only image bugger independent of opencv
void sobel_buffer(uchar* srcBuff, uchar * dstBuff, int width, int height)
{
  for (int row=1; row < height; row++){
     for(int col = 1; col < width; col++){
      int tempx = 0;
      int tempy = 0;
       for (int r = 0; r < 3; r++){
         for (int c =0; c < 3; c++){
             tempx += srcBuff[(row + r - 1) * width+ (col + c -1)] * sobel_x[r][c];
             tempy += srcBuff[(row + r - 1) * width+ (col + c -1)] * sobel_y[r][c];
             
         }
       }
       dstBuff[row * width + col] = (sqrt(tempx * tempx+ tempy * tempy)*255)/1884;;
     }   
   }
}

int sobel_custom(Mat &image)
{
   std::cout<<"sobel code entered"<<std::endl;
   
   namedWindow( "Sobel", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED );
   Mat gray,gray2;
   if (image.channels() == 3){
       cvtColor(image, gray, CV_BGR2GRAY);
       gray.copyTo(gray2);
   }else{
      image.copyTo(gray);
      image.copyTo(gray2);
   }
   uchar * buff2 = (uchar*)gray2.data;
   uchar * buff = (uchar*)gray.data;
   sobel_buffer(buff, buff2, gray.cols, gray.rows);
 
   imshow( "sobel", gray2);
   return 0;
}