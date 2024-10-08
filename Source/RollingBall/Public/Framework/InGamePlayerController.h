// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "InGamePlayerController.generated.h"

class UInputAction;

UCLASS()
class ROLLINGBALL_API AInGamePlayerController : public APlayerController {
	GENERATED_BODY()

public:
	// Constructor
	AInGamePlayerController();

protected:
	virtual void BeginPlay() override;

public:
	// APlayerControllerからOverride
	virtual void SetupInputComponent() override;

protected:
	// Pauseメニューを表示
	void DispPause(const FInputActionValue& Value);

private:
	// Input Action - Pause
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseAction;
};