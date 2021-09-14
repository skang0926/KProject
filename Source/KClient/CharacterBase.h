#pragma once

#include "KClient.h"
#include "CharacterBase.generated.h"

class USkillSystem;

UCLASS(Abstract)
class KCLIENT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	const struct FCharacterTable* const GetCharacterTableRow() { return characterTableRow; }

	class USkillSystem* GetSkillSystem() const;
	class UDamageableComponent* GetDamageableComponent() const;

	virtual int32 GetBaseDamage() const;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitialize();

	virtual void MoveForward(const float value);
	virtual void MoveSide(const float value);
	virtual void Attack(const float value);

	void SetDefaultAsset();

	void BeginJump();

private:
	void SetupDamageableComponent(const int32 healthPoint, const int32 shieldPoint);
	void SetupSkeletalMesh(const wchar_t* meshPath);
	void SetupAnimation(const wchar_t* animPath);	
	void SetupSkillSystem();
	void InitTransform();
	void Move(float deltaTime);
	

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UDamageableComponent* damageableComponent;
	UPROPERTY(VisibleAnywhere)
	class USkillSystem* skillSystem;

	UPROPERTY(BlueprintReadWrite)
	bool isAttacking;

	UPROPERTY(EditAnywhere, Category = Data)
	FName characterName;

	float movementSpeedRatio = 1.0f;

	UPROPERTY(VisibleAnywhere)
	FVector moveDirection;

	UPROPERTY(VisibleAnywhere)
	FVector localVelocityDirection;

private:
	const FCharacterTable* characterTableRow = nullptr;
	const wchar_t* ANIMATION_PATH;
	const float VELOCITY = 100.0f;
	const float MOVE_BACK_SPEED_RATIO = 0.7f;

};
