// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMesh.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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
	

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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
		enhancedInputComponent->BindAction(IA_MoveInput,ETriggerEvent::Triggered,this,&AMyPlayer::MoveInput);
		enhancedInputComponent->BindAction(IA_MouseInput, ETriggerEvent::Triggered, this, &AMyPlayer::MouseInput);
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

