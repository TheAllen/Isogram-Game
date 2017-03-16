#include "FBullCowGame.h"
#include <map>
#define TMap std::map

//constructor
FBullCowGame::FBullCowGame() {
	Reset();
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD[] = { "computers" , "planet", "almonds", "wafers"};
	int r = rand() % 4;
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = getMaxTries();
	MyHiddenWord = HIDDEN_WORD[r];
	MyCurrentTry = 1;
	bGameIsWon = false;

}


EGuessStatus FBullCowGame::checkGuess(FString string) const{
	//if the guess is not an isogram, return an error
	if (!IsIsogram(string)) {
		return EGuessStatus::NotIsogram;
	}
	//if the guess is not all lowercase
	else if (!IsLowercase(string)) {
		return EGuessStatus::NOT_LOWERCASE;
	}
	else if (string.length() != getWordLength()) {
		return EGuessStatus::WRONG_LENGTH;
	}
	else {
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::isGameWon() const {
	return bGameIsWon;
}

int32 FBullCowGame::getCurrentTry() const{
	TMap<int32, int32> WordLengthToMaxTries;
	return MyCurrentTry;
}

int32 FBullCowGame::getMaxTries()  const{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5}, {9,6} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::getWordLength() const {
	return MyHiddenWord.length();
}


BullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	//increment the turn number
	//set up return variable
	//loop through all the letters in the guess
	MyCurrentTry++;
	BullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();
	for (int32 i = 0; i < WordLength; i++) {
		for (int32 j = 0; j < WordLength; j++) {

			if (Guess[i] == MyHiddenWord[j]) {
				if (i == j) {
					BullCowCount.bulls++; //If they are in the same place
				}
				else {
					BullCowCount.cows++; //If they are not in the same place
				}
			}
		 }
	}
	if (BullCowCount.bulls == WordLength && BullCowCount.cows == 0) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString word) const {
	if (word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;
	for (auto Letter : word) { // for all letters of the word
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString word) const {

	for (auto letter : word) {
		if (!islower(letter)) {
			return false;
		}
		else {
			return true;
		}
	}
	return true;
}



