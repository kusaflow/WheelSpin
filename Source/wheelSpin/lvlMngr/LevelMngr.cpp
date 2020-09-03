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

	int wToSelect = 4;
	wToSelect = (int)FMath::FRandRange(1, 5);

	if (start)
		wToSelect = 1;


	//powerUps 
	if ((int)(FMath::FRandRange(0,100))%10 == 0) {
	//if (true){
		int pIdx = (int)FMath::FRandRange(1, 4);
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
		//jump UP----------------------------
		else if (pIdx == 3 && PU_JumpUp) {
			AActor* bl = world->SpawnActor<AActor>(PU_JumpUp,
				FVector(xpos + FMath::FRandRange(20, 180), FMath::FRandRange(-880, 880), 0),
				FRotator(0), spawnPara);
			bl->SetActorScale3D(FVector(1, 1, 1.05f));
			blocks.Push(bl);
		}
	}



	if (wToSelect == 1) {
		next_Milestone += 1000;
		for (int i = 0; i < 5; i++) {
			if (sharp_cube) {
				AActor* floor = world->SpawnActor<AActor>(sharp_cube, FVector(xpos + 100, 0, 0), FRotator(0), spawnPara);
				floor->SetActorScale3D(FVector(1, y_sz, 1));
				blocks.Push(floor);
			}
			xpos += 200;
		}
	}
	///--------------------------------very short bridge
	else if (wToSelect == 2) {
		next_Milestone += 1000;
		for (int i = 0; i < 5; i++) {
			if (sharp_cube) {
				if (i == 2) {
					AActor* b1 = world->SpawnActor<AActor>(smooth_cube, FVector(xpos + 100, -800, 0), FRotator(0), spawnPara);
					b1 ->SetActorScale3D(FVector(1, 2, 1));
					AActor* b2 = world->SpawnActor<AActor>(smooth_cube, FVector(xpos + 100, 0, 0), FRotator(0), spawnPara);
					b2->SetActorScale3D(FVector(1, 2, 1));
					AActor* b3 = world->SpawnActor<AActor>(smooth_cube, FVector(xpos + 100, 800, 0), FRotator(0), spawnPara);
					b3->SetActorScale3D(FVector(1, 2, 1));

					blocks.Push(b1); 
					blocks.Push(b2);
					blocks.Push(b3);
				}
				else {
					AActor* floor = world->SpawnActor<AActor>(smooth_cube, FVector(xpos + 100, 0, 0), FRotator(0), spawnPara);
					floor->SetActorScale3D(FVector(1, y_sz, 1));
					blocks.Push(floor);
				}
			}
			xpos += 200;
		}
	}
	///-------------------------------- short bridge
	else if (wToSelect == 3) {
		next_Milestone += 1000;
		for (int i = 0; i < 5; i++) {
			if (sharp_cube) {
				if (i % 2 == 0) {
					AActor* b1 = world->SpawnActor<AActor>(smooth_cube, FVector(xpos + 100, -800, 0), FRotator(0), spawnPara);
					b1->SetActorScale3D(FVector(1, 2, 1));
					AActor* b2 = world->SpawnActor<AActor>(smooth_cube, FVector(xpos + 100, 0, 0), FRotator(0), spawnPara);
					b2->SetActorScale3D(FVector(1, 2, 1));
					AActor* b3 = world->SpawnActor<AActor>(smooth_cube, FVector(xpos + 100, 800, 0), FRotator(0), spawnPara);
					b3->SetActorScale3D(FVector(1, 2, 1));

					blocks.Push(b1);
					blocks.Push(b2);
					blocks.Push(b3);
				}
				else {
					AActor* floor = world->SpawnActor<AActor>(smooth_cube, FVector(xpos + 100, 0, 0), FRotator(0), spawnPara);
					floor->SetActorScale3D(FVector(1, y_sz, 1));
					blocks.Push(floor);
				}
			}
			xpos += 200;
		}
	}
	///--------------------------------bridge
	else if (wToSelect == 4) {
		next_Milestone += 1000;
		for (int i = 0; i < 5; i++) {
			if (smooth_cube) {
				AActor* b1 = world->SpawnActor<AActor>(smooth_cube, FVector(xpos + 100, -800, 0), FRotator(0), spawnPara);
				b1->SetActorScale3D(FVector(1, 2, 1));
				AActor* b2 = world->SpawnActor<AActor>(smooth_cube, FVector(xpos + 100, 0, 0), FRotator(0), spawnPara);
				b2->SetActorScale3D(FVector(1, 2, 1));
				AActor* b3 = world->SpawnActor<AActor>(smooth_cube, FVector(xpos + 100, 800, 0), FRotator(0), spawnPara);
				b3->SetActorScale3D(FVector(1, 2, 1));

				blocks.Push(b1);
				blocks.Push(b2);
				blocks.Push(b3);
				
			}
			xpos += 200;
		}
	}

	//normal
	else {

	}


	if (init_block)
		next_Milestone -= 1000;

	LB_array.Enqueue(blocks);


}



