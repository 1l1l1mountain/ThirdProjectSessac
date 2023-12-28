// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/BoxComponent.h"
#include "Enemy.h"
#include "EnemyFunction.h"
// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxComp);
	BoxComp->SetBoxExtent(FVector(50, 10, 10));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	MeshComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Architecture/Pillar_50x500.Pillar_50x500'"));
	if (tempMesh.Succeeded())
	{
		MeshComp->SetStaticMesh(tempMesh.Object);
		MeshComp->SetRelativeScale3D(FVector(1,  0.2,0.2));
		//콜리전 처리는 다 블루 프린트로 진행할 예정
	}

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//어렵다 암기
void AWeapon::Grabbed(USkeletalMeshComponent* SkeletalComp, EAttachmentRule AttachmentRules)
{
	BoxComp->SetSimulatePhysics(false);


	if (AttachmentRules == EAttachmentRule::KeepWorld)
	{

		FAttachmentTransformRules rules = FAttachmentTransformRules::KeepWorldTransform;
		AttachToComponent(SkeletalComp, rules);

	}
	else if (AttachmentRules == EAttachmentRule::SnapToTarget)
	{

		FAttachmentTransformRules rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;//스케일 건들지 않고라는데 잘 모르겠음..
		AttachToComponent(SkeletalComp, rules,FName("GrabSocket"));
		
		//액터 로컬 트랜스폼 정보 바꿔주기
		SetActorRelativeLocation(LocationOffset);
		SetActorRelativeRotation(RotationOffset);
		SetActorRelativeScale3D(ScaleOffset);
	}
	//에너미 깨우기
# 

	//UE_LOG(LogTemp, Warning, TEXT("%d"),Enemies.Num());
	for (int32 i = 0;i < Enemies.Num();i++)
	{

		Enemies[i]->FunctionComp->SetState(EEnemyState::Move);


	}
	
}


