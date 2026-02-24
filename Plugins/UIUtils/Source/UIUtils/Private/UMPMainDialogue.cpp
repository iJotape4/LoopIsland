// Fill out your copyright notice in the Description page of Project Settings.


#include "UMPMainDialogue.h"

#include "EventRouterSubsystem.h"
#include "GenericPayloads.h"

#include "Components/SlateWrapperTypes.h"

void UMPMainDialogue::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Collapsed);
	DialogueEventHandle = UEventRouterSubsystem::SubscribeToEvent<FGenericUIDialogueEvent>(this, DialoguesTag, &UMPMainDialogue::DisplayText);
}

void UMPMainDialogue::DisplayText(const FGenericUIDialogueEvent& DialogueEvent)
{
	SetDialogueText(DialogueEvent.Text);
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	if (UWorld* World = GetWorld())
	{
		FTimerManager& TimerManager = World->GetTimerManager();
		TimerManager.ClearTimer(TimerHandle);
		TimerManager.SetTimer(TimerHandle, this, &UMPMainDialogue::CloseDialogue, DialogueEvent.Duration, false);
	}
}

void UMPMainDialogue::CloseDialogue()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UMPMainDialogue::NativeDestruct()
{
	Super::NativeDestruct();
	UEventRouterSubsystem::UnsubscribeFromEvent(this, DialoguesTag, DialogueEventHandle);
}