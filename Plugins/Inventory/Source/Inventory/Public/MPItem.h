// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "MPItem.generated.h"

UCLASS()
class INVENTORY_API UMPItem : public UDataAsset
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UMPItem();
};
