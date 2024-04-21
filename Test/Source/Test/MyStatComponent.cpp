// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// InitializeComponent() 함수를 호출하려면 true로 설정 필요.
	bWantsInitializeComponent = true;

	Level = 1;
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(Level);
}

void UMyStatComponent::SetLevel(const int32 ChangedLevel)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (MyGameInstance)
	{
		auto StatData = MyGameInstance->GetStatData(ChangedLevel);
		
		if (StatData)
		{
			Level	= StatData->Level;
			MaxHp	= StatData->MaxHp;
			Attack	= StatData->Attack;

			SetHp(StatData->MaxHp);

			UE_LOG(LogTemp, Warning, TEXT("UMyStatComponent::SetLevel %d %d %d"), Level, MaxHp, Attack);
		}
	}
}

void UMyStatComponent::SetHp(const int32 NewHP)
{
	Hp = NewHP;

	if (Hp < 0)
		Hp = 0;

	OnHpChanged.Broadcast();
}

void UMyStatComponent::OnAttacked(float DamageAmount)
{
	int32 newHP = Hp - DamageAmount;
	SetHp(newHP);

	//UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"), Hp);
}

float UMyStatComponent::GetHpRatio() const
{
	if (0 == Hp || 0 == MaxHp)
		return 0.f;

	return static_cast<float>(Hp / MaxHp);
}

