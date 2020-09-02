// Fill out your copyright notice in the Description page of Project Settings.


#include "WheelChar.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../kusaGameInstance.h"

// Sets default values
AWheelChar::AWheelChar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("sphereCollision"));
	RootComponent = wheel;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(wheel);
	cameraBoom->bDoCollisionTest = false;
	cameraBoom->TargetArmLength = 300;
	cameraBoom->SetRelativeRotation(FRotator(-30, 0, 0));
	cameraBoom->bInheritPitch = false;
	cameraBoom->bInheritRoll = false;
	cameraBoom->bInheritYaw = false;


	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void AWheelChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWheelChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UkusaGameInstance* gameInst = Cast<UkusaGameInstance>(GetGameInstance());
	gameInst->playerPos = RootComponent->GetComponentLocation().X;

	if (F_timer  >= 60) {
		wheel->AddAngularImpulse(FVector(0, 100 * DeltaTime, 0), NAME_None, true);
		//wheel->AddForce(FVector(0, 500 * DeltaTime, 0), NAME_None, true);
		F_timer = 0;
	}
	else {
		F_timer += DeltaTime * 120;
	}


}

// Called to bind functionality to input
void AWheelChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

