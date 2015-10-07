#include "headers.h"
#include "cvplot.h"
//CvHaarClassifierCascade *cascade_Single_Eye1;
static void print_InfoOnConsole();

int main(int argc, char **argv)
{
//    IplImage* dst = cvLoadImage("divya_124.png");  //    IplImage* dst = cvLoadImage("ankit.png");//    IplImage* dst  = cvLoadImage("vamsi_115.png");
//    IplImage* dst  = cvLoadImage("ramana_036.png");//    IplImage* dst  = cvLoadImage("samata_469.png"); //    IplImage* dst  = cvLoadImage("rohit_006.png");
//    cout << "Ip_width : " << dst->width << "  height : " << dst->height << endl; //cvNamedWindow( "Display window", CV_WINDOW_AUTOSIZE );imshow( "Display window", dst);waitKey(0);
    print_InfoOnConsole();
    //cout<< "Hai Surya..... Entered into Main Fn"  << endl;
    //cout<< "Label:  Eye_Open : +1, Eye_Close: -1"   << endl;
    printf("===============================================================================\n");

//    char *folderPath = argv[1]; //"/home/naresh/Documents/videosOffice/";
//    char *folderPath;
//    cout << "Enter folder Name..." << endl;
//    cin >> folderPath;
///===============================================================================

//    CvCapture* cap  = cvCaptureFromCAM(0);
//    if(cap)
//    {
//        while(1)
//        {
//            IplImage *frame = cvQueryFrame(cap);
//            //cvNamedWindow("Input_Frame", )
//            cvShowImage( "Input_Frame", frame);cvWaitKey(0);
//        }
//    }
//    else
//    printf("No cap :");

///===================== Video =====================================================
//    char *videoFolderPath = "/home/naresh/Documents/videosOffice/";
//    cout<< "Hai Surya..... Entered into Main Fn"  << endl; cout<< "Folder Path is: " << videoFolderPath <<endl;
//    readVideosFromFolderAndWriteFinalResultIntoTextFile(videoFolderPath);
    ///================= Video <<< =================================================
///===================== From Imgs=====================================================
    //char *imgFolderPath = "/home/naresh/Downloads/dataset_B_FacialImages_highResolution/";
    char *imgFolderPath = "/home/naresh/Documents/rupesh/open/";
    readImgesFromFolderAndWriteFinalResultIntoTextFile(imgFolderPath);
    printf("============================================================================\n");
///===================== From Imgs <<<<================================================
return 0;
}

static void print_InfoOnConsole()
{
    printf("============================================================================\n");
    printf("                   |  Author       : Naresh A.                           |\n  "
           "                 |  Organisation : SRM-RI @ Bangalore.                 |\n  "
           "                 |  Student Status(Watching a Video/Sleeping) Recognition |\n"
           );
    printf("=============================================================================\n");
}

