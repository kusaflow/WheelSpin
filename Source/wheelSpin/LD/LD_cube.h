// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LD_cube.generated.h"

UCLASS()
class WHEELSPIN_API ALD_cube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALD_cube();


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = mesh, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* cube;

	UPROPERTY(EditDefaultsOnly, category = "kusa_Meshes")
		class UStaticMeshComponent* c1;

	UPROPERTY(EditDefaultsOnly, category = "kusa_Meshes")
		class UStaticMeshComponent* c2;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setSM(int idx);

};
