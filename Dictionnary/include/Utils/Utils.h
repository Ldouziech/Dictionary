#pragma once

#include <string>
#include <algorithm>
#include <cstdlib>

#define WHITESPACES	" \t\n\v\f\r"

namespace Utils
{
	void	clearConsole();
	bool	isspace(const unsigned char& c);
	void	strip(std::string& str);
	void	trim(std::string& str);
}