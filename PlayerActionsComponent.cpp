// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PlayerActionsComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainCharacterInterface.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UPlayerActionsComponent::UPlayerActionsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerActionsComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = GetOwner<ACharacter>();
	MovementComp = CharacterRef->GetCharacterMovement();

	if (!CharacterRef->Implements<UMainCharacterInterface>())
	{
		return;
	}

	IMainCharacter = Cast<IMainCharacterInterface>(CharacterRef);
	
}


// Called every frame
void UPlayerActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerActionsComponent::Sprint()
{

	if (!IMainCharacter->HasEnoughStamina(SprintCost))
	{
		Walk();
		return;
	}

	if (MovementComp->Velocity.Equals(FVector::ZeroVector, 1)) //use FVector Zero to save memeory
	{
		return;
	}

	MovementComp->MaxWalkSpeed = SprintSpeed;

	OnSprintDelegate.Broadcast(SprintCost);
}

void UPlayerActionsComponent::Walk()
{

	MovementComp->MaxWalkSpeed = WalkSpeed;
}

