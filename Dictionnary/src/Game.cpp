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

void Game::resolveNumbers()
{
	m_Resolver.resolveNumbers("");
}

string Game::getInput()
{
	string input("");
	getline(cin, input);
	Utils::strip(input);
	return input;
}

void Game::addWord()
{
	cout << "Quel mot voulez-vous ajouter ?" << endl;

	string word(this->getInput());

	if (this->isInputValid(word))
		m_Dictionary.addWord(word);
}

void Game::deleteWord()
{
	cout << "Quel mot voulez-vous supprimer ?" << endl;

	string word(this->getInput());

	if (this->isInputValid(word))
		m_Dictionary.deleteWord(word);
}

Game::Mode Game::chooseMode()
{
	Mode choice(INVALID);

	Utils::clearConsole();
	cout << "Voulez-vous jouez avec des chiffres ou des lettres ?" << endl;
	cout << "CHIFFRES - 1" << endl;
	cout << "LETTRES  - 2" << endl;
	cout << "QUITTER  - 3" << endl;

	string input(this->getInput());

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

bool Game::isOkay()
{
	string input(this->getInput());
	if (input.empty() ||
		input.front() != 'o')
		return false;
	return true;
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

	string input(this->getInput());
	if (!this->isInputValid(input))
		return;

	cout << "Voulez-vous afficher tous les mots possibles ou seulement les plus long ? [o/n]" << endl;

	m_Resolver.resolveLetters(input, this->isOkay());

	cout << "Voulez-vous ajouter un mot au dictionnaire ? [o/n]" << endl;

	if (this->isOkay())
		this->addWord();

	cout << "Voulez-vous supprimer un mot du dictionnaire ? [o/n]" << endl;

	if (this->isOkay())
		this->deleteWord();
}

void Game::run()
{
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
				cout << "Veuillez choisir un mode de jeu valide !!!" << endl;
				break;
		}
	}
}