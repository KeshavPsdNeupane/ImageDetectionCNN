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
   std::vector<std::shared_ptr<ImageData>> testData;
   std::vector<std::shared_ptr<ImageData>> trainData;



public:
	ImageReading();
	~ImageReading();

public:
	void LoadTestPictures(const fs::path& dirPath);
	void LoadTrainingPictures(const fs::path& dirPath);


	std::shared_ptr<ImageData> GetRandomTrainingPicture();
	std::shared_ptr<ImageData> GetRandomTestPicture();

private:
	int getRandomInt(int min, int max);
	int CountDirectoryPicture(const fs::path& folderPath);
	void LoadImages(const std::string& fullPath, std::vector<std::shared_ptr<ImageData>>& data);
	std::vector<float> ConvertImgToVector(sf::Image& img);


};
