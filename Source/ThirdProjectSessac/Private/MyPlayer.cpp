// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMesh.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerFunction.h"
#include "MotionControllerComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"

//?? ����� �߰��ϸ� ���� �߰����� �ʾƵ� �Ǵ°ǰ� ??
//#include "InputActionValue.h" 


// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);
	
	//�޽� �ε� �ٲ��� ����
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Engine/EngineMeshes/SkeletalCube.SkeletalCube'"));
	if (tempMesh.Succeeded()) 
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(-30,0,30),FRotator(0,-90,0));
	}
	

	//�ϴ� ������ �� ����
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

	//vr ����

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


	//���� ������Ʈ ������ �ֱ�
	FunctionComp = CreateDefaultSubobject<UPlayerFunction>(TEXT("FunctionComp"));

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	//��� ����Ʈ ���÷��� ����� Ʈ��ŷ (����) ���� ��ġ�� Stage�� �����Ѵ�.
	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	//�Է� ���� �����ϱ� (�ϱ�)
	if (APlayerController* pc = GetWorld()->GetFirstPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* subsys =ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsys != nullptr && Imc != nullptr)
		{
			subsys->AddMappingContext(Imc, 0);
		}

	}
	//�Է� ���� �����ϱ� (�ϱ�)



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
	
	
	
	//�Է� ���� �����ϱ� (�ϱ�)
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent != nullptr)
	{
		//�Լ� �̺�Ʈȭ
		enhancedInputComponent->BindAction(inputs[0], ETriggerEvent::Triggered, this, &AMyPlayer::MoveInput);
		enhancedInputComponent->BindAction(inputs[1], ETriggerEvent::Triggered, this, &AMyPlayer::MouseInput);
		FunctionComp->SetupPlayerInputComponent(enhancedInputComponent, inputs);
		// ��ǲ �迭 ���� ����
		// inputs[0] : IA_MoveInput
		// inputs[1] : IA_MouseInput

		
	}
	//�Է� ���� �����ϱ� (�ϱ�)

}

void AMyPlayer::MoveInput(const FInputActionValue& value)
{
	//�Է� ���� inputvalue.x or .y
	FVector2D InputValue = value.Get<FVector2D>();

	// �̵� ���� �ϱ�
	FVector inputDir = FVector(InputValue.X, InputValue.Y , 0);
	inputDir.Normalize();
	FVector modifiedDir = GetTransform().TransformVector(inputDir);
	AddMovementInput(modifiedDir);
	// �̵� ���� �ϱ�

}

void AMyPlayer::MouseInput(const FInputActionValue& value)
{
	//�Է� ���� inputvalue.x or .y
	FVector2D InputValue = value.Get<FVector2D>();
	//ȸ�� ��Ʈ�ѷ� �ϱ�
	//���� �̰� ��Ʈ�ѷ� ������ �߰� �ʿ�
	AddControllerPitchInput(-InputValue.Y); //��ġ�� ���� �����ճ��� ��Ģ
	AddControllerYawInput(InputValue.X);	//�ߴ� �޼ճ��� ��Ģ
	//UE_LOG(LogTemp, Log, TEXT("X : %.2f, Y : %.2f\r\n"), InputValue.X, InputValue.Y);
	//ȸ�� ��Ʈ�ѷ� �ϱ�
}

