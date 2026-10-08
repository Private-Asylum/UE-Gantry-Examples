// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "Pawn/Character/GTCharacter.h"

#include "Core/Tags/GTGameplayTags.h"
#include "GantryExamplesLogCategories.h"
#include "Input/GTEnhancedInputComponent.h"
#include "Input/GTInputConfig.h"
#include "Pawn/Character/GTCharacterMovementComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "Net/UnrealNetwork.h"

AGTCharacter::AGTCharacter(const FObjectInitializer& ObjectInitializer)
	// Swap in the project movement component before the base constructor creates the default one.
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UGTCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
	, Stance(EGTMovementStance::Walking)
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	// The controller turns the character, not the camera boom.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

UGTCharacterMovementComponent* AGTCharacter::GetGTCharacterMovement() const
{
	return Cast<UGTCharacterMovementComponent>(GetCharacterMovement());
}

void AGTCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGTCharacter, Stance);
}

void AGTCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGTCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGTCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGTCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UE_LOG(LogGTPawn, Verbose, TEXT("%s possessed by %s."), *GetName(), *GetNameSafe(NewController));
}

void AGTCharacter::UnPossessed()
{
	Super::UnPossessed();
}

void AGTCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();
}

void AGTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UGTEnhancedInputComponent* GTInputComponent = Cast<UGTEnhancedInputComponent>(PlayerInputComponent))
	{
		BindInputActions(GTInputComponent);
	}
	else
	{
		UE_LOG(LogGTInput, Error,
			TEXT("%s expected a UGTEnhancedInputComponent. Check DefaultInputComponentClass in DefaultInput.ini."),
			*GetName());
	}
}

void AGTCharacter::BindInputActions(UGTEnhancedInputComponent* GTInputComponent)
{
	if (!InputConfig)
	{
		UE_LOG(LogGTInput, Warning, TEXT("%s has no InputConfig assigned; no actions bound."), *GetName());
		return;
	}

	// Tags are qualified rather than pulled in with a using-directive: this class has member
	// functions with the same names, and class scope would win the lookup.
	GTInputComponent->BindActionByTag(InputConfig, GTGameplayTags::Input_Move, ETriggerEvent::Triggered, this, &AGTCharacter::Input_Move);
	GTInputComponent->BindActionByTag(InputConfig, GTGameplayTags::Input_Look, ETriggerEvent::Triggered, this, &AGTCharacter::Input_Look);
	GTInputComponent->BindActionByTag(InputConfig, GTGameplayTags::Input_Jump, ETriggerEvent::Started, this, &AGTCharacter::Input_JumpStarted);
	GTInputComponent->BindActionByTag(InputConfig, GTGameplayTags::Input_Jump, ETriggerEvent::Completed, this, &AGTCharacter::Input_JumpCompleted);
	GTInputComponent->BindActionByTag(InputConfig, GTGameplayTags::Input_Crouch, ETriggerEvent::Started, this, &AGTCharacter::Input_CrouchToggle);
	GTInputComponent->BindActionByTag(InputConfig, GTGameplayTags::Input_Sprint, ETriggerEvent::Started, this, &AGTCharacter::Input_SprintStarted);
	GTInputComponent->BindActionByTag(InputConfig, GTGameplayTags::Input_Sprint, ETriggerEvent::Completed, this, &AGTCharacter::Input_SprintCompleted);
}

void AGTCharacter::Input_Move(const FInputActionValue& Value)
{
	const FVector2D MoveAxis = Value.Get<FVector2D>();
	const AController* MyController = GetController();

	if (!MyController || MoveAxis.IsNearlyZero())
	{
		return;
	}

	// Move relative to where the player is looking, flattened onto the ground plane.
	const FRotator YawRotation(0.0f, MyController->GetControlRotation().Yaw, 0.0f);
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, MoveAxis.Y);
	AddMovementInput(Right, MoveAxis.X);
}

void AGTCharacter::Input_Look(const FInputActionValue& Value)
{
	const FVector2D LookAxis = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxis.X);
	AddControllerPitchInput(LookAxis.Y);
}

void AGTCharacter::Input_JumpStarted()
{
	Jump();
}

void AGTCharacter::Input_JumpCompleted()
{
	StopJumping();
}

void AGTCharacter::Input_CrouchToggle()
{
	if (IsCrouched())
	{
		UnCrouch();
		SetStance(EGTMovementStance::Walking);
	}
	else
	{
		Crouch();
		SetStance(EGTMovementStance::Crouching);
	}
}

void AGTCharacter::Input_SprintStarted()
{
	SetStance(EGTMovementStance::Sprinting);
}

void AGTCharacter::Input_SprintCompleted()
{
	if (Stance == EGTMovementStance::Sprinting)
	{
		SetStance(EGTMovementStance::Walking);
	}
}

void AGTCharacter::SetStance(EGTMovementStance NewStance)
{
	if (Stance == NewStance)
	{
		return;
	}

	const EGTMovementStance OldStance = Stance;
	Stance = NewStance;

	// OnRep never runs on the authority, so drive the shared path by hand.
	OnRep_Stance(OldStance);
}

void AGTCharacter::OnRep_Stance(EGTMovementStance OldStance)
{
	if (UGTCharacterMovementComponent* Movement = GetGTCharacterMovement())
	{
		Movement->SetStance(Stance);
	}

	OnStanceChanged.Broadcast(OldStance, Stance);
}

void AGTCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
}

void AGTCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
}
