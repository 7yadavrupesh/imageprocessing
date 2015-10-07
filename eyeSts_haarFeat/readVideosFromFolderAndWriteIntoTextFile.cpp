#include "headers.h"
#include <dirent.h>

//int FRAMES_TO_DEFINE_SLEEP = 6 ;// "-ve Sign Indictes Closed Eye" total number of closed eye frames are 6
#define FRAMES_TO_DEFINE_SLEEP 6
#define FRAMES_TO_SKIP 20
#define VIDEO_FILENAME_LENGTH 200

void readVideosFromFolderAndWriteFinalResultIntoTextFile(char *folderPath)
{
    cout << "folderPath " << folderPath << endl;
    DIR *dir;
    char vFileName[VIDEO_FILENAME_LENGTH] = "";
    struct dirent *entry;
    dir = opendir(folderPath);
    if(dir != NULL)
    {
        while(entry = readdir(dir))
        {
             /// Doubt
            vFileName[0]='\0';
            if(entry->d_type == DT_REG)
            {
                strcpy(vFileName, entry->d_name);
                char temp[51] = "";
               // strcpy(temp,"/home/naresh/Documents/videosOffice/");
                strcpy(temp,folderPath);
                strcat(temp,vFileName);

                strcpy(vFileName,temp);
                cout << "temp is " << temp << endl;

/// ----------------------------------------------------------------------------------------------------------------------------------------------------------------
                CvCapture *capt  = 0;
                IplImage  *frame = 0;
                int classLabel   = 0;

                int nProcessedFrames = 0;

                //cvNamedWindow( "Input_Frame", CV_WINDOW_AUTOSIZE);

                ///  CV_CAP_PROP_FRAME_COUNT ----> number of video frames in agiven Video ------------------------------------------------------------
                cout << "File Name is: " << vFileName << endl;
                capt  = cvCaptureFromAVI(vFileName);
                //capt  = cvCaptureFromAVI("/home/naresh/valid_naresh.avi");
                //capt  = cvCaptureFromAVI("/home/naresh/Documents/videosOffice/samtha.avi");

                printf("capt=%d\n",capt);
                if(capt)
                {
                    int nTotalFrames_vid = 0 ;
                    nTotalFrames_vid = (int)cvGetCaptureProperty(capt, CV_CAP_PROP_FRAME_COUNT);
                        //cout<<"Total Number of Frames:   " << nTotalFrames_vid << endl;
                    int *result_label_arr = NULL;
                    result_label_arr = (int *)calloc(nTotalFrames_vid, sizeof(int));

                    for(int nFrame = 1; nFrame < nTotalFrames_vid; nFrame++)
                    {
                        frame   = cvQueryFrame(capt);
                        if(!frame){ cout << "Frame " << frame << endl;}
                        int key = cvWaitKey(0);
                        if(frame && key != 32 )
                        {
                            cvShowImage( "Input_Frame", frame);cvWaitKey(0);
                             if(nFrame%FRAMES_TO_SKIP == 0)
                             {
                                //cout << "------------------------------------------>> Frame  Number:  " << nFrame << "   <<-------"<< endl;
                                /// ==========================================================||
                                classLabel = test_getClassLabelFromGivenImg(frame);       /// ||
                                /// ==========================================================||
                                if(classLabel)
                                    //cout << "label :  "  << classLabel << endl;
                                    //cout << "Runnning.........." <<endl;
                                result_label_arr[nProcessedFrames] = classLabel;
                                nProcessedFrames = nProcessedFrames+1;
                                    //cvShowImage( "Input_Frame", frame);cvWaitKey(0);
                             }
                             else
                             {
                                //cout << "------------------------------------------->> Frame  Number:  " << nFrame << "   <<-------"<< endl;
                                //cout<< "Frame Skipped" << endl;
                             }
                        }
                        else
                        {
                            cout<< "Empty frame " << endl;
                            break;
                        }
                    }
                    ///------------------ Post-Processing of LabelArray, to improve the Accuracy ------------------------------------------------------
                    int *modified_resLabelArr = NULL;
                    modified_resLabelArr = (int *) calloc(nProcessedFrames, sizeof(int));

                    for(int idx = 0 ; idx < nProcessedFrames-2; idx++)
                    {
                        if(idx<2)
                        {
                            modified_resLabelArr[idx] = result_label_arr[idx];
                        }
                        else
                        {
                            int sum = 0;
                            sum = result_label_arr[idx-2] + result_label_arr[idx-1]+ result_label_arr[idx+1] + result_label_arr[idx+2];

                            if (sum > 0)
                                modified_resLabelArr[idx] =  1;
                            else if(sum < 0 )
                                modified_resLabelArr[idx] = -1;
                            else if (sum == 0 && (result_label_arr[idx-1] == result_label_arr[idx+1]))
                                modified_resLabelArr[idx] =  result_label_arr[idx-1];
                            else
                                modified_resLabelArr[idx] = 1; /// Benifit of the doubt
                                //cout<< "SUM : " << sum << endl;
                        }
                         //cout<< "modified_resLabelArr Value At IDX : " << modified_resLabelArr[idx] << endl;
                    }
                /// PLOTS ------------------>>>
                    //plot_myData(result_label_arr, modified_resLabelArr, nProcessedFrames, "Result_From Classifier");
                /// PLOTS <<<------------------
                    cout<< "--------------------------------------------------------------------------" << endl;

                    int *sts_resultArray = NULL;
                    sts_resultArray = (int *) calloc(nProcessedFrames, sizeof(int));
                    int nSts_sum = 0;

                    for(int idx2 = 0; idx2< (nProcessedFrames-FRAMES_TO_DEFINE_SLEEP); idx2++)
                    {
                        if(idx2 <  nProcessedFrames-FRAMES_TO_DEFINE_SLEEP)
                        {
                            nSts_sum = 0;
                            for(int p = idx2; p<FRAMES_TO_DEFINE_SLEEP+idx2; p++)
                            {
                                nSts_sum = nSts_sum + modified_resLabelArr[p];
                            }
                                //cout<< "nSts_sum: "<< nSts_sum << endl;
                            if(nSts_sum <= ((-1)*FRAMES_TO_DEFINE_SLEEP))
                            {
                                sts_resultArray[idx2] = -1;
                            }
                            else
                                sts_resultArray[idx2] = 1;
                        }
                        else
                            sts_resultArray[idx2] = 1; // benfit of doubt----
                    cout<< "Array Values at Idx: " << idx2 << "  "<< sts_resultArray[idx2] << endl;
                    }
                    plot_myData(modified_resLabelArr, sts_resultArray, nProcessedFrames, "sts_resultArray");
                    cout<< "nProcessedFrames: "<< nProcessedFrames << endl;
                    free(modified_resLabelArr);
                    free(sts_resultArray);
                    free(result_label_arr);
                }
                else
                { cout<< "\n------------------------------------------------Unable to Read Video " << endl; }

                //cvDestroyWindow("Input_Frame");
                cvReleaseCapture(&capt);
/// ----------------------------------------------------------------------------------------------------------------------------------------------------------------

            } // if(entry->d_type == DT_REG)
        } // while(entry = readdir(dir))
        printf("outside the while loop");

    } // if(dir)
    //closedir(dir);
} // void



///
//  int option;
//                cout << "\nTo read from existing AVI file,  Enter 1: " << endl;
//                cout << "\nTo read from Web Camera,  Enter 2: " << endl;
//                cin >> option;
//
//                switch(option)
//                        {
//                            case 1:
//                            {
//                                capt = cvCaptureFromAVI("/home/naresh/Documents/eyeSts_haarFeat/s4_ha_4.avi");
//                                nTotalFrames_vid = cvGetCaptureProperty(capt, CV_CAP_PROP_FRAME_COUNT);
//                                cout << "Total No of Frames: " << nTotalFrames_vid << endl;
//                                break;
//                            }
//                            case 2:
//                            {
//                                capt  = cvCaptureFromCAM(0);
//                                nTotalFrames_vid = maxNoOfFramesFromWebCam;
//                                cout << "Total No of Frames: " << nTotalFrames_vid << endl;
//                                break;
//                            }
//                            default:
//                                capt = cvCaptureFromAVI("/home/naresh/Documents/desktopPC_Data/Documents/Durga_DataSet/subject 24/happiness/sentence 4/s24_ha_4.avi");
//                        }
//
//
//                char vid_FileName_save[90], dst[90];
//                cout<< "Video_FileName" << endl;
//                cin >> vid_FileName_save;
//                    cout<< "Video_FileName: " << vid_FileName_save << endl;
//
//
//                strcpy(dst, ".avi");
//                strcat(vid_FileName_save, dst);
//                    cout<< "src:  " << vid_FileName_save << endl;
// CvVideoWriter *writer = cvCreateVideoWriter(vid_FileName_save, CV_FOURCC('D','I','V','X'), 15, videoFrameSize, 1);


  //cvReleaseVideoWriter(&writer);

                          /// ------------------------------------  Writing class labels(Text) on Frame ----------------------------------------------------------------->>>>
            //                    char cLabel[15];
            //                    switch(classLabel)
            //                    {
            //                        case 1:
            //                            strcpy(cLabel, "Opened Eyes");
            //                             break;
            //                        case -1:
            //                             strcpy(cLabel, "Closed Eyes");
            //                             break;
            //                        default :
            //                              strcpy(cLabel, "Opened Eyes");
            //                    }
            //
            //                    CvFont font;
            //                    double hScale = 1.0;
            //                    double vScale = 1.0;
            //                    int lineWidth = 2;
            //                    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);
            //                    cvPutText(frame, cLabel, cvPoint(nFrmWidth-(nFrmWidth/3), nFrmHeight-(3*nFrmHeight/4)), &font, cvScalar(0,0,255));
                                ///<<< ------------------------------------ Writing class labels on Frame --------------------------------------------------------------------------

///
//                    int nFrmWidth  = (int)cvGetCaptureProperty(capt, CV_CAP_PROP_FRAME_WIDTH);
//                    int nFrmHeight = (int)cvGetCaptureProperty(capt, CV_CAP_PROP_FRAME_HEIGHT);// CvSize videoFrameSize = cvSize(nFrmWidth, nFrmHeight);
