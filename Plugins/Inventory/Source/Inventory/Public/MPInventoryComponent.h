// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MPInventoryEventPayloads.h"
#include "Components/ActorComponent.h"

#include "MPInventoryComponent.generated.h"

struct FInputActionValue;
class AMPKeyItemDropZone;
class UMPItem;

UENUM(BlueprintType)
enum class EInventoryMode : uint8
{
	Default,
	MatchKeyItem,
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORY_API UMPInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
	FGameplayTag UIEventsTag = FGameplayTag::RequestGameplayTag("UI.Inventory", false);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
	FGameplayTag UIDialogueEventsTag = FGameplayTag::RequestGameplayTag("UI.Dialogues", false);
	
protected:
	TArray<UMPItem*> Inventory;
	// Sets default values for this component's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	bool bInventoryOpen =false;

public:
	UMPInventoryComponent();

	virtual void PostInitProperties() override;

	void MatchKeyItemEvent(const FMatchKeyItemEvent& MatchKeyItemEvent);
	void UpdateItem(const FItemUpdatedEvent& ItemUpdatedEvent);
	virtual void BeginPlay() override;

	UFUNCTION()
	void AddItem(const FItemPickedEvent& Ev);
	UFUNCTION()
	void RemoveItem(UMPItem* ItemToRemove);
	void RemoveItem(const FItemDroppedEvent& Event);
	
	bool HasItem(TArray<UMPItem*> ItemsToCheck) const;
	void ToggleInventory();
	void ToggleInventory(const FInventoryToggle& Event);
	void SlotSelected(const FSlotSelectedEvent& SlotSelectedEvent);

	void RotateItem(const FInputActionValue& Value);
	void CloseInspectView();

	virtual void BeginDestroy() override;
	void OnPointerDown(const FInputActionValue& Value);
	void OnZoom(const FInputActionValue& InputActionValue);

private:
	FDelegateHandle InventoryPickedUpHandle;
	FDelegateHandle InventoryItemUpdatedHandle;
	FDelegateHandle InventoryToggleHandle;
	FDelegateHandle InventoryMatchItemHandle;
	FDelegateHandle InventorySlotSelectedHandle;
	FDelegateHandle InventoryItemDroppedHandle;
	
	EInventoryMode InventoryMode = EInventoryMode::Default;

	AMPKeyItemDropZone* CurrentDropZone = nullptr;
};