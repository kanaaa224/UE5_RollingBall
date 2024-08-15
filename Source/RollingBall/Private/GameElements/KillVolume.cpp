// Fill out your copyright notice in the Description page of Project Settings.

#include "GameElements/KillVolume.h"
#include "Components/BoxComponent.h"
#include "Framework/InGameGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKillVolume::AKillVolume() {
	// SceneComponentを作成
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	// SceneComponentをRootComponentに設定
	RootComponent = DefaultSceneRoot;

	KillVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));

	// BoxComponentをRootComponentにAttach
	KillVolume->SetupAttachment(RootComponent);

	// BoxComponentのOnComponentBeginOverlapに関数「OnBoxBeginOverlap」を関連づけ
	KillVolume->OnComponentBeginOverlap.AddDynamic(this, &AKillVolume::OnBoxBeginOverlap);
}

void AKillVolume::OnConstruction(const FTransform& Transform) {
	// KillVolumeのBox Extentを変更
	KillVolume->SetBoxExtent(BoxExtent);
}

// Called when the game starts or when spawned
void AKillVolume::BeginPlay() {
	Super::BeginPlay();
}

void AKillVolume::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// 接触したActorがBallPlayerか判定する
	if (ABallPlayer* Player = Cast<ABallPlayer>(OtherActor)) {
		// GameModeを取得して、InGameGameModeにCastする
		if (AInGameGameMode* GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()))) {
			// KillPlayerを呼び出してPlayerを破棄する
			GameMode->KillPlayer(Player);
		}
	}
}