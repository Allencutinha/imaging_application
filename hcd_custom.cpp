#include "hcd_custom.h"
#include "gaussian_custom.h"
int dx_kernel [3][3] = {{-1, 0, 1},
                        {-1, 0, 1},
                        {-1, 0, 1}};
int dy_kernel [3][3] = {{-1,-1,-1},
                        {0, 0, 0},
                        {1,1,1}};

void harris_corner_det_buffer(uchar* inBuff, uchar* outBuff, int height, int width){
 
  std::cout<<"harris corner dtector entered"<<std::endl;
  int* dx_2Buff = new int[height * width];
  int* dy_2Buff = new int[height * width];
  int* dxdyBuff = new int[height * width];
  // calculate the derivative sin the x and y directions
  for(int row = 1; row < height-1; row++){
  	for (int col = 1; col < width-1; col++){
  	  int dx = 0;
  	  int dy = 0;
  	  for (int r=0; r<3; r++){
  	    for (int c =0; c<3; c++){
          dx += inBuff[(row+r-1) * width + (col+c-1)] * dx_kernel[r][c];
          dy += inBuff[(row+r-1) * width + (col+c-1)] * dy_kernel[r][c];
  	    }
  	  }
  	  dx_2Buff[row * width + col] = dx*dx;
      dy_2Buff[row * width + col] = dy*dy;
      dxdyBuff[row * width + col] = (dx * dy);
  	}
  }
 
  //scale the hcr for display
  // apply gaussian smoothing on the derivatives
  gaussian_buffer_int(dx_2Buff, dx_2Buff, 5, 2, height, width, 1/*channels*/);
  gaussian_buffer_int(dy_2Buff, dy_2Buff, 5, 2, height, width, 1/*channels*/);
  gaussian_buffer_int(dxdyBuff, dxdyBuff, 5, 2, height, width, 1/*channels*/);


  //compute harris corner response
  float k =0.04;
  double threshold = 10000000;////10000000;
  double Ix_2 = 0;
  double Iy_2 = 0;
  double Ixy_2 = 0;
  double Ixy = 0;
  double val = 0;
  // harris corner response matrix
  double* hcr = new double [height * width];
  double max = 0;

  for (int row =0; row< height; row++){
    for (int col = 0; col < width; col++){
      Ix_2 = dx_2Buff[row * width + col];
      Iy_2 = dy_2Buff[row * width + col];
      Ixy = dxdyBuff[row * width + col];
      Ixy_2 = Ixy * Ixy;
      // ((Ix^2 * Iy^2 - Ixy^2) - (k * (Ix^2 + Iy^2)^2))
      val = ((Ix_2 * Iy_2) - (Ixy_2)) - (k * (Ix_2 + Iy_2) * (Ix_2 + Iy_2));
      if (val > threshold){
        hcr [row * width + col] = val;
        if (val > max){
          max = val;
        }
      }else{
        hcr[row * width + col] = 0;
      }
    }
  }
  std::cout<<" max :: "<<max<<std::endl;
  // normalize the output from 0 to 255
  for (int row =0; row< height; row++){
    for (int col = 0; col < width; col++){
      outBuff[row * width + col] = (hcr [row * width + col] * 255) /(max);
    }
  }
  // this detection could and should be improved and needs to be done in the future 
  // for the Harrris corner deection to be fully useful for calibration
  // the number of pixels representing one corne should be ideally only one
  delete [] hcr;
  delete [] dx_2Buff;
  delete [] dy_2Buff;
  delete [] dxdyBuff;
}


// main function to test harris corner detection
void harris_corner_det(cv::Mat& image){
	cv::Mat gray;
  cv::Mat grayOut;
    
  if (image.channels() == 3){
    cvtColor(image, gray, CV_BGR2GRAY);
  }else{
    image.copyTo(gray);
  }
  gray.copyTo(grayOut);
  uchar * inBuff = (uchar *) gray.data;
  uchar * outBuff = (uchar *) grayOut.data;
  int height = image.rows;
  int width = image.cols;

  // custom implementation
  harris_corner_det_buffer(inBuff, outBuff, height, width);
  cv::namedWindow("out");
  cv::imshow("out", grayOut);
  int thresh = 10;
  for (int row = 0; row < height; row++){
    for (int col = 0; col < width; col++){
      if (outBuff[row *width+col] > thresh){
        cv::circle( image, cv::Point(col, row ), 3,  cv::Scalar(0,255,0), 2, 8, 0 );
      }
    }
  }
  cv::namedWindow("corners");
  cv::imshow("corners", image);

}