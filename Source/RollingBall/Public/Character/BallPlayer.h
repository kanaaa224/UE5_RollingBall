// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "BallPlayer.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class ROLLINGBALL_API ABallPlayer : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABallPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Hit EventをBindingする関数
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// PlayerにDamageを与える
	float TakeDamagePlayer(const float Damage);

	// PlayerをReboundさせる
	void Rebound(const float ReboundPower);

	// Playerを回復させる
	float Heal(const float Value);

	float GetHealth() const { return Health; }

	float GetHealthMax() const { return HealthMax; }

protected:
	// BallをControl
	void ControlBall(const FInputActionValue& Value);

	// 視点を操作
	void Look(const FInputActionValue& Value);

	// ジャンプ
	void Jump(const FInputActionValue& Value);

	// 加速する
	void Boost(const FInputActionValue& Value);

private:
	// Character用のStaticMesh - Sphere
	UPROPERTY(VisibleAnywhere, Category = Character, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Sphere;

	// Cameraを配置するためのSpringArm
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;

	// SpringArmの先端に配置するカメラ
	UPROPERTY(VisibleAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

	// 進行方向を表示するArrowComponent
	UPROPERTY(VisibleAnywhere, Category = Control, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> Arrow;

	// MappingContext
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	// Input Action - Control
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ControlAction;

	// Input Action - Look
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	// Input Action - Jump
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	// Input Action - Boost
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> BoostAction;

	// 速度
	float Speed = 300.0f;

	// 体力
	float Health = 100.0f;

	// 最大体力
	float HealthMax = 100.0f;

	// ジャンプに加える力
	float JumpImpulse = 500.0f;

	// ジャンプができるか判定するフラグ
	bool CanJump = false;

	// 加速する早さ
	float Torque = 500000000.0f;
};