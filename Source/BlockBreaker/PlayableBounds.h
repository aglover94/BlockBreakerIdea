// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayableBounds.generated.h"

class UBoxComponent;
class APlayerPaddleController;

UCLASS()
class BLOCKBREAKER_API APlayableBounds : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayableBounds();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The box collider to bind the OnOverlapBegin function to
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision;

	//Function for when the ball goes outside the playable area
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlapComponent, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
			const FHitResult& SweepResult);

	//Reference to the PlayerPaddleController in the map
	APlayerPaddleController* PlayerController_REF;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
