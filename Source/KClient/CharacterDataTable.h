// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Common/Lang/String.h"
#include "CharacterDataTable.generated.h"


USTRUCT(BlueprintType)
struct FCharacterTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterTable() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EStringKey AssetPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EStringKey AnimPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TSet<ESkillType> Skills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EStringKey BBPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EStringKey BTPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FRotator Rotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ESkillType defaultAttackSkillType;
};
