// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

#define OUT //for annotation only


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();	
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (physicsHandle) {
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing physicsHandle"), *GetOwner()->GetFName().ToString())
	}
	if (inputComponent) {
		inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		inputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Released);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing inputComponent"), *GetOwner()->GetFName().ToString())
	}
}

void UGrabber::Grab() {
	//UE_LOG(LogTemp, Warning, TEXT("grab"))
	FHitResult hitObject = RayCastObject().hitObject;
	if (hitObject.GetActor()) {
		auto componentToGrab = hitObject.GetComponent();
		physicsHandle->GrabComponentAtLocationWithRotation(componentToGrab, NAME_None,
			componentToGrab->GetOwner()->GetActorLocation(),
			componentToGrab->GetOwner()->GetActorRotation());
	}
}

void UGrabber::Released() {
	//UE_LOG(LogTemp, Warning, TEXT("released"))
	physicsHandle->ReleaseComponent();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!physicsHandle) return;	
	if (physicsHandle->GetGrabbedComponent()) {
		FVector endLocation = RayCastObject().endLocation;
		physicsHandle->SetTargetLocation(endLocation);
	}
}

LineTraceObjects UGrabber::RayCastObject () const
{
	FVector viewPointLocation;
	FRotator viewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewPointLocation, OUT viewPointRotation);
	/*UE_LOG(LogTemp, Warning, TEXT("%s %s"), *viewPointLocation.ToString(), *viewPointRotation.ToString())*/
	/*DrawDebugLine(GetWorld(), viewPointLocation, viewPointLocation + viewPointRotation.Vector()*reach, FColor(255, 0, 0),
		false, -1, 0,
		12.333);*/
	FCollisionQueryParams queryParams(FName(TEXT("")), false, GetOwner());
	FHitResult hit;
	FVector endLocation = viewPointLocation + viewPointRotation.Vector()*reach;
	GetWorld()->LineTraceSingleByObjectType(OUT hit, viewPointLocation, endLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		queryParams);
	/*AActor* actor = hit.GetActor();
	if (actor) { //must check otherwise will crash engine
		FName actorName = actor->GetFName();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *actorName.ToString())
	}*/
	return { hit, endLocation };
}