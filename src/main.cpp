#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "sobel_custom.h"
#include "gaussian_custom.h"
#include "median_custom.h"
#include "canny_custom.h"
#include "hough_custom.h"
#include "draw_custom.h"
#include "hcd_custom.h"
using namespace cv;

void displayErrorLog(){
   std::cout<<"_______________________________________________________"<<std::endl;
   std::cout<<"\tImaging Library needs two inputs"<<std::endl;
   std::cout<<"\tFormat needed: \n\t imaging image_filename algo"<<std::endl;
   std::cout<<"\tThe following algorithms are supported"<<std::endl;
   std::cout<<"\t\tsobel"<<std::endl;
   std::cout<<"\t\tgaussian"<<std::endl;
   std::cout<<"\t\tmedian"<<std::endl;
   std::cout<<"\t\tcanny"<<std::endl;
   std::cout<<"\t\though"<<std::endl;
   std::cout<<"\t\tlsd"<<std::endl;
   std::cout<<"\t\tcircle_det"<<std::endl;
   std::cout<<"\t\th_corner_det"<<std::endl;
   std::cout<<"\t\tcamera_calib"<<std::endl;
   std::cout<<"\t\tdraw"<<std::endl;
   std::cout<<"_______________________________________________________"<<std::endl;
}
// Main program to call various basic imaging filters
int main( int argc, char **argv)
{
   if (argv[2] == NULL || argv[1] == NULL){
      displayErrorLog();
      return 0;
   }
   std::cout<<"code entered  with arguments : "<<argv[1]<<"\t"<<argv[2]<<std::endl;
   // read the input image
   Mat   image = imread( argv[1], CV_LOAD_IMAGE_COLOR );
   

   namedWindow( "Original", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED );
   imshow( "Original", image );

   std::string input (argv[2]);
  // case "sobel":
   if (input == "sobel"){
      // Sobel example from http://docs.opencv.org/doc/user_guide/ug_mat.html#visualizing-images
      sobel_custom(image);
   }
   //case "gaussian":
   else if (input == "gaussian"){  
      // Gaussian filter
      gaussian_custom(image);
   }
   //case "median":
   else if (input == "median"){
      // median filter
      median_custom(image);
   }
   //case "canny":
   else if (input == "canny"){
      // canny
      canny_custom(image);
   }
   //case "hough":
   else if (input == "hough"){
      // hough transform
      hough_custom(image);
   }
   //case "lsd":
   else if (input == "lsd"){
      // Linesegment detector
      std::cout<<"not yet implemented"<<std::endl;
   }
   //case "circle_det":
   else if (input == "cicrlce_det"){ 
      // circle detector
      std::cout<<"not yet implemented"<<std::endl;
   }
   else if(input == "h_corner_det"){
      // corner detecttion
      harris_corner_det(image);
   }
   else if (input == "camera_calib"){
      // camera calibration
      std::cout<<"not yet implemented"<<std::endl;
   }
   //case "draw"
    else if (input == "draw"){
      // circle detector
      draw_custom(image);
   }
   //default:
   else{
      std::cout<<" selected algorithm not available!!!"<<std::endl;
   }
   
   std::cout<<"display done"<<std::endl;
   while ( waitKey( 33 ) != 27 )
      ;
      
   return 0;
}
