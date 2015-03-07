#include "draw_custom.h"

// module to draw line 
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

// module to rotate the point location wrt center of rotation
void rotate_point(int &x, int &y, int xCenterOfRotation, int yCenterOfRotation, float theta){
     float thetaRad = (theta*3.14)/180.0; 
     int xRot = cos(thetaRad) * float(x - xCenterOfRotation) - sin(thetaRad) * float(y - yCenterOfRotation) + xCenterOfRotation;
     int yRot = sin(thetaRad) * float(x - xCenterOfRotation) + cos(thetaRad) * float(y - yCenterOfRotation) + yCenterOfRotation;

     x = xRot;
     y = yRot;
}

// module to draw a rectangle
void draw_rectangle(uchar* inBuff, int height, int width,
               int x, int y, int rectHeight, int rectWidth, float theta)
{
    // vertices are defined clockwise 0->1->2->3->0
    // vertex 0
    int x0 = x;
    int y0 = y;
    // vertex 1
    int x1 = x+rectWidth;
    int y1 = y;
    //vertex 2
    int x2 = x+rectWidth;
    int y2 = y+rectHeight;
    //vertex 3
    int x3 = x;
    int y3 = y+rectHeight;

    if (theta != 0){
        // rotate the vertices wrt to 0th vertex
        //rotate_point(x0,y0, x0, y0, theta);
        rotate_point(x1,y1, x0, y0, theta);
        rotate_point(x2,y2, x0, y0, theta);
        rotate_point(x3,y3, x0, y0, theta);
    }
     std::cout<<"(x0, y0)"<<x0<<","<<y0<<std::endl;
     std::cout<<"(x1, y1)"<<x1<<","<<y1<<std::endl;
     std::cout<<"(x2, y2)"<<x2<<","<<y2<<std::endl;
     std::cout<<"(x3, y3)"<<x3<<","<<y3<<std::endl;
    // line from vertex 0->1
    draw_line(inBuff, height, width, x0, y0, x1, y1);
    // line from vertex 1->2
    draw_line(inBuff, height, width, x1, y1, x2, y2);
    // line from vertex 2->3
    draw_line(inBuff, height, width, x2, y2, x3, y3);
    // line from vertex 3->0
    draw_line(inBuff, height, width, x3, y3, x0, y0);

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
    
    draw_rectangle(inBuff, height, width, 200, 200, 100, 100, 20);

    cv::namedWindow("line");
    cv::imshow("line", gray);

	return 0;
}