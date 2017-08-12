// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AttributeSet.generated.h"

/**
 *  Class for attributes. Most of the code was taken from ue4 own attribute solution
 */

USTRUCT(BlueprintType)
struct ATOWERDEFENSEGAME_API FGameAttributeData
{
	GENERATED_BODY()

	FGameAttributeData()
		: BaseValue(0.f)
		,CurrentValue(0.f)
	{}

	FGameAttributeData(float DefaultVal)
		: BaseValue(DefaultVal)
		, CurrentValue(DefaultVal)
	{}

	virtual ~FGameAttributeData()
	{}

	float GetCurrentValue() const;
	virtual void SetCurrentValue(float NewValue);

	float GetBaseValue() const;
	virtual void SetBaseValue(float NewValue);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float BaseValue;
	UPROPERTY(BlueprintReadOnly, Category = "Attribute")
	float CurrentValue;
};

USTRUCT(BlueprintType)
struct ATOWERDEFENSEGAME_API FGameAttribute
{
	GENERATED_USTRUCT_BODY()

	FGameAttribute()
		: Attribute(nullptr)
		, AttributeOwner(nullptr)
	{}

	FGameAttribute(UProperty* NewProperty);

private:
	UPROPERTY(Category = GameAttribute, EditAnywhere)
		UProperty* Attribute;
	UPROPERTY(Category = GameAttribute, EditAnywhere)
		FString AttributeName;
	UPROPERTY(Category = GameAttribute, EditAnywhere)
		UStruct* AttributeOwner;
};

UCLASS()
class ATOWERDEFENSEGAME_API UAttributeSet : public UObject
{
	GENERATED_UCLASS_BODY()
	
public:


	
	
};
