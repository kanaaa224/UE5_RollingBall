// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameElements/ItemBase.h"
#include "ItemCoin.generated.h"

/**
 *
 */
UCLASS()
class ROLLINGBALL_API AItemCoin : public AItemBase
{
	GENERATED_BODY()

public:
	// Constructor
	AItemCoin();

protected:
	/** アイテムを取得する処理をOverrideする */
	void GetItem() override;

public:
	/** コインの取得枚数 */
	UPROPERTY(EditAnywhere, Category = "Item")
	int32 Number = 1;
};