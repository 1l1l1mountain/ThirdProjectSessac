// Fill out your copyright notice in the Description page of Project Settings.


#include "EgyptUserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "WideInvitationActor.h"


void UEgyptUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ��ư Ŭ���ϴ� �̺�Ʈ�� �Լ� ����
	btn_yes->OnClicked.AddDynamic(this, &UEgyptUserWidget::Yes);
	btn_no->OnClicked.AddDynamic(this, &UEgyptUserWidget::No);


}

void UEgyptUserWidget::Yes()
{
	if (invitationActor != nullptr)
	{
		invitationActor->YES();
	}
}

void UEgyptUserWidget::No()
{
	if (invitationActor != nullptr)
	{
		invitationActor->NO();
	}
}
