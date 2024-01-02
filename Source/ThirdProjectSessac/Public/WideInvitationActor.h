// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WideInvitationActor.generated.h"

UCLASS()
class THIRDPROJECTSESSAC_API AWideInvitationActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWideInvitationActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Mysettings");
	class USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mysettings");
	class UWidgetComponent* invitationWidget;

	UPROPERTY(EditAnywhere, Category = "Mysettings");
	class UWidget* paper;

	void YES();
	void NO();


};
