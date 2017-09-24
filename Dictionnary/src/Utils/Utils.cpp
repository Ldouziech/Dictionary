#include "Utils\Utils.h"

namespace Utils
{
	bool	isspace(const unsigned char& c)
	{
		for (const auto& v : WHITESPACES)
			if (c == v)
				return true;
		return false;
	}

	void	strip(std::string& str)
	{
		str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	}

	void	trim(std::string& str)
	{
		str.erase(str.begin(), find_if_not(str.begin(), str.end(), isspace));

		str.erase(find_if_not(str.rbegin(), str.rend(), isspace).base(), str.end());
	}
}