#include "headers.h"
#include <dirent.h>

#define IMG_FILENAME_LENGTH 200
void writeIntoTextFile(char *, int );


static int count=0;
void readImgesFromFolderAndWriteFinalResultIntoTextFile(char *folderPath)
{
    //cout << "Folder Path: " << folderPath << endl;
    int count =0;
    DIR *dir;
    char ImgName[IMG_FILENAME_LENGTH] = "";
    char ImgName2[IMG_FILENAME_LENGTH] = "";
    struct dirent *entry;
    dir = opendir(folderPath);
    if(dir != NULL)
    {
        while(entry = readdir(dir))
        {
            ImgName[IMG_FILENAME_LENGTH]='\0';
            ImgName2[IMG_FILENAME_LENGTH]='\0';
            char temp[IMG_FILENAME_LENGTH] = "";
            if(entry->d_type == DT_REG)
            {
                //cout << "entry->d_type  is " <<entry->d_type  << endl;
                int classLabel = 0;
                strcpy(ImgName, entry->d_name);
                strcpy(ImgName2, entry->d_name);
               // strcpy(temp,"/home/naresh/Documents/videosOffice/");
                strcpy(temp,folderPath);
                strcat(temp,ImgName);

                strcpy(ImgName,temp);
                    //cout << "temp is " << ImgName2 << endl;
                IplImage *inImg = cvLoadImage(temp);
                //cvShowImage("imp",inImg);

                //cvWaitKey(0);
                if(inImg)
                {

                    //cvShowImage("1", inImg); cvWaitKey(0);
                    /// ==========================================================||
                    classLabel = test_getClassLabelFromGivenImg(inImg);       /// ||
                    /// ==========================================================||
                    cout << "classLabel: " << classLabel << endl;

                    cv::FileStorage fs("result.txt", FileStorage::APPEND);
                    if (!fs.isOpened())
                        std::cout << "unable to open file for storing Results!" << std::endl;
                    else
                    {
                        fs << "Image" << ImgName2 << "Class" << classLabel;
                        // std::cout << "Results are stored" << std::endl;
                    }
                    count++;
                }
            }
        }
         //printf("count ___________________________%d", count);
    }
    closedir(dir);

}

void writeIntoTextFile(char *imgName, int classLabel)
{

    //remove(testImgPath);/////Removing/Deleting an Img, after writing the Emotion into a Text file
}
