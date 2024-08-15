// Fill out your copyright notice in the Description page of Project Settings.

#include "GameElements/GoalActor.h"

#include "Character/BallPlayer.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGoalActor::AGoalActor() {
	// StaticMeshComponentを追加し、RootComponentに設定する
	Goal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = Goal;

	// StaticMeshをLoadしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/RollingBall/Enviroment/Meshes/S_Goal")); // TODO: Environment

	// StaticMeshをStaticMeshComponentに設定する
	Goal->SetStaticMesh(Mesh);

	// SphereCollisionを追加する
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);

	// Radiusを設定する
	Sphere->SetSphereRadius(72.0f);

	// OnComponentBeginOverlapをBindする
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGoalActor::OnSphereBeginOverlap);
}

void AGoalActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// 接触したActorがBallPlayerか判定する
	if (const ABallPlayer* player = Cast<ABallPlayer>(OtherActor)) {
		// 遷移するLevelをLoadする
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, LoadLevel);
	}
}