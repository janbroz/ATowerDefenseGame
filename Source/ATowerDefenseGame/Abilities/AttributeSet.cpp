// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "AttributeSet.h"


float FGameAttributeData::GetBaseValue() const
{
	return BaseValue;
}

float FGameAttributeData::GetCurrentValue() const
{
	return CurrentValue;
}

void FGameAttributeData::SetBaseValue(float NewValue)
{
	BaseValue = NewValue;
}

void FGameAttributeData::SetCurrentValue(float NewValue)
{
	CurrentValue = NewValue;
}

FGameAttribute::FGameAttribute(UProperty* NewProperty)
{
	Attribute = Cast<UNumericProperty>(NewProperty);
	AttributeOwner = nullptr;



}

UAttributeSet::UAttributeSet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

