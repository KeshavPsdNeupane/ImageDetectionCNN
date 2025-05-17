#pragma once
#include<iostream>
#include<memory>
#include<vector>
#include"../FileHandling/File.h"

// U HAVE TO GIVE THE INPUT LAYER SIZE YOURSELF THIS WILL HANDLE ALL THE OTHER HIDDEN AND 
// OUTPUT LAYER
typedef struct lay {
	int size;
	lay(int i = 1): size(i){}
}LayerCountAndSize;


class CNN{
	File file;
	int batchSize, inputSize,hiddenSize, outputSize;
	std::vector<float> input;
	std::vector<std::vector<float>>hiddenWeight;
	std::vector<float> hiddenBias;
	std::vector<std::vector<float>>outputWeight;
	std::vector<float> outputBias;
public:
	CNN(int batchSize,int inputSize,int hiddenSize, int outputSize);
	~CNN();

public:
	void CnnOperate();
private:
	std::vector<float> Convulation(
		std::vector<float>& input,
		std::vector<std::vector<float>>& weight,
		std::vector<float>& bias);
	std::vector<float> ConvulationWithSoftmax(
		std::vector<float>& input,
		std::vector<std::vector<float>>& weight,
		std::vector<float>& bias);
	std::vector<float> CostForSigmoid(
		std::vector<float>result,
		int y);
	std::vector<float> BackPropError(
		const std::vector<std::vector<float>>& currentWeight,
		const std::vector<float>cost);
	std::vector<float> ActivationCost(
		const std::vector<float>& activelayer,
		const std::vector<float>& backPropagationCost);
	void UpdateWeightAndBias(
		std::vector<std::vector<float>>& weight,
		std::vector<float>& bias,
		const std::vector<float>& cost ,
		const std::vector<float>& input);
private:
	inline float Sigmoid(float x) { return 1.0f / (1 + std::exp(-x)); }
	inline float SoftMaxPlusCostDerivative(float x , float y) { return (x-y); }
	inline float SigmoidDerivation(float x) { return x * (1 - x); }
	inline float TotalCost(std::vector<float> result ,  int y){float epsilon = 1e-7f; return -std::log(result[y] + epsilon);}

private:
	void ReadWeightAndBiases(
		const std::string& weight ,
		const std::string& bias);
	void WriteWeightAndBiases(
		const std::string& weight,
		const std::string& bias);
};

