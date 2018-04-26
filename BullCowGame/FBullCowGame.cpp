#include "stdafx.h"
#include "FBullCowGame.h"
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset() 
{
	constexpr int32 CURRENT_TRY = 1;
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	bGameIsWon = false;
	MyCurrentTry = CURRENT_TRY;
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (! IsIsogram(Guess)) // if the guess is not an isogram 
	{
		return EGuessStatus::Not_Isogram;
	} 
	
	else if (! IsLowercase(Guess)) // if the guess isn´t all lowercase 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
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
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	// loop through all letters in the hidden word

	for ( int32 MHWChar = 0; MHWChar < WordLength ; MHWChar++)
	{
		// compare letters against the guess
		for ( int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) // if they´re in the same place
				{
					BullCowCount.Bulls++; // incriment bulls
				}
				// if they´re in the wrong place
				else
				{
					BullCowCount.Cows++; // incriment cows
				}
				
			}
		}		
	}
	if (BullCowCount.Bulls ==  WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterLower;
	for (auto Letter : Word)
	{
		Letter = islower(Letter);
		if (LetterLower[Letter]) 
		{
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsIsogram(FString Word) const
{ 
	if (Word.length() <= 1) { return true; }	//treat 0 and 1 letter words as isograms
	
	TMap<char, bool> LetterSeen;//setup our map
	for (auto Letter : Word) // for all the letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter])//if the letter is in the map
		{
			return false;// we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;// add the letter to the map as seen
		}	
			
	}	
	return true; // for example, in cases where /0 is entered 
}

