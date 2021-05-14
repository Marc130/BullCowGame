// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
	Super::BeginPlay();

	InitGame();

	PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord); //Debug line

	PrintLine(TEXT("Welcome to Bull Cow!"));
	PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
	PrintLine(TEXT("Type in your guess and press enter to continue..."));

	//Prompt Player for guess
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
	ClearScreen();

	//Checking player guess

	if (Input == HiddenWord)
	{
		PrintLine(TEXT("You have won!"));
	}
	else
	{
		if (Input.Len() != HiddenWord.Len())
		{
			PrintLine(TEXT("The hidden word is %i characters long, try again!"), HiddenWord.Len());
		}
		PrintLine(TEXT("You have lost!"));
	}
	
}

void UBullCowCartridge::InitGame() {
	HiddenWord = TEXT("cake");
	Lives = 4;
}