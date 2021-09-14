#pragma once

#include "KClient.h"
#include "PlayerCharacter.generated.h"

UCLASS(BlueprintType, Blueprintable)
class KCLIENT_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()

public:
	APlayerCharacter();

public:
	virtual int32 GetBaseDamage() const override;
	
	UFUNCTION(BlueprintCallable)
	FVector GetMoveDirection() { return localVelocityDirection; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:
	void InitCameraSetting();
	void InitControllerSetting();

	void BeginFocusing();
	void EndFocusing();

	void Dash();
	void DashTimerReset();
	FVector GetPlayerMovementInput();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _cameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _followCamera;

private:
	const float target_arm_length = 250.0f;
	const float DASH_COOLTIME = 5.0f;
	const float DASH_MOVEMENT_AMOUNT = 300.0f;
	const float DASH_VELOCITY = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isFocusing;
	bool isDashing;

	FTimerHandle dashTimerHandle;
};

USTRUCT(BlueprintType)
struct FCharacterStatTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterStatTableRow() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 ReloadingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 CanAim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 SpeedRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 DamageRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 WeaponRangeRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 RecoilRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 CameraZoomRate;
};