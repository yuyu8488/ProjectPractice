// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AircraftBase.generated.h"

class UFloatingPawnMovement;
class UInputAction;
class AProjectile;
struct FInputActionInstance;

UCLASS()
class PROJECTPRACTICE_API AAircraftBase : public APawn
{
	GENERATED_BODY()

public:
	AAircraftBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnyWhere, Category = "Components")
	TObjectPtr<UFloatingPawnMovement> FloatingMovement;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileClass;

protected:
	void AirControl(const FInputActionInstance& Instance);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Fire();
	virtual void Fire_Implementation();

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UInputAction> AirControlAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inputs")
	TObjectPtr<UInputAction> FireAction;

};
