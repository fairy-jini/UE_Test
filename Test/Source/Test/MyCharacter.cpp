// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyAnimInstance.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	// 스켈레톤 메쉬 로드
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	animInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (animInstance)
	{
		animInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);
		animInstance->OnAttackHit.AddUObject(this, &AMyCharacter::AttackCheck);
	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Released, this, &AMyCharacter::Attack);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);
}

void AMyCharacter::Attack()
{
	if (isAttacking)
		return;

	animInstance->PlayAttackMontage();

	animInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % 3;

	isAttacking = true;
}

void AMyCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	const float AttackRange		= 100.f;
	const float AttackRadius	= 50.f;

	// 충돌 결과 가져오기
	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult
		, GetActorLocation()
		, GetActorLocation() + GetActorForwardVector() * AttackRange
		, FQuat::Identity
		, ECollisionChannel::ECC_GameTraceChannel2		// Config/DefaultEngine.ini 파일에서 확인 + 추가한 것으로 세팅
		, FCollisionShape::MakeSphere(AttackRadius)
		, Params
	);

	// 충돌 결과 확인
	FVector Vec			= GetActorForwardVector() * AttackRange;
	FVector Center		= GetActorLocation() + Vec * 0.5f;
	float HalfHeight	= AttackRange * 0.5f + AttackRadius;
	FQuat Rotation		= FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor	= bResult ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.0f);

	if (bResult && HitResult.Actor.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Hit Actor %s"), *HitResult.Actor->GetName());
	}
}

void AMyCharacter::UpDown(float value)
{
	//UE_LOG(LogTemp, Warning, TEXT("UpDown %f"), value);
	UpDownValue = value;
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyCharacter::LeftRight(float value)
{
	//UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), value);
	LeftRightValue = value;
	AddMovementInput(GetActorRightVector(), value);
}

void AMyCharacter::Yaw(float value)
{
	AddControllerYawInput(value);
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking = false;
}
