// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TowerData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	PointDamage		UMETA(DisplayName = "Point Damage"),
	AreaOfDamage	UMETA(DisplayName = "Area of damage"),
	DamageOverTime	UMETA(DisplayName = "Damage over time")
};

UENUM(BlueprintType)
enum class EDamageElement : uint8
{
	Physical		UMETA(DisplayName = "Physical"),
	Magical		    UMETA(DisplayName = "Magical"),
	Pure			UMETA(DisplayName = "Pure"),
	Fire			UMETA(DisplayName = "Fire"),
	Ice				UMETA(DisplayName = "Ice"),
	Lighting		UMETA(DisplayName = "Lighting")
};

UENUM(BlueprintType)
enum class EArmorType : uint8
{
	None			UMETA(DisplayName = "None"),
	Light			UMETA(DisplayName = "Light"),
	Medium			UMETA(DisplayName = "Medium"),
	Heavy			UMETA(DisplayName = "Heavy")
};

UENUM(BlueprintType)
enum class EBuildingMode : uint8
{
	Placing			UMETA(DisplayName = "Placing"),
	Building		UMETA(DisplayName = "Building"),
	Working			UMETA(DisplayName = "Working")
};

UENUM(BlueprintType)
enum class EDisplayMode : uint8
{
	Buildings		UMETA(DisplayName = "Buildings"),
	Level			UMETA(DisplayName = "Level"),
	Minions			UMETA(DisplayName = "Minions"),
	NONE			UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class ESelectedUnitType : uint8
{
	Building		UMETA(DisplayName = "Building"),
	Minion			UMETA(DisplayName = "Minion"),
	NONE			UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class ETowerMode : uint8
{
	Placing			UMETA(DisplayName = "Placing"),
	Building		UMETA(DisplayName = "Building"),
	Enabled			UMETA(DisplayName = "Enabled")
};

UENUM(BlueprintType)
enum class EPlayerClass : uint8
{
	OldOnesWorshiper	UMETA(DisplayName = "OldOnes"),
	LightZealot			UMETA(DisplayName = "Zealot"),
	TechBringer			UMETA(DisplayName = "Tech")
};

UENUM(BlueprintType)
enum class ESkillType : uint8
{
	Passive			UMETA(DisplayName = "Passive"),
	Active			UMETA(DisplayName = "Active")
};

UENUM(BlueprintType)
enum class EAbilityEffect : uint8
{
	Evasion				UMETA(DisplayName = "Evasion"),
	DamageMultiplier	UMETA(DisplayName = "DamageMultiplier"),
	ArmorModifier		UMETA(DisplayName = "ArmorModifier")
};

inline uint8 GetTypeHash(const EDamageType A) { return (uint8)A; }
inline uint8 GetTypeHash(const EDamageElement A) { return (uint8)A; }
inline uint8 GetTypeHash(const EArmorType A) { return (uint8)A; }
inline uint8 GetTypeHash(const EBuildingMode A) { return (uint8)A; }
inline uint8 GetTypeHash(const EDisplayMode A) { return (uint8)A; }
inline uint8 GetTypeHash(const ESelectedUnitType A) { return (uint8)A; }
inline uint8 GetTypeHash(const ETowerMode A) { return (uint8)A; }
inline uint8 GetTypeHash(const EPlayerClass A) { return (uint8)A; }
inline uint8 GetTypeHash(const ESkillType A) { return (uint8)A; }
inline uint8 GetTypeHash(const EAbilityEffect A) { return (uint8)A; }

USTRUCT(Blueprintable)
struct FAbilityEffect
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Ability Effects")
		EAbilityEffect Effect;
	UPROPERTY(BlueprintReadOnly, Category = "Ability Effects")
		bool bEnabled;
	UPROPERTY(BlueprintReadOnly, Category = "Ability Effects")
		float Multiplier;

};

USTRUCT(Blueprintable)
struct FAssetsManager : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Towers information")
		TAssetSubclassOf<class ATower> TowerClass;
	UPROPERTY(BlueprintReadOnly, Category = "Towers information")
		TAssetPtr<UTexture> Icon;
	UPROPERTY(BlueprintReadOnly, Category = "Towers information")
		FText Title;
	UPROPERTY(BlueprintReadOnly, Category = "Towers information")
		FText Description;
	UPROPERTY(BlueprintReadOnly, Category = "Towers information")
		int32 Cost;
	UPROPERTY(BlueprintReadOnly, Category = "Towers information")
		float Damage;
	UPROPERTY(BlueprintReadOnly, Category = "Towers information")
		float Speed;
	UPROPERTY(BlueprintReadOnly, Category = "Towers information")
		float Range;

};

UCLASS()
class ATOWERDEFENSEGAME_API UTowerData : public UObject
{
	GENERATED_BODY()
public:
	UTowerData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Singleton")
		FString Test = TEXT("This is the singleton! It works!");
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Singleton")
		int32 TestValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Minion information")
		UDataTable* TowersTable;


};
