// Fill out your copyright notice in the Description page of Project Settings.


#include "WideInvitationActor.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"


// Sets default values
AWideInvitationActor::AWideInvitationActor()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComp);

	invitationWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget Component"));
	invitationWidget->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void AWideInvitationActor::BeginPlay()
{
	Super::BeginPlay();
	

	// Cast<UEgyptUserWidget>(invitationWidget->GetWidget())->invitationActor = this;
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
}

// Called every frame
void AWideInvitationActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWideInvitationActor::YES()
{

}

void AWideInvitationActor::NO()
{

}

