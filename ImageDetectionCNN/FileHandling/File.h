#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include<string>
#include<fstream>
#include<sstream>

struct ItandLearn {
	long iteration;
	float learnRate;
public:
	ItandLearn() : iteration(0), learnRate(0.0f) {}
	ItandLearn(long it, float lr) : iteration(it), learnRate(lr) {}

};


class File{
public:
	File();
	~File();
public:
	std::vector<std::vector<float>> ReadWeight(const std::string& filePath,int wi ,int wj);
	std::vector<float> ReadBias(const std::string& filePath , int bi);
	std::vector<float> ReadCost(const std::string& filePath);
	void WriteWeight(
		const std::string& filePath,
		const std::vector<std::vector<float>>& weight);
	void WriteBias(
		const std::string& filePath ,
		const std::vector<float>& bias);
	void WriteCostToFIle(
		const std::string& filePath,
		const std::vector<float>& cost);
	ItandLearn ReadLearnRate(const std::string& filePath);
	void WriteLearnRate(const std::string& filePath, ItandLearn itAndLearn);
public:
	void PrintW(const std::vector<std::vector<float>>& weight);
	void PrintB(const std::vector<float>& bias);
};

