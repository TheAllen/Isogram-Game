#include <iostream>
#include <string>
#include "FBullCowGame.h"


using FText = std::string;
using int32 = int;
//using namespace std;

//declaration
void intro();
void PlayGame();
FText GetValidGuess();

void GameSummary();
bool PlayAgain();


FBullCowGame BCGame;

int main() {

	
	do {
		PlayGame();
	} while (PlayAgain());

	std::cout << std::endl;

	system("pause");
	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	intro();
	int32 maxTries = BCGame.getMaxTries();

	while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= maxTries) {
		FText Guess = GetValidGuess();

		BullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.bulls;
		std::cout << ". Cows = " << BullCowCount.cows << std::endl;
		std::cout << "Your guess is " << Guess << std::endl;
		std::cout << "You have " << BCGame.getMaxTries() - BCGame.getCurrentTry() << " tries left." << std::endl;
		std::cout << std::endl;

		GameSummary();
	}
	

	//Summarize the game


}

void intro() {
	std::cout << "Welcome to Bulls and Cows, a word game." << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.getWordLength() << " letter isogram?" << std::endl;
	std::cout << std::endl;
}

//get valid guess
FText GetValidGuess() { 
	EGuessStatus status = EGuessStatus::INVALID;
	FText guess = "";
	
	do {
		int32 currentTry = BCGame.getCurrentTry();
		//get a guess from the player
		std::cout << "Try " << currentTry << ". Enter your guess: ";
		std::getline(std::cin, guess); //Useful for adding spaces and reading the whole line
		status = BCGame.checkGuess(guess);
		//Used for invalid inputs
		switch (status) {
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.getWordLength() << " word." << std::endl;
			break;
		case EGuessStatus::NotIsogram:
			std::cout << "Please enter a word without repeating letters." << std::endl;
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter all lowercase letters" << std::endl;
			break;

		default:
			return guess;
			break;
		}
		std::cout << std::endl;
	} while (status != EGuessStatus::OK); //Once the input is valid, it goes to the default and exits switch case
	return guess;
}


bool PlayAgain() {
	std::cout << "Do you want to play again? " << std::endl;
	FText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y' || response[0] == 'Y');
}

void GameSummary() {
	if (BCGame.isGameWon()) {
		std::cout << "Well Done. You win." << std::endl;
	}
	else {
		std::cout << "Good try, but not quite it." << std::endl;
	}
}

