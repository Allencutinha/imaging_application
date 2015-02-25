#include "sobel_custom.h"

using namespace cv;


int sobel_custom(Mat &image)
{
   std::cout<<"code entered"<<std::endl;
   //waitKey();
   //Mat   image = imread( "test.jpg", CV_LOAD_IMAGE_COLOR );
   
   namedWindow( "custom", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED );
   
   uchar * buff = image.data;
   for (int i=0; i < 500; i++){
      for(int j = 0; j < 500; j++){
         buff[i * image.cols * image.channels()+ j +0] = 0;
      }   
   }
   imshow( "custom", image );
  /* 
   // Sobel example from http://docs.opencv.org/doc/user_guide/ug_mat.html#visualizing-images
   Mat gray;
   
   cvtColor( image, gray, CV_BGR2GRAY );
   
   Mat sobelx;
   
   Sobel( gray, sobelx, CV_32F, 1, 0 );
   
   double minVal = 0.0;
   double maxVal = 0.0;
   
   minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
   
   Mat draw;
   
   sobelx.convertTo( draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal) );
   
   namedWindow( "custom", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED );
   imshow( "custom", draw );
   std::cout<<"display done"<<std::endl;
   while ( waitKey( 33 ) != 27 )
      ;
  */    
   return 0;
}