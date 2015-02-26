#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "sobel_custom.h"
using namespace cv;
// Main program to call various basic imaging filters
int main( int argc, char **argv)
{
   std::cout<<"code entered"<<std::endl;
   //waitKey();
   Mat   image = imread( argv[1], CV_LOAD_IMAGE_COLOR );
   
   namedWindow( "Original", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED );
   imshow( "Original", image );
   
   // Sobel example from http://docs.opencv.org/doc/user_guide/ug_mat.html#visualizing-images
   sobel_custom(image);

   // median filter

   // canny

   // hough transform

   // Linesegment detector

   // circle detector
   std::cout<<"display done"<<std::endl;
   while ( waitKey( 33 ) != 27 )
      ;
      
   return 0;
}