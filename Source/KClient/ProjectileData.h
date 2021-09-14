#pragma once

#include "KClient.h"
#include "ProjectileData.generated.h"

UCLASS(BlueprintType)
class KCLIENT_API UProjectileData : public UDataAsset {
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere)
	float lifeSpan;

	UPROPERTY(EditAnywhere)
	float collisionSphereRadius;

	UPROPERTY(EditAnywhere)
	float initSpeed;

	UPROPERTY(EditAnywhere)
	float maxSpeed;

	UPROPERTY(EditAnywhere)
	float gravityScale;

	UPROPERTY(EditAnywhere)
	FVector scale;
};