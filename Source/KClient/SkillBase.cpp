#include "SkillBase.h"

USkillBase::USkillBase() {
	PrimaryComponentTick.bCanEverTick = true;
}

void USkillBase::TickComponent( float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction ) {
	Super::TickComponent( deltaTime, tickType, thisTickFunction );
}

void USkillBase::Initialize( const FSkillProperty* initProperty ) {
	if ( initProperty == nullptr ) {
		return;
	}

	SetComponentTickEnabled(false);

	commonProperty = *initProperty;

	FString assetPath = CONVERT_TEXT( EStringKey::PATH_DIR_SKILL_DATA );
	assetPath.Append( GetClass()->GetName() );

	uniqueProperty = LoadObject<UDataAsset>( nullptr, *assetPath );
	if ( uniqueProperty == nullptr ) {
		UE_LOG( KP, Error, TEXT("doesn't exist unique property %s"), *assetPath );
		return;
	}
}

void USkillBase::Use() {
	lastUpdatedTime = FPlatformTime::Seconds();
}

FSkillProperty& USkillBase::GetCommonProperty() {
	return commonProperty;
}

bool USkillBase::IsActiveType() const {  
	return commonProperty.isActiveType; 
}

bool USkillBase::IsInstallType() const {  
	return commonProperty.isInstallType; 
}

bool USkillBase::IsRemainCooldown() const {
	return FPlatformTime::Seconds() <= lastUpdatedTime + static_cast<double>( commonProperty.cooldown );
}

double USkillBase::GetCooldownRemaining() const {
	return lastUpdatedTime;
}