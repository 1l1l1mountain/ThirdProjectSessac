// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelTransformVolumeActor.h"
#include "MyPlayer.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"




// Sets default values
ALevelTransformVolumeActor::ALevelTransformVolumeActor()
{
	PrimaryActorTick.bCanEverTick = true;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Transfer Volume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));

}

void ALevelTransformVolumeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALevelTransformVolumeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelTransformVolumeActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AMyPlayer* Character = Cast<AMyPlayer>(OtherActor);
	if (Character)
	{
		UGameplayStatics::OpenLevel(GetWorld(), FName(TransferLevelName));
	}



}