// No copyright


#include "Character/AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	//No need for the base character to tick
	PrimaryActorTick.bCanEverTick = false;

	//Create weapon, attach to socket, disable collision
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

