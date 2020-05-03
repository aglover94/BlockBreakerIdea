// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddle.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerPaddle::APlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create sub object of type UFloatingPawnMovement
	SM_Paddle = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle"));
	//Set root component to eh SM_Paddle
	RootComponent = SM_Paddle;

	SM_Paddle->SetEnableGravity(false); //Don't enable gravity on the static mesh
	SM_Paddle->SetConstraintMode(EDOFMode::XZPlane); //Constrain the movement to the XZ plane
	SM_Paddle->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); //Set collision to QueryAndPhysics
	SM_Paddle->SetCollisionProfileName(TEXT("PhysicsActor")); //Set the collision profile name to PhysicsActor

	//Create sub object of type UFloatingPawnMovement
	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	//Set default score to 0
	Score = 0;
}

// Called when the game starts or when spawned
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();

	//Check if the Widget_Class doesn't equal nullptr
	if (Player_Score_Widget_Class != nullptr)
	{
		//If it doesn't then create the widget and add it to the viewPort
		Player_Score_Widget = CreateWidget(GetWorld(), Player_Score_Widget_Class);
		Player_Score_Widget->AddToViewport();
	}
	
}

// Called every frame
void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPaddle::MoveHorizontal(float AxisValue)
{
	AddMovementInput(FVector(AxisValue, 0.0f, 0.0), 1.0f, false);
}

