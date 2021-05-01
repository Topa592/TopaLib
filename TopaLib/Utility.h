#pragma once

namespace tl {
	namespace utility {
		namespace dataTypes {
			struct DataConstSleep;
		}
		class ConstSleep {
		public:
			void start();
			void end();
			ConstSleep(int ms);
		private:
			const int ms;
			dataTypes::DataConstSleep* data;
		};
	}
}