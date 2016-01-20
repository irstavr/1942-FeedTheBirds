#include "..\..\..\include\Objects\Characters\Bird.h"


Bird::Bird(Dim _x, Dim _y, AnimationFilm* film,
	FrameRangeAnimation *_flyAnimation,
	FrameRangeAnimator *_flyAnimator) :
	Sprite(_x, _y, film),
	flyAnimation(_flyAnimation),
	flyAnimator(_flyAnimator){
	droppings = new vector<BirdDropping*>();
}

Bird::~Bird(void)
{
	delete droppings;
}

void Bird::shoot() {
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
}

void Bird::displayAll() {
	this->display(Rect(0, 0, 0, 0));
	for (unsigned int i = 0; i < droppings->size(); i++) {
		BirdDropping* dropping = droppings->at(i);
		dropping->display(Rect(0, 0, 0, 0));
	}
}

void Bird::startMoving(void) {
	fprintf(stdout, "startMoving -> ButtonBird.cpp\n");
	flyAnimator->start(this, flyAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(flyAnimator);
}

void Bird::removeLife() {

}

void Bird::leaveScreen() {

}

// called when bird collides with Fish
void Bird::collisionAction(Sprite* s) {

	Fish* fish = (Fish*) s;

	birdLives--;
	
	// kill fish sprite
	delete fish;

	if (birdLives == 0) {
		leaveScreen();
	}
}