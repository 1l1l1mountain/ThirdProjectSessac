// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class THIRDPROJECTSESSAC_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UEnemyFunction* FunctionComp;

	//언리얼 텍스트 출력용
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UTextRenderComponent* TextComp;

	

	UFUNCTION()
	void OnCapsuleComponentBeginOverlap (UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	class USphereComponent* RightHandCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	class USphereComponent* LeftHandCollision;
	//점프블프
	UFUNCTION(BlueprintImplementableEvent)
	void ActionJump();


};