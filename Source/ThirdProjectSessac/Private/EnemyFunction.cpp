// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFunction.h"
#include "Enemy.h"
#include "Components/TextRenderComponent.h"
#include "MyPlayer.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAnimInstance.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UEnemyFunction::UEnemyFunction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}


// Called when the game starts
void UEnemyFunction::BeginPlay()
{
	Super::BeginPlay();


	//처음은 아이들 상태
	Enemy = Cast<AEnemy>(GetOwner());
	Player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Ai = Cast <AAIController>(Enemy->GetController());
	Enemy->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	
	EnemyAnim = Cast<UEnemyAnimInstance>(Enemy->GetMesh()->GetAnimInstance());
	SetState(EEnemyState::Idle);


	Enemy->RightHandCollision->OnComponentBeginOverlap.AddDynamic(this, &UEnemyFunction::OnComponentBeginOverlap);
	Enemy->LeftHandCollision->OnComponentBeginOverlap.AddDynamic(this, &UEnemyFunction::OnComponentBeginOverlap);


}


// Called every frame
void UEnemyFunction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (State) 
	{

	case EEnemyState::Idle:	TickIdle(); break;
	case EEnemyState::Move:	TickMove(); break;
	case EEnemyState::Attack:TickAttack(); break;
	case EEnemyState::Damage:TickDamage(); break;
	case EEnemyState::Die:	TickDie();	break;
	case EEnemyState::Jump: Jump(); break;

	}
}

void UEnemyFunction::TickIdle()
{
	Enemy->TextComp->SetText(FText::FromString(FString("Sleep..")));
	Enemy->TextComp->SetTextRenderColor(FColor(255, 255,255, 255));

	// 거리에 의한 함수를 검을 들었을 때, 무브 활성화로 바꿀 것
	//float Distance = FVector::Distance(Player->GetActorLocation(), Enemy->GetActorLocation());
	
	
	/*if (Player && Distance < 500)
	{

		SetState(EEnemyState::Move);
	}*/
	//무기가 직접 틱 무브로 전환해줄예정
	
}
	
void UEnemyFunction::TickMove()
{	
	
	FVector StartLoc = Enemy->GetActorLocation();
	StartLoc.Z = StartLoc.Z - 80;
	FVector dir = Enemy->GetActorForwardVector();
	FVector EndLoc = StartLoc + dir * 100;
	
	
	Enemy->TextComp->SetText(FText::FromString(FString("Move!!")));
	Enemy->TextComp->SetTextRenderColor(FColor(0, 71, 255, 255));
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if (CurrentTime < 0.3f)
	{
		Ai->MoveToLocation(Player->GetActorLocation());
	}
	else
	{
		FVector PlayerDir = Player->GetActorLocation() - Enemy->GetActorLocation();
		PlayerDir.Normalize();
		//FVector MoveLoc = StartLoc + PlayerDir * 100 * GetWorld()->GetDeltaSeconds();
		FTransform controllerTransform = FTransform(Enemy->GetControlRotation());
		FVector RealDir = controllerTransform.TransformVector(PlayerDir);
		Enemy->AddMovementInput(RealDir);

		if (CurrentTime > 1.0f) CurrentTime = 0;
	}
	Distance = FVector::Distance(Player->GetActorLocation(), Enemy->GetActorLocation());

	if (Player && Distance < 200)
	{

		SetState(EEnemyState::Attack);
	}

	//앞에 장애물이 있으면 점프를 한다.
	//라인트레이싱을 한다.
	//앞에 플레이 제외한 장애물을 인식한다.
	//점프 상태로 바꾼다.
	
	//DrawDebugLine(GetWorld(), StartLoc, EndLoc, FColor::Emerald, true, -1, 0, 10);
	if (GetWorld()->LineTraceSingleByChannel(Outhit, StartLoc, EndLoc, ECC_Visibility))
	{
# 
		UE_LOG(LogTemp, Warning, TEXT("LineTrace"));
		if (!Cast<AMyPlayer>(Outhit.GetActor()))
		{
			SetState(EEnemyState::Jump);

		}
	}
}

void UEnemyFunction::TickAttack()
{
	Enemy->TextComp->SetText(FText::FromString(FString("Attack!!!")));
	Enemy->TextComp->SetTextRenderColor(FColor(255, 0, 0, 255));

	Distance = FVector::Distance(Player->GetActorLocation(), Enemy->GetActorLocation());
	if (Player && Distance >= 200)
	{
		SetState(EEnemyState::Move);
	}

}

void UEnemyFunction::TickDamage()
{
	Enemy->TextComp->SetText(FText::FromString(FString("Hp--..")));
	Enemy->TextComp->SetTextRenderColor(FColor(255, 30, 0, 255));

}

void UEnemyFunction::TickDie()
{
	Enemy->TextComp->SetText(FText::FromString(FString("-Die-")));
	Enemy->TextComp->SetTextRenderColor(FColor(0, 0, 0, 255));

}

void UEnemyFunction::SetState(EEnemyState next)
{
	CurrentTime = 0;
	State = next;
	if (EnemyAnim != nullptr)
	{

		EnemyAnim->State = next; 

	}
	
}

void UEnemyFunction::WakeUp()
{
	
	FVector Loc = Enemy->GetMesh()->GetRelativeLocation();
	float i = 0;
	float OriginZ = Loc.Z;
	float NewZ;
	//i가 딱 1로 떨어지지 않음... 이유는?
	while (i<1) 
	{
	
		NewZ = FMath::Lerp(OriginZ , OriginZ + 40 , i );
		i += 0.05;
		Loc.Z = NewZ;
		Enemy->GetMesh()->SetRelativeLocation(Loc);
	}

}

void UEnemyFunction::Jump()
{
	//if (Cast<AMyPlayer>(Outhit.GetActor())== nullptr   ) 
	//{
	//	/*	AActor* Temp;
	//		if (AObstacle* Obstacle = Cast<AObstacle>(Temp))
	//		{
	//			Obstacle->GetActorScale();
	//		}
	//		*/

	//	Enemy->Jump();

	//}
	
	Enemy->ActionJump();
}
// 두대씩 때리는 문제 ㅋㅋ
void UEnemyFunction::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//충돌이 플레이어라면?
	if (Cast<AMyPlayer>(OtherActor))
	{
		//성욱이 형의 위젯을 뛰운다
		UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetActorNameOrLabel());
		Player->DisplayWidgetRandom();

	}
}