// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFunction.h"
#include "MyPlayer.h"
#include "EnhancedInputComponent.h"

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
	UWorld* world = GetWorld();
	if (CurrentWeapon != nullptr)
	{
		



		UE_LOG(LogTemp, Warning, TEXT("Grabbed!!")); //추상화
	
	
	}
	
}

void UPlayerFunction::Dettached()
{

	UE_LOG(LogTemp, Warning, TEXT("Dettached!!"));//추상화
}

//기능 분할법
//1. 플레이어를 알아야 한다.
//2. 플레이어에서 나를 알아야 한다.
//3. 플레이어에서 나를 호출하면, 내가 플레이어를 호출한다.