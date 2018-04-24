#include <SFML/Graphics.hpp> // All major graphics functions
#include <time.h>
#include <stdlib.h> //rand()
#include <iostream> //cout (for debugging)
using namespace sf;

///////////////////   Elements for world generation     ///////////////////////////////////

int size = 75; // the pixel size of each square; in future make resizable for zooming in & out

//Features of the map; in the future these will all be in the same object
// class Map {
// 	int board[10][10];
// 	int obstacle_num;
//	int creature_num; // party_size+enemy_num
// 	int party_max;
// 	int enemy_max;
// }

//CircleShape f[creature_num];

CircleShape f[2]; //figures for character and enemy
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

////////////////////////      Elements for Combat Mechanics     //////////////////////////////////// 
// in future, these values will be pulled from character header files

class Creature() { // inherit graphical shape?
public:
	float hp;
	float maxHP; // standard max hp should be 20 hp, for the set damage
	bool stunned;
	bool blocking;
	bool inAir;
	bool canAttack;
	bool canJump;
	bool canMove;
	int actionCounter;
	int turnCounter;
	int party_num;
	Creature(){};
	Creature(float h,float H,bool s,bool b,bool a){
		hp=h;
		maxHP=H;
		stunned=s;
		blocking=b;
		inAir=a;
	}
	~Creature(){};
	
};

// class Character {
// 	float hp;
// 	float maxHP;
// 	bool stunned = 0;
// 	bool blocking = 0;
// 	bool inAir = 0;
// public:
// 	Character();
// 	~Character();
	
// };

// class Enemy {
// 	float hp;
// 	float maxHP;
// 	bool stunned = 0;
// 	bool blocking = 0;
// 	bool inAir = 0;
// public:
// 	Enemy();
// 	~Enemy();
	
// };

// float character_HP = 10;
// float character_maxHP = 10;
// float enemy_HP = 10;
// float enemy_maxHP = 10;
// bool character_stun = 0;
// bool enemy_stun = 0;

void lightAerialAttack(Creature target, Creature attacker){//bool blockState, bool airState, float victim) {
	// check distance - would be good before end of LD, but not necessary
	
	//check block
	if(target.blocking) continue;

	//check jump
	if(!target.inAir) continue;

	int dmg = 2;
	target -= dmg;
}

void heavyAerialAttack(Creature attacker, Creature target) {
	// check distance - would be good before end of LD, but not necessary
	if (actionCounter==1){
		//check block
		if(target.blocking){
			attacker.stunned = 1;
		} continue;
		
		//check jump
		if(!target.inAir) continue;

		float dmg = 5;
		victim -= dmg;
		attacker.actionCounter = 0;	
	} else {
		turnCounter = 2; // do nothing while counter > 0; tick down when Keyboard::isKeyPressed(Keyboard::Space);
	}
}

void smashAerialAttack(Creature attacker, Creature target) {
	// check distance - would be good before end of LD, but not necessary
	
	// smash attacks go through blocks 
	if (attacker.actionCounter==2){
		//check jump
		if(!target.inAir) continue;

		int dmg = 10;
		victim -= dmg;
		attacker.actionCounter = 0;
	} else {
		attacker.turnCounter = 2;
	}
}

void lightGroundAttack(Creature attacker, Creature target){//bool blockState, bool airState, float victim) {
	// check distance - would be good before end of LD, but not necessary
	
	//check block
	if(target.blocking) continue;

	//check jump
	if(target.inAir) continue;

	int dmg = 2;
	target -= dmg;
}

void heavyGroundAttack(Creature attacker, Creature target) {
	// check distance - would be good before end of LD, but not necessary
	
	//check block
	if(blockState){
		// stunn
	} continue;
	
	//check jump
	if(!target.inAir) continue;

	float dmg = 5;
	victim -= dmg;

}

void smashGroundAttack(Creature attacker, Creature target) {
	// check distance - would be good before end of LD, but not necessary
	
	// smash attacks go through blocks 

	//check jump
	if(!target.inAir) continue;
	
	int dmg = 10;
	victim -= dmg;	
}

////////////////////////      Utility elements for the game to run     //////////////////////////////

// int vect2Coord(Vector2f p, Vector2f q) {
// 	//int s[4];
// 	s[0] = p.x-2/size;
// 	s[1] = p.y-2/size;
// 	s[2] = q.x-2/size;
// 	s[3] = q.y-2/size;
// 	return s;
// }

int s[4]; // hold the old and new, x and y coordinates for motion

Vector2f coord2Vect(int a,int b) {
	return Vector2f(a*size+2,b*size+2);
}

void move(int arr[4]) {
	Vector2f oldPos = coord2Vect(arr[0],arr[1]);
	Vector2f newPos = coord2Vect(arr[2],arr[3]);
}

void getNextMove(Vector2f currLocat, Vector2f victim, Creature attacker, Creature target) {
	//take position of the character - input arg

	// Since we have the current position, set that as oldPos
	s[0] = currLocat.x-2/size;
	s[1] = currLocat.y-2/size;

	int dx = victim.x-currLocat.x; // these get used often
	int dy = victim.y-currLocat.y;
	int dxdy = abs(dx)-abs(dy);

	//  if close -> use light attack continously
	if (abs(dx)>75 || abs(dy)>75){
		//move toward the victim; should you move vertically or horizontally?
		// Are there any gaps here? Anything I'm missing
		if (dxdy<-150){
			// move in the y
			s[2] = s[0];
			int m = dy>0?1:-1;
			s[3] = s[1]+n*2;

		} else if (dxdy>150) {
			// move in the x
			int m = dx>0?1:-1;
			s[2] = s[0]+n*2;
			s[3] = s[1];

		} else if (dxdy>-150 && dxdy<150) { // case of -150<abs(dx)-abs(dy)<150; dx =225, dy = 150
			// move diagonally
			int m = dx>0?1:-1;
			int n = dy>0?1:-1;
			s[2] = s[0]+m*1;
			s[3] = s[1]+n*1;

		} else if (abs(dx)==150 && dy==0) { // Case of 150 and 0
			// move 1, then attack; which direction? make the 150 into 75
			int m = dx>0?1:-1;
			s[2] = s[0]+m*1;
			s[3] = s[1];

			//then attack
			lightAttack(character_HP);

		} else if (abs(dy)==150 && dx==0) { // other half of the above
			int m = dy>0?1:-1;
			s[2] = s[0];
			s[3] = s[1]+m*1;

			//then attack
			lightAttack(character_HP);

		} else if (abs(dy)==150 && dx==75) { // Case of 150 and 75
			// move 2, then attack; make the 150 into 0
			int m = dy>0?1:-1;
			s[2] = s[0];
			s[3] = s[1]+m*2;

			//then attack
			lightAttack(character_HP);

		} else if (abs(dx)==150 && dy==75) { // other half of the above
			int m = dx>0?1:-1;
			s[2] = s[0]+m*2;
			s[3] = s[1];

			//then attack
			lightAttack(character_HP);
		}


	} 
	if (abs(dx)==75 && abs(dy)==75){ // if diagonally from victim
		// move and attack
		bool m = rand() % 2;
		bool n = !m;
		s[2] = s[0]+m*1;
		s[3] = s[1]+n*1;

		//then attack
		lightAttack(character_HP);

	}
	if () { // case of 75 and 0 
		// attack
		lightAttack(character_HP);
	}
	


}

int main() {
	RenderWindow window(VideoMode(751,751), "Fantasy Fighter");



	Texture grid;
	grid.loadFromFile("images/grid3.png");

	startingPosition();

	Creature character = Creature(20,20,0,0,0);
	Creature enemy = Creature(20,20,0,0,0);

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

			// Also change 1's to i's and run for each party member

			while (window.pollEvent(e)) {
				if (e.type == Event::Closed)
					window.close();

				if (e.type == Event::MouseButtonPressed)
					if (e.key.code == Mouse::Left)
						//for(int i=0;i<party_size;i++){ // must only have party members in f[]
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

			if (Keyboard::isKeyPressed(Keyboard::A)){
				if (character.canAttack){
					lightGroundAttack();
					character.canAttack = 0;
				}

			}

			if (Keyboard::isKeyPressed(Keyboard::Q)){
				if (character.canAttack){
					lightAerialAttack();
					character.canAttack = 0;
				}
			}


			// Perform enemy actions (and ally actions, if AI controlled)
			if (Keyboard::isKeyPressed(Keyboard::Space)){
				s[0] = 1; // This is the only problem...
				s[1] = 2; //   any one move takes an entire array[4]
				s[2] = 1;
				s[3] = 4;

				//getNextMove();

				oldPos = Vector2f(size*s[0]+2, size*s[1]+2);
				newPos = Vector2f(size*s[2]+2, size*s[3]+2);

				for(int i=0;i<2;i++) if (f[i].getPosition()==oldPos) n=i;

				// animation
				for(int k=0;k<1000;k++){
					Vector2f p = newPos - oldPos;
					f[n].move(p.x/1000, p.y/1000);
					window.draw(sBoard);
					for(int i=0;i<2;i++) window.draw(f[i]); 
					window.draw(f[n]);
					//for(int i=0;i<7;i++) window.draw(obstacles[i]);
					window.display();
				}

				move(s); 
				f[n].setPosition(newPos);
			}

			if (isMove) f[1].setPosition(pos.x-dx,pos.y-dy);

			
			


			// Perform ally actions, or set for ally to take user input

			//Create the screen
			window.clear();
			window.draw(sBoard);
			for(int i=0;i<2;i++) window.draw(f[i]);
			//for(int i=0;i<7;i++) window.draw(obstacles[i]);
			window.display();
			}
		//}
	//}

	return 0;

}