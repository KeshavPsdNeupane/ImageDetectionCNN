#include"File.h"
File::File(){}
File::~File(){}
std::vector<std::vector<float>> File::ReadWeight(const std::string& filePath, int wi, int wj) {
    std::vector<std::vector<float>> weight(wi, std::vector<float>(wj, 0.0f));
    std::ifstream read(filePath);
    if (!read) {
        std::cerr << "Error opening file. for  = " << filePath << "\n";
        std::abort();
    }
    std::string line;
    int rowcount = 0;
    while (std::getline(read, line) && rowcount < wi) {
        std::stringstream ss(line);
        std::string value;
        int colcount = 0;
        while (std::getline(ss, value, ',') && colcount < wj) {
            weight[rowcount][colcount] = std::stof(value);
            ++colcount;
        }
        ++rowcount;
    }
    read.close();
    return weight;
}


// THIS BIAS READS ONLY FOR BIAS MATRIC WITH SIZE 1XN  SINCE ROW IS FIXEL TO 1
std::vector<float> File::ReadBias(const std::string& filePath, int bi) {
    std::vector<float> bias(bi, 0.0f);
    std::ifstream read(filePath);
    if (!read) {
        std::cerr << "Error opening file. for  = " << filePath << "\n";
        std::abort();
    }
    std::string line;
    std::getline(read, line);
    std::stringstream ss(line);
    std::string value;
    int colcount = 0;
    while (std::getline(ss, value, ',') && colcount < bi) {
        bias[colcount] = std::stof(value);
        ++colcount;
    }
    read.close();
    return bias;
}

void File::WriteWeight(
    const std::string& filePath,
    const std::vector<std::vector<float>>& weight) {

    if (weight.empty() || weight[0].empty()) {
        std::cerr << "Weight matrix is empty. for  = " << filePath << "\n";
        std::abort();
    }

    int x = weight.size(), y = weight.at(0).size();
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    std::cout << "coming " << filePath << "\n";
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing. for  = " << filePath << std::endl;
        std::abort();
    }
    for (size_t i = 0; i < x; ++i) {
        for (size_t j = 0; j < y; ++j) {
            outFile << weight[i].at(j);
            if (j != weight[i].size() - 1) {
                outFile << ",";
            }
        }
        outFile << "\n";
    }
}

void File::WriteBias(
    const std::string& filePath,
    const std::vector<float>& bias) {

    if (bias.size() == 0) {
        std::cerr << "bias matrix is empty. for  = " << filePath << "\n";
        std::abort();
    }
    int x = bias.size();
    std::ofstream outFile(filePath, std::ios::out | std::ios::trunc);
    std::cout << "coming " << filePath << "\n";
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing. for  = "<<  filePath  << std::endl;
        std::abort();
    }
    for (size_t i = 0; i < x; ++i) {
        outFile << bias[i];
        if (i != bias.size() - 1) {
            outFile << ",";
        }
    }
    outFile << "\n";
}

void File::PrintW(const std::vector<std::vector<float>>& weight){
    for (int i = 0; i < weight.size(); ++i) {
        for (int j = 0; j < weight[0].size(); ++j) {
            std::cout << weight[i][j] << ",";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void File::PrintB(const std::vector<float>& bias){
    for (int i = 0; i < bias.size(); ++i) {
        std::cout << bias[i] << ",";
    }
    std::cout << "\n";
}
