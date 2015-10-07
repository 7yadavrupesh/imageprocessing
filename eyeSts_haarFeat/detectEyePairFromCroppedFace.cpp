#include "headers.h"


//char *eye_pair_s    = (char *) "haarcascade_mcs_eyepair_small.xml"; //"haarcascade_eye.xml";
char *eye_pair_s    = (char *) "/home/naresh/Documents/eyeSts_haarFeat/haarcascade_mcs_eyepair_big.xml"; //"haarcascade_eye.xml";
char *eye_single    = (char *) "haarcascade_eye.xml";

CvHaarClassifierCascade *cascade_Eye_Pair;



IplImage* detectEyePairFromCroppedFace(IplImage *inFaceImg)
{
            //cvNamedWindow( "inFaceImg", 1);   cvShowImage( "inFaceImg", inFaceImg ); cvWaitKey(0);

   //IplImage *eyePair;
   cout << "Face width : " << inFaceImg->width << "  height : " << inFaceImg->height << endl;
   CvMemStorage *storage  = cvCreateMemStorage(0);
   cascade_Eye_Pair       = (CvHaarClassifierCascade *) cvLoad(eye_pair_s);
   CvSeq *eyeObjects      = cvHaarDetectObjects(inFaceImg,cascade_Eye_Pair, storage, 1.2, 2, 0, cvSize(20, 20));
   //CvSeq *eyeObjects      = cvHaarDetectObjects(inFaceImg,cascade_Eye_Pair, storage, 1.2, 2, 0, cvSize(20, 9));

   //IplImage *croppedEye;
            cout<< "Eye objects: " << eyeObjects->total << endl;


   if(eyeObjects->total == 0)
   return NULL;

   else
   {
      for(int nEyeObjects = 0; nEyeObjects<(eyeObjects->total); nEyeObjects++)
      {
         CvRect *rect = (CvRect *)cvGetSeqElem(eyeObjects, nEyeObjects);
         CvPoint pt1  = {rect->x-10, (rect->y)-10};
         CvPoint pt2  = {rect->x-10 + rect->width+5, rect->y + rect->height };
        //Drawing rectangle on a image...
         cvRectangle(inFaceImg, pt1, pt2, CV_RGB(255,255,255), 1, 8, 0);
         CvRect boundingBox = cvRect(pt1.x, pt1.y, rect->width, rect->height);
         //cvNamedWindow( "FaceWithDetectedEyes", 1);   cvShowImage( "FaceWithDetectedEyes", inFaceImg ); cvWaitKey(0);
         cvSetImageROI(inFaceImg, boundingBox);
         cvSaveImage("eyePair.jpg", inFaceImg);

      }
   }
   return inFaceImg;
}

