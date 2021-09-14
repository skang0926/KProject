#include "ActiveSkill.h"
#include "ActiveSkillCommon.h"
#include "SkillData.h"
#include "PlayerCharacter.h"
#include "DamageableComponent.h"

void UCircularSectorShotSkill::Use() {
    Super::Use();

    ACharacterBase* ownerActor = GetOwner<ACharacterBase>();
    if (ownerActor == nullptr) {
        UE_LOG( KP, Error, TEXT("doesn't exist owner actor") );
        return;
    }

    const UCircularSectorShotData* prop = Cast<UCircularSectorShotData>( uniqueProperty );
    if ( prop == nullptr ) {
        UE_LOG( KP, Error, TEXT("doesn't exist unique property") );
        return;
    }

    int32 damage = ownerActor->GetBaseDamage() * commonProperty.damagePercentRate * 0.01f;
    UseCircularShot( ownerActor, commonProperty.skillType, damage, prop->centralAngle, prop->offset, prop->projectileCount );
}

void UHitScanShotSkill::Use() {
    Super::Use();

    APlayerCharacter* player = GetOwner<APlayerCharacter>();
    if (player == nullptr) {
        return;
    }

    UWorld* world = GetWorld();
    if ( !world ) {
        return;
    }

    const UHitScanShotData* prop = Cast<UHitScanShotData>( uniqueProperty );
    if ( prop == nullptr ) {
        UE_LOG( KP, Error, TEXT("doesn't exist unique property") );
        return;
    }

    APlayerController* controller = player->GetController<APlayerController>();
    if ( !controller ) {
        UE_LOG( KP, Error, TEXT("doesn't exist controller") );
        return;
    }

    FVector2D center = GetViewportCenter();
    FVector crossHairPos, crossHairDir;
    if ( !controller->DeprojectScreenPositionToWorld( center.X, center.Y, crossHairPos, crossHairDir ) ) {
        return;
    }

    FVector start = crossHairPos;
    FVector end = start + crossHairDir * prop->maxRange;

    FCollisionQueryParams collisionParams;
    collisionParams.AddIgnoredActor( player );

    FHitResult outHit( EForceInit::ForceInit );
    if ( !world->LineTraceSingleByChannel( outHit, start, end, ECollisionChannel::ECC_GameTraceChannel3, collisionParams ) ) {
        outHit.ImpactPoint = end;
    }

    DrawDebugLine( world, start, outHit.ImpactPoint, FColor( 0, 0, 255 ), false, 10.0f, 0, 3.0f );

    FVector playerLocation = player->GetActorLocation();
    playerLocation.Z += player->BaseEyeHeight;

    start = playerLocation;
    end = outHit.ImpactPoint + ( outHit.ImpactPoint - start ).GetSafeNormal();

    if ( !world->LineTraceSingleByChannel( outHit, start, end, ECollisionChannel::ECC_GameTraceChannel3, collisionParams ) ) {
        outHit.ImpactPoint = end;
    }

    DrawDebugLine( world, start, outHit.ImpactPoint, FColor( 255, 0, 0 ), false, 10.0f, 0, 3.0f );

    ACharacterBase* hitActor = Cast<ACharacterBase>( outHit.GetActor() );
    if ( !hitActor ) {
        return;
    }
    
    auto damageableComponent = hitActor->GetDamageableComponent();
    if ( damageableComponent )	{
        int32 damage = player->GetBaseDamage() * commonProperty.damagePercentRate;
        damageableComponent->ApplyDamage( damage );
    }
}