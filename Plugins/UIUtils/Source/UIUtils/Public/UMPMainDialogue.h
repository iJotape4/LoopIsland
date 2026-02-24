// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericPayloads.h"
#include "Blueprint/UserWidget.h"
#include "UMPMainDialogue.generated.h"

/**
 * 
 */
UCLASS()
class UIUTILS_API UMPMainDialogue : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Config")
	FGameplayTag DialoguesTag = FGameplayTag::RequestGameplayTag("UI.Dialogues", false);

	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	FText SetDialogueText(const FText& InDialogueText);
	
	void DisplayText(const FGenericUIDialogueEvent& DialogueEvent);
	void CloseDialogue();

	virtual void NativeDestruct() override;
	
private:
	FText DialogueText;
	FTimerHandle TimerHandle;

	FDelegateHandle DialogueEventHandle;
};