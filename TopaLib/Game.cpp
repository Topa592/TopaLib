#include "Game.h"
#include "Input.h"

void tl::game::Player::slowStartMovement() {
	for (int i = 0; i < 4; i++) {
		if (input[i])
			curStep[i] = (maxStep >= curStep[i]) ? curStep[i] + speedUpMultiplier : curStep[i];
		else curStep[i] = (curStep[i] > speedDownMultiplier) ? curStep[i] - speedDownMultiplier : 0;
		if (i % 2 == 0) {
			y += perStepSpeed * (float)(curStep[i] * ifPositive[i]);
		}
		else {
			x += perStepSpeed * (float)(curStep[i] * ifPositive[i]);
		}
	}
}

void tl::game::Player::updateInput() {
	input[0] = tl::input::getKey('W');
	input[1] = tl::input::getKey('A');
	input[2] = tl::input::getKey('S');
	input[3] = tl::input::getKey('D');
}

tl::game::Player::Player() {
	for (int i = 0; i < 4; i++) {
		curStep[i] = 0;
		input[i] = false;
	}
}