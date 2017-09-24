#pragma once

#include <string>
#include <algorithm>

#define WHITESPACES	" \t\n\v\f\r"

namespace Utils
{
	bool	isspace(const unsigned char& c);
	void	strip(std::string& str);
	void	trim(std::string& str);
}