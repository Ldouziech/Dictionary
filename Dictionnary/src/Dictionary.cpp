#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary(const string& dictPath, unsigned int minSize, unsigned int maxSize) :
	m_dictPath(dictPath),
	m_Dict()
{
	setMinSize(minSize);
	setMaxSize(maxSize);

	vector<list<string>> tmp((m_MaxSize - m_MinSize + 1), list<string>());
	for (auto& c : Dictionary::Ref)
		m_Dict.emplace(c, tmp);
}

Dictionary::~Dictionary()
{}

const WordList& Dictionary::getConst(const char& key, const unsigned int& pos) const
{
	if (pos < m_MinSize || Dictionary::Ref.find(key) == string::npos)
		return WordList();
	return m_Dict.at(key).at(pos - m_MinSize);
}

WordList& Dictionary::getRef(const char& key, const unsigned int& pos)
{
	return m_Dict.at(key).at(pos - m_MinSize);
}

void Dictionary::addWord(const string& word)
{
	for (const string& w : this->getConst(word.front(), word.size()))
		if (word == w)
			return;
	this->getRef(word.front(), word.size()).emplace_back(word);

	ofstream file(Dictionary::ResFolder + m_dictPath, ofstream::out | ofstream::app);

	file << endl << word;

	file.close();
}

void Dictionary::setMinSize(const unsigned int& size)
{
	m_MinSize = (size < MIN_SIZE ? MIN_SIZE : size);
}

void Dictionary::setMaxSize(const unsigned int& size)
{
	m_MaxSize = (size > MAX_SIZE ? MAX_SIZE : size);
}

bool Dictionary::isValid(const string& line)
{
	if (line.empty() ||
		line.size() < m_MinSize ||
		line.size() > m_MaxSize ||
		line.find_first_not_of(Dictionary::Ref) != line.npos)
		return false;
	return true;
}

void Dictionary::formatLine(string& line)
{
	Utils::trim(line);
	unsigned char c;

	for (auto& it = line.begin(); it != line.end(); ++it)
	{
		c = static_cast<unsigned char>(*it);

		if (Utils::isspace(c))
		{
			line.clear();
			return;
		}

		if (c == E_IN_O)
		{
			line.replace(it, it + 1, "oe");
			it++;
			continue;
		}
		if (c == E_IN_A)
		{
			line.replace(it, it + 1, "ae");
			it++;
			continue;
		}

		for (const auto& kv : Dictionary::Accents)
		{
			if (kv.second.find(c) != kv.second.end())
			{
				*it = kv.first;
				break;
			}
		}
	}
	Utils::strip(line);
}

void Dictionary::addWordToDict(const string& word)
{
	m_Dict.at(word.front()).at(word.size() - m_MinSize).emplace_back(word);
}

void Dictionary::uniqueWord()
{
	for (auto& kv : m_Dict)
		for (auto& lst : kv.second)
		{
			lst.sort();
			lst.unique();
		}
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
		this->formatLine(line);

		if (this->isValid(line))
			this->addWordToDict(line);
	}
	file.close();
	this->uniqueWord();

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
	unsigned int size = dict.getMinSize();

	for (const auto& kv : dict.getDict())
	{
		cout << "Letter: " << kv.first << endl;
		int i = 0;
		for (const auto& lst : kv.second)
		{
			if (lst.empty())
			{
				i++;
				continue;
			}
			cout << "\t" << "Word size: " << i++ + size << endl;
			for (const auto& word : lst)
			{
				cout << "\t\t" << word << endl;
				//cin.get();
			}
		}
	}
	return os;
}

const string Dictionary::Ref = "abcdefghijklmnopqrstuvwxyz";
const string Dictionary::ResFolder = "./res/";
const map<char, AccentSet> Dictionary::Accents = {
	{'a', {u'�', u'�', u'�', u'�'}},
	{'e', {u'�', u'�', u'�', u'�'}},
	{'i', {u'�', u'�'}},
	{'o', {u'�', u'�', u'�'}},
	{'n', {u'�'}},
	{'u', {u'�', u'�', u'�'}},
	{'c', {u'�'}},
	{' ', {u'-'}}
};