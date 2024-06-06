// Fill out your copyright notice in the Description page of Project Settings.


#include "GameElements/CheckpointActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Character/BallPlayer.h"
#include "Framework/InGameGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACheckpointActor::ACheckpointActor()
{
	// StaticMeshComponentを追加し、RootComponentに設定する
	Checkpoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentCheckpoint"));
	RootComponent = Checkpoint;

	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* CheckpointMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/RollingBall/Enviroment/Meshes/S_Checkpoint"));

	// StaticMeshをStaticMeshComponentに設定する
	Checkpoint->SetStaticMesh(CheckpointMesh);

	// StaticMeshComponentを追加し、RootComponentにAttachする
	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponentButton"));
	Button->SetupAttachment(RootComponent);

	// StaticMeshをLaodしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* ButtonMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/RollingBall/Enviroment/Meshes/S_CheckpointButton"));

	// StaticMeshをStaticMeshComponentに設定する
	Button->SetStaticMesh(ButtonMesh);

	// SphereCollisionを追加する
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);

	// Radiusを設定する
	Sphere->SetSphereRadius(70.0f);

	// SceneComponentを作成する
	CheckTransform = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	CheckTransform->SetupAttachment(RootComponent);

	// 高さを調整する
	CheckTransform->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	// OnComponentBeginOverlapをBindする
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OnSphereBeginOverlap);
}

void ACheckpointActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 接触したActorがBallPlayerか判定する
	if (const ABallPlayer* Player = Cast<ABallPlayer>(OtherActor))
	{
		// GameModeを取得して、InGameGameModeにCastする
		if (AInGameGameMode* GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			//　CheckTransformのWorldTransformを取得する
			const FTransform& WorldTransform = CheckTransform->GetComponentToWorld();

			// Transform情報が一致しなかったらSpawnするTransform情報を更新する
			if (!GameMode->SpawnTransform.Equals(WorldTransform))
			{
				// RespawnするTransform情報を更新する
				GameMode->SpawnTransform = WorldTransform;
			}
		}
	}
}
