# include "headers.h"



int findFvClass_Hog_Svm(cv::Mat testFvInPut)
{

    int testLabel;
    cv::Mat testImgFv  = testFvInPut.t();/// Matrix Transpose...

    testImgFv.convertTo(testImgFv, CV_32FC1);
    CvMat testFv = testImgFv;

    CvSVM eyeStsSVM_hog;

    eyeStsSVM_hog.load("hog_svm_RBF_model.xml",0);
    float label =  eyeStsSVM_hog.predict(&testFv);
    printf("Class : %f\n", label);

    if ((int)label == -1) // OPEN  Eye............
    testLabel = -1;
    if ((int)label ==  1) // Close Eye............
    testLabel = 1;

    return testLabel;
}
