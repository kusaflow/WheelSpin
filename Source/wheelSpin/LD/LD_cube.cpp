// Fill out your copyright notice in the Description page of Project Settings.


#include "LD_cube.h"

// Sets default values
ALD_cube::ALD_cube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sphereCollision"));
	RootComponent = cube;

}

// Called when the game starts or when spawned
void ALD_cube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALD_cube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALD_cube::setSM(int idx) {
	switch (idx) {
	case 1 :
		break;
	case 2 :
		break;
	default:
		break;
	}
}

