#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	constexpr int32 CURRENT_TRY = 1;
	MyCurrentTry = CURRENT_TRY;

	const FString HIDDEN_WORD = "niga";
	MyHiddenWord = HIDDEN_WORD;

	bGameIsWon = false;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength()) 
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}

	else // else 
	{
		return EGuessStatus::OK;
	}
}

// receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); 

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) 
				{
					BullCowCount.Bulls++; 
				}
				else
				{
					BullCowCount.Cows++; 
				}

			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }	//treat 0 and 1 letter words as isograms

	TMap<char, bool> LetterSeen;//setup our map
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter])//if the letter is in the map
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;// add the letter to the map as seen
		}

	}
	return true; // for example, in cases where /0 is entered 
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
