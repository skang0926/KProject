#pragma once

UENUM(BlueprintType)
enum class EAttackType : uint8 {
	None,
	OneHit,
	MultipleHit,
	Explosion,
	Count = Explosion
};

UENUM(BlueprintType)
enum class ESkillType : uint8 {
	None,
	HitScanShot,
	CircularSectorShot,
	Count = CircularSectorShot
};

UENUM(BlueprintType)
enum class EAttackAttribute : uint8 {
	None,
	Fire,
	Poison,
	Oil,
	Ice,
	Count = Ice
};