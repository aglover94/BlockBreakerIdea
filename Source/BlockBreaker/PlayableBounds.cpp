// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayableBounds.h"
#include "Components\BoxComponent.h"
#include "Kismet\GameplayStatics.h"
#include "PlayerPaddleController.h"

// Sets default values
APlayableBounds::APlayableBounds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a UBoxComponent subobject and set it as the rootComponent
	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = Box_Collision;

}

// Called when the game starts or when spawned
void APlayableBounds::BeginPlay()
{
	Super::BeginPlay();
	
	//Set notification for when the Box_Collision overlaps with something
	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &APlayableBounds::OnOverlapBegin);

	//Cast to the APlayerPaddleController, and return the PlayerController at index 0
	PlayerController_REF = Cast<APlayerPaddleController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void APlayableBounds::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayableBounds::OnOverlapBegin(UPrimitiveComponent * OverlapComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndexType, bool bFromSweep, const FHitResult & SweepResult)
{
	//Check if the otherActor that is overlapping has the tag Ball
	if (OtherActor->ActorHasTag("Ball"))
	{
		//If it does then destroy the ball, and using the PlayerController reference call the SpawnNewBall function
		OtherActor->Destroy();
		PlayerController_REF->SpawnNewBall();
	}
}
