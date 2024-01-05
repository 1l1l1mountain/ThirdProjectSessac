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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettingValues")
	FVector LocationOffset = FVector(22, 1.180213, 20.785830);
	FRotator RotationOffset = FRotator(49.238718,  4.001260,  0.000000);
	FVector ScaleOffset= FVector(1.0);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettingValues")
	TArray<class AEnemy*> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettingValues")
	bool bIsGrab;

};
