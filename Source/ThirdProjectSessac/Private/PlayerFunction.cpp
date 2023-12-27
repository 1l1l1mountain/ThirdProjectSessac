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

	// ��ǲ �迭 ���� ����
		// inputs[2] : IA_MouseInputClick_Bool_GDH


}

void UPlayerFunction::Grabbed()
{

	UE_LOG(LogTemp, Warning, TEXT("Grabbed!!"));
}

void UPlayerFunction::Dettached()
{

	UE_LOG(LogTemp, Warning, TEXT("Dettached!!"));
}

//��� ���ҹ�
//1. �÷��̾ �˾ƾ� �Ѵ�.
//2. �÷��̾�� ���� �˾ƾ� �Ѵ�.
//3. �÷��̾�� ���� ȣ���ϸ�, ���� �÷��̾ ȣ���Ѵ�.