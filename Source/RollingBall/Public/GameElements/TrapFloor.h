// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapFloor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class ROLLINGBALL_API ATrapFloor : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrapFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	// Trap用 StaticMesh - TrapMesh
	UPROPERTY(VisibleAnywhere, Category = Trap, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> TrapMesh;

	// PlayerにDamageを与えるBox Collision - Box
	UPROPERTY(VisibleAnywhere, Category = Trap, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Box;

public:
	// Playerに与えるDamage
	UPROPERTY(EditAnywhere, Category = "Trap")
	float Damage = 25.0f;

	// PlayerをReboundさせる強さ
	UPROPERTY(EditAnywhere, Category = "Trap")
	float Rebound = 600.0f;
};