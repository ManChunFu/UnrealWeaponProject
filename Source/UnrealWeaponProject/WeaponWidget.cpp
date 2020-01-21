// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWidget.h"

UWeaponWidget::UWeaponWidget(const FObjectInitializer& ObjectInitalizer) : Super(ObjectInitalizer)
{}

void UWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StoreWidgetAnimations();

	DamageFadeAnimation = GetAnimationByName(TEXT("DamageFade"));
	DamageShakeAnimation = GetAnimationByName(TEXT("DamageShake"));
}

void UWeaponWidget::UpdateHealthCout(float Value)
{
	if (TXTDamage && Value >= 0)
	{
		 //turn textblock visible if already hidden
		if (TXTDamage->Visibility == ESlateVisibility::Hidden)
		{
			TXTDamage->SetVisibility(ESlateVisibility::Visible);
		}
		TXTDamage->SetText(FText::FromString("Current Health : " + FString::SanitizeFloat(Value)));

		if (DamageFadeAnimation)
		{
			PlayAnimation(DamageFadeAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
		}

		if (DamageShakeAnimation)
		{
			PlayAnimation(DamageShakeAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
		}
	}
}

void UWeaponWidget::PrintFireMode(FString Name)
{
	TXTFireMode->SetVisibility(ESlateVisibility::Visible);
	TXTFireMode->SetText(FText::FromString(Name));
}

void UWeaponWidget::PrintShotCost(int Value)
{
	TXTShotCost->SetVisibility(ESlateVisibility::Visible);
	TXTShotCost->SetText(FText::FromString(FString::FromInt(Value)));
}

void UWeaponWidget::PrintShotRate(float Value)
{
	TXTShotRate->SetVisibility(ESlateVisibility::Visible);
	TXTShotRate->SetText(FText::FromString(FString::SanitizeFloat(Value)));
}


void UWeaponWidget::StoreWidgetAnimations()
{
	AnimationsMap.Empty();

	UProperty* Property = GetClass()->PropertyLink;

	while (Property)
	{
		// only deal with object properties
		if (Property->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property);

			// only get properties that are widget animations
			if (ObjectProperty->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* Object = ObjectProperty->GetObjectPropertyValue_InContainer(this);
				UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(Object);

				if (WidgetAnimation && WidgetAnimation->MovieScene)
				{
					FName AnimName = WidgetAnimation->MovieScene->GetFName();
					GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, AnimName.ToString());
					AnimationsMap.Add(AnimName, WidgetAnimation);
				}
			}
		}

		Property = Property->PropertyLinkNext;
	}
}

UWidgetAnimation* UWeaponWidget::GetAnimationByName(FName AnimationName) const
{
	UWidgetAnimation* const* WidgetAnimation = AnimationsMap.Find(AnimationName);
	if (WidgetAnimation)
	{
		return *WidgetAnimation;
	}
	return nullptr;
}


