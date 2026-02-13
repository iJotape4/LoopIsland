// Fill out your copyright notice in the Description page of Project Settings.


// Sets default values
#include "MPKeyItemDropZone.h"

AMPKeyItemDropZone::AMPKeyItemDropZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMPKeyItemDropZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMPKeyItemDropZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

