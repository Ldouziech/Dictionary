#pragma once

#include <map>
#include <vector>
#include <list>
#include <string>
#include <cctype>

#include <utility>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <unordered_set>

#include <exception>
#include <iostream>

#include "Utils\Utils.h"

#define MIN_SIZE	2
#define MAX_SIZE	25
#define E_IN_O		0x9c
#define E_IN_A		0xe6

using WordList = std::list<std::string>;
using DictValue = std::vector<WordList>;
using Dict = std::map<char, DictValue>;
using AccentSet = std::unordered_set<unsigned char>;


class Dictionary
{
	std::string		m_dictFileName;
	Dict			m_Dict;
	unsigned int	m_MinSize;
	unsigned int	m_MaxSize;

	static const std::string				ResFolder;
	static const std::map<char, AccentSet>	Accents;

public:
	static const std::string				Ref;

public:
	Dictionary(const std::string& dictPath = "DefaultDict.txt", unsigned int minSize = MIN_SIZE, unsigned int maxSize = MAX_SIZE);
	Dictionary(const Dictionary&) = delete;
	Dictionary operator=(const Dictionary&) = delete;
	~Dictionary();

	void				addWord(const std::string& word);
	void				deleteWord(const std::string& word);
	void				load(const std::string& dictPath = "");

	void				setMinSize(const unsigned int& size);
	void				setMaxSize(const unsigned int& size);

	const Dict&			getDict() const;
	const unsigned int&	getMinSize() const;
	const unsigned int&	getMaxSize() const;
	const unsigned int	getSize() const;
	const WordList&		getConst(const char& key, const unsigned int& pos) const;
	WordList&			getRef(const char& key, const unsigned int& pos);

private:
	bool		isValid(const std::string& line);
	void		formatLine(std::string& line);
	void		addWordToDict(const std::string& word);
	void		uniqueWord();
};

std::ostream&	operator<<(std::ostream& os, const Dictionary& dict);