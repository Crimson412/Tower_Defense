// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "PossessedController.generated.h"

// Forward declaration to improve compiling times
class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class APossessedController : public APlayerController
{
	GENERATED_BODY()

	//Input Actions:

	// Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	// Fire Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	// Reload Input Action (Manual)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	// Zoom Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomAction;

	// Switch Base Weapon Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchBaseAction;

	// Switch Primary Weapon Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchPrimaryAction;

	// Switch Secondary Weapon Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchSecondaryAction;

	// Switch Melee Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UInputAction* ScrollSwitchAction;

	// The timer handle for the weapon switch dealy
	FTimerHandle weaponSwitchTimerHandle;

	// Delay between weapon switching (So track pad doesn't go crazy)
	float weaponSwitchDelay;

	// Has the weapon been switched Boolean
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool isWeaponSwitchOnCooldown;

	// To let the input know whether the player is possessing or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool isPossessed;

	// Is Zoomed In Boolean
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool isZoomedIn;

	// Is Reloading Boolean
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool isReloading;

	// Is Shooting Boolean
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool isShooting;

	// Is Shot on Cooldown Boolean (to manage time between single-fire/semi-auto weapons)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool isShotOnCooldown;

protected:

	// Function Called for looking input
	void Look(const FInputActionValue& Value);

	// Function that shoots a weapon
	UFUNCTION(BlueprintImplementableEvent, Category = Weapon)
	void Fire();

	// Functions that Allow the character to begin and stop zooming
	void Zoom();

	void StopZooming();

	// Functions that switch to the specified weapons
	void SwitchToBase();
	void SwitchToPrimary();
	void SwitchToSecondary();

	// Function that switches the weapon using the mouse scroll wheel instead
	void ScrollSwitch(const FInputActionValue& Value);

	// Function that switches the weapon in BP
	UFUNCTION(BlueprintImplementableEvent, Category = HUD)
	void SwitchWeaponMesh(int _index);

	// Function used to add in a switch weapon delay (For trackpad craziness)
	void WeaponSwitchCooldownComplete();

	//virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void SetupInputComponent() override;

	virtual void BeginPlay();

public:

	APossessedController();

	// Returns FirstPersonCameraComponent subobject
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// First person camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	// MappingContext
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
};
