// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

#include "Components\StaticMeshComponent.h"
#include "GameFramework\ProjectileMovementComponent.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create sub object of type UStaticMeshComponent
	SM_Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	//Set root component to the static mesh
	RootComponent = SM_Ball;

	SM_Ball->SetSimulatePhysics(true); //Set SimulatePhysics on the static mesh to true
	SM_Ball->SetEnableGravity(false); //Don't enable gravity on the static mesh
	SM_Ball->SetConstraintMode(EDOFMode::XZPlane); //Constrain the movement to the XZ plane
	SM_Ball->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); //Set collision to QueryAndPhysics
	SM_Ball->SetCollisionProfileName(TEXT("PhysicsActor")); //Set the collision profile name to PhysicsActor

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->bShouldBounce = true; //Set that it should bounce
	ProjectileMovement->Bounciness = 1.1f; //Set bounciness value to 1.1f
	ProjectileMovement->Friction = 0.0f; //Set friction value to 0
	ProjectileMovement->Velocity.X = 0.0f; //Set velocity along X to 0
}



// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABall::Launch()
{
	//Check if the ball isn't launched yet
	if (!IsBallLaunched)
	{
		//If it isn't then add impulse to the static mesh
		SM_Ball->AddImpulse(FVector(140.0f, 0.0f, 130.0f), FName(), true);

		//Set IsBallLaunched to true
		IsBallLaunched = true;
	}
}

UStaticMeshComponent * ABall::GetBall()
{
	//Return the ball static mesh
	return SM_Ball;
}

