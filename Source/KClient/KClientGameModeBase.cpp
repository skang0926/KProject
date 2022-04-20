#include "KClientGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacter.h"

AKClientGameModeBase::AKClientGameModeBase()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;

    DefaultPawnClass = APlayerCharacter::StaticClass();

    PathTable::GetInstance().Load();
}

void AKClientGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    ChangeMenuWidget(startingWidgetClass); 
}

void AKClientGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> newWidgetClass)
{
    if (currentWidget != nullptr)
    { 
        currentWidget->RemoveFromViewport(); 
        currentWidget = nullptr;
    } 
    
    if (newWidgetClass != nullptr) 
    {
        currentWidget = CreateWidget(GetWorld(), newWidgetClass); 
        if (currentWidget != nullptr)
        {
            currentWidget->AddToViewport(); 
        }
    }
}
