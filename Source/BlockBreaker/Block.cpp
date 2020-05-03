// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

#include "Components\StaticMeshComponent.h"
#include "Components\BoxComponent.h"
#include "Ball.h"
#include "Kismet\GameplayStatics.h"
#include "PlayerPaddle.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create sub object of type UStaticMeshComponent, then set the collisionEnabled to type QueryAndPhysics
	SM_Brick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
	SM_Brick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//Create a sub object of type UBoxComponent and then set the extent of the box to these values
	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Box_Collision->SetBoxExtent(FVector(25.0f, 10.0f, 10.0f));

	//Set the root component to the Box_Collision
	RootComponent = Box_Collision;

	//Create sub objects for the materials that will be used
	GreenMaterial = CreateDefaultSubobject<UMaterial>(TEXT("GreenMaterial"));
	OrangeMaterial = CreateDefaultSubobject<UMaterial>(TEXT("OrangeMaterial"));
	RedMaterial = CreateDefaultSubobject<UMaterial>(TEXT("RedMaterial"));

	//Set default numberOfHits to 0
	NumberOfHits = 0;
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();

	//Set notification for when the Box_Collision overlaps with something
	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABlock::OnOverlapBegin);

	//Set the default material of the block static mesh to the green material
	SM_Brick->SetMaterial(0, GreenMaterial);

	//Cast to the APlayerPaddle, and return the PlayerPawn at index 0
	PlayerPaddle_REF = Cast<APlayerPaddle>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}



// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlock::OnOverlapBegin(UPrimitiveComponent * OverlapComponent, AActor * OtherActor, 
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndexType, bool bFromSweep, 
	const FHitResult & SweepResult)
{
	//Check is otherActor has the ball tag, and that otherActor isn't this, and that otherComp is true
	if (OtherActor->ActorHasTag("Ball") && (OtherActor != this) && OtherComp)
	{
		//If all this is true then do this

		//Get the ball and modify the velocity of it
		ABall* MyBall = Cast<ABall>(OtherActor);
		FVector BallVelocity = MyBall->GetVelocity();
		BallVelocity *= (SpeedModify - 0.8f);
		MyBall->GetBall()->SetPhysicsLinearVelocity(BallVelocity, true);

		//Check if the number of hits is equal to 0
		if (NumberOfHits == 0)
		{
			//If it is then set the material on the block mesh to the OrangeMaterial
			SM_Brick->SetMaterial(0, OrangeMaterial);
			//Increase the number of hits value
			NumberOfHits++;
			//Increase the Score value at the PlayerPaddle reference
			PlayerPaddle_REF->Score += 50;
		}
		else if (NumberOfHits == 1)//Else check if the number of hits is equal to 1
		{
			//If it is then set the material on the block mesh to the RedMaterial
			SM_Brick->SetMaterial(0, RedMaterial);
			//Increase the number of hits value
			NumberOfHits++;
			//Increase the Score value at the PlayerPaddle reference
			PlayerPaddle_REF->Score += 100;
		}
		else
		{
			//Else do this
			//Increase the Score value at the PlayerPaddle reference
			PlayerPaddle_REF->Score += 150;
			
			FTimerHandle UnusedHandle; //Need to have this for use below but don't actual need to do anything with it
			//Use this to call the DestroyBlock function after 0.1 seconds, false is used so that it doesn't repeat
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &ABlock::DestroyBlock, 0.1f, false);
		}
	}
}

void ABlock::DestroyBlock()
{
	//Destroy this block in the level
	this->Destroy();
}

