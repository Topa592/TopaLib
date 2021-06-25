#pragma once
namespace tl {
	namespace sge {
		namespace util {
			struct PlayerInputData {
				bool top = false;
				bool left = false;
				bool down = false;
				bool right = false;
			};
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

				void slowStartMovement();
				void updateInput(const PlayerInputData& input);
			public:
				Player();
			};
		}
	}
}