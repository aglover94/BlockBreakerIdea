// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerPaddleController.generated.h"

class ABall;

UCLASS()
class BLOCKBREAKER_API APlayerPaddleController : public APlayerController
{
	GENERATED_BODY()

		APlayerPaddleController();

	UFUNCTION()
		virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;

	//Function to move the paddle horizontally
	void MoveHorizontal(float AxisValue);
	
	//Function to launch the ball
	void LaunchBall();

	//The Ball Object
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABall> BallObj;

	ABall* MyBall;

	//Set Spawn Position for the ball
	FVector SpawnPos = FVector(10.0f, 0.0f, 40.0f);
	//Set Spawn Rotation for the ball
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;

public:
	//Function to spawn a new ball
	void SpawnNewBall();
};
