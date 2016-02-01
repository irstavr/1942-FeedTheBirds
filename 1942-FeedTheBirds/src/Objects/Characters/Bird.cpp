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
	this->followsSuperAce = 0;
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

DROPPINGS* Bird::bossShoot() {
	MovingAnimation* bullet1Animation = new MovingAnimation(-7, -2, 10, true, 4);
	MovingAnimator* bullet1Animator = new MovingAnimator();
	MovingAnimation* bullet2Animation = new MovingAnimation(-7, 0, 10, true, 5);
	MovingAnimator* bullet2Animator = new MovingAnimator();
	MovingAnimation* bullet3Animation = new MovingAnimation(-7, 2, 10, true, 6);
	MovingAnimator* bullet3Animator = new MovingAnimator();

	AnimatorHolder::animRegister(bullet1Animator);
	AnimatorHolder::animRegister(bullet2Animator);
	AnimatorHolder::animRegister(bullet3Animator);

	DROPPINGS* bossDroppings = new vector<BirdDropping*>();
	BirdDropping* dropping1 = new BirdDropping(x - 70, y - 30,
		(AnimationFilm*)
		AnimationFilmHolder::getSingleton()->
		getFilm("birdshit"),
		bullet1Animation,
		bullet1Animator);
	BirdDropping* dropping2 = new BirdDropping(x - 70, y - 30,
		(AnimationFilm*)
		AnimationFilmHolder::getSingleton()->
		getFilm("birdshit"),
		bullet2Animation,
		bullet2Animator);
	BirdDropping* dropping3 = new BirdDropping(x - 70, y - 30,
		(AnimationFilm*)
		AnimationFilmHolder::getSingleton()->
		getFilm("birdshit"),
		bullet3Animation,
		bullet3Animator);
	droppings->push_back(dropping1);
	droppings->push_back(dropping2);
	droppings->push_back(dropping3);
	bossDroppings->push_back(dropping1);
	bossDroppings->push_back(dropping2);
	bossDroppings->push_back(dropping3);
	dropping1->startMoving();
	dropping2->startMoving();
	dropping3->startMoving();
	return bossDroppings;
}

void Bird::setFollowsSuperAce(int b)
{
	this->followsSuperAce = b;
}

int Bird::getFollowsSuperAce()
{
	return this->followsSuperAce;
}

BirdSpeed Bird::getBirdSpeed()
{
	return this->birdSpeed;
}

BirdFire Bird::getShotsRemaining()
{
	return this->birdFire;
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