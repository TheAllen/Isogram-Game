#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct BullCowCount {
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus {
	OK,
	NotIsogram,
	WRONG_LENGTH,
	NOT_LOWERCASE,
	INVALID
};


class FBullCowGame {

public:
	FBullCowGame();
	void Reset();
	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	int32 getWordLength() const;
	bool isGameWon() const;
	EGuessStatus checkGuess(FString) const;

	//provide a method to count the balls and cows and increases try number
	BullCowCount SubmitValidGuess(FString);


private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};