#pragma once

#include <map>
#include <vector>
#include <list>
#include <string>
#include <cctype>

#include <utility>
#include <algorithm>
#include <fstream>
#include <unordered_set>

#include <exception>
#include <iostream>

using DictValuePair = std::vector<std::list<std::string>>;
using Dict = std::map<char, DictValuePair>;
using AccentSet = std::unordered_set<unsigned char>;

#define MIN_SIZE	2
#define MAX_SIZE	25

class Dictionary
{
	std::string		m_dictPath;
	Dict			m_Dict;
	unsigned int	m_MinSize;
	unsigned int	m_MaxSize;

	static const std::string				Ref;
	static const std::string				ResFolder;
	static const std::map<char, AccentSet>	Accents;

public:
	Dictionary(const std::string& dictPath = "DefaultDict.txt", unsigned int minSize = MIN_SIZE, unsigned int maxSize = MAX_SIZE);
	~Dictionary();

	void				load(const std::string& dictPath = "");

	void				setMinSize(const unsigned int& size);
	void				setMaxSize(const unsigned int& size);

	const Dict&			getDict() const;
	const unsigned int&	getMinSize() const;
	const unsigned int&	getMaxSize() const;
	const unsigned int	getSize() const;

private:
	void	strip(std::string& str);
	bool	isValid(const std::string& line);
	void	formatLine(std::string& line);
	void	addWord(const std::string& word);
};

std::ostream&	operator<<(std::ostream& os, const Dictionary& dict);