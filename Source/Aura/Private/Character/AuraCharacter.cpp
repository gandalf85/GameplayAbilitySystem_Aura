// No copyright


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AAuraCharacter::AAuraCharacter()
{
	//character rotates with movement direction
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	//parameters for top-down game
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}
