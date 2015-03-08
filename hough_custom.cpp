#include "hough_custom.h"
#include "canny_custom.h"

#include "draw_custom.h"

#define THETA_DIM 180

#define MAX_LINES 500

//#define MIN_LINE_PIXELS 100
//sLine lines[500];
//int iterLine =0;

void hough_buffer(uchar * inBuff, int height, int width, sLine* lines, int &numLines, int minLinePixels){
	/// r = x cos (theta) + y sin(theta)
// make sure the num of lines detected are zero before hough
  numLines = 0;
  int aWidth = THETA_DIM;
  int aHeight = sqrt(height* height + width * width) - 1;
  int * accum = new int[aWidth * aHeight];
  for(int row = 0; row < height; row++){
    for (int col = 0; col < width; col++){
      if (inBuff[row * width + col] == 255){
        for (int theta = 0; theta<180; theta++){
          double thetaRad = (float(theta) * 3.14)/180.0;
          int r = int (col * cos(thetaRad) + row *  sin(thetaRad));
          accum[r * THETA_DIM + theta]++;
        }
      }
    }
  }

  // detect lines which have voted more than 100 pixels
  for (int t = 0; t < THETA_DIM; t++){
   for(int r =0; r < aHeight; r++){
     if (accum[r * THETA_DIM+ t] > 300){
       if(numLines < 500){
         lines[numLines].rho = r;
         lines[numLines].theta = t;
         numLines++;
      }

    }
  }
}
std::cout<<"number of lines dtected "<<numLines<<std::endl;

#if 0 // debug code to draw lines
for(int i = 0; i < numLines; i++ )
  {
     float rho = lines[i].rho, theta = (float(lines[i].theta) * 3.14)/(180.0);
     //Point pt1, pt2;
     double a = cos(theta), b = sin(theta);
     double x0 = a*rho, y0 = b*rho;
     int x1 = cvRound(x0 + 1000*(-b));
     int y1 = cvRound(y0 + 1000*(a));
     int x2 = cvRound(x0 - 1000*(-b));
     int y2 = cvRound(y0 - 1000*(a));
     draw_line(inBuff, height, width, x1, y1, x2, y2);
     //line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
  }
#endif

}
int im_round(double number)
{
    return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
}
// Note accepts theta in radians
void polarToEucledianLine(int rho, float theta, int &x1, int &y1, int &x2, int &y2){
    // x = rho cos(theta)
    // y = rho sin(theta)
    double a = cos(theta), b = sin(theta);
    double x0 = a*rho, y0 = b*rho;
    x1 = im_round(x0 + 1000*(-b));
    y1 = im_round(y0 + 1000*(a));
    x2 = im_round(x0 - 1000*(-b));
    y2 = im_round(y0 - 1000*(a));
}
int hough_custom(cv::Mat &image){
    cv::Mat gray;
    cv::Mat grayOut;
    cv::Mat grayInt;
    if (image.channels() == 3){
       cvtColor(image, gray, CV_BGR2GRAY);
    }else{
      image.copyTo(gray);
    }
    gray.copyTo(grayInt);
    gray.copyTo(grayOut);
    uchar * inBuff = (uchar *) gray.data;
    uchar * outBuff = (uchar *) grayOut.data;
    uchar * intBuff = (uchar*) grayInt.data;
    int height = image.rows;
    int width = image.cols;

    sLine lines[MAX_LINES];
    int numLinesDetected = 0;

    // minimum nuber of pixels required to be considered a line
    int minLinePixels = 200;

    detectCannyEdges(inBuff, outBuff, intBuff, height, width);

    hough_buffer(outBuff, height, width, 
                 lines, numLinesDetected, minLinePixels);

    for(int i = 0; i < numLinesDetected; i++ )
    {
      float rho = lines[i].rho, theta = (float(lines[i].theta) * 3.14)/(180.0);
      cv::Point pt1, pt2;
      double a = cos(theta), b = sin(theta);
      double x0 = a*rho, y0 = b*rho;
      pt1.x = cvRound(x0 + 1000*(-b));
      pt1.y = cvRound(y0 + 1000*(a));
      pt2.x = cvRound(x0 - 1000*(-b));
      pt2.y = cvRound(y0 - 1000*(a));
      //draw_line(inBuff, height, width, x1, y1, x2, y2);
      cv::line( image, pt1, pt2, cv::Scalar(0,0,255), 3, CV_AA);
    }
    cv::namedWindow("edge");
    cv::imshow("edge", grayOut);

    cv::namedWindow("lines");
    cv::imshow("lines",image);
    return 0;
}