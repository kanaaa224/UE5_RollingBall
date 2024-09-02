// Fill out your copyright notice in the Description page of Project Settings.

#include "Kadai/Propeller.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APropeller::APropeller() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponentを追加し、RootComponentに設定する
	PropellerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = PropellerMesh;

	// StaticMeshをLoadしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Kadai/Meshes/SM_Propeller"));

	// StaticMeshをStaticMeshComponentに設定する
	PropellerMesh->SetStaticMesh(Mesh);

	// 初期回転角度
	RotationValue = FRotator(0.0f, 100.0f, 0.0f);
}

// Called every frame
void APropeller::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// DeltaTimeを掛けてフレームレートに依存せずに回転
	AddActorLocalRotation(RotationValue * DeltaTime);
}