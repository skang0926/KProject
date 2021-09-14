// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnComponent.h"
#include "CharacterBase.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetComponentTickEnabled(false);
	
}

// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (targetCharacter == nullptr)
	{
		SetComponentTickEnabled(false);
		return;
	}

	if (targetCharacter->IsActorBeingDestroyed())
	{
		targetCharacter = nullptr;
		SetComponentTickEnabled(false);
		return;
	}

	UpdateControllerRotator();
}

void ULockOnComponent::SetTargetCharacter(ACharacterBase* const otherCharacter)
{
	if (otherCharacter)
	{
		targetCharacter = otherCharacter;
		SetComponentTickEnabled(true);
	}
	else
	{
		targetCharacter = nullptr;
		SetComponentTickEnabled(false);
	}
}

void ULockOnComponent::UpdateControllerRotator()
{
	ACharacterBase* onwerCharacter = dynamic_cast<ACharacterBase*>(GetOwner());

	FVector vDir = targetCharacter->GetActorLocation() - onwerCharacter->GetActorLocation();
	FRotator targetRotator = vDir.Rotation();
	auto onwerController = onwerCharacter->GetController();
	targetRotator = FRotator(targetRotator.Pitch, FMath::RInterpTo(onwerController->GetControlRotation(), targetRotator, GetWorld()->GetDeltaSeconds(), 5.f).Yaw, targetRotator.Roll);
	onwerCharacter->SetActorRotation(FRotator(0.f, targetRotator.Yaw, 0.f));
	onwerController->SetControlRotation(targetRotator);
}
