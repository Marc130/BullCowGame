// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();
	
	FBullCowCount Count;
	Isograms = GetValidWords(Words);

	InitGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
	if (bGameOver)
	{
		ClearScreen();
		InitGame();
	}
	else
	{
		ProcessGuess(PlayerInput);
	}
}

void UBullCowCartridge::InitGame() {
	PrintLine(TEXT("Welcome to Bull Cow!"));

	int32 RandWord = FMath::RandRange(0, Isograms.Num() - 1);
	HiddenWord = Isograms[RandWord];

	Lives = HiddenWord.Len();
	bGameOver = false;

	PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
	PrintLine(TEXT("You have %i lives."), Lives);
	PrintLine(TEXT("Type in your guess. \npress enter to continue..."));

	PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); //Debug line
}

void UBullCowCartridge::EndGame() {
	bGameOver = true;
	PrintLine(TEXT("\nPress Enter to play again"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess) {
	if (Guess == HiddenWord)
	{
		PrintLine(TEXT("You have won!"));
		EndGame();
		return;
	}

	if (Guess.Len() != HiddenWord.Len())
	{
		PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
		PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
		return;
	}

	if (!IsIsogram(Guess))
	{
		PrintLine(TEXT("No repeating letters, guess again"));
		return;
	}

	PrintLine(TEXT("Lost a life!"));
	--Lives;

	if (Lives <= 0)
	{
		ClearScreen();
		PrintLine(TEXT("You have no lives left!"));
		PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

		EndGame();
		return;
	}

	FBullCowCount Score = GetBullCows(Guess);

	PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const {
	for (size_t i = 0; i < Word.Len(); i++)
	{
		for (int32 Comparison = i + 1; Comparison < Word.Len(); Comparison++)
		{
			if (Word[i] == Word[Comparison])
			{
				return false;
			}
		}
	}
	return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const {
	TArray<FString> ValidWords;

	for (FString Word : WordList)
	{
		if (Word.Len() >= 4/* && Word.Len() <= 8*/)
		{
			if (IsIsogram(Word))
			{
				ValidWords.Emplace(Word);
			}
		}
	}
	return ValidWords;
}



FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const {
	FBullCowCount Count;

	for (int32 i = 0; i < Guess.Len(); i++)
	{
		if (Guess[i] == HiddenWord[i])
		{
			Count.Bulls++;
			continue;
		}

		for (int32 j = 0; j < HiddenWord.Len(); j++)
		{
			if (Guess[i] == HiddenWord[j])
			{
				Count.Cows++;
				break;
			}
		}
	}
	return Count;
}