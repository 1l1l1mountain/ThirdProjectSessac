// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class THIRDPROJECTSESSAC_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySetting|Components")
	class UStaticMeshComponent* MeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySetting|Components")
	class UBoxComponent * BoxComp; 

	void Grabbed(class USkeletalMeshComponent* SkeletalComp, EAttachmentRule AttachmentRules); //어태치먼트룰은 선언이 필요 없나봄
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting|Values")
	FVector LocationOffset = FVector(0,0,10);
};
