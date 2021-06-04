#include "canny_custom.h"

float Gaussian[5][5] = { { 2.f, 4.f, 5.f, 4.f, 2.f },
						 { 4.f, 9.f, 12.f, 9.f, 4.f },
						 { 5.f, 12.f, 15.f, 12.f, 5.f },
						 { 4.f, 9.f, 12.f, 9.f, 4.f },
						 { 2.f, 4.f, 5.f, 4.f, 2.f }
};
float sobelx[3][3] = {
		{-1, 0, 1 }, 
		{-2, 0, 2 },
		{-1, 0, 1 }
};
float sobely[3][3] = {
		{ 1, 2, 1 },
		{ 0, 0, 0 },
		{-1,-2,-1 }
};

void detectCannyEdges(uchar* inBuff, uchar* outBuff, uchar * intBuff, int height, int width){
	
	float * G        = new float[height * width];
	float * GTemp    = new float[width* height];
	uchar * tempBuff = new uchar[height * width];
	uchar * edgeDir = new uchar[height* width];

	// Apply gaussian filter
	for (int row = 2; row < height - 2; row++){
	  for (int col = 2; col < width - 2; col++){
	    float sum = 0;
	    for (int r = 0; r < 5; r++){
	      for (int c = 0; c < 5; c++){
	        sum += inBuff[(row + r - 2)* width + (col + c - 2)] * Gaussian[r][c];
	      }
	    }
	    tempBuff[row*width + col] = (uchar)(sum / 159);
	  }
	}

	
	//calculate edge directon and gradient
	float maxDiff = 0;
	for (int row = 1; row < height - 1; row++){
	  for (int col = 1; col < width - 1; col++){
        float sum = 0;
        float Gx = 0;
        float Gy = 0;
        for (int r = 0; r < 3; r++){
	      for (int c = 0; c < 3; c++){
		    Gx += tempBuff[(row + r - 1)* width + (col + c - 1)] * sobelx[r][c];
		    Gy += tempBuff[(row + r - 1)* width + (col + c - 1)] * sobely[r][c];
	      }
        }
        float tempDiff = 0;
		tempDiff = GTemp[row * width + col] = G[row * width + col] = sqrt(Gx*Gx + Gy * Gy);
		if (tempDiff > maxDiff){ maxDiff = tempDiff;}

		float thetaDeg = (atan2(Gy, Gx) * 180 / 3.14);
		edgeDir[row * width + col] = 0;

		uchar newAngle = 0;
		// assign edge directions to bins of 0, 45, 90 and 135
		if (((thetaDeg <= 22.5) && (thetaDeg >= -22.5))  || ((thetaDeg >= 157.5) && (thetaDeg <= -157.5)))
		  newAngle = 0;
        if (((thetaDeg > 22.5)  && (thetaDeg <   67.5))  || ((thetaDeg < -112.5)&& (thetaDeg >  -157.5)))
	      newAngle = 45;
        if (((thetaDeg >= 67.5) && (thetaDeg <= 112.5))  || ((thetaDeg < -67.5) && (thetaDeg >= -112.5)))
	      newAngle = 90;
        if (((thetaDeg > 112.5) && (thetaDeg <  157.5))  || ((thetaDeg < -22.5) && (thetaDeg >   -67.5)))
	      newAngle = 135;			

        edgeDir[row * width + col] = newAngle;

	  }
	}
	

	// non maximum supression of edges, here we reduce the thickness of the previously obtained edges
	for (int row = 1; row < height - 1; row++){
	  for (int col = 1; col < width - 1; col++){
	    GTemp[row * width + col] = 0;
	    
	    if (edgeDir[row*width + col] == 0){
	      if (G[row * width + col] > G[(row)* width + (col - 1)] && G[row * width + col] > G[(row)* width + (col + 1)]){ GTemp[row * width + col] = G[row * width + col]; }
	    }
	    if (edgeDir[row*width + col] == 45){
	      if (G[row * width + col] > G[(row + 1)* width + (col - 1)] && G[row * width + col] > G[(row - 1)* width + (col + 1)]){ GTemp[row * width + col] = G[row * width + col]; }
	    }
	    if (edgeDir[row*width + col] == 90){
	      if (G[row * width + col] > G[(row - 1)* width + (col)] && G[row * width + col] > G[(row + 1)* width + (col)]){ GTemp[row * width + col] = G[row * width + col]; }
	    }
	    if (edgeDir[row*width + col] == 135){
	      if (G[row * width + col] > G[(row + 1)* width + (col + 1)] && G[row * width + col] > G[(row - 1)* width + (col - 1)]){ GTemp[row * width + col] = G[row * width + col]; }
	    }
	    intBuff[row*width + col] = GTemp[row * width + col] = (uchar)((GTemp[row * width + col] * 255) / maxDiff);	  
	  }
	}

	//Double Thresholding
	int lowerThreshold = 20;
	int upperThreshold = 50;
	for (int row = 1; row < height - 1; row++){
		for (int col = 1; col < width - 1; col++){
			intBuff[row*width + col] = 0;
			if (GTemp[row * width + col] > upperThreshold){ GTemp[row * width + col] = 255; }
			else if (GTemp[row * width + col] < lowerThreshold){ GTemp[row * width + col] = 0; }
			intBuff[row*width + col] = GTemp[row * width + col];
		}
	}

	//edge tracking by hysterisis
	int iterations = height * 0.8;//;
	while (iterations > 0){
	  for (int row = 1; row < height - 1; row++){
	    for (int col = 1; col < width - 1; col++){
	      outBuff[row*width + col] = 0;
	      if (GTemp[row * width + col] != 0){
	        // make the current pixel an edge pixel if any of its 8 neighbours are a strong edge
	        for (int r = 0; r < 3; r++){
	          for (int c = 0; c < 3; c++){
	            if (GTemp[(row + r - 1)* width + (col + c - 1)] == 255)
	            {
	              GTemp[row * width + col] = 255;
	              outBuff[row*width + col] = 255;
	            }
	          }
	        }
	      }
	    }
	  }
	  iterations--;
	}

	// free temporary memory
	delete[] G;
	delete[] GTemp;
	delete[] tempBuff;
	delete[] edgeDir;

}


void canny_custom(cv::Mat& image){
	std::cout<<"entered Canny custom"<<std::endl;
	cv::Mat result;
	cv::Mat grayImage;
    cv::Mat intImage;
    if (image.channels() == 3){
    	std::cout<<"color image"<<std::endl;
       cvtColor(image, grayImage, CV_BGR2GRAY);
       grayImage.copyTo(result);
       grayImage.copyTo(intImage);
    }else{
      image.copyTo(grayImage);
      image.copyTo(result);
      grayImage.copyTo(intImage);
    }
	uchar * inBuff = (uchar*) grayImage.data;
	uchar * outBuff = (uchar *) result.data;
        uchar * intBuff = (uchar *)intImage.data;
	detectCannyEdges(inBuff, outBuff, intBuff, image.rows, image.cols);
    cv::namedWindow("canny");
    cv::imshow("canny", result);
}
