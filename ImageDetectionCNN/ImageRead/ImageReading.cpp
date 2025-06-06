#include "ImageReading.h"

ImageReading::ImageReading():
    trainingFolderName(GMNumber::TRAINING_PNG_FOLDER_NAME),
    testFolderName(GMNumber::TEST_PNG_FOLDER_NAME) {}



ImageReading::~ImageReading(){}

void ImageReading::LoadTestPictures(const fs::path& dirPath){
    std::string testPath = (fs::path(dirPath) / this->testFolderName).generic_string();
    if (!fs::exists(testPath)) {
        std::cerr << "ERROR: Folder does not exist: " << testPath << "\n";
        return;
    }
    int size = CountDirectoryPicture(testPath);
    this->testData.reserve(size);
    LoadImages(testPath, this->testData);
}

void ImageReading::LoadTrainingPictures(const fs::path& dirPath){
    std::string testPath = (fs::path(dirPath) / this->trainingFolderName).generic_string();
    if (!fs::exists(testPath)) {
        std::cerr << "ERROR: Folder does not exist: " << testPath << "\n";
        return;
    }
    int size = CountDirectoryPicture(testPath);
    this->testData.reserve(size);
    LoadImages(testPath, this->trainData);
}

std::shared_ptr<ImageData> ImageReading::GetRandomTrainingPicture(){
    assert(!this->trainData.empty());
    return this->trainData[getRandomInt(0, this->trainData.size() - 1)];
}

std::shared_ptr<ImageData> ImageReading::GetRandomTestPicture(){
    assert(!this->testData.empty());
    return this->testData[getRandomInt(0, this->testData.size() - 1)];
}

int ImageReading::getRandomInt(int min, int max) {
    static std::mt19937 gen(std::random_device{}()); 
    std::uniform_int_distribution<> dist;
    return dist(gen, decltype(dist)::param_type{min, max});
}

int ImageReading::CountDirectoryPicture(const fs::path& folderPath){
    int count = std::count_if(
        fs::directory_iterator(folderPath),
        fs::directory_iterator(),
        [](const fs::directory_entry& entry) {
            return entry.is_regular_file() && entry.path().extension() == ".png";
        }
    );
    return count;
}


void ImageReading::LoadImages(const std::string& fullPath, std::vector<std::shared_ptr<ImageData>>& data){
    for (const auto& entry : fs::directory_iterator(fullPath)) {
        if (entry.path().extension() == ".png") {
            sf::Image img;
            if (img.loadFromFile(entry.path().string())) {
                // need to be here cant be made into a helper func
                std::string filename = entry.path().stem().string();
                std::string labelStr = filename.substr(0, filename.find('_'));
                int label = std::stoi(labelStr);
                sf::Texture texture;
                texture.loadFromImage(img);
                std::vector<float> pixelValues = ConvertImgToVector(img);
                data.push_back(std::make_shared<ImageData>(ImageData(label, std::move(pixelValues), std::move(texture))));
            }
            else {
                std::cout << "Failed to load: " << entry.path().generic_string() << "\n";
            }
        }
    }
 
    std::cout << "loaded | " << fullPath << " |image data vec folder size = " << data.size() << "\n";
}

std::vector<float> ImageReading::ConvertImgToVector(sf::Image& img){
    sf::Vector2u sizes = img.getSize();
    std::vector<float> val;
    val.reserve(sizes.x * sizes.y);
    for (unsigned int i = 0; i < sizes.x; ++i) {
        for (unsigned int j = 0; j < sizes.y; ++j) {
            const sf::Color& c = img.getPixel(i, j);
            float combined = (float(c.r) + float(c.g) + float(c.b)) / (255.0f + 255.0f + 255.0f);
            val.push_back(combined);
        }
    }
    return val;
}












