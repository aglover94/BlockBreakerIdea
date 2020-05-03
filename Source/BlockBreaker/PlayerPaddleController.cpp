// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddleController.h"

#include "Kismet\GameplayStatics.h"
#include "Camera\CameraActor.h"

#include "PlayerPaddle.h"
#include "Ball.h"

APlayerPaddleController::APlayerPaddleController()
{

}

void APlayerPaddleController::BeginPlay()
{
	TArray<AActor* > CameraActors;
	
	//Get all actors in the map of class
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);

	//Set the view to the cameraActor at index 0
	FViewTargetTransitionParams params;
	SetViewTarget(CameraActors[0], params);

	//Call the SpawnNewBall function
	SpawnNewBall();

}

void APlayerPaddleController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	//Bind the axis and actions to these
	InputComponent->BindAxis("MoveHorizontal", this, &APlayerPaddleController::MoveHorizontal);
	InputComponent->BindAction("Launch", IE_Pressed, this, &APlayerPaddleController::LaunchBall);
}



void APlayerPaddleController::MoveHorizontal(float AxisValue)
{
	//Cast to APlayerPaddle and get the pawn
	auto MyPawn = Cast<APlayerPaddle>(GetPawn());

	//Check if MyPawn is true
	if (MyPawn)
	{
		//If it is then call the MoveHorizontal function passing in the AxisValue parameter
		MyPawn->MoveHorizontal(AxisValue);
	}
}

void APlayerPaddleController::LaunchBall()
{
	//Launch the ball
	MyBall->Launch();
}

void APlayerPaddleController::SpawnNewBall()
{
	//Check if MYBall is false
	if (!MyBall)
	{
		//If it is then set MyBall to nullptr
		MyBall = nullptr;
	}

	//Check if BallObj is true
	if (BallObj)
	{
		//If it is then SpawnActor in the level
		MyBall = GetWorld()->SpawnActor<ABall>(BallObj, SpawnPos, SpawnRotation, SpawnInfo);
	}
}
