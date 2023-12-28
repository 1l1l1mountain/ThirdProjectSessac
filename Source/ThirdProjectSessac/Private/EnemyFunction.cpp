// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFunction.h"
#include "Enemy.h"
#include "Components/TextRenderComponent.h"
#include "MyPlayer.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	SetState(EEnemyState::Idle);
	Enemy = GetOwner<AEnemy>();
	Player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	Ai = Cast <AAIController>(Enemy->GetController());
	Enemy->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
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
	Enemy->TextComp->SetText(FText::FromString(FString("Move!!")));
	Enemy->TextComp->SetTextRenderColor(FColor(0, 71, 255, 255));
	
	Ai->MoveToLocation(Player->GetActorLocation());

	Distance = FVector::Distance(Player->GetActorLocation(), Enemy->GetActorLocation());

	if (Player && Distance < 200)
	{

		SetState(EEnemyState::Attack);
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
	State = next;
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
	
		NewZ = FMath::Lerp(OriginZ , OriginZ + 90 , i );
		i += 0.05;
		Loc.Z = NewZ;
		Enemy->GetMesh()->SetRelativeLocation(Loc);
	}

}
