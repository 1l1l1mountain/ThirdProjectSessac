// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFunction.h"
#include "MyPlayer.h"
#include "EnhancedInputComponent.h"
#include "Weapon.h"

// Sets default values for this component's properties
UPlayerFunction::UPlayerFunction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerFunction::BeginPlay()
{
	Super::BeginPlay();



	Player = GetOwner<AMyPlayer>();
}


// Called every frame
void UPlayerFunction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerFunction::SetupPlayerInputComponent( UEnhancedInputComponent* EnhancedInputComponent, TArray <UInputAction*> inputs)
{

	EnhancedInputComponent->BindAction(inputs[2],ETriggerEvent::Triggered, this, &UPlayerFunction::Grabbed);
	EnhancedInputComponent->BindAction(inputs[2], ETriggerEvent::Completed, this, &UPlayerFunction::Dettached);

	// ��ǲ �迭 ���� ����
		// inputs[2] : IA_MouseInputClick_Bool_GDH


}

void UPlayerFunction::Grabbed()
{

	if (CurrentWeapon != nullptr) return;
	UWorld* world = GetWorld();

	//������ ���Ǿ� (���� Ʈ���̽� ����)
	TArray<FOverlapResult> hitInfos;
	FVector StartLoc = Player->RightHand->GetComponentLocation();
	FQuat StartDir = Player->RightHand->GetComponentQuat(); //FQuat�� ����� ���� �ǹ� �ϱ�? �����ϱ�
	//������ ���� ������
	if(world->OverlapMultiByProfile(hitInfos,StartLoc,StartDir,FName("PlayerWeapon"),FCollisionShape::MakeSphere(25.0f)))
	{
	//UE_LOG(LogTemp, Warning, TEXT("Exec!!")); 
	
	float MinDistance = 25.0f;
	int32 idx = 0;
	
	// � ��ü���� ���� (���� ����� ��ü)
	for (int32 i = 0;i < hitInfos.Num() - 1;i++)
	{
		//������ �ְ� �����϶��� ��
		if (hitInfos[i].GetActor()->IsA<AWeapon>())
		{
			float dist = FVector::Distance(hitInfos[i].GetActor()->GetActorLocation(), StartLoc);
			
			if (dist < MinDistance)
			{
				MinDistance = dist;
				idx = dist;
			}

		}

	}
	
	CurrentWeapon = Cast<AWeapon>(hitInfos[idx].GetActor());
	if (CurrentWeapon != nullptr)
	{
		
		CurrentWeapon->Grabbed(Player->RightHand,EAttachmentRule::SnapToTarget); //�׷��Լ� ���� �Ϸ�
		UE_LOG(LogTemp, Warning, TEXT("Grabbed!!")); //�߻�ȭ
	
	
	}
	
	
	
	
	}

	//DrawDebugSphere(world,StartLoc, 25.0f,30, FColor::Green ,false, 3, 0 ,1 );//���׸�Ʈ �Ķ���ʹ� ����?
	
}

void UPlayerFunction::Dettached()
{

	UE_LOG(LogTemp, Warning, TEXT("Dettached!!"));//�߻�ȭ
}

//��� ���ҹ�
//1. �÷��̾ �˾ƾ� �Ѵ�.
//2. �÷��̾�� ���� �˾ƾ� �Ѵ�.
//3. �÷��̾�� ���� ȣ���ϸ�, ���� �÷��̾ ȣ���Ѵ�.