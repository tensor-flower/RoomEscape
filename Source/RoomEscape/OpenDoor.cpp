// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();	
	actor = GetWorld()->GetFirstPlayerController()->GetPawn();
	CloseDoor();
}

void UOpenDoor::OpenDoor()
{
	GetOwner()->SetActorRotation(FRotator(0.f, openAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	GetOwner()->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (pressurePlate && pressurePlate->IsOverlappingActor(actor)) {
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() > lastDoorOpenTime + doorCloseDelay) {
		CloseDoor();
	}
}

