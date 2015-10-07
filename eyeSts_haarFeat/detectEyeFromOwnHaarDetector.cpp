#include "headers.h"
/// Working ----------------
CvHaarClassifierCascade *own_cascade_Eye;
//char *ownHaarFile =   (char *) "/home/naresh/Documents/surya_haarTr/haar_new_4k_20st/haar_20st.xml";
//char *ownHaarFile   =   (char *) "/home/naresh/Documents/surya_haarTr/haar_new_4k_9st/haar_9st.xml";
/// Good XML file...
char *ownHaarFile     =   (char *) "/home/naresh/Documents/myOwnHaar_eyeSts/trained/h_10st/h_10st.xml"; //       1
//char *ownHaarFile   =   (char *) "/home/naresh/Documents/myOwnHaar_eyeSts/validation_test/h_filt_20st.xml"; // 2
//char *ownHaarFile   =   (char *) "/home/naresh/Documents/myOwnHaar_eyeSts/validation_test/haar_pos_581_st20.xml";
//char *ownHaarFile   =   (char *) "/home/naresh/Documents/myOwnHaar_eyeSts/validation_test/h_filt_pos2k_20st.xml";
//char *ownHaarFile   =   (char *) "/home/naresh/Documents/myOwnHaar_eyeSts/validation_test/h_filt_pos15k_20st.xml";

/// Not Good ----------------------------------------------------------------------------------------------------------------------------------------------
//char *ownHaarFile   =   (char *) "/home/naresh/Documents/myOwnHaar_eyeSts/validation_test/h_filt_pos15k_20st.xml";
//char *ownHaarFile   =   (char *) "/home/naresh/Documents/myOwnHaar_eyeSts/validation_test/haar_pos_581_st15.xml";
//char *ownHaarFile   =   (char *) "/home/naresh/Documents/myOwnHaar_eyeSts/validation_test/haar_pos_581.xml";
//char *ownHaarFile   =   (char *) "/home/naresh/Documents/myOwnHaar_eyeSts/validation_test/haar_pos_581_st10.xml";




///----------------------------------------------------------------------------------------------------------------------------------------------





int detectEyesFromMyOwnHaarClassifier(IplImage *croppedEye)
{
    int label = 0;
    if(croppedEye)
    {
        IplImage *temp, *showRectImg;
        temp        = cvCreateImage(cvGetSize(croppedEye), croppedEye->depth,croppedEye->nChannels);
        showRectImg = cvCreateImage(cvGetSize(croppedEye), croppedEye->depth,croppedEye->nChannels);

        cvCopy(croppedEye, temp); cvCopy(croppedEye, showRectImg);

           // cvNamedWindow( "Ip_Own_HAAR", 1);   cvShowImage( "Ip_Own_HAAR", temp ); cvWaitKey(0);
           // cout << "Ip_Own_HAAR width : " << temp->width << "  height : " << temp->height << endl;

        CvMemStorage *storage3  = cvCreateMemStorage(0);
        own_cascade_Eye         = (CvHaarClassifierCascade *) cvLoad(ownHaarFile);
        CvSeq *eyeObjects       = cvHaarDetectObjects(temp,own_cascade_Eye, storage3, 1.2, 2, 0, cvSize(30, 15));
//        CvSeq *eyeObjects=cvHaarDetectObjects(temp,own_cascade_Eye, storage3, 1.1, 2, CV_HAAR_SCALE_IMAGE, cvSize(30, 15));
//        CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage, 1.1, 2, CV_HAAR_SCALE_IMAGE, cvSize(30, 30) );
        int nEyeObj = 0;
        nEyeObj = eyeObjects->total;

           // cout<< "No of Own Haar_obj---------------------------------------------     : " << nEyeObj << endl;
        if(eyeObjects->total != 0)
        {
            for(int nEyeObjects = 0; nEyeObjects<(eyeObjects->total); nEyeObjects++)
            {
                CvRect *r    = (CvRect *)cvGetSeqElem(eyeObjects, nEyeObjects);
                CvPoint pt1  = {r->x, r->y};
                CvPoint pt2  = {r->x + r->width, r->y + r->height };
                //Drawing rectangle on a image...
                cvRectangle(showRectImg, pt1, pt2, CV_RGB(0,255,0), 1, 4, 0);
                    //cvNamedWindow("Detected_Eye_4m_OwnHaarCl", 1);   cvShowImage( "Detected_Eye_4m_OwnHaarCl", showRectImg); cvWaitKey(0);
                   // cout<<"Eye Dim x: "<< pt1.x<< " y: " << pt1.y << " width: "<< (pt2.x-pt1.x)<< " height: "<< (pt2.y-pt1.y)<<endl;
                //CvRect boundingBox = cvRect(pt1.x, pt1.y, r->width , r->height);
                cvSetImageROI(temp, cvRect(pt1.x, pt1.y, (pt2.x-pt1.x), (pt2.y-pt1.y)));
                   // cvNamedWindow("IpToHOG", 1);   cvShowImage( "IpToHOG", temp); cvWaitKey(0);
                /// Testing ..............
                ///----------- Hog feat Extraction -----------
                cv::Mat testImgHogFv =  hogFv(temp);
                ///----------- Testing Hog Fv with SVM --------
                label = findFvClass_Hog_Svm(testImgHogFv);
                //label =1;
                cvResetImageROI(temp);
                //cout<< "MY label is >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   " << label << endl;
                if(label == 1)
                    break;
                /// Testing ..............
            }
        }
        else
            label = -1;
        cvReleaseImage(&showRectImg);
        cvReleaseImage(&temp);
        cvReleaseMemStorage(&storage3);
        cvReleaseHaarClassifierCascade(&own_cascade_Eye);
        /// i.e Eye objects are not found means Positive class obj(opened eye) is not found. therefore the eyests is Closed
    }
    else
    {
           // cout<< "Cropped Eye is Empty" << endl;
    }
    return label;
}

/// ==========================================================================================================================================
//                temp1 = cvCreateImage(cvSize(r->width, r->height), temp->depth,temp->nChannels);
//                cvCopy(temp, temp1);
//                cvResetImageROI(temp);
////              cout << "temp x : " << pt1.x << "  y : " << pt1.y << endl;
////              cout << "temp width : " << temp->width << "  height : " << temp->height << endl;
//                cvNamedWindow( "tempCC2", 1);   cvShowImage( "tempCC2", temp ); cvWaitKey(0);

//             CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
//             CvPoint pt1 = { r->x, r->y };
//             CvPoint pt2 = { r->x + r->width, r->y + r->height };
//             cvRectangle( small_image, pt1, pt2, CV_RGB(0,255,0), 3, 8, 0 );
//             CvRect boundingBox = cvRect(pt1.x,pt1.y, r->width , r->height);
//             cvSetImageROI(small_image, boundingBox);
//             temp = cvCreateImage(cvGetSize(small_image), small_image->depth,small_image->nChannels);
//             cvCopy(small_image, temp, NULL);
