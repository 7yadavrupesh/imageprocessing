#ifndef _headers_h
#define _headers_h

    #include <iostream>
    #include <stdlib.h>

    #include "highgui.h"
    #include "cv.h"
    #include "ml.h"
    #include <opencv2/core/core.hpp>



    using namespace std;
    using namespace cv;


    IplImage* faceDetection(IplImage *);
    IplImage* detectEyePairFromCroppedFace(IplImage *);
    int detectEyesFromMyOwnHaarClassifier(IplImage *);


    cv::Mat hogFv(IplImage *);
    void hog_trDataPreparation();

    void training_Hog_Svm();
    int findFvClass_Hog_Svm(cv::Mat);
    int test_getClassLabelFromGivenImg(IplImage *);

    void plot_myData(int *, int *, int,  char *);
    void resize_saveImages();
    void readVideosFromFolderAndWriteFinalResultIntoTextFile(char *);
    void readImgesFromFolderAndWriteFinalResultIntoTextFile(char *);

#endif
/// *******************   Rough   **************************************************************************************

/// Rough Resize and saving Code....
//void resize_saveImages()
//{
//    for(int i = 1; i< 6; i++)
//    {
//
//        char srcPath[99]  = "/home/naresh/Documents/DataSets/Haar_DataSets/pos_data/all_imgs/";
//        char destPath[99] = "/home/naresh/Documents/DataSets/Haar_DataSets/posData_new_40_20/";
//        char srcPath1[2] = {};
//        char destPath1[2]= {};
//        sprintf(srcPath1, "%d", i);
//        sprintf(destPath1, "%d.png", i);
//
//        strcat(srcPath,srcPath1);
//        strcat(destPath,destPath1);
//
//
//        cout<< "path : " << srcPath<< endl;
//        IplImage *ip = cvLoadImage(srcPath);
//         cvNamedWindow( "ip", 1);   cvShowImage( "ip", ip ); cvWaitKey(0);
//        IplImage *dest = cvCreateImage(cvSize(40, 20), ip->depth, ip->nChannels);
//
//        cvResize(ip, dest, CV_INTER_CUBIC);
//        cvSaveImage(destPath, dest);
//    }
//}
//#include "opencv2/objdetect/objdetect.hpp"
//#include "opencv2/highgui/highgui.hpp"
//
//#include <ctype.h>
//#include <stdio.h>
//
//static void help(void)
//{
//    printf("\n This sample demonstrates cascade's convertation \n"
//    "Usage:\n"
//    "./convert_cascade --size=\"<width>x<height>\"<convertation size> \n"
//    "                   input_cascade_path \n"
//    "                   output_cascade_filename\n"
//    "Example: \n"
//    "./convert_cascade --size=640x480 ../../opencv/data/haarcascades/haarcascade_eye.xml ../../opencv/data/haarcascades/test_cascade.xml \n"
//    );
//}
//
//int main( int argc, char** argv )
//{
//    const char* size_opt = "--size=";
//    char comment[1024];
//    CvHaarClassifierCascade* cascade = 0;
//    CvSize size;
//
//    //help();
//printf("Arguments: %d \n", argc);
//    if( argc != 4 || strncmp( argv[1], size_opt, strlen(size_opt) ) != 0 )
//    {
//
//        help();
//        return -1;
//    }
//
//    sscanf( argv[1], "--size=%ux%u", &size.width, &size.height );
//    cascade = cvLoadHaarClassifierCascade( argv[2], size );
//
//    if( !cascade )
//    {
//        fprintf( stderr, "Input cascade could not be found/opened\n" );
//        return -1;
//    }
//
//    sprintf( comment, "Automatically converted from %s, window size = %dx%d", argv[2], size.width, size.height );
//    cvSave( argv[3], cascade, 0, comment, cvAttrList(0,0) );
//    return 0;
//}

//    IplImage *inImg;
//    for (int i =400 ; i< 404 ; i++)
//    {
//        char dirPath[127] = "/home/naresh/Documents/surya_haarTr/pos_Data_Haar/";
//        char imgName[9]  = {0}; //png
//        char imgName2[9] = {0}; // jpg
//        char imgName3[9] = {0}; // pgm
//        char imgName4[9] = {0}; //jpeg
//
//        printf("%d\n",i);
//        sprintf(imgName, "p%d.jpeg", i);
//
//        strcat(dirPath, imgName);
//
//        inImg  = cvLoadImage(dirPath);        // cv::imshow("inImg",inImg); cv::waitKey(0);
//
//
//
//        printf("Channels : %d \n", inImg->nChannels);
//        cvNamedWindow("png",1); cvShowImage("png", inImg); cvWaitKey(0);
//
//        IplImage *dst = cvCreateImage(cvSize(38,22), inImg->depth, inImg->nChannels);
//        cvResize(inImg, dst);
//        cvSmooth(dst,dst);
//        //cvEqualizeHist(dst, dst);
//        cvSaveImage(imgName, dst);
//    }
/// Rough =========================================================
/// *******************   Rough   **************************************************************************************
