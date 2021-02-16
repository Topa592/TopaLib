#include "GraphicsText.h"

void GraphicsText::characterToText(const char& t, int x, int y) {
	switch (t) {
	case '1':
		
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case '0':
	default:
		break;
	}
}

void GraphicsText::stringToText(std::string& s, int x, int y) {
	for (int i = 0; i < s.length(); i++) {
		characterToText(s[i], x + i * 15, y);
	}
}