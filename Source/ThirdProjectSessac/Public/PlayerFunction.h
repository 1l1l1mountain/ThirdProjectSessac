// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerFunction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPROJECTSESSAC_API UPlayerFunction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFunction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings")
	class AMyPlayer* Player;
	


	void SetupPlayerInputComponent(class UEnhancedInputComponent* EnhancedInputComponent,TArray <class UInputAction*> inputs);

	void Grabbed();
	void Dettached();
	
	class AWeapon* CurrentWeapon;


	//vr ����
	void Jump();



	


};
