class InputManager {
	float current_pos;
	enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE, F1, A };

	// kinds of input
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void shoot();

	void twist();
	void pause();

};