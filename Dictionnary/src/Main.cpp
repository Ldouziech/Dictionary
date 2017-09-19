#include <iostream>
#include "Dictionary.h"

using namespace std;

bool myIsspace(const unsigned char& c)
{
	for (const auto& v : WHITESPACES)
		if (c == v)
			return true;
	return false;
}

void trim(string& str)
{
	str.erase(str.begin(), find_if_not(str.begin(), str.end(), myIsspace));

	str.erase(find_if_not(str.rbegin(), str.rend(), myIsspace).base(), str.end());
}

void strip(string& str)
{
	str.erase(remove_if(str.begin(), str.end(), myIsspace), str.end());
}

int main()
{
	Dictionary	dict;
	//dict.load();
	dict.load();

	cout << dict << endl;

	//string test("יא  aze");
	//trim(test);
	//cout << test << ": " << test.size() << endl;

	cin.get();
	return 0;
}