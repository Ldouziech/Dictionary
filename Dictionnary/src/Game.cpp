#include "Game.h"

using namespace std;

Game::Game() :
	m_Dictionary(),
	m_Resolver(m_Dictionary),
	m_IsRunning(true)
{
	m_Dictionary.load();
}

Game::~Game()
{}

Game::Mode Game::chooseMode()
{
	Mode choice(INVALID);
	string input("");

	cout << "Voulez-vous jouez avec des chiffres ou des lettres ?" << endl;
	cout << "CHIFFRES - 1" << endl;
	cout << "LETTRES  - 2" << endl;
	cout << "QUITTER  - 3" << endl;

	getline(cin, input);
	if (!input.empty())
		switch (input.front())
		{
			case '1':
				choice = CHIFFRES;
				break;
			case '2':
				choice = LETTRES;
				break;
			case '3':
				choice = QUITTER;
				break;
			default:
				break;
		}
	return choice;
}

void Game::resolveNumbers()
{
	m_Resolver.resolveNumbers("");
}

bool Game::isInputValid(const string& input)
{
	if (input.size() < m_Dictionary.getMinSize() ||
		input.size() > MAX_INPUT ||
		input.find_first_not_of(Dictionary::Ref) != input.npos)
		return false;
	return true;
}

void Game::resolveLetters()
{
	cout << "Avec quelles lettres voulez-vous trouver un mot ?" << endl;
	cout << "Les lettres valides sont: [" << Dictionary::Ref << "]" << endl;

	string input("");
	getline(cin, input);
	Utils::strip(input);
	if (!this->isInputValid(input))
	{
		cout << "Entree invalide !!!" << endl;
		return;
	}

	cout << "Voulez-vous afficher tous les mots possibles ou seulement les plus long ? [o/n]" << endl;

	string full("");
	getline(cin, full);
	Utils::strip(full);
	if (full.empty() ||
		full.find_first_of("on") != 0)
	{
		cout << "Entree invalide !!!" << endl;
		return;
	}
	m_Resolver.resolveLetters(input, (full.front() == 'o' ? true : false));
}

void Game::run()
{
	cout << "Bienvenue dans des chiffres et des lettres!" << endl;

	while (m_IsRunning)
	{
		switch (this->chooseMode())
		{
			case CHIFFRES:
				this->resolveNumbers();
				break;
			case LETTRES:
				this->resolveLetters();
				break;
			case QUITTER:
				m_IsRunning = false;
				break;
			default:
				cout << "Veuillez chosir un mode de jeu valide !!!" << endl;
				break;
		}
		cout << string(25, '-') << endl;
	}

	cout << "Merci d'avoir joue a des chiffres et des lettres ! A bientot !!!" << endl;
}