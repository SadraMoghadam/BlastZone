// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

#include "GameFramework/PlayerState.h" // Add this include to resolve the incomplete type error

void UOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
   if (!InPawn) return;

   ENetRole LocalRole = InPawn->GetLocalRole();
   APlayerState* PlayerState = InPawn->GetPlayerState<APlayerState>();
   FString PlayerName = PlayerState ? PlayerState->GetPlayerName() : TEXT("Unknown");

   FString Role;
   switch (LocalRole)
   {
   case ENetRole::ROLE_Authority:
       Role = FString("Authority");
       break;
   case ENetRole::ROLE_AutonomousProxy:
       Role = FString("Autonomous Proxy");
       break;
   case ENetRole::ROLE_SimulatedProxy:
       Role = FString("Simulated Proxy");
       break;
   case ENetRole::ROLE_None:
       Role = FString("None");
       break;
   }

   FString LocalRoleString = FString::Printf(TEXT("Local Role: %s\nName: %s"), *Role, *PlayerName);
   SetDisplayText(LocalRoleString);
}

void UOverheadWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	RemoveFromParent();
	Super::NativeDestruct();

}
