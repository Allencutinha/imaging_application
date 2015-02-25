#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "sobel_custom.h"
using namespace cv;

int main( int argc, char **argv)
{
   std::cout<<"code entered"<<std::endl;
   //waitKey();
   Mat   image = imread( argv[1], CV_LOAD_IMAGE_COLOR );
   
   namedWindow( "Original", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED );
   imshow( "Original", image );
   
   // Sobel example from http://docs.opencv.org/doc/user_guide/ug_mat.html#visualizing-images
   Mat gray;
   sobel_custom(image);
   cvtColor( image, gray, CV_BGR2GRAY );
   
   Mat sobelx;


   
   Sobel( gray, sobelx, CV_32F, 1, 0 );
   
   double minVal = 0.0;
   double maxVal = 0.0;
   
   minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
   
   Mat draw;
   
   sobelx.convertTo( draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal) );
   
   namedWindow( "Sobel", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED );
   imshow( "Sobel", draw );
   std::cout<<"display done"<<std::endl;
   while ( waitKey( 33 ) != 27 )
      ;
      
   return 0;
}