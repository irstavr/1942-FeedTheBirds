#ifndef AI_H
#define AI_H

#include <vector>
#include "..\Objects\Characters\Bird.h"

class AI {

std::vector<Bird*> visibleObjects;

public:
	AI();
	~AI();

private:
	void addBirds();
	void goToSuperAce();

	void handleLittleBirds();
	void handleMediumBirds();
	void handleBoss();	
};

#endif