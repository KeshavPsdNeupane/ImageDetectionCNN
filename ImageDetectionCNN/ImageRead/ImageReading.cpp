#include "ImageReading.h"

ImageReading::ImageReading():
    trainingFolderName(GMNumber::TRAINING_PNG_FOLDER_NAME),
    testFolderName(GMNumber::TEST_PNG_FOLDER_NAME) {
    //std::string testPath = (fs::path(imageFileFolderPath) / this->testFolderName).generic_string();
    //    std::string trainingPath = (fs::path(imageFileFolderPath) / this->trainingFolderName).generic_string();

    //    if (!fs::exists(testPath)) {
    //        std::cerr << "ERROR: Folder does not exist: " << testPath << "\n";
    //        return;
    //    }

    //    std::cout << "test size = " << CountDirectoryPicture(testPath) << "\n";



    //    for (const auto& entry : fs::directory_iterator(testPath)) {
    //        if (entry.path().extension() == ".png") {
    //            sf::Image img;
    //            if (img.loadFromFile(entry.path().string())) {
    //                this->images.push_back(img);

    //                std::string filename = entry.path().stem().string();
    //                std::string labelStr = filename.substr(0, filename.find('_'));
    //                int label = std::stoi(labelStr);

    //                std::cout << "Loaded: " << entry.path().generic_string() << "\n";
    //                std::cout << "Label: " << label << "\n";
    //            }
    //            else {
    //                std::cout << "Failed to load: " << entry.path().generic_string() << "\n";
    //            }
    //        }
    //    }

    //    std::cout << "folder size = " << this->images.size() << "\n";
}



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

ImageData& ImageReading::GetRandomTrainingPicture(){
    assert(!trainData.empty());
    return this->trainData[getRandomInt(0, this->trainData.size() - 1)];
}

ImageData& ImageReading::GetRandomTestPicture(){
    assert(!trainData.empty());
    return this->testData[getRandomInt(0, this->testData.size() - 1)];
}

int ImageReading::getRandomInt(int min, int max) {
    static std::mt19937 gen(std::random_device{}());  // persistent engine
    std::uniform_int_distribution<> dist;             // stateless distribution
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


void ImageReading::LoadImages(const std::string& fullPath, std::vector<ImageData>& data){
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
                data.push_back(ImageData(label, std::move(img), std::move(texture)));
            }
            else {
                std::cout << "Failed to load: " << entry.path().generic_string() << "\n";
            }
        }
    }
    std::cout << "loaded | " << fullPath << " |image data vec folder size = " << data.size() << "\n";
}












