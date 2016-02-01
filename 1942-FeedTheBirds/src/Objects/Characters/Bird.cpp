#include "..\..\..\include\Objects\Characters\Bird.h"

Bird::Bird(Dim _x, Dim _y, 
			BirdID birdID, 
			BirdLives birdLives,
			BirdSpeed birdSpeed,
			BirdFire birdFire,
			AnimationFilm* film,
			FrameRangeAnimation *_flyAnimation,
			FrameRangeAnimator *_flyAnimator) :
		Sprite(_x, _y, film),
		flyAnimation(_flyAnimation),
		flyAnimator(_flyAnimator),
		birdID(birdID),
		birdLives(birdLives),
		birdSpeed(birdSpeed),
		birdFire(birdFire),
		isAlive(true),
		isFed(false)  {
	droppings = new vector<BirdDropping*>();
}

Bird::~Bird(void) {
	delete droppings;
}

BirdDropping* Bird::shoot() {
	MovingAnimation* bulletAnimation = new MovingAnimation(-5, 0, 10, true, 4);
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
	cerr << __FUNCTION__ << "\n";
	flyAnimator->start(this, flyAnimation, getCurrTime());
	AnimatorHolder::markAsRunning(flyAnimator);
}

int Bird::getLives() {
	return this->birdLives;
}

void Bird::removeLife() {
	// force compiler to convert an int value to an enumerated value
	this->birdLives = static_cast<BirdLives>(birdLives - 1);
}

// called when bird fires a bullshit
void Bird::decrFire() {
	// force compiler to convert an int value to an enumerated value
	this->birdFire = static_cast<BirdFire>(birdFire - 1);
}

void Bird::leaveScreen() {
	flyAnimation->setNewOffsets(5, -20);
	flyAnimation->setDelay(50);
	this->setFlipH(true);
}

bool Bird::isDead(void) {
	return !isAlive;
}

void Bird::scare() {
	birdLives = static_cast<BirdLives>(0);
	leaveScreen();
	isAlive = false;
}

int Bird::getBirdID() {
	return this->birdID;
}

// Called when Bird collides with Fish
void Bird::collisionAction(Sprite* s) {
	cerr << "COLLISION! fish with bird \n";

	Fish* fish = (Fish*) s;
	fish->setVisibility(false);
	fish->disableMovement();
	fish->setDead();

	if (birdID == littleBird) {
		ScoreBoard::getInstance().incrScore(100);
	}
	else if (birdID == bonusBird) {
		ScoreBoard::getInstance().incrScore(100);
	}
	else if (birdID == mediumBird) {
		ScoreBoard::getInstance().incrScore(200);
	}
	else if (birdID == bossBird) {
		ScoreBoard::getInstance().incrScore(300);
	}

	this->removeLife();

	// kill fish sprite
	if (this->birdLives == 0) {
		cerr << "BIRD DEAD!\n";
		this->leaveScreen();
		this->isAlive = false;
		this->isFed = true;
	}
}