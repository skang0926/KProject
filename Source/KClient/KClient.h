// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

/////////////// Engine ///////////////
#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"

#include "UObject/UObjectBase.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/NoExportTypes.h"

#include "Misc/DateTime.h"
#include "Misc/Paths.h"

#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"

#include "DrawDebugHelpers.h"

/////////////// STL ///////////////
#include <fstream>
#include <iostream>
#include <string>

/////////////// COMMON ///////////////
#include "../PathLoader/PathTable.h"

/////////////// Implement ///////////
#include "BasicType.h"

#include "KProjectGameInstance.h"
#include "KClientGameState.h"

#include "SkillBase.h"

#include "CharacterBase.h"

KCLIENT_API DECLARE_LOG_CATEGORY_EXTERN(KP, Log, All);