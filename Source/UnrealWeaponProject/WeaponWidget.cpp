// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponWidget.h"

UWeaponWidget::UWeaponWidget(const FObjectInitializer& ObjectInitalizer) : Super(ObjectInitalizer)
{}

void UWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StoreWidgetAnimations();

	HealthFadeAnimation = GetAnimationByName(TEXT("HealthFade"));
	HealthShakeAnimation = GetAnimationByName(TEXT("HealthShake"));
}

void UWeaponWidget::ChangeMagazineColor()
{
}

void UWeaponWidget::UpdateHealthCout(float Value)
{
	if (TXTHealth && Value >= 0)
	{
		 //turn textblock visible if already hidden
		if (TXTHealth->Visibility == ESlateVisibility::Hidden)
		{
			TXTHealth->SetVisibility(ESlateVisibility::Visible);
		}
		TXTHealth->SetText(FText::FromString("Current Health : " + FString::SanitizeFloat(Value)));

		if (HealthFadeAnimation)
		{
			PlayAnimation(HealthFadeAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
		}

		if (HealthShakeAnimation)
		{
			PlayAnimation(HealthShakeAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
		}
	}
}

void UWeaponWidget::PrintDamagePerShot(float Value, FString Multiplier)
{
	TXTDamagePerShot->SetVisibility(ESlateVisibility::Visible);
	TXTDamagePerShot->SetText(FText::FromString(FString::SanitizeFloat(Value) + " " + Multiplier));
}

void UWeaponWidget::PrintFireMode(FString Name)
{
	TXTFireMode->SetVisibility(ESlateVisibility::Visible);
	TXTFireMode->SetText(FText::FromString(Name));
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


