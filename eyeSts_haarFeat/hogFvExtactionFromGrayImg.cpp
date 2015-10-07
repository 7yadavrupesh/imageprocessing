#include "headers.h"

cv::Mat hogFv(IplImage *detectedImg)
{
   // cvNamedWindow( "ipImg2", 1);   cvShowImage( "ipImg2", detectedImg ); cvWaitKey(0);
    cv::Mat img = Mat(detectedImg, false);
   // namedWindow( "Display window", CV_WINDOW_AUTOSIZE );    imshow( "Display window", img );    waitKey(0);

    resize(img, img, Size(40,20) );
    //namedWindow( "Ip2HOg", CV_WINDOW_AUTOSIZE );    imshow( "Ip2HOg", img );    waitKey(0);

    HOGDescriptor d;
    d.winSize     = Size(40,20);
    d.blockSize   = Size(20,10);
    d.cellSize    = Size(10,5) ;
    d.blockStride = Size(10,5) ;
    d.nbins       = 9;
    // Size(128,64), //winSize
    // Size(16,16), //blocksize
    // Size(8,8), //blockStride,
    // Size(8,8), //cellSize,
    // 9, //nbins,
    // 0, //derivAper,
    // -1, //winSigma,
    // 0, //histMatogramNormType,
    // 0.2, //L2HysThresh,
    // 0 //gammal correction,
    // //nlevels=64
    //);

    // void HOGDescriptor::compute(const Mat& img, vector<float>& descriptors,
    //                             Size winStride, Size padding,
    //                             const vector<Point>& locations) const
    /// Feature Vector size is : 9*(bins)* 9 *(Blocks) * 2*2(2X2 cells) = 324, each cell size: 10X5
    vector<float> descriptorsValues;
    vector<Point> locations;
    d.compute( img, descriptorsValues, Size(0,0), Size(0,0), locations);

//    cout << "HOG descriptor size is " << d.getDescriptorSize() << endl;
//    cout << "img dimensions: " << img.cols << " width x " << img.rows << "height" << endl;
//    cout << "Found " << descriptorsValues.size() << " descriptor values" << endl;
//    cout << "Nr of locations specified : " << locations.size() << endl;

    cv::Mat hogfeat;
    hogfeat.create(descriptorsValues.size(), 1, CV_32FC1);

    for(unsigned int i=0;i<descriptorsValues.size();i++)
    {
        hogfeat.at<float>(i,0)=descriptorsValues.at(i);
        //cout<< "Hog FValue : " << descriptorsValues.at(i) << endl;
    }
   return hogfeat;
}
