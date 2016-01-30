#include "..\..\..\include\Objects\Characters\Bird.h"

Bird::Bird(Dim _x, Dim _y, int birdLives,
			AnimationFilm* film,
			FrameRangeAnimation *_flyAnimation,
			FrameRangeAnimator *_flyAnimator) :
		Sprite(_x, _y, film),
		flyAnimation(_flyAnimation),
		flyAnimator(_flyAnimator),
		birdLives(birdLives),
		isAlive(true) {
	droppings = new vector<BirdDropping*>();
}

Bird::~Bird(void) {
	delete droppings;
}

BirdDropping* Bird::shoot() {
	MovingAnimation* bulletAnimation = new MovingAnimation(-5, 0, 20, true, 4);
	MovingAnimator* bulletAnimator = new MovingAnimator();

	AnimatorHolder::animRegister(bulletAnimator);
	BirdDropping* dropping = new BirdDropping(x - 70, y - 30,
											(AnimationFilm*)
											AnimationFilmHolder::getSingleton()->
											getFilm("birdshit"),
											bulletAnimation,
											bulletAnimator);
	droppings->push_back(dropping);
	dropping->startMoving();
	return dropping;
	//checker->registerCollisions(superAce, dropping);

}

void Bird::displayAll() {
	if (isSpriteVisible()) {
		this->display(Rect(0, 0, 0, 0));

		for (unsigned int i = 0; i < droppings->size(); i++) {
			BirdDropping* dropping = droppings->at(i);
			dropping->display(Rect(0, 0, 0, 0));
		}
	}
}

void Bird::startMoving(void) {
	fprintf(stdout, "startMoving -> Bird.cpp\n");
	flyAnimator->start(this, flyAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(flyAnimator);
}

int Bird::getLives() {
	return birdLives;
}

void Bird::removeLife() {
	birdLives--;
}

void Bird::createRoute() {

}

void Bird::leaveScreen() {
	flyAnimator->stop();
	flyAnimation->setNewOffsets(5, -20);
	flyAnimation->setDelay(50);
	this->setFlipH(true);
	startMoving();
}

bool Bird::isDead(void) {
	return !isAlive;
}

void Bird::scare() {
	birdLives = 0;
	leaveScreen();
	isAlive = false;
}

// called when Bird collides with Fish
void Bird::collisionAction(Sprite* s) {
	Fish* fish = (Fish*) s;
	cerr << "COLLISION! fish with bird \n";

	removeLife();
	fish->setVisibility(false);
	fish->disableMovement();
	fish->setDead();

	//TODO: change depending on the kind of bird
	ScoreBoard::getInstance().incrScore(500);

	// kill fish sprite
	if (birdLives == 0) {
		cout << "BIRD DEAD!\n";
		leaveScreen();
		this->isAlive = false;
	}
}