// Fill out your copyright notice in the Description page of Project Settings.
#include "AircraftBase.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Projectile.h"

// Sets default values
AAircraftBase::AAircraftBase()
{
	PrimaryActorTick.bCanEverTick = true;

	FloatingMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	FloatingMovement->MaxSpeed = 1200.f;
}

void AAircraftBase::BeginPlay()
{
	Super::BeginPlay();

}

void AAircraftBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector());
}

// Called to bind functionality to input
void AAircraftBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(AirControlAction, ETriggerEvent::Triggered, this, &AAircraftBase::AirControl);
	}
}

void AAircraftBase::AirControl(const FInputActionInstance& Instance)
{
	FVector3d Input = Instance.GetValue().Get<FVector3d>();

	float Roll = Input.X;
	float Pitch = Input.Y;
	float Yaw = Input.Z;

	//UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	//GetWorld()->GetDeltaSeconds();

	FRotator Rotation = FRotator(Pitch * 100.f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		Yaw * 10.f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),
		Roll * 100.f * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()));

	AddActorLocalRotation(Rotation);
}

void AAircraftBase::Fire_Implementation()
{
}

