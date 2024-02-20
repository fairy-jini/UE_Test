// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = m_pMesh;

	// 메쉬 로드
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Couch.SM_Couch'"));

	if (SM.Succeeded())
	{
		m_pMesh->SetStaticMesh(SM.Object);
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Logging/ELogVerbosity__Type/
	// 카테고리, 로깅 수준, 형식, 인자
	UE_LOG(LogTemp, Warning, TEXT("BeginePlay %d"), 3);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Error, TEXT("Tick %f"), DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, RotateSpeed * DeltaTime, 0.f));
}

