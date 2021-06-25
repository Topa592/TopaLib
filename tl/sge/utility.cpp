#include "sge.h"

void tl::sge::util::Player::slowStartMovement() {
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

void tl::sge::util::Player::updateInput(const PlayerInputData& input) {
	this->input[0] = input.top;
	this->input[1] = input.left;
	this->input[2] = input.down;
	this->input[3] = input.right;
}

tl::sge::util::Player::Player() {
	for (int i = 0; i < 4; i++) {
		curStep[i] = 0;
		input[i] = false;
	}
}