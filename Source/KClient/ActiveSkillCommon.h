#pragma once

#include "KClient.h"
#include "Projectile.h"
#include "BehaviorComponent.h"

void UseCircularShot( AActor* owner, ESkillType type, int32 damage, float centralAngle, FVector offset, int projectileCount, bool useCrossHair = true ) {
    if ( owner == nullptr ) {
        return;
    }

    UWorld* world = owner->GetWorld();
    if ( world == nullptr ) {
        return;
    }

    FActorSpawnParameters spawnParams;
    spawnParams.Owner = owner;
    spawnParams.Instigator = owner->GetInstigator();

    FVector baseLocation;
    FRotator baseRotation;
    owner->GetActorEyesViewPoint( baseLocation, baseRotation );

    const float angleOffset = centralAngle / static_cast<float>( projectileCount );
    float startAngle = baseRotation.Yaw - centralAngle / 2.0f;

    for ( int segments = 0; segments < projectileCount; ++segments ) {
        FRotator projectileRotation = baseRotation;
        projectileRotation.Yaw      = startAngle;
        projectileRotation.Pitch    = ( useCrossHair ? baseRotation.Pitch : 0.0f );

        FVector projectileLocation = baseLocation + FTransform( projectileRotation ).TransformVector( offset );
        startAngle += angleOffset;

        AProjectile* newProjectile = world->SpawnActor<AProjectile>( AProjectile::StaticClass(), projectileLocation, projectileRotation, spawnParams );
        newProjectile->Initialize( type, damage );

        UStraightMovement* movement = newProjectile->AddComponent<UStraightMovement>();
        movement->Initialize();
        movement->SetDirection( projectileRotation.Vector() );
    }
}