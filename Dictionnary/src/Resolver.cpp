#include "Resolver.h"

using namespace std;

Resolver::Resolver(Dictionary& dict) :
	m_RefDict(dict)
{}

Resolver::~Resolver()
{}

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
	size_t	count(0);
	size_t	sizeSearch = min(input.size(), m_RefDict.getMaxSize());
	bool	stop = false;

	Utils::clearConsole();
	cout << "Start searching: " << input << endl;
	cout << string(25, '-') << endl;

	while (sizeSearch >= m_RefDict.getMinSize())
	{
		for (const char& keySearch : input)
		{
			if (alreadySeen.find(keySearch) != alreadySeen.end())
				continue;

			for (const string& word : m_RefDict.getConst(keySearch, sizeSearch))
			{
				if (this->match(input, word))
				{
					count++;
					cout << word << endl;
					if (!full)
						stop = true;
				}
			}
			alreadySeen.emplace(keySearch);
		}
		if (!full && stop)
			break;
		alreadySeen.clear();
		--sizeSearch;
	}

	cout << count << " words found with: " << input << endl;
	cout << string(25, '-') << endl;
}

void Resolver::resolveNumbers(const string& input)
{
	cout << "Not implemented yet !!!" << endl;
}