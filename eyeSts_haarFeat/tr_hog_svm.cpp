#include "headers.h"


cv::Mat loadFromDataMat1(char *);
cv::Mat loadFromDataMat2(char *);


/// Training with SVM=============>>>>

void training_Hog_Svm()
{
    /// loading data from here...............
    cv::Mat openEyeTrDataMat  = loadFromDataMat1("hog_pos_fil_data.xml");
    cv::Mat closeEyeTrDataMat = loadFromDataMat2("hog_neg_fil_data.xml");
    /// Training start from here..............
    int nFvLength = openEyeTrDataMat.rows;

    cv::Mat trainData[2];
    trainData[0] = openEyeTrDataMat.t();
    trainData[1] = closeEyeTrDataMat.t();

    trainData[0].convertTo(trainData[0],CV_32FC1);
    trainData[1].convertTo(trainData[1],CV_32FC1);


    cv::Mat curTrainData ;
    cv::Mat curTrainLabel ;

    curTrainData.create(trainData[0].rows + trainData[1].rows, nFvLength , CV_32FC1);
    curTrainLabel.create(curTrainData.rows, 1, CV_32FC1);
    cv::vconcat(trainData[0],trainData[1],curTrainData);

    Mat class1Labels;
    Mat class2Labels;

    class1Labels = Mat::ones(trainData[0].rows, 1, CV_32FC1)*1;
    class2Labels = Mat::ones(trainData[1].rows, 1, CV_32FC1)*-1;

    cv::vconcat(class1Labels, class2Labels,curTrainLabel);
    curTrainLabel;

    /// SVM RBF Parameter settings ======>>>>
    CvSVMParams svmRBF_Param;

    svmRBF_Param.svm_type      = CvSVM::C_SVC;
    svmRBF_Param.kernel_type   = CvSVM::SIGMOID;
    svmRBF_Param.gamma         = 20;
    svmRBF_Param.term_crit     = cvTermCriteria(CV_TERMCRIT_ITER, 100, 1e-6);
    /// SVM RBF Parameter settings <<<<<=====

    CvSVM  eyeStatusSVM_hog;
    eyeStatusSVM_hog.train_auto(curTrainData, curTrainLabel, Mat(), Mat(), svmRBF_Param,10);
   //eyeStatusSVM_hog.train(curTrainData, curTrainLabel, Mat(), Mat(), svmRBF_Param);
    int noOfSupportVec = 0;
    noOfSupportVec     = eyeStatusSVM_hog.get_support_vector_count(); printf("eyeStatusSVM__noOfSupportVect:\t%d\n",noOfSupportVec);

    eyeStatusSVM_hog.save("hog_svm_sigmoidCV_model.xml");
}

///=================================================================================================
cv::Mat loadFromDataMat1(char * fileName)
{

   cv::Mat trDataMatrix_OpenEyes;
   cv::FileStorage fs;

   fs.open(fileName, FileStorage::READ);
   if (!fs.isOpened())
   {
      std::cout << "unable to open file for reading featureVect!" << std::endl;
   }
   else
      fs["hogFeat_posData"] >> trDataMatrix_OpenEyes;
   fs.release();
   return trDataMatrix_OpenEyes;
}
///=================================================================================================
cv::Mat loadFromDataMat2(char * fileName)
{

   cv::Mat trDataMatrix_closeEyes;
   cv::FileStorage fs;

   fs.open(fileName, FileStorage::READ);
   if (!fs.isOpened())
   {
      std::cout << "unable to open file for reading featureVect!" << std::endl;
   }
   else
      fs["hogFeat_negData"] >> trDataMatrix_closeEyes;
   fs.release();
   return trDataMatrix_closeEyes;

}
