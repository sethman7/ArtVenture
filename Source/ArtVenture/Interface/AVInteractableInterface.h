// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AVInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, Meta = (ImplementInterfaceInBlueprint))
class UAVInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARTVENTURE_API IAVInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Interact() = 0;
};

