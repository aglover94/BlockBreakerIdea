// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

class UProjectileMovementComponent;

UCLASS()
class BLOCKBREAKER_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	//Used to launch the ball
	virtual void Launch();

	//Used to make sure don't try to launch ball a second time while already launched
	bool IsBallLaunched;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The static mesh for the ball
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Ball;

	//The movement for the ball
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UProjectileMovementComponent* ProjectileMovement;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Function to return the ball
	UFUNCTION()
		UStaticMeshComponent* GetBall();
};
