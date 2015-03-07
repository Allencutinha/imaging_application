#include "draw_custom.h"

void draw_line(uchar * inBuff, int height, int width,
	           int x0, int y0, int x1, int y1){

	// make sure that (x0, y0) lie on the upper left corner of (x1, y1)
    // calculate slope
    float m = 1000;
    if ((x1 - x0) != 0) {m = float(y1-y0)/float(x1-x0);}
    
    //calculate c
    float c = y1 - m * x1;
    std::cout<<c<<"  "<<m<<std::endl;
    // find the xMin, xMax and yMin , yMax
    int xMin = 0;
    int xMax = 0;
    if (x0 <= x1){xMin = x0; xMax = x1;}
    else {xMin = x1; xMax = x0;}
    int yMin = 0;
    int yMax = 0;
    if (y0 <= y1){yMin = y0; yMax = y1;}
    else {yMin = y1; yMax = y0;}

    // now to draw the most possible points possible  we must
    // iterate through the axes with maximum difference
    int xRange = abs(xMax - xMin);
    int yRange = abs(yMax - yMin);
    if (xRange >= yRange){
        // draw th line
        for (int x = xMin; x <= xMax; x++){
    	    int y = m * x + c;
    	    if ((m * x + c) - y  > 0.5){y = y+1;}
    	    if (y < height  && y >=0
    	    	&& x < width && x >=0){
                inBuff[y * width + x] = 255;
            }
        }
    }else{
    	//iterate through y
    	for (int y = yMin; y <= yMax; y++){
    	    //int y = m * x + c;
    	    int x = (y - c)/m;
    	    if((y-c)/m - x  >= 0.5){x= x+1;}
    	    if (y < height  && y >=0
    	    	&& x < width && x >=0){
                inBuff[y * width + x] = 255;
            }
        }

    }

}
int draw_custom(cv::Mat &image)
{    
	cv::Mat gray;
    if (image.channels() == 3){
       cvtColor(image, gray, CV_BGR2GRAY);
    }else{
      image.copyTo(gray);
    }
    uchar * inBuff = (uchar *) gray.data;
    int height = image.rows;
    int width = image.cols;
    int x0 =  0;
    int y0 =  height;
    int x1 = width;
    int y1 = 0;
    
	draw_line(inBuff, height, width, x0, y0, x1, y1);

	cv::namedWindow("line");
	cv::imshow("line", gray);

	return 0;
}