// Fill out your copyright notice in the Description page of Project Settings.


#include "CXPlayerController.h"

#include "UI/CXChatInput.h"

void ACXPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	
	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UCXChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}
}

void ACXPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;
}
