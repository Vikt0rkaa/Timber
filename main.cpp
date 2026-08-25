#include <iostream>
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

	while (window.isOpen()) {

		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
			window.close();
		}
		window.clear();
		window.draw(spriteBackground);
		window.draw(spriteTree);
		window.display();


	}


	return 0;
}