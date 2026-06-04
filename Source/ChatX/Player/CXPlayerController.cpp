// Fill out your copyright notice in the Description page of Project Settings.


#include "CXPlayerController.h"

#include "ChatX.h"
#include "CXPlayerState.h"
#include "Game/CXGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "UI/CXChatInput.h"

ACXPlayerController::ACXPlayerController()
{
	bReplicates = true;
}

void ACXPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsLocalController() == false)
	{
		return;
	}
	
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
	
	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void ACXPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;
	
	if (IsLocalController() == true)
	{
		ACXPlayerState* CXPS = GetPlayerState<ACXPlayerState>();
		if (IsValid(CXPS) == true)
		{
			// FString CombinedMessageString = CXPS->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;

			FString CombinedMessageString = CXPS->PlayerNameString + TEXT(": ") + InChatMessageString;
			
			ServerRPCPrintChatMessageString(CombinedMessageString);
		}
	}
}

void ACXPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	ChatXFunctionLibrary::MyPrintString(this, InChatMessageString);
}

void ACXPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, NotificationText);
}

void ACXPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ACXPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		ACXGameModeBase* CXGM = Cast<ACXGameModeBase>(GM);
		if (IsValid(CXGM) == true)
		{
			CXGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}

void ACXPlayerController::NetMulticastRPCPrintCastMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}