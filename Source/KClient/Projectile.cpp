#include "Projectile.h"
#include "ProjectileData.h"
#include "CharacterBase.h"
#include "DamageableComponent.h"

AProjectile::AProjectile() {
	PrimaryActorTick.bCanEverTick = true;

	SetupComponent();
}

void AProjectile::BeginPlay() {
	Super::BeginPlay();	
}

void AProjectile::Initialize( ESkillType skillType, int32 damage) {
	usedSkillType = skillType;
	projectileDamage = damage;

	FString assetPath = CONVERT_TEXT( EStringKey::PATH_DIR_SKILL_DATA );
	assetPath.Append( GetClass()->GetName() );

	commonProperty = Cast<UProjectileData>( LoadObject<UDataAsset>( nullptr, *assetPath ) );
	if ( commonProperty == nullptr ) {
		UE_LOG( KP, Error, TEXT("doesn't exist common property %s"), *assetPath );
		return;
	}

	collisionComponent->InitSphereRadius( commonProperty->collisionSphereRadius );
	meshComponent->SetRelativeScale3D( commonProperty->scale );
	SetLifeSpan( commonProperty->lifeSpan );
	SetActorEnableCollision( true );
}

void AProjectile::SetupComponent() {
	// Setup collision component
	collisionComponent = CreateDefaultSubobject<USphereComponent>( TEXT( "SphereComponent" ) );
	collisionComponent->BodyInstance.SetCollisionProfileName( TEXT( "Projectile" ) );
	collisionComponent->OnComponentHit.AddDynamic( this, &AProjectile::OnHit );
	collisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin); 
	collisionComponent->OnComponentEndOverlap.AddDynamic(this, &AProjectile::OnOverlapEnd); 
	RootComponent = collisionComponent;

	SetActorEnableCollision( false );

	// Setup mesh component
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "ProjectileMeshComponent" ) );
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh( CONVERT_TEXT( EStringKey::PATH_MESH_SPHERE ) );
	if ( mesh.Succeeded() ) {
		meshComponent->SetStaticMesh( mesh.Object );
	}

	meshComponent->SetupAttachment( RootComponent );
}

void AProjectile::Tick(float deltaTime) {
	Super::Tick( deltaTime );
}

void AProjectile::OnDestroy() {
	Destroy();
}

void AProjectile::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit) {
	OnDestroy();
}

void AProjectile::OnOverlapBegin( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult ) {
	if ( otherActor == this ) {
		return;
	}

	if ( otherActor == GetOwner() ) {
		return;
	}

	AProjectile* const otherProjectile = Cast<AProjectile>( otherActor );
	if ( otherProjectile ) {
		return;
	}

	ACharacterBase* const targetCharacter = Cast<ACharacterBase>(otherActor);
	if (targetCharacter) {
		auto damaeableComponent = targetCharacter->GetDamageableComponent();
		if (damaeableComponent && !damaeableComponent->IsInvincible())
		{
			damaeableComponent->ApplyDamage(projectileDamage);
		}
	}
	
	OnDestroy();
}

void AProjectile::OnOverlapEnd( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex ) {

}

ESkillType AProjectile::GetUsedSkillType() const {
	return usedSkillType;
}

ACharacterBase* const AProjectile::GetShooter() const {
	return GetOwner<ACharacterBase>();
}

UStaticMeshComponent* const AProjectile::GetMesh() const {
	return meshComponent; 
}

USphereComponent* const AProjectile::GetCollider() const {
	return collisionComponent;
}

float AProjectile::GetInitSpeed() const {
	return commonProperty->initSpeed;
}

float AProjectile::GetMaxSpeed() const {
	return commonProperty->maxSpeed;
}

float AProjectile::GetGravityScale() const {
	return commonProperty->gravityScale;
}