// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GoalActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class ROLLINGBALL_API AGoalActor : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGoalActor();

private:
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// 遷移するLevelのSoft参照
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
	TSoftObjectPtr<UWorld> LoadLevel;

private:
	// Goal用 StaticMesh - Goal
	UPROPERTY(VisibleAnywhere, Category = Goal, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Goal;

	// 接触判定用 Collision - Sphere
	UPROPERTY(VisibleAnywhere, Category = Goal, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Sphere;
};