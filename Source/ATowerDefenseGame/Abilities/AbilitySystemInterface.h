// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Interface.h"
#include "AbilitySystemInterface.generated.h"


class UAbilitySystemComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAbilitySystemInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class ATOWERDEFENSEGAME_API IAbilitySystemInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const = 0;
	
	// Some testing and stuff
	UFUNCTION()
	virtual void SayHello() const = 0;

};
