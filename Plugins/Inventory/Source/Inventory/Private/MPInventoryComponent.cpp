// Fill out your copyright notice in the Description page of Project Settings.


// Sets default values for this component's properties
#include "MPInventoryComponent.h"
#include "EventRouterSubsystem.h"
#include "MPItem.h"
#include "Internationalization/Text.h"
#include "MPKeyItemDropZone.h"
#include "UI/MPInventorySlot.h"

struct FInputActionValue;

// Sets default values for this component's properties
UMPInventoryComponent::UMPInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UMPInventoryComponent::PostInitProperties()
{
	Super::PostInitProperties();
	
}

void UMPInventoryComponent::MatchKeyItemEvent(const FMatchKeyItemEvent& MatchKeyItemEvent)
{
	// if (HasItem(MatchKeyItemEvent.DropZone->RequiredItems))
	// {
	// 	InventoryMode = EInventoryMode::MatchKeyItem;
	// 	CurrentDropZone = MatchKeyItemEvent.DropZone;
	// 	ToggleInventory();
	// 	
	// 	UEventRouterSubsystem::BroadcastEvent(this, UIDialogueEventsTag, FGenericUIDialogueEvent{FText::FromString("It Seems I can put something here"), 10.0f});
	// }
	// else
	// {
	// 	UEventRouterSubsystem::BroadcastEvent(this, UIDialogueEventsTag, FGenericUIDialogueEvent{FText::FromString("I do not have required item to match")});
	// }
}

void UMPInventoryComponent::UpdateItem(const FItemUpdatedEvent& ItemUpdatedEvent)
{
	Inventory.Remove(ItemUpdatedEvent.Item);
	// if (UMPItem* Item = ItemUpdatedEvent.Item->RemainingItemAfterInteraction)
	// 	Inventory.Add(Item);
}

void UMPInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	// InspectItemActor = GetWorld()->SpawnActor<ATTInspectItem>(InspectItemClass);
	// InspectItemActor->SetActorLocation (FVector(1000.0f,0.0f,0.0f) );
	
	InventoryPickedUpHandle = UEventRouterSubsystem::SubscribeToEvent<FItemPickedEvent>(
		this, 
		UIEventsTag, 
		&UMPInventoryComponent::AddItem 
	);
	
	InventoryToggleHandle = UEventRouterSubsystem::SubscribeToEvent<FInventoryToggle>(this, UIEventsTag, &UMPInventoryComponent::ToggleInventory);
	InventoryMatchItemHandle = UEventRouterSubsystem::SubscribeToEvent<FMatchKeyItemEvent>(this, UIEventsTag, &UMPInventoryComponent::MatchKeyItemEvent);
	InventorySlotSelectedHandle = UEventRouterSubsystem::SubscribeToEvent<FSlotSelectedEvent>(this,UIEventsTag,&UMPInventoryComponent::SlotSelected);
	InventoryItemDroppedHandle = UEventRouterSubsystem::SubscribeToEvent<FItemDroppedEvent>(this,UIEventsTag,&UMPInventoryComponent::RemoveItem);
	InventoryItemUpdatedHandle = UEventRouterSubsystem::SubscribeToEvent<FItemUpdatedEvent>(this,UIEventsTag,&UMPInventoryComponent::UpdateItem);

}

void UMPInventoryComponent::AddItem(const FItemPickedEvent& Ev)
{
	Inventory.Add(Ev.Item);
	//UEventRouterSubsystem::BroadcastEvent(this, "UI.Dialogues", FGenericDialogueEvent{Ev.Item->PickupSentence});
}

void UMPInventoryComponent::RemoveItem(const FItemDroppedEvent& Event)
{
	//RemoveItem(Event.InventorySlot->GetItem());
}

void UMPInventoryComponent::RemoveItem(UMPItem* ItemToRemove)
{
	Inventory.Remove(ItemToRemove);
}

bool UMPInventoryComponent::HasItem(TArray<UMPItem*> ItemsToCheck) const
{
	for (auto ToCheck : ItemsToCheck)
	{
		if (Inventory.Contains(ToCheck))
		{
			return true;
		}
	}
	return false;
}

void UMPInventoryComponent::ToggleInventory()
{
	// if (!InspectItemActor) return;
	// if (InspectItemActor->IsInspecting())
	// {
	// 	CloseInspectView();
	// }
	// else
	// {
	// 	bInventoryOpen = !bInventoryOpen;
	// 	UEventRouterSubsystem::BroadcastEvent(this, UIEventsTag, FInventoryToggle(bInventoryOpen));
	// }
}

void UMPInventoryComponent::ToggleInventory(const FInventoryToggle& Event)
{
	bInventoryOpen = Event.bOpen;
}

void UMPInventoryComponent::SlotSelected(const FSlotSelectedEvent& SlotSelectedEvent)
{
	if (InventoryMode == EInventoryMode::Default)
	{
		//InspectItemActor->InspectItem(SlotSelectedEvent.InventorySlot->GetItem());
	}
	else if (InventoryMode == EInventoryMode::MatchKeyItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("Picking in TryDropItem:"));
		// if ( CurrentDropZone->ReceiveItem(SlotSelectedEvent.InventorySlot->GetItem()))
		// {
		// 	UE_LOG(LogTemp, Warning, TEXT("Item dropped"));
		// 	UEventRouterSubsystem::BroadcastEvent(this, UIEventsTag, FItemDroppedEvent{SlotSelectedEvent.InventorySlot});
		// 	ToggleInventory();
		// }
	}
}


void UMPInventoryComponent::RotateItem(const FInputActionValue& Value)
{
	// if (!InspectItemActor->IsInspecting())
	// 	return;
	// InspectItemActor->RotateItem(Value.Get<FVector2D>()*3.0f);
}

void UMPInventoryComponent::OnPointerDown(const FInputActionValue& Value)
{
	// if (!InspectItemActor->IsInspecting())
	// 	return;
	// InspectItemActor->CheckHitResult();
}

void UMPInventoryComponent::OnZoom(const FInputActionValue& InputActionValue)
{
	// if (!InspectItemActor->IsInspecting())
	// 	return;
	// InspectItemActor->Zoom(InputActionValue.Get<float>());
}

void UMPInventoryComponent::CloseInspectView()
{
	// InspectItemActor->CloseInspectWidget();
}

void UMPInventoryComponent::BeginDestroy()
{
	UEventRouterSubsystem::UnsubscribeFromEvent(this, "UI.Inventory", InventoryPickedUpHandle);
	Super::BeginDestroy();
}


