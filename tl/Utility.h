#pragma once
#include <memory>
namespace tl {
	namespace utility {
		class ConsistantSleep {
			class Impl; std::unique_ptr<Impl> impl;
		public:
			ConsistantSleep();
			~ConsistantSleep();
			void Start();
			void End(int msTotal);
		};
		class Timer {
			class Impl; std::unique_ptr<Impl> impl;
		public:
			Timer();
			~Timer();
			bool ifTimeReset(int ms);
			bool ifTime(int ms);
			void reset();
		};
		namespace windows {
			void GetClientPos(int& x, int& y);
		}
	}
}