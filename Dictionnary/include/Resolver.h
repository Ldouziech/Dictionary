#pragma once

#include "Dictionary.h"

class Resolver
{
	const Dictionary&	m_dict;

public:
	explicit Resolver(const Dictionary& dict);
	~Resolver();

	void	resolve();
};