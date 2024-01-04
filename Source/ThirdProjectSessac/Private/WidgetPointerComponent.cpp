// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetPointerComponent.h"
#include "MyPlayer.h"
#include "EnhancedInputComponent.h"
#include "Components/WidgetInteractionComponent.h"
// Sets default values for this component's properties
UWidgetPointerComponent::UWidgetPointerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWidgetPointerComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AMyPlayer>(GetOwner());
}


// Called every frame
void UWidgetPointerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWidgetPointerComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent, TArray<UInputAction*>inputs)
{
	enhancedInputComponent->BindAction(inputs[3],ETriggerEvent::Started, this, &UWidgetPointerComponent::MouseLeftClick);
	enhancedInputComponent->BindAction(inputs[3], ETriggerEvent::Completed, this, &UWidgetPointerComponent::MouseLeftRelease);
}

void UWidgetPointerComponent::MouseLeftClick(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("presswidget"));
	Player->rightPointer->PressPointerKey(EKeys::LeftMouseButton);

}

void UWidgetPointerComponent::MouseLeftRelease(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("releasewidget"));

	Player->rightPointer->ReleasePointerKey(EKeys::LeftMouseButton);

}

