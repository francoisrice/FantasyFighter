#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main() {
	RenderWindow window(VideoMode(453,453), "Fantasy-Fighter!");

	Texture grid;
	grid.loadFromFile("images/grid.png");

	//Sprite s(t1);
	Sprite sBoard(grid);

	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}

		//Create the screen
		window.clear();
		window.draw();
		window.display();

	}
}