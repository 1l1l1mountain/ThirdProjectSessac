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

	// 인풋 배열 매핑 정보
		// inputs[2] : IA_MouseInputClick_Bool_GDH


}

void UPlayerFunction::Grabbed()
{

	if (CurrentWeapon != nullptr) return;
	UWorld* world = GetWorld();

	//오버랩 스피어 (라인 트레이싱 개념)
	TArray<FOverlapResult> hitInfos;
	FVector StartLoc = Player->RightHand->GetComponentLocation();
	FQuat StartDir = Player->RightHand->GetComponentQuat(); //FQuat가 제대로 무슨 의미 일까? 공부하기
	//감지된 것이 있을때
	if(world->OverlapMultiByProfile(hitInfos,StartLoc,StartDir,FName("PlayerWeapon"),FCollisionShape::MakeSphere(25.0f)))
	{
	//UE_LOG(LogTemp, Warning, TEXT("Exec!!")); 
	
	float MinDistance = 25.0f;
	int32 idx = 0;
	
	// 어떤 물체인지 고르기 (가장 가까운 물체)
	for (int32 i = 0;i < hitInfos.Num() - 1;i++)
	{
		//감지된 애가 무기일때만 비교
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
		
		CurrentWeapon->Grabbed(Player->RightHand,EAttachmentRule::SnapToTarget); //그랩함수 구현 완료
		UE_LOG(LogTemp, Warning, TEXT("Grabbed!!")); //추상화
	
	
	}
	
	
	
	
	}

	//DrawDebugSphere(world,StartLoc, 25.0f,30, FColor::Green ,false, 3, 0 ,1 );//세그먼트 파라미터는 뭐지?
	
}

void UPlayerFunction::Dettached()
{

	UE_LOG(LogTemp, Warning, TEXT("Dettached!!"));//추상화
}

//기능 분할법
//1. 플레이어를 알아야 한다.
//2. 플레이어에서 나를 알아야 한다.
//3. 플레이어에서 나를 호출하면, 내가 플레이어를 호출한다.