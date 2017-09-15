#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary(const string& dictPath, unsigned int minLength, unsigned int maxLength) :
	m_dictPath(dictPath),
	m_MinLength(minLength),
	m_MaxLength(maxLength),
	m_Dict()
{
	vector<list<string>> tmp((m_MaxLength - m_MinLength), list<string>());
	for (auto& c : Dictionary::REF)
		m_Dict.emplace(c, tmp);
}

Dictionary::~Dictionary()
{}

void Dictionary::formatLine(string& line)
{
	for (auto& c : line)
	{
		if ()
	}
	line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
}

void Dictionary::load(const string& dictPath)
{
	if (!dictPath.empty())
		m_dictPath = dictPath;
	string path = (Dictionary::RES_FOLDER + m_dictPath);

	ifstream file(path);
	if (!file.is_open())
		throw invalid_argument(path + " is not a valid path");

	string line;
	while (file.good())
	{
		getline(file, line);
		this->formatLine(line);
	}
}

const Dict&	Dictionary::getDict() const
{
	return m_Dict;
}

const unsigned int& Dictionary::getMinLength() const
{
	return m_MinLength;
}

const unsigned int& Dictionary::getMaxLength() const
{
	return m_MaxLength;
}

const unsigned int Dictionary::getLength() const
{
	return m_MaxLength - m_MinLength;
}

ostream& operator<<(ostream& os, const Dictionary& dict)
{
	for (const auto& kv : dict.getDict())
	{
		int words = 0;
		for (const auto& lst : kv.second)
			words += lst.size();
		os << words << " words starting with letter " << kv.first << endl;
	}
	return os;
}

const string Dictionary::REF = "abcdefghijklmnopqrstuvwxyz";
const string Dictionary::RES_FOLDER = "../res/";