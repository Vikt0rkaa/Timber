#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
	// Create a video mode object with the desired resolution
	VideoMode vm({ 1920, 1080 });
	RenderWindow window(vm, "Timber!!!", State::Fullscreen);

	// Load a background texture and create a sprite for it
	Texture textureBackground;
	if (!textureBackground.loadFromFile("graphics/background.png")) {
		std::cout << "Error loading background texture" << std::endl;
		return 1;
	}
	Sprite spriteBackground(textureBackground);
	spriteBackground.setPosition({0, 0});

	// Load a tree texture and create a sprite for it
	Texture textureTree;
	if (!textureTree.loadFromFile("graphics/tree.png")) {
		std::cout << "Error loading tree texture" << std::endl;
		return 1;
	}
	Sprite spriteTree(textureTree);
	spriteTree.setPosition({810, 0});

	// Load a bee texture and create a sprite for it
	Texture textureBee;
	if (!textureBee.loadFromFile("graphics/bee.png")) {
		std::cout << "Error loading bee texture" << std::endl;
		return 1;
	}
	Sprite spriteBee(textureBee);
	spriteBee.setPosition({0, 800});

	// Is the bee moving?
	bool beeActive = false;
		
	// How fast can the bee fly
	float beeSpeed = 0.0f;

	// Load a cloud texture and create sprites for it
	Texture textureCloud;
	if (!textureCloud.loadFromFile("graphics/cloud.png")) {
		std::cout << "Error loading cloud texture" << std::endl;
		return 1;
	}
	Sprite spriteCloud1(textureCloud);
	Sprite spriteCloud2(textureCloud);
	Sprite spriteCloud3(textureCloud);
	spriteCloud1.setPosition({ 0, 0 });
	spriteCloud2.setPosition({ 0, 250 });
	spriteCloud3.setPosition({ 0, 500 });

	// Are the clouds currently on the screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	// How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Create a clock to track the time
	Clock clock;

	// Create a rectangle shape to represent the time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize({ timeBarStartWidth, timeBarHeight });
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition({ (1920 / 2) - timeBarStartWidth / 2, 980 });

	// Create a variable to track the total game time
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Pause the game when it starts
	bool paused = true;

	// Create a variable to track the score
	int score = 0;

	// Create a font and load it from a file
	Font font;
	if (!font.openFromFile("fonts/KOMIKAP_.ttf")) {
		std::cout << "Error loading font" << std::endl;
		return 1;
	}

	Text messageText(font);
	Text scoreText(font);
	messageText.setFont(font);
	scoreText.setFont(font);

	messageText.setString("Press Enter to start!");
	scoreText.setString("Score: 0");

	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);	

	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin({ textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f });
	messageText.setPosition({1920 / 2.0f, 1080 / 2.0f});
	scoreText.setPosition({ 20, 20 });


	while (window.isOpen()) {

		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
			window.close();
		}

		if(Keyboard::isKeyPressed(Keyboard::Key::Enter)) {
			paused = false;
			score = 0;
			timeRemaining = 6.0f;
		}

		if (!paused) {
			//Measure time
			Time dt = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();

			// Resize the time bar
			timeBar.setSize({ timeRemaining * timeBarWidthPerSecond, timeBarHeight });

			// Has the player run out of time?
			if (timeRemaining <= 0.0f) {
				paused = true;
				messageText.setString("Out of time!");

				// Recenter the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin({ textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f });
				messageText.setPosition({1920 / 2.0f, 1080 / 2.0f});
			}

			//set up the bee
			if (!beeActive) {
				// How fast is the bee?
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200;

				// How high is the bee?
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition({ 2000, height });
				beeActive = true;

			}
			else {
				// Move the bee
				spriteBee.setPosition({ spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y });

				// Has the bee reached the left-hand edge of the screen?
				if (spriteBee.getPosition().x < -100) {
					beeActive = false;
				}
			}

			if (!cloud1Active) {
				// How fast is the cloud?
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				// How high is the cloud?
				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloud1.setPosition({ -200, height });
				cloud1Active = true;
			}
			else {
				// Move the cloud
				spriteCloud1.setPosition({ spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y });

				// Has the cloud reached the left-hand edge of the screen?
				if (spriteCloud1.getPosition().x > 1920) {
					cloud1Active = false;
				}
			}

			if (!cloud2Active) {

				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);


				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloud2.setPosition({ -200, height });
				cloud2Active = true;
			}
			else {

				spriteCloud2.setPosition({ spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y });

				if (spriteCloud2.getPosition().x > 1920) {
					cloud2Active = false;
				}
			}

			if (!cloud3Active) {

				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloud3.setPosition({ -200, height });
				cloud3Active = true;

			}
			else {
				spriteCloud3.setPosition({ spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y });
				if (spriteCloud3.getPosition().x > 1920) {
					cloud3Active = false;
				}
			}

			// Update the score text
			std::stringstream ss;
			ss << "Score: " << score;
			scoreText.setString(ss.str());
		}

		window.clear();
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteTree);
		window.draw(spriteBee);
		window.draw(scoreText);
		window.draw(timeBar);
		if (paused) {
			window.draw(messageText);
		}
		window.display();


	}


	return 0;
}