#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include "PlayerProfile.h"
#include "..\Sprites\Sprite.h"
#include "..\Objects\Characters\SuperAce.h"
#include "..\Objects\Characters\Bird.h"

typedef vector<Bird*> BIRDS;

class GameLogic {
	SuperAce *superAce;
	BIRDS &birds;

	static PlayerProfile* profile;

	int height, width, superAceKilled;
	bool gameRunning;
	
	static Points highScore;


public:
	GameLogic(SuperAce *superAce, BIRDS &birds, int height, int width);
	/*solve all the outrange stuff*/
	void solveOutRange();
	/*solve all the collision stuff*/
	int solveCollision(int &p, int status);
	/*decide if add bird*/
	//MOVE TO AI -- bool addBird(float &t, int p);
	/*return if the game is still running*/
	bool isRunning() const;
};

#endif