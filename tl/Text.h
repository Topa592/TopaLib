#pragma once
namespace tl {
	class text {
	public:
		//std::string and std::to_string() are supported 
		template<typename Text>
		static void drawText(const Text& text
			, const int& top
			, const int& left
			, const int& bottom
			, const int& right
		);
	};
	//std::wstring and std::to_wstring() are supported
	class widetext {
		template<typename Text>
		static void drawText(const Text& wtext
			, const int& top
			, const int& left
			, const int& bottom
			, const int& right
		);
	};
}