// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "WeaponWidget.generated.h"

class UWidgetAnimation;
/**
 *
 */
UCLASS()
class UNREALWEAPONPROJECT_API UWeaponWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UWeaponWidget(const FObjectInitializer& ObjectInitalizer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTFireMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTDamagePerShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTShotRate;


	void UpdateHealthCout(float Value);

	void PrintDamagePerShot(float Value);

	void PrintFireMode(FString Name);;

	void PrintShotRate(float Value);


	void StoreWidgetAnimations();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

private:
	TMap<FName, UWidgetAnimation*> AnimationsMap;
	UWidgetAnimation* HealthFadeAnimation;
	UWidgetAnimation* HealthShakeAnimation;
};