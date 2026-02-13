// Fill out your copyright notice in the Description page of Project Settings.


// Sets default values
#include "MPPickableItem.h"

AMPPickableItem::AMPPickableItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMPPickableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMPPickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

