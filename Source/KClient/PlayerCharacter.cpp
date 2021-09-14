#include "PlayerCharacter.h"
#include "DamageableComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SkillSystem.h"

APlayerCharacter::APlayerCharacter()
{
	characterName = TEXT("PlayerCharacter");
	InitControllerSetting();
	InitCameraSetting();

	auto controller = GetController();
	if (controller)
	{
		controller->Possess(this);
	}
}

void APlayerCharacter::BeginPlay() 
{
	Super::BeginPlay();

	damageableComponent->Init(100, 100);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &APlayerCharacter::MoveSide);

	PlayerInputComponent->BindAction("Focusing", IE_Pressed, this, &APlayerCharacter::BeginFocusing);
	PlayerInputComponent->BindAction("Focusing", IE_Released, this, &APlayerCharacter::EndFocusing);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::BeginJump);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::Dash);

	PlayerInputComponent->BindAxis("Attack", this, &APlayerCharacter::Attack);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::InitControllerSetting()
{
	GetCharacterMovement()->bOrientRotationToMovement = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
}

void APlayerCharacter::InitCameraSetting()
{
	_cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	_cameraBoom->SetupAttachment(RootComponent);
	_cameraBoom->TargetArmLength = target_arm_length;
	_cameraBoom->SetRelativeLocation(FVector(-50.0f, 70.0f, 70.0f));
	_cameraBoom->bUsePawnControlRotation = true;
	_cameraBoom->ProbeSize = 0.1f;
	_followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	_followCamera->SetupAttachment(_cameraBoom, USpringArmComponent::SocketName);
	_followCamera->bUsePawnControlRotation = false;
}

void APlayerCharacter::Dash()
{
	if (isDashing)
	{
		return;
	}

	isDashing = true;
	damageableComponent->SetInvincible(true);

	FVector dashTargetLocation;

	auto movementInput = GetPlayerMovementInput();
	dashTargetLocation = GetActorLocation();
	dashTargetLocation += GetActorForwardVector() * movementInput.X * DASH_MOVEMENT_AMOUNT;
	dashTargetLocation += GetActorRightVector() * movementInput.Y * DASH_MOVEMENT_AMOUNT;

	SetActorLocation(FMath::VInterpTo(GetActorLocation(), dashTargetLocation, DASH_VELOCITY * GetWorld()->GetDeltaSeconds(), 0.5f));

	GetWorld()->GetTimerManager().SetTimer(dashTimerHandle, this, &APlayerCharacter::DashTimerReset, 0.1f, false, DASH_COOLTIME);

}

void APlayerCharacter::DashTimerReset()
{
	UE_LOG(LogClass, Warning, TEXT("Dash Timer Test"));
	GetWorldTimerManager().ClearTimer(dashTimerHandle);
	isDashing = false;
	damageableComponent->SetInvincible(false);
}

FVector APlayerCharacter::GetPlayerMovementInput()
{
	if (GetOwner() && InputComponent)
	{
		return FVector(InputComponent->GetAxisValue("MoveForward"), InputComponent->GetAxisValue("MoveSide"), 0);
	}
	else
	{
		return GetActorForwardVector();
	}
}

void APlayerCharacter::BeginFocusing()
{
	isFocusing = true;
}

void APlayerCharacter::EndFocusing()
{
	isFocusing = false;
}

int32 APlayerCharacter::GetBaseDamage() const
{
	// #To do, 플레이어 스텟 구현
	return 1;
}