// Fill out your copyright notice in the Description page of Project Settings.

#include "GameElements/ItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Character/BallPlayer.h"

// Sets default values
AItemBase::AItemBase()
{
	// StaticMeshComponentを追加し、RootComponentに設定する
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = ItemMesh;

	// SphereCollisionを追加する
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(RootComponent);

	// Radiusを設定する
	Sphere->SetSphereRadius(50.0f);

	// OnComponentBeginOverlapをBindする
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnSphereBeginOverlap);

	// RotatingMovementComponentを追加する
	RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovement->SetUpdatedComponent(ItemMesh);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

}

void AItemBase::GetItem()
{
	// 処理は子クラスで継承
}

void AItemBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 接触したActorがBallPlayerか判定する
	if (const ABallPlayer* Player = Cast<ABallPlayer>(OtherActor))
	{
		// Itemを取得する処理を実装する
		this->GetItem();

		// アイテムを破棄する
		this->Destroy();
	}
}