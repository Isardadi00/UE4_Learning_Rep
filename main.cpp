/*  This is the console executable, that makes use of the BullCow class
	this acts as the view in an MVC pattern, and is responsible for all
	user interaction.
	For game logic see the FBullCowGame class.
*/
#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

// the entry point for the whole game
int main() 
{	
	do 
	{
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain());
}

// introduce the game
void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fantastic word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?\n";
	return;
}

void PlayGame() 
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game 
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();	

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

FText GetValidGuess()
{	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTries = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTries << ". Enter your guess: ";	
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "This is not an isogram. Please enter a word with no reocurring letters. \n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word with no uppercase letters. \n";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);  // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain() 
{
	std::cout << "Do you want to play again with the same hidden word? (y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You won. Great Job!\n";
	}
	else
	{
		std::cout << "You lost. Better luck next time!\n";
	}
	return;
}


