#pragma once
#include <string>
namespace tl {
	namespace text {
		void drawText(const std::string& text
			, const int& top
			, const int& left
			, const int& bottom
			, const int& right
		);
		void drawText(const std::wstring& wtext
			, const int& top
			, const int& left
			, const int& bottom
			, const int& right
		);
	}
	
}

