// Fill out your copyright notice in the Description page of Project Settings.

#include "Kadai/jumpBoard.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Character/BallPlayer.h"

// Sets default values
AjumpBoard::AjumpBoard() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// StaticMeshComponentを追加し、RootComponentに設定する
	JumpBoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = JumpBoardMesh;

	// StaticMeshをLoadしてStaticMeshComponentのStaticMeshに設定する
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Kadai/Meshes/SM_JumpBoard"));

	// StaticMeshをStaticMeshComponentに設定する
	JumpBoardMesh->SetStaticMesh(Mesh);

	// BoxComponentを追加し、BoxComponentをRootComponentにAttachする
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->SetupAttachment(RootComponent);

	// Boxのサイズを設定する
	Box->SetBoxExtent(FVector(25.0f, 12.5f, 5.0f));

	// Boxの位置を調整する
	Box->SetRelativeLocation(FVector(0.0f, -50.0f, 5.0f), false);

	// OnComponentBeginOverlapをBindする
	Box->OnComponentBeginOverlap.AddDynamic(this, &AjumpBoard::OnBoxBeginOverlap);

	// ジャンプ台の展開値を初期化
	Expanded = 0.0f;

	// 初期時のジャンプ台の展開値上限
	ExpandUpperLimit = 20.0f;
}

// Called when the game starts or when spawned
void AjumpBoard::BeginPlay() {
	Super::BeginPlay();

	// 初期ローテーションを保存
	InitialRotation = GetActorRotation();
}

// Called every frame
void AjumpBoard::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// ジャンプ台が展開していたら、展開を徐々に戻す
	if (Expanded) {
		Expanded--;

		FRotator Rotation = InitialRotation + FRotator(0.0f, 0.0f, Expanded);
		SetActorRotation(Rotation);
	}
}

void AjumpBoard::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	// ジャンプ台が展開していないとき、展開する
	if (!Expanded) {
		FRotator Rotation = InitialRotation + FRotator(0.0f, 0.0f, ExpandUpperLimit);
		SetActorRotation(Rotation);

		Expanded = ExpandUpperLimit;
	}
}