#include "headers.h"

#define STD_FACE_WIDTH  163
#define STD_FACE_HEIGHT 171

int test_getClassLabelFromGivenImg(IplImage *ipImg)
{
    int label = 0;
    if(ipImg)
    {
        IplImage *face = faceDetection(ipImg);
        //IplImage *face = ipImg;
        if(face)
        {
            IplImage *tempFace = cvCreateImage(cvSize(STD_FACE_WIDTH, STD_FACE_HEIGHT), face->depth, face->nChannels);
            cvResize(face, tempFace);
                //cvNamedWindow( "face", 1); cvShowImage( "face", face ); cvWaitKey(0);
                //cout << "CroppedFace_width : " << face->width << "  height : " << face->height << endl;
                //cout << "ResizedFace_width : " << tempFace->width << "  height : " << tempFace->height << endl;
                //cvNamedWindow( "ResizedFace", 1); cvShowImage( "ResizedFace", tempFace ); cvWaitKey(0);

            CvRect eyes_portion_rect = cvRect(1, 5+((tempFace->height)/5), (tempFace->width)/2, (tempFace->height)/3);
            cvSetImageROI(tempFace, eyes_portion_rect);
            //      cvNamedWindow( "CroppedEye", 1);   cvShowImage( "CroppedEye", face ); cvWaitKey(0);
                IplImage* eyePair = detectEyePairFromCroppedFace(ipImg);
                IplImage *eyePair2 = cvLoadImage("eyePair.jpg");
                //cvNamedWindow("pEye", 1); cvShowImage("pEye", eyePair2); cvWaitKey(0);
                  cout<< "paired Eye width :  " << eyePair2->width << "   height : " << eyePair2-> height << endl;
                  cvShowImage("croppedeye",tempFace);
                  cvWaitKey(0);
            label = detectEyesFromMyOwnHaarClassifier(tempFace);

            cvReleaseImage(& tempFace);
        }
        else
            cout << "      Face Not Detected !!!!!" << endl;
    }
    return label;
}
