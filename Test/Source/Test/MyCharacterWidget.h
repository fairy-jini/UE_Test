// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class TEST_API UMyCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindHp(class UMyStatComponent* StatCompo);
	void UpdateHP();
	
private:
	TWeakObjectPtr<class UMyStatComponent> CurStatCompo;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* PB_HpBar;
};
