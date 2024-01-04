// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMesh.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerFunction.h"
#include "MotionControllerComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"

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
	

	//일단 연습용 손 장착
	//RightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightHand"));
	//RightHand->SetupAttachment(RootComponent);
	//ConstructorHelpers::FObjectFinder<USkeletalMesh> RightMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/A_GDH/SkeletalMesh/SM_RightHand_GDH.SM_RightHand_GDH'"));
	//if (RightMesh.Succeeded())
	//{
	//	RightHand->SetSkeletalMesh(RightMesh.Object);
	//	RightHand->SetRelativeLocationAndRotation(FVector(25,15,6),FRotator(90,0,80));
	//	/*(X = 24.554299, Y = 14.710379, Z = 6.401193)
	//	(Pitch = 90.000000, Yaw = 0.000000, Roll = 79.999999)*/
	//}

	//vr 연동

	hmdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh"));
	hmdMesh->SetupAttachment(CameraComp);
	rightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	rightController->SetupAttachment(RootComponent);
	rightController->SetRelativeLocation(FVector(50, 30, -10));
	rightController->SetTrackingMotionSource(FName("Right"));

	RightHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> RightMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/A_GDH/SkeletalMesh/SM_RightHand_GDH.SM_RightHand_GDH'"));
	if (RightMesh.Succeeded())
	{
		RightHand->SetSkeletalMesh(RightMesh.Object);
		RightHand->SetupAttachment(rightController);
		RightHand->SetRelativeRotation(FRotator(70, 0, 90));
		
	}


	//액터 컴포넌트 가지고 있기
	FunctionComp = CreateDefaultSubobject<UPlayerFunction>(TEXT("FunctionComp"));

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	//헤드 마운트 디스플레이 장비의 트래킹 (추적) 기준 위치를 Stage로 설정한다.
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

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
		enhancedInputComponent->BindAction(inputs[0], ETriggerEvent::Triggered, this, &AMyPlayer::MoveInput);
		enhancedInputComponent->BindAction(inputs[1], ETriggerEvent::Triggered, this, &AMyPlayer::MouseInput);
		FunctionComp->SetupPlayerInputComponent(enhancedInputComponent, inputs);
		// 인풋 배열 매핑 정보
		// inputs[0] : IA_MoveInput
		// inputs[1] : IA_MouseInput

		
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

