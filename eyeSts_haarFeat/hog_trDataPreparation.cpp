#include "headers.h"



void hog_trDataPreparation()
{
    IplImage *ipImg;
/// HOG Feature extraction from Neg DataSet=========>>>>>>>>>>
    cv::Mat hog_negFVData;
    hog_negFVData.create(324, 1, CV_32FC1); // 9*3*3*4 = 324

    hog_negFVData = Mat::zeros(324, 1, CV_32FC1);
    int i;
    for (i = 1; i < 1331 ; i++) // Not using PGM imgs for training
    {
        char path[98] = "/home/naresh/Documents/eyeSts_haarFeat/negImgs_Hog_gray/neg_hog_gray_";

        char num[4] = {};
        sprintf(num, "%d", i);

        strcat(path, num);

        char path1[98] = {};

        strcpy(path1, path);
        strcat(path1, ".png");

        cout<< "No: " << path1 << endl;
        ipImg = cvLoadImage(path1, CV_LOAD_IMAGE_GRAYSCALE);

        cv::Mat h1 =  hogFv(ipImg);
        hconcat(hog_negFVData,h1,hog_negFVData);
        cout<< "No: " << i << endl;
    }
    cv::Mat h_neg = hog_negFVData.colRange(Range(1, i));
    cv::FileStorage hog_negXmlFile("hog_neg_filt_data.xml", cv::FileStorage::WRITE);
    hog_negXmlFile << "hogFeat_negData" <<  h_neg;


/// HOG Feature extraction from Pos DataSet=========>>>>>>>>>>
    cv::Mat hog_posFVData;
    hog_posFVData.create(324, 1, CV_32FC1); // 9*3*3*4 = 324

    hog_posFVData = Mat::zeros(324, 1, CV_32FC1);
    int j;
    for (j = 1; j < 1331 ; j++) // Not using PGM imgs for training
    {
        char path[98] = "/home/naresh/Documents/eyeSts_haarFeat/pos_hog_gray/pos_Hog_gray_";

        char num[4]   = {};
        sprintf(num, "%d", j);
        strcat(path, num);
        char path1[98] = {};
        strcpy(path1, path);
        strcat(path1, ".png");

        cout<< "No: " << path1 << endl;
        ipImg = cvLoadImage(path1, CV_LOAD_IMAGE_GRAYSCALE);

        cv::Mat h1 =  hogFv(ipImg);
        hconcat(hog_posFVData,h1,hog_posFVData);
        cout<< "No: " << j << endl;
    }
    cv::Mat h_pos = hog_posFVData.colRange(Range(1, j));
    cv::FileStorage hog_posXmlFile("hog_pos_filt_data.xml", cv::FileStorage::WRITE);
    hog_posXmlFile << "hogFeat_posData" <<  h_pos;
}
