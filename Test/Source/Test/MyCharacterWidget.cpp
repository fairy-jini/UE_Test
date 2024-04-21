// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterWidget.h"
#include "MyStatComponent.h"
#include "Components/ProgressBar.h"

void UMyCharacterWidget::BindHp(class UMyStatComponent* StatCompo)
{
	CurStatCompo = StatCompo;

	StatCompo->OnHpChanged.AddUObject(this, &UMyCharacterWidget::UpdateHP);
	StatCompo->GetHpRatio();
}


void UMyCharacterWidget::UpdateHP()
{
	if (CurStatCompo.IsValid())
	{
		PB_HpBar->SetPercent(CurStatCompo->GetHpRatio());
	}
}
