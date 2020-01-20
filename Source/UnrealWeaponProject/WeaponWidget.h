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

	void UpdateDamageCout(float Value);

	void ResetDamage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TXTDamage;

	void StoreWidgetAnimations();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

private:
	TMap<FName, UWidgetAnimation*> AnimationsMap;
	UWidgetAnimation* DamageFadeAnimation;
	UWidgetAnimation* DamageShakeAnimation;
};