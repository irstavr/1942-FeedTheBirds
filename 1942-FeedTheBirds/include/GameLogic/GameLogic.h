#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include "PlayerProfile.h"
#include "..\Sprites\Sprite.h"
#include "..\Objects\Characters\SuperAce.h"
#include "..\Objects\Characters\Bird.h"
#include "..\Objects\Items\Fish.h"

typedef vector<Bird*> BIRDS;

class GameLogic {

public:
	SuperAce *superAce;
	BIRDS &birds;

	PlayerProfile* profile;

	int height, width, superAceKilled;
	bool gameRunning;
	
	static Points highScore;

	GameLogic(SuperAce *superAce, BIRDS &birds, int height, int width);
	/*solve all the outrange stuff*/
	void solveOutRange();
	/*solve all the collision stuff*/
	int solveCollision(int &p, int status);
	/*return if the game is still running*/
	bool isRunning() const;
	void clearUp();
};

#endif