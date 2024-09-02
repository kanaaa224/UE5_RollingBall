// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "jumpBoard.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class ROLLINGBALL_API AjumpBoard : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AjumpBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	// Blow用 StaticMesh - BlowMesh
	UPROPERTY(VisibleAnywhere, Category = Trap, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> JumpBoardMesh;

	// 吹き飛ばし用 Box Collision - Box
	UPROPERTY(VisibleAnywhere, Category = Trap, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> Box;

	// ジャンプ台の展開値
	float Expanded;

	// 配置時の向き
	FRotator InitialRotation;

public:
	// ジャンプ台の展開値上限
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Expand")
	float ExpandUpperLimit;
};