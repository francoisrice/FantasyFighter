//Need to still do:
// Generate grid semi-randomly (random 8 exterior, 8 dungeon) 0.1.XX
// Load creatures onto map, connected to respective stats 0.2.XX
// Implement taking of turns between the two sides and rolling initiative 0.3.XX
// Add A* navigation and basic attacking AI 0.4.XX
// Implement order of turns for each side, for companions and multiple creatures 0.5.XX
// On each sides turn give respective move and standard actions 0.6.XX
// Implement attack function for basic attack logic on each turn 0.7.XX
// Add shading filter on squares reachable based on move and attack range 0.8.XX
// Implement longrange attack 0.9.XX
// Display Health UI and overworld stuff 1.0

#include <SFML/Graphics.hpp> // Sprite, Texture, 
#include <time.h>
#include <stdlib.h> // rand()
using namespace sf;

int size = 56;

Sprite f[32]; //figures; this may be unnecessary

int mapNum = rand() % 1 + 1
	
class Map {
	int board;
public:
	void choose_map(int); // spin random number generator from 1 to 8 (or as many maps as are created) to choose map
	Map get_map(); // send the chosen map out to be used
}

void Map::choose_map (int mapNum) {
	
}

//TODO - Randomly generate the board based on different
// parameters. Randomly generate obstacles and randomly
// place the party.

int board1[10][10] = // initial zones will be 16 by 16 boards, randomly generated
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0,-1, 0, 1, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
	  0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	  0,-1, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 6, 4,
	  0, 0, 0, 0, 0, 0, 0, 0, 2, 3,
	  0, 0, 0, 0, 0, 0, 0, 0, 7, 5,
	  0,-1, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
	  0, 0,-1, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int board2[10][10] = // initial zones will be 16 by 16 boards, randomly generated 
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
	  0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
	  0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	  0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

std::string toChessNote(Vector2f p) {
	std::string s = "";
	s += char(p.x/size+97);
	s += char(7-p.y/size+49);
	return s;
}

//toCoord moves the creature to the new 
// square, and move uses toCoord to take the
// piece that is on that square.

//TODO - have each piece move, but remove the
// function of capturing piece. Add function 
// for attacking adjacent pieces and gaining
// Experience from the attack.

Vector2f toCoord(char a,char b) {
	int x = int(a) - 97;
	int y = 7-int(b)+49;
	return Vector2f(x*size,y*size);
}

void move(std::string str) {
	Vector2f oldPos = toCoord(str[0],str[1]);
	Vector2f newPos = toCoord(str[2],str[3]);

	//for(int i=0;i<32;i++)
	//if ( f[i].getPosition()==newPos) f[i].setPosition(-100,-100);
	
	//for(int i=0;i<32;i++)
	//if (f[i].getPosition()==oldPos) f[i].setPosition(newPos);
}

std::string position="";

void loadPosition() { //Use this to load obstacles and players
  int k=0;
  for(int i=0;i<10;i++)
    for(int j=0;j<10;j++) {
	int n = board[i][j];
	if (!n) continue;
	int x = abs(n)-1;
	int y = n>0?1:0;
	f[k].setTextureRect( IntRect(size*x,size*y,size,size) );
	f[k].setPosition(size*j,size*i);
	k++;
	}

	for(int i=0;i<position.length();i+=5)
	  move(position.substr(i,4));
}

int main() {
RenderWindow window(VideoMode(821, 661), "Fantasy Fighter");

// Generate grid semi-randomly (random 8 exterior, 8 dungeon) 0.1.XX
//Texture t1;
//t1.loadFromFile("images/figures.png");

Texture grid;
grid.loadFromFile("images/grid.png");

Sprite s(t1);
Sprite sBoard(grid);

for(int i=0;i<32;i++) f[i].setTexture(t1);

loadPosition();

bool isMove=false;
float dx=0, dy=0;
Vector2f oldPos,newPos;
std::string str;
int n=0;

while (window.isOpen()) {
	Vector2i pos = Mouse::getPosition(window);
	Event e;
	while (window.pollEvent(e)) {
		if (e.type == Event::Closed)
			window.close();
	//////////   move back    /////////
//As the headline suggests, the following allows the user
// to reverse the moves that have occurred.
//For Simplescape, this will not be necessary as the moves
// made should not be so easily undone.

	if (e.type == Event::KeyPressed)
		if (e.key.code == Keyboard::Backspace)
		{ position.erase(position.length()-6,5); loadPosition();}

	////////// Move creature /////////
	if (e.type == Event::MouseButtonPressed)
	   if (e.key.code == Mouse::Left)
	      if (s.getGlobalBounds().contains(pos.x,pos.y)) {
		isMove=true; n=i;
		dx=pos.x - f[i].getPosition().x;
		dy=pos.y - f[i].getPosition().y;
		oldPos = f[i].getPosition();
		}

	if (e.type == Event::MouseButtonReleased)
	   if (e.key.code == Mouse::Left) {

	      //Make sure that the creatures move and stay on the squares
	      // of the board.
	      isMove=false;
	      Vector2f p = f[n].getPosition() + Vector2f(size/2,size/2);
	      newPos = Vector2f( size*int(p.x/size), size*int(p.y/size) );

	      str = toChessNote(oldPos)+toChessNote(newPos);
	      move(str); position+=str+" ";
	      std::cout<<str<<str::endl; //print what was moved where
	      f[n].setPosition(newPos);
	      }
	}

	//TODO - 
	//AI's move - currently set for example movement - need to set
	// using A* movement algorithms and load AI based on creature
	//Eventually, can also train allies based on NN's to strategize and
	// to attack on their own. 
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		str = "d7d5"; //example

		oldPos = toCoord(str[0],str[1]);
		newPos = toCoord(str[2],str[3]);

		for(int i=0;i<32,i++) if (f[i].getPosition()==oldPos) n=i;

		////// animation /////
		for(int k=0;k<50;k++) {
			Vector2f p = newPos - oldPos;
			f[n].move(p.x/50, p.y/50);
			window.draw(sBoard);
			for(int i=0;i<32;i++) window.draw(f[i]); window.draw(f[n]);
			window.display();
		}
	move(str); position+=str+" ";
	f[n].setPosition(newPos);
	}

	if (isMove) f[n].setPosition(pos.x-dx,pos.y-dy);


   ////// Display the elements on the window /////
window.clear();
window.draw(sBoard);
for (int i=0;i<32;i++) window.draw(f[1]);
window.display(); 
}

return 0;

}
