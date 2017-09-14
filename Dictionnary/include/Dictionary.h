#pragma once

#include <map>
#include <vector>
#include <list>
#include <string>

using Dict = std::map<char, std::vector<std::list<std::string>>>;

class Dictionary
{
	std::string		m_dictPath;
	unsigned int	m_MaxSize;
	Dict			m_Dict;
public:
	Dictionary(const std::string& dictPath = "Default.txt", unsigned int maxSize = 25);
	~Dictionary();

	void	load(const std::string& dictPath);
};