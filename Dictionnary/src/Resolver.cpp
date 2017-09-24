#include "Resolver.h"

using namespace std;

Resolver::Resolver(Dictionary& dict) :
	m_RefDict(dict)
{}

Resolver::~Resolver()
{}

/*
	toSearch = "caca"
	pA = [opiace]
*/

bool Resolver::match(string pA, const string& ref)
{
	size_t	pos;

	for (const char& cRef : ref)
	{
		if ((pos = pA.find(cRef)) != pA.npos)
			pA.erase(pos, 1);
		else
			return false;
	}
	return true;
}

void Resolver::resolveLetters(const string& input, bool full)
{
	unordered_set<char>	alreadySeen{};
	size_t	count(0), curSize = input.size();
	bool	stop = false;

	cout << "Start searching: " << input << endl;
	cout << string(25, '-') << endl;

	while (curSize-- > m_RefDict.getMinSize())
	{
		for (const char& startSearch : input)
		{
			if (alreadySeen.find(startSearch) != alreadySeen.end())
				continue;

			for (const string& word : m_RefDict[startSearch].at(curSize))
			{
				if (this->match(input, word))
				{
					count++;
					cout << word << endl;
					if (!full)
						stop = true;
				}
			}
			alreadySeen.emplace(startSearch);
		}
		alreadySeen.clear();
		if (!full && stop)
			break;
	}

	cout << count << " words found !!!" << endl;
}

void Resolver::resolveNumbers(const string& input)
{
	cout << "Not implemented yet !!!" << endl;
}