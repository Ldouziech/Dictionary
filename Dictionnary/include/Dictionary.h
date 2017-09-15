#pragma once

#include <map>
#include <vector>
#include <list>
#include <string>

#include <utility>
#include <algorithm>
#include <fstream>
#include <unordered_set>

#include <exception>
#include <iostream>

using DictValuePair = std::vector<std::list<std::string>>;
using Dict = std::map<char, DictValuePair>;

class Dictionary
{
	std::string		m_dictPath;
	unsigned int	m_MinLength;
	unsigned int	m_MaxLength;
	Dict			m_Dict;

	std::unordered_set<char>	m_Accents = {};

public:
	static const std::string REF;
	static const std::string RES_FOLDER;

public:
	Dictionary(const std::string& dictPath = "DefaultDict.txt", unsigned int minLength = 2, unsigned int maxLength = 25);
	~Dictionary();

	void				load(const std::string& dictPath = "");
	const Dict&			getDict() const;
	const unsigned int&	getMinLength() const;
	const unsigned int&	getMaxLength() const;
	const unsigned int	getLength() const;

private:
	void	formatLine(std::string& line);
};

std::ostream&	operator<<(std::ostream& os, const Dictionary& dict);