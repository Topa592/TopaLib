#pragma once
#include "Input.h"

namespace tl {
	namespace game {
		class Player {
		private:
			bool input[4];
			int curStep[4];
			int ifPositive[4] = { -1,-1,1,1 };
		public:
			float x = 0;
			float y = 0;
			float perStepSpeed = 1;
			int maxStep = 10;
			int speedUpMultiplier = 1;
			int speedDownMultiplier = 1;

			void slowStartMovement() {
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
			void updateInput() {
				input[0] = tl::input::getKey('W');
				input[1] = tl::input::getKey('A');
				input[2] = tl::input::getKey('S');
				input[3] = tl::input::getKey('D');
			}
		private:
			
		public:
			Player() {
				for (int i = 0; i < 4; i++) {
					curStep[i] = 0;
					input[i] = false;
				}
			}
		};
	}
}