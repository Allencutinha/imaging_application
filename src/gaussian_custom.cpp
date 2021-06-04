#include "gaussian_custom.h"

#define FILTER_SIZE 3

void createFilter(double * gKernel, int filterSize, double sigma)
{
    // set standard deviation to 1.0
    //double sigma = 1.0;
    double r, s = ((float)filterSize/2.0) * sigma * sigma;
 
    // sum is for normalization
    double sum = 0.0;
 
    // generate 5x5 kernel
    for (int x = -filterSize/2; x <= filterSize/2; x++)
    {
        for(int y = -filterSize/2; y <= filterSize/2; y++)
        {
            r = sqrt(x*x + y*y);
            gKernel[(x + filterSize/2) * filterSize + (y + filterSize/2)] = (exp(-(r*r)/s))/(M_PI * s);
            sum += gKernel[(x + filterSize/2) * filterSize + (y + filterSize/2)];
        }
    }
    std::cout<<sum<<std::endl;
    // normalize the Kernel
    for(int i = 0; i < filterSize; ++i)
        for(int j = 0; j < filterSize; ++j)
            gKernel[i*filterSize + j] /= sum;
 
}

int test_filter()
{
    double gKernel[FILTER_SIZE* FILTER_SIZE];
    createFilter(gKernel, FILTER_SIZE, 1.0);
    for(int i = 0; i < FILTER_SIZE; ++i)
    {
        for (int j = 0; j < FILTER_SIZE; ++j)
            std::cout<<gKernel[i* FILTER_SIZE+j]<<"\t";
        std::cout<<std::endl;
    }
    return 0;
}

void gaussian_buffer(uchar* inBuff, uchar* outBuff,
                     int KernelSize, double sigma,
                     int height, int width, int channels)
{
    double * gaussianKernel;
    gaussianKernel = new double [KernelSize * KernelSize];
    createFilter(gaussianKernel, KernelSize, sigma);
    
    uchar * outBuffTemp = new uchar[height * width * channels];
    int offset = KernelSize/2;
    for (int row = offset; row < height -offset; row++){
        for (int col = offset; col < width-offset; col++){
            for (int ch = 0; ch < channels; ch++){
                double sum = 0;
                for (int r = -offset; r <= offset; r++){
                    for (int c = -offset; c <= offset; c++){
                        sum += /*inBuff[(col+ c) * channels+ (row + r)  * width* channels + ch];*/inBuff[((col+c) * channels)+ ((row+r) * width * channels)+ ch] * gaussianKernel[(r+offset)*KernelSize+(c+offset)];
                    }
                }
                outBuffTemp[col * channels+ row * width * channels+ch] = (uchar)(sum);
            }
        }
    }
    memcpy(outBuff, outBuffTemp, height * width * channels);
    delete [] outBuffTemp;
}
void gaussian_buffer_int(int* inBuff, int* outBuff,
                     int KernelSize, double sigma,
                     int height, int width, int channels)
{
    double * gaussianKernel;
    gaussianKernel = new double [KernelSize * KernelSize];
    createFilter(gaussianKernel, KernelSize, sigma);
    
    int * outBuffTemp = new int[height * width * channels];
    int offset = KernelSize/2;
    for (int row = offset; row < height -offset; row++){
        for (int col = offset; col < width-offset; col++){
            for (int ch = 0; ch < channels; ch++){
                double sum = 0;
                for (int r = -offset; r <= offset; r++){
                    for (int c = -offset; c <= offset; c++){
                        sum += /*inBuff[(col+ c) * channels+ (row + r)  * width* channels + ch];*/inBuff[((col+c) * channels)+ ((row+r) * width * channels)+ ch] * gaussianKernel[(r+offset)*KernelSize+(c+offset)];
                    }
                }
                outBuffTemp[col * channels+ row * width * channels+ch] = (sum);
            }
        }
    }
    memcpy(outBuff, outBuffTemp, height * width * channels * sizeof(int));
    delete [] outBuffTemp;
}
void gaussian_custom(cv::Mat &image)
{
    cv::Mat result;
    image.copyTo(result);
    uchar* inBuff = (uchar*) image.data;
    uchar* outBuff = (uchar*) result.data;
    gaussian_buffer(inBuff, outBuff, 3, 1, image.rows, image.cols, image.channels());
    cv::namedWindow( "gaussian", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO | CV_GUI_EXPANDED );
    cv::imshow("gaussian", result);
}