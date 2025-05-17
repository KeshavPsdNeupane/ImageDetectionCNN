#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include<string>
#include<fstream>
#include<sstream>
class File{
public:
	File();
	~File();
public:




	std::vector<std::vector<float>> ReadWeight(const std::string& filePath,int wi ,int wj);
	std::vector<float> ReadBias(const std::string& filePath , int bi);
	void WriteWeight(
		const std::string& filePath,
		const std::vector<std::vector<float>>& weight);
	void WriteBias(
		const std::string& filePath ,
		const std::vector<float>& bias);



public:
	void PrintW(const std::vector<std::vector<float>>& weight);
	void PrintB(const std::vector<float>& bias);
};

