// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Propeller.generated.h"

class UStaticMeshComponent;

UCLASS()
class ROLLINGBALL_API APropeller : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APropeller();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Propeller用 StaticMesh - PropellerMesh
	UPROPERTY(VisibleAnywhere, Category = Trap, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> PropellerMesh;

public:
	// 回転角度
	UPROPERTY(EditAnywhere, Category = "Rotation")
	FRotator RotationValue;
};