// Fill out your copyright notice in the Description page of Project Settings.


// Sets default values
#include "MPItem.h"

AMPItem::AMPItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMPItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMPItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

