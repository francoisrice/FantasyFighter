#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int size = 56;
//int party_size = ; //start with 1 for now

Sprite f[32]; //figures; this may be unnecessary

int board[10][10] = // generic 10x10 zone with 1 as obstacles
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0,-1, 0, 0, 1, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
	  0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

CircleShape createCharacterIcon() {
	CircleShape shape(60.f);
	shape.setFillColor(Color(0,100,255));
	return shape;
}

RectangleShape createObstacle() {
	RectangleShape rectangle(Vector2f(82,66));
	rectangle.setFillColor(Color(0,0,0));
	return rectangle;
}

void loadCharacterIcon() {
	//return 0;
}

std::string toChessNote(Vector2f p) {
	std::string s = "";
	s += char(p.x/size);
	s += char(p.y/size);
	return s;
}

Vector2f toCoord(char a,char b) {
	//int x = int(a) - 97;
	//int y = 7-int(b)+49;
	
	return Vector2f(a*size,b*size);
}

void move(std::string str) {
	Vector2f oldPos = toCoord(str[0],str[1]);
	Vector2f newPos = toCoord(str[2],str[3]);

	//for(int i=0;i<32;i++)
	//if ( f[i].getPosition()==newPos) f[i].setPosition(-100,-100);
	
	//for(int i=0;i<32;i++)
	//if (f[i].getPosition()==oldPos) f[i].setPosition(newPos);
}

// std::string position="";

// void loadPosition() {
//   int k=0;
//   for(int i=0;i<10;i++)
//     for(int j=0;j<10;j++) {
// 	int n = board[i][j];
// 	if (!n) continue;
// 	int x = abs(n)-1;
// 	int y = n>0?1:0;
// 	f[k].setTextureRect( IntRect(size*x,size*y,size,size) );
// 	f[k].setPosition(size*j,size*i);
// 	k++;
// 	}

// 	for(int i=0;i<position.length();i+=5)
// 	  move(position.substr(i,4));
// }

int main() {
	RenderWindow window(VideoMode(751,751), "Fantasy Fighter!");

	Texture grid; //import character+color?
	grid.loadFromFile("images/grid3.png");

	CircleShape s(36);
	s.setFillColor(Color(0,170,200));

	//loadPosition //place Correct circles and obstacle squares

	bool isMove=false;
	float dx=0, dy=0;
	Vector2f oldPos,newPos;
	std::string str;
	int n=0;

	//Sprite s(t1);
	Sprite sBoard(grid);

	while (window.isOpen()) {
		Vector2i pos = Mouse::getPosition(window);

		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
					if (s.getGlobalBounds().contains(pos.x,pos.y)){
						isMove = true;
						dx=pos.x -s.getPosition().x;
						dy=pos.y -s.getPosition().y;
					}
			if (e.type == Event::MouseButtonReleased)
				if (e.key.code == Mouse::Left)
					isMove=false;
		}

		if (isMove) s.setPosition(pos.x-dx,pos.y-dy);

		//Create the screen
		window.clear();
		window.draw(sBoard);
		window.draw(s);
		window.display();

	}

	return 0;

}