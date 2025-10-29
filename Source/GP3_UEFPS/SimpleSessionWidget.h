// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SimpleSessionWidget.generated.h"

/**
 * 
 */
UCLASS()
class GP3_UEFPS_API USimpleSessionWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable) void CreateSession();
	UFUNCTION(BlueprintCallable) void FindSession();
};
