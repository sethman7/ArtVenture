//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "AVVRTeleportVisualizer.generated.h"
//
//UCLASS()
//class ARTVENTURE_API AAVVRTeleportVisualizer : public AActor
//{
//	GENERATED_BODY()
//	
//public:	
//	// Sets default values for this actor's properties
//	AAVVRTeleportVisualizer();
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
//	TObjectPtr<class UNiagaraComponent> TeleportRing;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
//	TObjectPtr<class UNiagaraComponent> PlayAreaBound;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
//	TObjectPtr<class UNiagaraComponent> TeleportTraceNiagaraSystem;
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//	
//	APawn* Player;
//	class APlayerCameraManager* CameraManager;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//};
