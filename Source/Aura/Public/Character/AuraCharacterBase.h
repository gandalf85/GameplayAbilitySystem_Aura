// No copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values
	AAuraCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// We attach a weapon to a socket on the skeletal mesh
	// TObjectPtr has some additional features compared to a normal pointer in editor -- this is now the standard
	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
};
