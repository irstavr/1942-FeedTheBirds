#include "..\..\..\include\Objects\Characters\Bird.h"

Bird::Bird(Dim _x, Dim _y, AnimationFilm* film,
			FrameRangeAnimation *_flyAnimation,
			FrameRangeAnimator *_flyAnimator) :
			Sprite(_x, _y, film),
			flyAnimation(_flyAnimation),
	flyAnimator(_flyAnimator){
	birdLives = 2; //TODO: change
	droppings = new vector<BirdDropping*>();
}

Bird::~Bird(void) {
	delete droppings;
}

void Bird::shoot(CollisionChecker*& checker, SuperAce* &superAce) {
	MovingAnimation* bulletAnimation = new MovingAnimation(-5, 0, 20, true, 4);
	MovingAnimator* bulletAnimator = new MovingAnimator();

	AnimatorHolder::animRegister(bulletAnimator);
	BirdDropping* dropping = new BirdDropping(x - 70, y - 30,
											(AnimationFilm*)
											AnimationFilmHolder::getSingleton()->
											getFilm("doubleFish"),
											bulletAnimation,
											bulletAnimator);
	droppings->push_back(dropping);
	dropping->startMoving();

	checker->registerCollisions(superAce, dropping);

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
	startMoving();
}

bool Bird::isDead(void) {
	return !isAlive;
}

void Bird::collisionAction() {
	cout << "BIRD COLLISION!\n";
	this->removeLife();
	if (birdLives == 0) {
		cout << "BIRD DEAD!\n";
		leaveScreen();
	}
}
