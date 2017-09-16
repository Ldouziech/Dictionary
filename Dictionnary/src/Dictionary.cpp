#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary(const string& dictPath, unsigned int minSize, unsigned int maxSize) :
	m_dictPath(dictPath),
	m_Dict()
{
	setMinSize(minSize);
	setMaxSize(maxSize);

	vector<list<string>> tmp((m_MaxSize - m_MinSize), list<string>());
	for (auto& c : Dictionary::Ref)
		m_Dict.emplace(c, tmp);
}

Dictionary::~Dictionary()
{}

void Dictionary::setMinSize(const unsigned int& size)
{
	m_MinSize = (size < MIN_SIZE ? MIN_SIZE : size);
}

void Dictionary::setMaxSize(const unsigned int& size)
{
	m_MaxSize = (size > MAX_SIZE ? MAX_SIZE : size);
}

void Dictionary::strip(string& str)
{
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

bool Dictionary::isValid(const string& line)
{
	if (line.empty() || isupper(line.at(0))
		|| line.size() < m_MinSize || line.size() > m_MaxSize)
		return false;
	return true;
}

void Dictionary::formatLine(string& line)
{
	for (auto& c : line)
	{
		if (isspace(c))
			continue;

		unsigned char tmp = static_cast<unsigned char>(c);
		for (const auto& kv : Dictionary::Accents)
		{
			if (kv.second.find(tmp) != kv.second.end())
			{
				c = kv.first;
				break;
			}
		}
	}
	this->strip(line);
}

void Dictionary::addWord(const string& word)
{

}

void Dictionary::load(const string& dictPath)
{
	if (!dictPath.empty())
		m_dictPath = dictPath;
	string path = (Dictionary::ResFolder + m_dictPath);

	ifstream file(path);
	if (!file.is_open())
		throw invalid_argument("Dictionary: cannot open file: " + path);

	cout << "Loading dictionary from file: " << path << endl;
	string line;
	while (file.good())
	{
		getline(file, line);
		this->strip(line);
		if (!this->isValid(line))
			continue;
		this->formatLine(line);
		if (line.find_first_not_of(Dictionary::Ref) != line.npos)
			continue;
		this->addWord(line);
	}
	file.close();
	cout << "Dictionary loaded! Ready to use!" << endl;
}

const Dict&	Dictionary::getDict() const
{
	return m_Dict;
}

const unsigned int& Dictionary::getMinSize() const
{
	return m_MinSize;
}

const unsigned int& Dictionary::getMaxSize() const
{
	return m_MaxSize;
}

const unsigned int Dictionary::getSize() const
{
	return m_MaxSize - m_MinSize;
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

const string Dictionary::Ref = "abcdefghijklmnopqrstuvwxyz";
const string Dictionary::ResFolder = "./res/";
const map<char, AccentSet> Dictionary::Accents = {
	{'a', {u'à', u'â', u'ä', u'ã'}},
	{'e', {u'è', u'é', u'ê', u'ë'}},
	{'i', {u'î', u'ï'}},
	{'o', {u'ô', u'ö', u'õ'}},
	{'u', {u'ù', u'û', u'ü'}},
	{'c', {u'ç'}},
	{' ', {u'-'}}
};