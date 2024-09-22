// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AVCharacter.generated.h"

UCLASS()
class ARTVENTURE_API AAVCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAVCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Camera Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAcess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	APlayerCameraManager* PlayerCameraManager;

	//Input Section
	UPROPERTY(EditAnywhere, Category = Input, Meta = (AllowPrivateAcess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input, Meta = (AllowPrivateAcess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input, Meta = (AllowPrivateAcess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = Input, Meta = (AllowPrivateAcess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input, Meta = (AllowPrivateAcess = "true"))
	TObjectPtr<class UInputAction> InteractAction;

	//Movement Section
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



};
