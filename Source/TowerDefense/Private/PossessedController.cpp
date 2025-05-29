// Fill out your copyright notice in the Description page of Project Settings.


#include "PossessedController.h"
#include "GameFramework/Pawn.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"


APossessedController::APossessedController()
{
	isPossessed = false;
	weaponSwitchDelay = 0.3f;
	isZoomedIn = false;
}

void APossessedController::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

}

void APossessedController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Look
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APossessedController::Look);
		// Fire
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APossessedController::Fire);
		// Zooming
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Started, this, &APossessedController::Zoom);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Completed, this, &APossessedController::StopZooming);
		// Switching Weapons
		EnhancedInputComponent->BindAction(SwitchBaseAction, ETriggerEvent::Started, this, &APossessedController::SwitchToBase);
		EnhancedInputComponent->BindAction(SwitchPrimaryAction, ETriggerEvent::Started, this, &APossessedController::SwitchToPrimary);
		EnhancedInputComponent->BindAction(SwitchSecondaryAction, ETriggerEvent::Started, this, &APossessedController::SwitchToSecondary);
		// Scroll Switching Weapons
		EnhancedInputComponent->BindAction(ScrollSwitchAction, ETriggerEvent::Triggered, this, &APossessedController::ScrollSwitch);
	}
}


void APossessedController::Look(const FInputActionValue& Value)
{
	if (isPossessed)
	{
		// Input is a Vector2D
		FVector2D LookAxisVector = Value.Get<FVector2D>();

		// Add yaw and pitch input to controller	
		AddYawInput(LookAxisVector.X);
		AddPitchInput(LookAxisVector.Y*-1.0);
	}
}

void APossessedController::Zoom()
{
	if (isPossessed)
	{
		if (auto firstPersonCamera = GetFirstPersonCameraComponent())
		{
			firstPersonCamera->SetFieldOfView(70.0f);
			isZoomedIn = true;
		}
	}
}

void APossessedController::StopZooming()
{
	if (isPossessed)
	{
		if (isZoomedIn)
		{
			if (auto firstPersonCamera = GetFirstPersonCameraComponent())
			{
				firstPersonCamera->SetFieldOfView(90.0f);
				isZoomedIn = false;
			}
		}
	}
}

//To be implemented
void APossessedController::SwitchToBase()
{

}

void APossessedController::SwitchToPrimary()
{

}

void APossessedController::SwitchToSecondary()
{

}

void APossessedController::ScrollSwitch(const FInputActionValue& Value)
{

}
