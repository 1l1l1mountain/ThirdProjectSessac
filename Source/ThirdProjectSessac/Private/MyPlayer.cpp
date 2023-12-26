// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMesh.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

//?? 헤더에 추가하면 따로 추가하지 않아도 되는건가 ??
//#include "InputActionValue.h" 


// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);
	
	//메쉬 로드 바꿔줄 예정
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'"));
	if (tempMesh.Succeeded()) 
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(-30,0,30),FRotator(0,-90,0));
	}
	

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	//입력 매핑 설정하기 (암기)
	if (APlayerController* pc = GetWorld()->GetFirstPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* subsys =ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsys != nullptr && Imc != nullptr)
		{
			subsys->AddMappingContext(Imc, 0);
		}

	}
	//입력 매핑 설정하기 (암기)



}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	
	
	//입력 매핑 설정하기 (암기)
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		//함수 이벤트화
		enhancedInputComponent->BindAction(IA_MoveInput,ETriggerEvent::Triggered,this,&AMyPlayer::MoveInput);
		enhancedInputComponent->BindAction(IA_MouseInput, ETriggerEvent::Triggered, this, &AMyPlayer::MouseInput);
	}
	//입력 매핑 설정하기 (암기)

}

void AMyPlayer::MoveInput(const FInputActionValue& value)
{
	//입력 저장 inputvalue.x or .y
	FVector2D InputValue = value.Get<FVector2D>();

	// 이동 공식 암기
	FVector inputDir = FVector(InputValue.X, InputValue.Y , 0);
	inputDir.Normalize();
	FVector modifiedDir = GetTransform().TransformVector(inputDir);
	AddMovementInput(modifiedDir);
	// 이동 공식 암기

}

void AMyPlayer::MouseInput(const FInputActionValue& value)
{
	//입력 저장 inputvalue.x or .y
	FVector2D InputValue = value.Get<FVector2D>();
	//회전 컨트롤러 암기
	//주의 이건 컨트롤러 설정이 추가 필요
	AddControllerPitchInput(-InputValue.Y); //피치와 롤은 오른손나사 법칙
	AddControllerYawInput(InputValue.X);	//야는 왼손나사 법칙
	//UE_LOG(LogTemp, Log, TEXT("X : %.2f, Y : %.2f\r\n"), InputValue.X, InputValue.Y);
	//회전 컨트롤러 암기
}

