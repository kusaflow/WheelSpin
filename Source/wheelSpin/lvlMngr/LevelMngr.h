// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelMngr.generated.h"

UCLASS()
class WHEELSPIN_API ALevelMngr : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelMngr();

	TQueue<TArray<AActor*>> LB_array;

	UPROPERTY(BlueprintReadOnly, Category = "kusavar")
	int next_Milestone;

	int xpos = -500000;

	bool start = true, init_block = true, hasNext = false;

	
	//kusa meshes===========================================================================/
	UPROPERTY(EditDefaultsOnly, category = "kusa_Meshes")
	TSubclassOf<class AActor> sharp_cube;

	UPROPERTY(EditDefaultsOnly, category = "kusa_Meshes")
	TSubclassOf<class AActor> smooth_cube;

	UPROPERTY(EditDefaultsOnly, category = "kusa_Meshes")
	TSubclassOf<class AActor> Base_Track;

	UPROPERTY(EditDefaultsOnly, category = "kusa_Meshes")
	TSubclassOf<class AActor> Base_hole1;

	UPROPERTY(EditDefaultsOnly, category = "kusa_Meshes")
	TSubclassOf<class AActor> Base_hole2;





	//power Ups ===================================================================>
	UPROPERTY(EditDefaultsOnly, category = "PowerUps")
	TSubclassOf<class AActor> PU_slowDown;

	UPROPERTY(EditDefaultsOnly, category = "PowerUps")
		TSubclassOf<class AActor> PU_speedUp;

	UPROPERTY(EditDefaultsOnly, category = "PowerUps")
		TSubclassOf<class AActor> PU_JumpUp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void UpdateLevel();

	void initBlocks();

	void CreateLevelBlock();

	void popBlock();

};
