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

std::vector<float> File::ReadCost(const std::string& filePath){
    std::vector<float> cost;
    std::ifstream read(filePath);
    if (!read) {
        std::cerr << "Error opening file. for  = " << filePath << "\n";
        std::abort();
    }
    std::string line;
    std::getline(read, line);
    std::stringstream ss(line);
    std::string value;
    while (std::getline(ss, value, ',')) {
        cost.push_back(std::stof(value));
    }
    read.close();
    return cost;
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
   // std::cout << "coming " << filePath << "\n";
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing. for  = " << filePath << std::endl;
        std::abort();
    }
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
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
  //  std::cout << "coming " << filePath << "\n";
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing. for  = "<<  filePath  << std::endl;
        std::abort();
    }
    for (int i = 0; i < x; ++i) {
        outFile << bias[i];
        if (i != bias.size() - 1) {
            outFile << ",";
        }
    }
    outFile << "\n";
}

void File::WriteCostToFIle(
    const std::string& filePath,
    const std::vector<float>& cost){
    if (cost.size() == 0) {
        std::cerr << "bias matrix is empty. for  = " << filePath << "\n";
        std::abort();
    }
    int x = cost.size();
    std::ofstream outFile(filePath, std::ios::out | std::ios::app);
    std::cout << "coming " << filePath << "\n";
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing. for  = " << filePath << std::endl;
        std::abort();
    }
    for (int i = 0; i < x; ++i) {
        outFile << cost[i];
        if (i != cost.size() - 1) {
            outFile << ",";
        }
    }
}

ItandLearn File::ReadLearnRate(const std::string& filePath){
    std::ifstream read(filePath);
    std::string buf;
    long itera = 0;
    float rate = 0.01f;
    if (!read.is_open()) {
        std::cout << "Unable to read learn rate\n";
        std::abort();
    }
    read >> buf >> itera;
    read >> buf >> rate;
    return ItandLearn(itera,rate);
}

void File::WriteLearnRate(const std::string& filePath, ItandLearn itAndLearn){
    std::ofstream read(filePath);
    std::string buf = "Iteration= ";
    std::string buf2 = "LearnRate= ";
    if (!read.is_open()) {
        std::cout << "Unable to write learn rate\n";
        std::abort();
    }
    read << buf << itAndLearn.iteration << "\n";
    read << buf2 << itAndLearn.learnRate;
}

void File::PrintW(const std::vector<std::vector<float>>& weight){
    for (unsigned int i = 0; i < weight.size(); ++i) {
        for (unsigned int j = 0; j < weight[0].size(); ++j) {
            std::cout << weight[i][j] << ",";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void File::PrintB(const std::vector<float>& bias){
    for (unsigned int i = 0; i < bias.size(); ++i) {
        std::cout << bias[i] << ",";
    }
    std::cout << "done\n";
}
