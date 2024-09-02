// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blow.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class ROLLINGBALL_API ABlow : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlow();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Blow用 StaticMesh - BlowMesh
	UPROPERTY(VisibleAnywhere, Category = Trap, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BlowMesh;

	// 吹き飛ばし用 Box Collision - Box
	UPROPERTY(VisibleAnywhere, Category = Trap, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Box;

	// プレイヤーを吹き飛ばす
	UFUNCTION()
	void BlowPlayer(AActor* Player);

public:
	// 吹き飛ばす強さ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blow")
	float BlowStrength;
};