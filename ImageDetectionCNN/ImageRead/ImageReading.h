#pragma once  
#include<iostream>  
#include<filesystem>  
#include"FileStruct.h"  
#include<string>
#include<random>
#include<assert.h>

namespace fs = std::filesystem;

class ImageReading{  
   const std::string& trainingFolderName;
   const std::string& testFolderName;
   std::vector<ImageData> testData;
   std::vector<ImageData> trainData;



public:
	ImageReading();
	~ImageReading();

public:
	void LoadTestPictures(const fs::path& dirPath);
	void LoadTrainingPictures(const fs::path& dirPath);


	ImageData& GetRandomTrainingPicture();
	ImageData& GetRandomTestPicture();

private:
	int getRandomInt(int min, int max);
	int CountDirectoryPicture(const fs::path& folderPath);
	void LoadImages(const std::string& fullPath, std::vector<ImageData>& data);

};
