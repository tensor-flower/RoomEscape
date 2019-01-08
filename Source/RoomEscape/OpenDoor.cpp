// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

#define OUT

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
	if (!pressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s missing pressurePlate"), *GetOwner()->GetFName().ToString())
	}
}




// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!pressurePlate) return;
	if (GetTotalMass()>thresholdMass) {
		OnOpenRequest.Broadcast();
		//lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	//if (GetWorld()->GetTimeSeconds() > lastDoorOpenTime + doorCloseDelay) {
		//CloseDoor();
	//}
	else {
		//CloseDoor();
		OnCloseRequest.Broadcast();
	}
}

float UOpenDoor::GetTotalMass() {
	float totalMass = 0.f;
	TArray<AActor*> overlappingActors;
	pressurePlate->GetOverlappingActors(OUT overlappingActors);
	for (const auto* actor : overlappingActors) {			
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		FName name = actor->GetOwner()->GetFName();
		//UE_LOG(LogTemp, Warning, TEXT("Actor's FName is %s"), *actor->GetName())
	}

	return totalMass;
}

