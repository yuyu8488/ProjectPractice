
#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(BoxCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AProjectile::ProcessBeginOverlap);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UGameplayStatics::ApplyDamage(OtherActor, 10.f, UGameplayStatics::GetPlayerController(GetWorld(), 0), this, nullptr);
}

