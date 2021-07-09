#include <iostream>
#include <iomanip>
#include <dirent.h>
#include <algorithm>
#include <vector>


typedef struct __dirstream DIR;

inline int Data_collation(std::string dir, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL)
    {
        return -1;
    }

    while ((dirp = readdir(dp)) != NULL) {
        std::string name = std::string(dirp->d_name);

        if(name != "." && name != "..")
            files.push_back(name);
    }
    closedir(dp);


    std::sort(files.begin(), files.end());
    if(dir.at( dir.length() - 1 ) != '/') dir = dir+"/";
    std::string newName;
    std::stringstream name;
    for(unsigned int i=0;i<files.size();i++)
    {
        if(files[i].at(0) != '/')
            files[i] = dir + files[i];

        name.clear();
        name.str("");
        name<<std::setw(6)<<setiosflags(std::ios::right)<<std::setfill('0')<<std::to_string(i);
        name>>newName;
        newName=dir+newName+".jpg";
        std::cout<<"oldName="<<files[i]<<std::endl;
        std::cout<<"newName="<<newName<<std::endl;
        if (!rename(files[i].c_str(), newName.c_str()))
        {
            std::cout << "rename success of "<< i<<std::endl;
        }
        else
        {
            std::cout << "rename error of "<< i<<std::endl;
        }

    }

    return files.size();
}

int main()
{
    std::vector<std::string> files;
    int imagesNums;
    std::string path="/home/wya/Project/Dataset/001/images";
    imagesNums=Data_collation(path,files);
    std::cout<<"images Nums="<<imagesNums<<std::endl;

}