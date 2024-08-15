// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/BallPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/InGameGameMode.h"

// Sets default values
ABallPlayer::ABallPlayer() {
	// StaticMeshComponentを追加し、RootComponentに設定
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = Sphere;

	// StaticMeshをLoadし、StaticMeshComponentのStaticMeshに設定
	UStaticMesh* Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Sphere"));

	// StaticMeshをStaticMeshComponentに設定
	Sphere->SetStaticMesh(Mesh);

	// MaterialをStaticMeshに設定
	UMaterial* Material = LoadObject<UMaterial>(nullptr, TEXT("/Engine/BasicShapes/BasicShapeMaterial"));

	// MaterialをStaticMeshComponentに設定
	Sphere->SetMaterial(0, Material);

	// Simulate Physicsを有効にする
	Sphere->SetSimulatePhysics(true);

	// CollisionPresetを「PhysicsActor」に変更
	Sphere->SetCollisionProfileName(TEXT("PhysicsActor"));

	// Hit Eventを有効にする
	Sphere->BodyInstance.bNotifyRigidBodyCollision = true;

	// SpringArmを追加
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(RootComponent);

	// SpringArmの長さを調整
	SpringArm->TargetArmLength = 450.0f;

	// PawnのControllerRotationを使用
	SpringArm->bUsePawnControlRotation = true;

	// CameraのLagを有効にする
	SpringArm->bEnableCameraLag = true;

	// Cameraを追加
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(SpringArm);

	// MotionBlurをオフにする
	Camera->PostProcessSettings.MotionBlurAmount = 0.0f;

	// Arrowを追加
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	Arrow->SetupAttachment(Camera);

	// Sphereの頭上に移動するようにLocationを設定
	Arrow->SetRelativeLocation(FVector(400.0f, 0.0f, 130.0f));

	// Arrowを表示されるようにする
	Arrow->bHiddenInGame = false;

	// Input Mapping Context「IM_Controls」を読み込む
	DefaultMappingContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/RollingBall/Input/IM_Controls"));

	// Input Action「IA_Control」を読み込む
	ControlAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/RollingBall/Input/Action/IA_Control"));

	// Input Action「IA_Look」を読み込む
	LookAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/RollingBall/Input/Action/IA_Look"));

	// Input Action「IA_Jump」を読み込む
	JumpAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/RollingBall/Input/Action/IA_Jump"));

	// Input Action「IA_Boost」を読み込む
	BoostAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/RollingBall/Input/Action/IA_Boost"));
}

// Called when the game starts or when spawned
void ABallPlayer::BeginPlay() {
	Super::BeginPlay();

	//Add Input Mapping Context
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ABallPlayer::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) {
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	CanJump = true;
}

// Called to bind functionality to input
void ABallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		// ControlBallとIA_ControlのTriggeredをBind
		EnhancedInputComponent->BindAction(ControlAction, ETriggerEvent::Triggered, this, &ABallPlayer::ControlBall);

		// LookとIA_LookのTriggeredをBind
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABallPlayer::Look);

		// JumpとIA_JumpのTriggeredをBind
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ABallPlayer::Jump);

		// BoostとIA_BoostのTriggeredをBind
		EnhancedInputComponent->BindAction(BoostAction, ETriggerEvent::Triggered, this, &ABallPlayer::Boost);
	}
}

float ABallPlayer::TakeDamagePlayer(const float Damage) {
	Health = Health - Damage;

	if (Health <= 0) {
		// GameModeを取得して、InGameGameModeにCast
		if (AInGameGameMode* GameMode = Cast<AInGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()))) {
			// KillPlayerを呼び出してPlayerを破棄
			GameMode->KillPlayer(this);
		}
	}

	return Health;
}

void ABallPlayer::Rebound(const float ReboundPower) {
	// Reboundさせるimpulseの値を算出
	FVector impulse = Arrow->GetForwardVector() * (-1.0f * ReboundPower);

	// Sphereに力を与える
	Sphere->AddImpulse(impulse, TEXT("None"), true);
}

float ABallPlayer::Heal(const float Value) {
	// HealthがHealthMax以上にならないように制限
	Health = FMath::Clamp(Health + Value, 0, HealthMax);

	return Health;
}

void ABallPlayer::ControlBall(const FInputActionValue& Value) {
	// inputのValueはVector2Dに変換できる
	const FVector2D V = Value.Get<FVector2D>();

	// Vectorを計算
	FVector ForceVector = FVector(V.Y, V.X, 0.0f) * Speed;

	// Arrowの進行方向のVectorを計算
	FVector ArrowForceVector = Arrow->GetComponentToWorld().TransformVectorNoScale(ForceVector);
	//UKismetMathLibrary::TransformDirection(Arrow->GetComponentToWorld(), ForceVector);

	// Sphereに力を加える
	Sphere->AddForce(ArrowForceVector, TEXT("NONE"), true);
}

void ABallPlayer::Look(const FInputActionValue& Value) {
	// inputのValueはVector2Dに変換できる
	const FVector2D V = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		// add yaw and pitch input to controller
		AddControllerYawInput(V.X);
		AddControllerPitchInput(V.Y);

		// Pawnが持っているControlの角度を取得
		FRotator ControlRotate = GetControlRotation();

		// controllerのPitchの角度を制限
		double LimitPitchAngle = FMath::ClampAngle(ControlRotate.Pitch, -40.0f, -10.0f);

		// PlayerControllerの角度を設定
		UGameplayStatics::GetPlayerController(this, 0)->SetControlRotation(FRotator(LimitPitchAngle, ControlRotate.Yaw, 0.0f));
	}
}

void ABallPlayer::Jump(const FInputActionValue& Value) {
	// inputのValueはboolに変換できる
	if (const bool V = Value.Get<bool>() && CanJump) {
		Sphere->AddImpulse(FVector(0.0f, 0.0f, JumpImpulse), TEXT("None"), true);
		CanJump = false;
	}
}

void ABallPlayer::Boost(const FInputActionValue& Value) {
	// inputのValueはboolに変換できる
	if (const bool V = Value.Get<bool>()) {
		// Arrowが向いている前方方向のVector情報を取得
		FVector ForwardVector = Arrow->GetForwardVector().GetSafeNormal(0.0001f);

		// Torqueとして与えるVectorを作成
		FVector TorqueVector = FVector(ForwardVector.Y * Torque * -1.0f, ForwardVector.X * Torque, 0.0f);

		// Torqueを与えて加速する
		Sphere->AddTorqueInRadians(TorqueVector, TEXT("None"), true);
	}
}