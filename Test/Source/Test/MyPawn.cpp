// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pMesh		= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	m_pMovement	= CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));

	RootComponent = m_pMesh;

	// 메쉬 로드
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Couch.SM_Couch'"));

	if (SM.Succeeded())
	{
		m_pMesh->SetStaticMesh(SM.Object);
	}

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPawn::LeftRight);

}

void AMyPawn::UpDown(float value)
{
	if (0.0f == value)
		return;

	//UE_LOG(LogTemp, Warning, TEXT("UpDown %f"), value);
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyPawn::LeftRight(float value)
{
	if (0.0f == value)
		return;

	//UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), value);
	AddMovementInput(GetActorRightVector(), value);
}

