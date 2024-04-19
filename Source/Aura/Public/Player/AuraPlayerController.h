// No copyright

#pragma once

//Needed to get enhanced input mappings working
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


//Forward declarations
//I had to add "EnhancedInput" to the modules in Aura.Build.cs 
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

	// We are using Enhanced Input
public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	//The Cursor Trace keeps track of the last highlighted enemy and updates ThisActor when a valid target is highlighted
	void CursorTrace();
	IEnemyInterface* LastActor;
	IEnemyInterface* ThisActor;
};
