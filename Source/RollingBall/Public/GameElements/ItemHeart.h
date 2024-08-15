// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElements/ItemBase.h"
#include "ItemHeart.generated.h"

UCLASS()
class ROLLINGBALL_API AItemHeart : public AItemBase {
	GENERATED_BODY()

public:
	// Constructor
	AItemHeart();

protected:
	// アイテムを取得する処理をOverride
	void GetItem() override;

public:
	// 回復量
	UPROPERTY(EditAnywhere, Category = "Item")
	float HealValue = 25.0f;
};