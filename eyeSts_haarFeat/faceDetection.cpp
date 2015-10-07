#include "headers.h"

#define MAX_STR_LENGTH 99

IplImage* faceDetection(IplImage* dst)
{
      IplImage *small_image;
      IplImage *temp;

     if(dst!= 0 )
    {
            //cvNamedWindow( "Ip", 0 );cvShowImage( "Ip", dst ); cvWaitKey(0);
        char faceXMLFile[MAX_STR_LENGTH]  = "\0";
        strcpy(faceXMLFile, "/home/naresh/Documents/eyeSts_haarFeat/haarcascade_frontalface_alt.xml");
        CvHaarClassifierCascade* cascade = cvLoadHaarClassifierCascade(faceXMLFile, cvSize(90, 70));

        CvMemStorage *storage = cvCreateMemStorage(0);
        CvSeq *faces;

        small_image = cvCreateImage(cvSize((dst->width)/2,(dst->height/2)), IPL_DEPTH_8U, 3);
        cvPyrDown(dst, small_image, CV_GAUSSIAN_5x5);
            //cout<< "Width: " << small_image->width << "   Height: " << small_image->height << endl;

        faces = cvHaarDetectObjects( small_image, cascade, storage, 1.2, 2, CV_HAAR_DO_CANNY_PRUNING );

        if(faces->total !=0)
        {
            //cout << "No of Face Objects " << faces->total << endl;
            for(int i = 0; i < faces->total; i++ )
            {
                 CvRect *r = (CvRect*)cvGetSeqElem( faces, i );
                 CvPoint pt1 = { r->x, r->y };
                 CvPoint pt2 = { r->x + r->width, r->y + r->height };
                 cvRectangle( small_image, pt1, pt2, CV_RGB(94, 206, 165), 1, 8, 0 );
                 CvRect boundingBox = cvRect(pt1.x,pt1.y, r->width , r->height);
                 cvSetImageROI(small_image, boundingBox);
                 temp = cvCreateImage(cvGetSize(small_image), small_image->depth,small_image->nChannels);
                 cvCopy(small_image, temp, NULL);

                //             face1 = cvCloneImage(small_image);
                //             cvNamedWindow("faceface", 0);cvShowImage("faceface", face1);cvWaitKey(0);
                //             cout << "temp Width : " << temp->width << "  height : " << temp->height << endl;
            }
            cvReleaseMemStorage( &storage );
     //       cvReleaseHaarClassifierCascade( &cascade );
            cvNamedWindow("smallImg", 0);cvShowImage("smallImg", temp);cvWaitKey(0);
            return temp;
        }
        else
        {
            cvReleaseMemStorage( &storage );
            cvReleaseHaarClassifierCascade( &cascade );
            return NULL;
        }
        //cvReleaseImage( &small_image);
        cvNamedWindow("smallImg", 0);cvShowImage("smallImg", small_image);cvWaitKey(0);
    }
    return NULL;

}

