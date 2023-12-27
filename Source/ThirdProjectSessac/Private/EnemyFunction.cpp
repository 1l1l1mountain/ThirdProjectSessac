// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFunction.h"
#include "Enemy.h"
#include "Components/TextRenderComponent.h"
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

	


}

void UEnemyFunction::TickMove()
{
	Enemy->TextComp->SetText(FText::FromString(FString("Move!!")));
	Enemy->TextComp->SetTextRenderColor(FColor(0, 71, 255, 255));
	
}

void UEnemyFunction::TickAttack()
{
	Enemy->TextComp->SetText(FText::FromString(FString("Attack!!!")));
	Enemy->TextComp->SetTextRenderColor(FColor(255, 0, 0, 255));

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
