// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EgyptUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPROJECTSESSAC_API UEgyptUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mysettings", meta = (BindWidget));
	class UImage* screen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mysettings", meta = (BindWidget));
	class UButton* btn_yes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mysettings", meta = (BindWidget));
	class UButton* btn_no;

	class AWideInvitationActor* invitationActor;

private:
	UFUNCTION()
	void Yes();
	void No();


};
