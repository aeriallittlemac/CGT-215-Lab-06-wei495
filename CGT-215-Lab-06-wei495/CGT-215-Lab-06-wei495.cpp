#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int main() {
	string background = "images1/backgrounds/alebrije.png"; //path to background
	string foreground = "images1/characters/yoda.png"; //path to foreground
	Texture backgroundTex;
	if (!backgroundTex.loadFromFile(background)) { //loading in the background
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}
	Texture foregroundTex;
	if (!foregroundTex.loadFromFile(foreground)) {//loading in the foreground
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}
	Image foregroundImage;
	foregroundImage = foregroundTex.copyToImage(); //image object is made for foreground to analyze
	Vector2u sz = foregroundImage.getSize();
	for (int y = 0; y < sz.y; y++) {
		for (int x = 0; x < sz.x; x++) {
			
				Color c = foregroundImage.getPixel(x, y);
				int green = foregroundImage.getPixel(foregroundImage.getSize().x - 1, foregroundImage.getSize().y - 1).toInteger(); //taking a corner of the foreground to obtain the target green color
				if (c.toInteger() == green) {
					c.a = 0; //setting any green pixel to an alpha of 0
				}
				
				foregroundImage.setPixel(x, y, c); //apply pixel to image
		}
	}
	RenderWindow window(VideoMode(1024, 768), "Here's the output");
	Sprite sprite;
	sprite.setTexture(backgroundTex); //use the background texture
	window.clear();
	window.draw(sprite);

	Sprite sprite1;
	Texture tex1;
	tex1.loadFromImage(foregroundImage); //new foreground texture loaded from modified image
	sprite1.setTexture(tex1); //use the modified foreground texture
	window.draw(sprite1); //foreground image draws on top of background image without clearing


	window.display();
	while (true);
}