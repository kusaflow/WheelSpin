// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelMngr.h"
#include "Kismet/GameplayStatics.h"
#include "../kusaGameInstance.h"

// Sets default values
ALevelMngr::ALevelMngr()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelMngr::BeginPlay()
{
	Super::BeginPlay();
	initBlocks();
	//next_Milestone += 1000 * 10;
}

// Called every frame
void ALevelMngr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UkusaGameInstance* gameInst = Cast<UkusaGameInstance>(GetGameInstance());
	int playerPosX =  gameInst->playerPos;

	

	if (playerPosX >= next_Milestone) {
		UpdateLevel();
	}

}

void ALevelMngr::initBlocks() {

	init_block = true;
	for (int i = 0; i < 10; i++) {
		CreateLevelBlock();
		if (i == 2) {
			next_Milestone = xpos;

		}if (i == 5) {
			start = false;
		}

	}

	init_block = false;

}


void ALevelMngr::popBlock() {

	if (LB_array.IsEmpty()) {
		return;
	}
	TArray<AActor*> rem;
	LB_array.Peek(rem);
	LB_array.Pop();
	//UE_LOG(LogTemp, Warning, TEXT("%d"), rem.Num());
	if (rem.Num() >= 0) {
		while (rem.Num() != 0) {
			AActor* toDest = rem.Pop();
			if (toDest) {
				toDest->Destroy();
			}
		}
	}


}

void ALevelMngr::UpdateLevel() {

	//next_Milestone += 1000;

	CreateLevelBlock();
	popBlock();

}

void ALevelMngr::CreateLevelBlock() {
	FActorSpawnParameters spawnPara;
	spawnPara.Owner = this;

	TArray<AActor*> blocks;

	UWorld* world = GetWorld();

	int y_sz = 10;

	int wToSelect = 10;

	if (!hasNext)
		wToSelect = (int)FMath::FRandRange(1, 4);

	hasNext = false;

	if (start)
		wToSelect = 10;


	//powerUps ==============================================================================
	//jump UP----------------------------
	if (PU_JumpUp) {
		AActor* bl = world->SpawnActor<AActor>(PU_JumpUp,
			FVector(xpos + FMath::FRandRange(20, 180), FMath::FRandRange(-880, 880), 0),
			FRotator(0), spawnPara);
		bl->SetActorScale3D(FVector(1, 1, 1.05f));
		blocks.Push(bl);
	}

	if ((int)(FMath::FRandRange(0,100))%10 == 0) {
	//if (true){
		int pIdx = (int)FMath::FRandRange(1, 3);
		//pIdx = 3;

		//=====================slow Down
		if (pIdx == 1 && PU_slowDown) {
			AActor* bl = world->SpawnActor<AActor>(PU_slowDown, 
				FVector(xpos + FMath::FRandRange(20, 180), FMath::FRandRange(-880, 880), 0),
				FRotator(0), spawnPara);
			bl->SetActorScale3D(FVector(1, 1, 5));
			blocks.Push(bl);
		}
		//speed UP----------------------------
		else if (pIdx == 2 && PU_speedUp) {
			AActor* bl = world->SpawnActor<AActor>(PU_speedUp,
				FVector(xpos + FMath::FRandRange(20, 180), FMath::FRandRange(-880, 880), 0),
				FRotator(0), spawnPara);
			bl->SetActorScale3D(FVector(1, 1, 5));
			blocks.Push(bl);
		}



		
	}


	///--------------------------------hole1
	 if (wToSelect == 1) {

		 next_Milestone += 1000;
		 if (Base_hole1) {
			 AActor* floor = world->SpawnActor<AActor>(Base_hole1, FVector(xpos + 500, 0, 0), FRotator(0), spawnPara);
			 blocks.Push(floor);
		 }
		 xpos += 1000;
		 hasNext = true;
		 wToSelect = 1000;
	}
	///-------------------------------- hole2
	else if (wToSelect == 2) {

		 next_Milestone += 1000;
		 if (Base_hole2) {
			 AActor* floor = world->SpawnActor<AActor>(Base_hole2, FVector(xpos + 500, 0, 0), FRotator(0), spawnPara);
			 blocks.Push(floor);
		 }
		 xpos += 1000;
		 hasNext = true;
		 wToSelect = 1000;
	}

	//normal
	else {
		 next_Milestone += 1000;
		if (Base_Track) {
			AActor* floor = world->SpawnActor<AActor>(Base_Track, FVector(xpos + 500, 0, 0), FRotator(0), spawnPara);
			blocks.Push(floor);
		}
		xpos += 1000;
	}


	if (init_block)
		next_Milestone -= 1000;

	LB_array.Enqueue(blocks);


}



