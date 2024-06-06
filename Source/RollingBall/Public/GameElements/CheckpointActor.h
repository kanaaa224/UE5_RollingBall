// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class ROLLINGBALL_API ACheckpointActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACheckpointActor();

private:
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** Checkpoint用のStaticMesh : Checkpoint */
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Checkpoint;

	/** Checkpoint用のStaticMesh : Button */
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Button;

	/** 接触判定用のCollision : Sphere */
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Sphere;

	/** Respawn用のTransformを更新するSceneComponent **/
	UPROPERTY(VisibleAnywhere, Category = Checkpoint, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> CheckTransform;
};