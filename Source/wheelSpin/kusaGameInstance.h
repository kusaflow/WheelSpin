// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "kusaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WHEELSPIN_API UkusaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	float playerPos = 0;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	float BrakeTimer = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	float SpeedTimer = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "kusaVar")
	int WheelIdx = 0;

};
