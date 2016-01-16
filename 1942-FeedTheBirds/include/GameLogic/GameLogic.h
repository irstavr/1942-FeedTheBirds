#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include "PlayerProfile.h"
#include "..\Sprites\Sprite.h"
#include "..\Objects\Characters\SuperAce.h"
#include "..\Objects\Characters\Bird.h"
#include "..\Objects\Items\Fish.h"

typedef vector<Bird*> BIRDS;
typedef vector<Fish*> FISHES;

class GameLogic {

public:
	SuperAce *superAce;
	BIRDS &birds;
	FISHES &fishes;

	PlayerProfile* profile;

	int height, width, superAceKilled;
	bool gameRunning;
	
	static Points highScore;

	GameLogic(SuperAce *superAce, BIRDS &birds, FISHES &fishes, int height, int width);
	/*solve all the outrange stuff*/
	void solveOutRange();
	/*solve all the collision stuff*/
	int solveCollision(int &p, int status);
	/*decide if add bird*/
	//MOVE TO AI -- bool addBird(float &t, int p);
	/*return if the game is still running*/
	bool isRunning() const;
	void clearUp();
};

#endif