#pragma once

#include "Dictionary.h"

class Resolver
{
	Dictionary&	m_RefDict;

public:
	explicit Resolver(Dictionary& dict);
	~Resolver();

	void	resolveLetters(const std::string& input, bool full);
	void	resolveNumbers(const std::string& input);

private:
	bool	match(std::string pA, const std::string& ref);
};