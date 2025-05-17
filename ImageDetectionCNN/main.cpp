#include"CnnRunner.h"
#include"CNN/CNN.h"
#include"ImageRead/ImageReading.h"
int main(){

    CnnRunner c;
    c.Run();





    //const std::string& path = GMNumber::PICTURE_DOCKER_PATH;
    //CNN c(1, 784, 100, 10);
    //c.CnnOperate();
	/*ImageReading img;
	img.LoadTestPictures(path);
	img.LoadTrainingPictures(path);



	for (size_t i = 0; i < 40; i++){
		ImageData test = img.GetRandomTestPicture();
		ImageData train = img.GetRandomTrainingPicture();
		std::cout << "Test = " << test.result << " | Train = " << train.result << "\n";
	}*/

}





// simple code to make a graph
/*    sf::RenderWindow window(sf::VideoMode(800, 600), "Simple SFML Graph");
    // Sample data points (y-values)
    std::vector<float> data = { 100, 150, 200, 180, 220, 300, 280, 320, 270, 250 };

    // Scale factors to fit graph in window
    float xSpacing = 70.f;
    float yScale = 1.f;

    // Create vertex array for the line strip
    sf::VertexArray lines(sf::LineStrip, data.size());

    for (size_t i = 0; i < data.size(); ++i) {
        float x = 50 + i * xSpacing;          // x position with some margin
        float y = 550 - data[i] * yScale;     // y inverted to draw upwards, margin at bottom
        lines[i].position = sf::Vector2f(x, y);
        lines[i].color = sf::Color::Green;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(lines);
        window.display();
    }

    return 0;


*/