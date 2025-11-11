// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework\SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Kismet\KismetMathLibrary.h"
//C:\Program Files\Epic Games\UE_5.6\Engine\Source\Runtime\Engine\Private\KismetMathLibrary.cpp

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
	}
}

void APlayerCharacter::Move(const FInputActionInstance& Instance)
{
	FVector2D Input = Instance.GetValue().Get<FVector2D>();

	FRotator ControlRotation = GetController()->GetControlRotation();
	FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator(0.f, ControlRotation.Yaw, 0.f));
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(FRotator(0.f, ControlRotation.Yaw, 0.f));

	AddMovementInput(RightVector, Input.X);
	AddMovementInput(ForwardVector, Input.Y);
}

void APlayerCharacter::Look(const FInputActionInstance& Instance)
{
	FVector2D Input = Instance.GetValue().Get<FVector2D>();

	UE_LOG(LogTemp, Warning, TEXT("Look InputX: '%f' / InputY: '%f"), Input.X, Input.Y);
	//FRotator Rotation = FRotator()
	//AddActorLocalRotation();
	
	AddControllerYawInput(Input.X);
	AddControllerPitchInput(Input.Y);
}

