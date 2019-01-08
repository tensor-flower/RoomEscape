// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorRequest);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintAssignable) FOnDoorRequest OnOpenRequest;
	UPROPERTY(BlueprintAssignable) FOnDoorRequest OnCloseRequest;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//UPROPERTY(EditAnywhere) float openAngle = -90.f;
	UPROPERTY(EditAnywhere) ATriggerVolume* pressurePlate = nullptr;
	//UPROPERTY(EditAnywhere) float doorCloseDelay = 0.6f;
	//float lastDoorOpenTime;
	float GetTotalMass();
	float thresholdMass = 40.f;
};
