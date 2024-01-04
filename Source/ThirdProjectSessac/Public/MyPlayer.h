// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyPlayer.generated.h"

UCLASS()
class THIRDPROJECTSESSAC_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* RightHand;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UPlayerFunction* FunctionComp;
	
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputMappingContext* Imc;
	
	
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction * IA_MoveInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_MouseInput;*/
	//--> 아래의 배열로 이동

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	TArray <class UInputAction*> inputs;





	//?? 얘는 전방 선언이 안되나?
	void MoveInput(const FInputActionValue & value);
	void MouseInput(const FInputActionValue & value);



	//성욱이 형 함수
	UFUNCTION(BlueprintImplementableEvent, Category = "WidgetFunction")
	void DisplayWidgetRandom();



	//vr 연동

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettingsComponents")
	class UStaticMeshComponent* hmdMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettingsComponents")
	class UMotionControllerComponent* rightController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettingsComponents")
	class UWidgetInteractionComponent* rightPointer;


	UFUNCTION(BlueprintImplementableEvent)
	void ClickWidget();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "MySettings|Components")
	class UWidgetPointerComponent* widgetPointerComp;
	

};
