#pragma once

#include "KClient.h"
#include "KClientGameModeBase.generated.h"

UCLASS()
class KCLIENT_API AKClientGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AKClientGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "UMG_Game") 
	void ChangeMenuWidget(TSubclassOf<UUserWidget> newWidgetClass);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG_Game") 
	TSubclassOf<UUserWidget> startingWidgetClass;

	UPROPERTY() 
	UUserWidget* currentWidget;
};
