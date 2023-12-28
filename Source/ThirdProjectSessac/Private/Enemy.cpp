// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFunction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Weapon.h"
// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//임시 큐브 스켈레탈 메쉬
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'"));
	if (tempMesh.Succeeded())
	{

		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-90),FRotator(0,-90,0));

	}

	TextComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComp"));
	TextComp->SetupAttachment(GetMesh());
	TextComp->SetRelativeLocationAndRotation(FVector(-20,0,30),FRotator(0,90,0));
	
	GetCharacterMovement()->bOrientRotationToMovement = true;


	//액터 컴포넌트
	FunctionComp = CreateDefaultSubobject<UEnemyFunction>(TEXT("FunctionComp"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCapsuleComponentBeginOverlap);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
//이벤트 함수 이거는 어떻게 액터 컴포넌트로 보낼까?
void AEnemy::OnCapsuleComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto temp = Cast<AActor>(OtherActor);
		if (temp == nullptr)
		{
			return;
		}
		if (AWeapon* Weapon = Cast<AWeapon>(temp))
		{
			FunctionComp->SetState(EEnemyState::Damage);
		}
}
