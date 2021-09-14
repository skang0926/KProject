#include "CharacterBase.h"
#include "DamageableComponent.h"
#include "SkillSystem.h"
#include "CharacterDataTable.h"
#include "Engine/DataTable.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetDefaultAsset();
	SetupDamageableComponent(100, 100);
	SetupSkillSystem();
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	PostInitialize();
}

void ACharacterBase::PostInitialize()
{
	auto gameInstance = dynamic_cast<UKProjectGameInstance*>(GetWorld()->GetGameInstance());
	characterTableRow = gameInstance->GetCharacterTableRow(characterName);
	
	if (characterTableRow != nullptr)
	{
		GetMesh()->SetSkeletalMesh(LoadObject<USkeletalMesh>(NULL, CONVERT_TEXT(characterTableRow->AssetPath), NULL, LOAD_None, NULL));
		GetMesh()->SetAnimInstanceClass(LoadObject<UAnimBlueprint>(NULL, CONVERT_TEXT(characterTableRow->AnimPath), NULL, LOAD_None, NULL)->GetAnimBlueprintGeneratedClass());
		
		InitTransform();
	}

	for (const auto& skill : characterTableRow->Skills)
	{
		skillSystem->RegisterSkill(skill);
	}
}

void ACharacterBase::SetDefaultAsset()
{
	//EStringKey 쓰면 null 값 리턴 되는 문제 발생
	SetupSkeletalMesh(TEXT("/Game/Characters/Monster/NormalMonster/Gunman/Heroes/TwinBlast/Meshes/TwinBlast_ShadowOps"));

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void ACharacterBase::SetupSkeletalMesh(const wchar_t* meshPath)
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> characterMesh(meshPath);
	if (characterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(characterMesh.Object);
		GetMesh()->SetAnimationMode( EAnimationMode::AnimationBlueprint );
	}
}

void ACharacterBase::SetupAnimation(const wchar_t* animPath)
{
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> animBP(animPath);
	if (animBP.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(animBP.Object->GetAnimBlueprintGeneratedClass());
	}
}

void ACharacterBase::SetupDamageableComponent(const int32 healthPoint, const int32 shieldPoint)
{
	damageableComponent = CreateDefaultSubobject<UDamageableComponent>(TEXT("Damageable"));
	damageableComponent->Init(healthPoint, shieldPoint);
}

void ACharacterBase::InitTransform()
{
	GetMesh()->SetRelativeLocation(characterTableRow->Location);
	GetMesh()->SetRelativeRotation(characterTableRow->Rotator);
	GetMesh()->SetRelativeScale3D(characterTableRow->Scale);
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void ACharacterBase::BeginJump()
{
	if (damageableComponent->IsDead())
	{
		return;
	}

	bPressedJump = true;
}


void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::MoveForward(const float value)
{
	if (value == 0 || damageableComponent->IsDead())
	{
		return;
	}

	float movementAmount = value < 0 ? value * MOVE_BACK_SPEED_RATIO : value;

	FVector direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::X);
	direction.Z = 0.0f;
	direction.Normalize();
	moveDirection += direction * FMath::Clamp(value, -1.0f, 1.0f);
}

void ACharacterBase::MoveSide(const float value)
{
	if (value == 0 || damageableComponent->IsDead())
	{
		return;
	}

	FVector direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y);
	direction.Z = 0.0f;
	direction.Normalize();
	moveDirection += direction * FMath::Clamp(value, -1.0f, 1.0f);
}

void ACharacterBase::Move(float deltaTime)
{
	if (moveDirection.IsZero())
	{
		localVelocityDirection = FVector::ZeroVector;
		return;
	}

	moveDirection.Normalize();
	AddMovementInput(moveDirection);

	FVector axis = FVector(0.f, 0.f, 1.f);
	localVelocityDirection = moveDirection.RotateAngleAxis(-GetActorRotation().Yaw, axis);
	moveDirection.Set(0.0f, 0.0f, 0.0f);
}

void ACharacterBase::SetupSkillSystem() 
{
	isAttacking = false;
	skillSystem = CreateDefaultSubobject<USkillSystem>(TEXT("USkillSystem"));
}

void ACharacterBase::Attack(const float value)
{
	if ( damageableComponent->IsDead() ) {
		return;
	}

	if ( value <= 0.0f ) {
		return;
	}

	if ( !skillSystem ) {
		return;
	}

	if (!characterTableRow) {
		return;
	}

	isAttacking = true;
	skillSystem->UseActiveSkill( characterTableRow->defaultAttackSkillType );
}

class USkillSystem* ACharacterBase::GetSkillSystem() const
{
	return skillSystem;
}

class UDamageableComponent* ACharacterBase::GetDamageableComponent() const
{
	return damageableComponent;
}

int32 ACharacterBase::GetBaseDamage() const
{
	// You must override this
	unimplemented();
	return 0;
}
