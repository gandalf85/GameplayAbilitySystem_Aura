// No copyright


#include "Player/AuraPlayerController.h"

#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	// Replication in multiplayer is when changes get sent down from the server to all clients
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// Handle highlighting of enemies
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor()); //if this cast succeeds, the actor implements the enemy highlighting functions 

	/**
	 * Line trace from cursor. There are several scenarios.
	 *	A) LastActor is null && ThisActor is null
	 *		- Do nothing
	 *	B) LastActor is null && ThisActor is valid
	 *		- We're hovering over ThisActor for the first time, Highlight ThisActor
	 *	C) LastActor is valid && ThisActor is null
	 *		- Unhighlight LastActor
	 *	D) LastActor is valid && ThisActor is valid, but LastActor != ThisActor
	 *		- Unhighlight LastActor, Highlight ThisActor
	 *	E) LastActor is valid && ThisActor is valid, but LastActor == ThisActor
	 *		- Do nothing
	 */
	
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// Case B
			ThisActor->HighlightActor();
		}
		else
		{
			// Case A
		}
	}
	else // LastActor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else //Both Actors are valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E
				
			}
		}
	}

}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Setup the input mapping context -- halt execution if there is none
	check(AuraContext);

	// Subsystems are singletons -- AuraContext has highest priority
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}	

	//Default mouse behavior -- show the default cursor
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//Basic game mode settings -- when the cursor is captured, don't hide it
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Cast and assert enhanced input component
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	//Bind functions to actions
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	//Why is yaw the axis we are interested in
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//In Unreal, X is forward
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	//Add movement input to controlled pawn
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		//In the 2D input mapping context, X is left-right, Y is forward-backward
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


