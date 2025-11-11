// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

// Sets default values
ATarget::ATarget()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATarget::ProcessTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("'%s' Hit '%s' by '%f' Damage"), *InstigatedBy->GetPawn()->GetName(), *this->GetName(), Damage);

		Destroy();
	}
}

