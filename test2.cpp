#include <SFML/Graphics.hpp> // All major graphics functions
#include <time.h>
#include <stdlib.h> //rand()
#include <iostream> //cout (for debugging)
using namespace sf;

int size = 75; // the pixel size of each square

//int party_size = ; //start with 1 for now

//Features of the map; in the future these will all be in the same object

//int creature_num = 2;
//CircleShape f[creature_num];
CircleShape f[2]; //figures for character and enemy

//int obstacle_num = 7;
//CircleShape obstacles[obstacle_num];
RectangleShape obstacles[7]; // store obstacle rectangles and their position

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

// void countMap(int board[10][10], int& party_size, int& obstacle_num, int& enemy_count) {
// 	//Want to get all information from the map, after the first pass through
// 	//Since C++ can't pass multiple variables as return parameters (at least before
// 	// C++11), the values we need must be passed by reference as with pointers

// 	// int obstacle_num=0;
// 	// int enemy_count=0;
// 	// int party_size=0;
// 	for(int i=0;i<10;i++)
// 		for(int j=0;j<10;j++) {
// 			int n = board[i][j];
// 			obstacle_num += n==1?1:0;
// 			enemy_count += n<0?1:0;
// 			party_size += n>=2?1:0;
// 		}
// 	//return party_size,obstacle_num,enemy_count 
// }


CircleShape createCharacterIcon(int red,int green,int blue) {
	CircleShape shape(36);
	shape.setFillColor(Color(0,100,255));
	//shape.setFillColor(Color(red,green,blue)); // when creating shapes from character profiles
	return shape;
}

RectangleShape createObstacle() {
	RectangleShape rectangle(Vector2f(75,75));
	rectangle.setFillColor(Color(0,0,0));
	return rectangle;
}

void startingPosition() {
	int k=0;
	int ob=0;
  	for(int i=0;i<10;i++)
	    for(int j=0;j<10;j++) {
		int n = board[i][j];
		if (!n) continue;
		if (n>=2) {
			//place character
			f[k].setRadius(36);
			f[k].setFillColor(Color(0,170,200));
			f[k].setPosition(size*j+2,size*i+2);
			k++;
		}
		if (n==1) {
			//generate obstacle
			obstacles[ob].setSize(Vector2f(75,75));
			obstacles[ob].setFillColor(Color(0,0,0));
			obstacles[ob].setPosition(size*j+2,size*i+2);
			ob++;
		}
		if (n<0) {
			//place enemy
			f[k].setRadius(36);
			f[k].setFillColor(Color(229,142,29));	
			f[k].setPosition(size*j+2,size*i+2);
			k++;
		}
	}
}

// void loadPosition() { 
// //Use this to load obstacles and players
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

void loadCharacterIcon() {
	//return 0;
}

int vect2Coord(Vector2f p, Vector2f q) {
	int s[4];
	s[0] = p.x-2/size;
	s[1] = p.y-2/size;
	s[2] = q.x-2/size;
	s[3] = q.y-2/size;
	return s;
}

std::string position="";

int s[4];

Vector2f coord2Vect(int a,int b) {
	return Vector2f(a*size+2,b*size+2);
}

void move(int arr[4]) {
	Vector2f oldPos = coord2Vect(arr[0],arr[1]);
	Vector2f newPos = coord2Vect(arr[2],arr[3]);

	//for(int i=0;i<32;i++)
	//if ( f[i].getPosition()==newPos) f[i].setPosition(-100,-100); // capturing chess pieces
	
	//for(int i=0;i<32;i++)
	//if (f[i].getPosition()==oldPos) f[i].setPosition(newPos); // For when erasing moves
}

int main() {
	RenderWindow window(VideoMode(751,751), "Fantasy Fighter!");



	Texture grid; //import character+color?
	grid.loadFromFile("images/grid3.png");

	//CircleShape f[0](36);
	//f[0].setFillColor(Color(0,170,200));

	//CircleShape f[1](36);
	//f[1].setFillColor(Color(229,142,29));	

	//loadPosition //place Correct circles and obstacle squares

	// int party_size, int obstacle_num, int enemy_count
	// int* ps = &party_size;
	// int* obn = &obstacle_num;
	// int* ec = &enemy_count; 
	// countMap(board,*ps,*obn,*ec);

	// RectangleShape obstacles[obstacle_num-1];
	// Vector2f noGoes[obstacles_num-1];

	startingPosition();

	bool isMove=false;
	float dx=0, dy=0;
	Vector2f oldPos,newPos;
	std::string str;
	int n=0;

	//Sprite s(t1);
	Sprite sBoard(grid);
	//while (e.key.code!=Keyboard::C || ){
		while (window.isOpen()) {
			Vector2i pos = Mouse::getPosition(window);

			Event e;

			//For multiple characters
			//  for(z=0;z<1;z++){
			//  int z = rand(initiative_list)[k] // psuedocode
			// int z = 0;
			// while(newPos==startPos){
			// for(int z=0;z<1;z++){
			// 	if (yourTurn){
			// 		z=1;
			// 	} else {
			// 		z=0;
			// 	}
			while (window.pollEvent(e)) {
				if (e.type == Event::Closed)
					window.close();

				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
						//for(int i=0;i<2;i++){
							if (f[1].getGlobalBounds().contains(pos.x,pos.y)){
								isMove = true; //n=z;
								dx=pos.x -f[1].getPosition().x;
								dy=pos.y -f[1].getPosition().y;
								oldPos = f[1].getPosition();
							}
						//}
				if (e.type == Event::MouseButtonReleased)
					if (e.key.code == Mouse::Left){
						isMove=false;
						Vector2f p = f[1].getPosition() + Vector2f(37,37); //Vector2f(size/2,size/2);
						newPos = Vector2f(75*int(p.x/75)+2, 75*int(p.y/75)+2);
						s[0] = oldPos.x-2/size;
						s[1] = oldPos.y-2/size;
						s[2] = newPos.x-2/size;
						s[3] = newPos.y-2/size;
						move(s);
						f[1].setPosition(newPos);
					}
			}

			// Perform enemy actions (and ally actions)
			if (Keyboard::isKeyPressed(Keyboard::Space)){
				s = "1214";
				s[0] = oldPos.x-2/size; // This is the only problem...
				s[1] = oldPos.y-2/size; //   any one move takes an entire array[4]
				s[2] = newPos.x-2/size;
				s[3] = newPos.y-2/size;
				oldPos = Vector2f(size*str[0]+2, size*str[1]+2);
				newPos = Vector2f(size*str[2]+2, size*str[3]+2);

				for(int i=0;i<2;i++) if (f[0].getPosition()==oldPos) n=i;

				// animation
				for(int k=0;k<25;k++){
					Vector2f p = newPos - oldPos;
					f[n].move(p.x/25, p.y/25);
					window.draw(sBoard);
					for(int i=0;i<2;i++) window.draw(f[i]); 
					window.draw(f[n]);
					for(int i=0;i<7;i++) window.draw(obstacles[i]);
					window.display();
				}
			}

			if (isMove) f[1].setPosition(pos.x-dx,pos.y-dy);

			
			


			// Perform ally actions, or set for ally to take user input

			//Create the screen
			window.clear();
			window.draw(sBoard);
			for(int i=0;i<2;i++) window.draw(f[i]);
			for(int i=0;i<7;i++) window.draw(obstacles[i]);
			window.display();
			}
		//}
	//}

	return 0;

}