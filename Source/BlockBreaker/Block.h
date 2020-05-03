// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

class UBoxComponent;
class UMaterial;
class APlayerPaddle;

UCLASS()
class BLOCKBREAKER_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The block static mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Brick;

	//The box collider to use for the block
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision;

	//Material properties for the different colours to show player
	UPROPERTY(EditAnywhere)
		UMaterial* GreenMaterial;

	UPROPERTY(EditAnywhere)
		UMaterial* OrangeMaterial;

	UPROPERTY(EditAnywhere)
		UMaterial* RedMaterial;

	//The number of times the blocks have been hit, making sure it can only be read in a blueprint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int NumberOfHits;
	
	//The modifier to change the speed of the ball when it hits a block
	float SpeedModify = 1.01f;
	

	//Function for when the ball overlaps with the block
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlapComponent, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
			const FHitResult& SweepResult);

	//Function to destroy the block
	void DestroyBlock();

	//Reference to APlayerPaddle
	APlayerPaddle* PlayerPaddle_REF;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
