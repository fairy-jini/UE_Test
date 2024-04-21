// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST_API UMyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	void SetLevel(const int32 ChangedLevel);
	void SetHp(const int32 NewHP);
	void OnAttacked(float DamageAmount);

	int32 GetLevel() const { return Level; }
	int32 GetHp() const { return Hp; }
	int32 GetMaxHp() const { return MaxHp; }
	float GetHpRatio() const;
	int32 GetAttack() const { return Attack; }

private:
	UPROPERTY(EditAnywhere, Category = Stat, Meta =(AllowPrivateAccess=true))
	int32 Level;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Hp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 MaxHp;

	UPROPERTY(EditAnywhere, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Attack;

public:
	FOnHpChanged OnHpChanged;

};
