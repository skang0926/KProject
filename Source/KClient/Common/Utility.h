#pragma once

#include "../KClient.h"

#define STRINGIFY(value) #value

inline bool IsEnabledActor( AActor* actor ) {
	if ( actor == nullptr ) {
		return false;
	}

	USceneComponent* rootComponent = actor->GetRootComponent();
	if ( rootComponent == nullptr ) {
		return false;
	}

	return rootComponent->IsVisible();
}

inline void EnableActor( AActor* actor, bool enable ) {
	if ( actor == nullptr ) {
		return;
	}

	USceneComponent* rootComponent = actor->GetRootComponent();
	if ( rootComponent == nullptr ) {
		return;
	}

	actor->SetActorEnableCollision( enable );
	actor->SetActorTickEnabled( enable );
	rootComponent->SetVisibility( enable );
}

template<typename T>
constexpr inline uint8 EnumToNum( T value ) {
	return static_cast<uint8>( value );
}

template<typename T>
constexpr inline T NumToEnum( uint8 value ) {
	if ( !StaticEnum<ESkillType>()->IsValidEnumValue( value ) ) {
		return T::Count;
	}

	return static_cast<T>( value );
}

template<typename T>
constexpr inline FString EnumToFStr( T value ) {
	return StaticEnum<T>()->GetValueAsString( value );
}

template<typename T>
constexpr inline T FStrToEnum( const FString& value ) {
	if ( value.IsEmpty() ) {
		return T::Count;
	}

	if ( !StaticEnum<ESkillType>()->IsValidEnumName( *value ) ) {
		return T::Count;
	}

	return NumToEnum<T>( StaticEnum<T>()->GetIndexByName( *value ) );
}

inline FVector2D GetViewportSize() {
	FVector2D viewport = { 1, 1 };
	if ( GEngine && GEngine->GameViewport ) {
		GEngine->GameViewport->GetViewportSize( viewport );
	}

	return viewport;
}

inline FVector2D GetViewportCenter() {
	FVector2D viewport = { 1, 1 };
	if ( GEngine && GEngine->GameViewport ) {
		GEngine->GameViewport->GetViewportSize( viewport );
	}

	return FVector2D( viewport.X / 2, viewport.Y / 2 );
}