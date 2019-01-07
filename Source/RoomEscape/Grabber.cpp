// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

#define OUT //for annotation only

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewPointLocation, OUT viewPointRotation);
	/*UE_LOG(LogTemp, Warning, TEXT("%s %s"), *viewPointLocation.ToString(), *viewPointRotation.ToString())*/
	DrawDebugLine(GetWorld(), viewPointLocation, viewPointLocation + viewPointRotation.Vector()*reach, FColor(255, 0, 0),
		false, -1, 0,
		12.333);
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(OUT hit, viewPointLocation, viewPointLocation + viewPointRotation.Vector()*reach,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		queryParams);
	AActor* actor = hit.GetActor();
	if (actor) { //must check otherwise will crash engine
		FName actorName = actor->GetFName();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *actorName.ToString())
	}
}

