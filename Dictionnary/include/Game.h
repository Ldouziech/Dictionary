#pragma once

#include "Resolver.h"
#include "Utils\Utils.h"

#define MAX_INPUT	100

class Game
{
	Dictionary	m_Dictionary;
	Resolver	m_Resolver;
	bool		m_IsRunning;

	enum Mode
	{
		INVALID,
		CHIFFRES,
		LETTRES,
		QUITTER
	};

public:
	Game();
	~Game();

	void	run();

private:
	void		resolveNumbers();

	std::string	getInput();
	void		addWord();
	void		deleteWord();
	Mode		chooseMode();
	bool		isOkay();
	bool		isInputValid(const std::string& input);
	void		resolveLetters();
};