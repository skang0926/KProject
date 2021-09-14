#pragma once

#include "KClient.h"
#include "SkillData.generated.h"

UCLASS(BlueprintType)
class KCLIENT_API UCircularSectorShotData : public UDataAsset {
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere)
	float centralAngle;

	UPROPERTY(EditAnywhere)
	FVector offset;

	UPROPERTY(EditAnywhere)
	int32 projectileCount;
};

UCLASS(BlueprintType)
class KCLIENT_API UHitScanShotData : public UDataAsset {
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere)
	float maxRange;
};