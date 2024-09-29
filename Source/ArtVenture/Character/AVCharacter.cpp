//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Character/AVCharacter.h"
//
////Camera
//#include "Camera/CameraComponent.h"
//#include "Camera/PlayerCameraManager.h"
//#include "Kismet/KismetMathLibrary.h"
////Collision
//#include "Components/CapsuleComponent.h"
////Movement
//#include "GameFramework/CharacterMovementComponent.h"
////Mapping,Input
//#include "InputMappingContext.h"
//#include "EnhancedInputComponent.h"
//#include "EnhancedInputSubsystems.h"
//
////Interface
//#include "Interface/AVInteractableInterface.h"
//
////Teleport Section
//#include "Gimmick/AVVRTeleportVisualizer.h"
////#include "NiagaraFunctionLibrary.h"
//#include "NiagaraComponent.h"
////#include "NiagaraActor.h"
////#include "NiagaraSystem.h"
//#include "Kismet/GameplayStatics.h"
//#include "NavigationSystem.h"
//
//// Sets default values
//AAVCharacter::AAVCharacter()
//{
// 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//
//	//Pawn
//	bUseControllerRotationPitch = false;
//	bUseControllerRotationRoll = false;
//	bUseControllerRotationYaw = false;
//
//	//Capsule
//	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
//	GetCapsuleComponent()->SetCollisionProfileName("Pawn");
//
//	//Movement
//	GetCharacterMovement()->bOrientRotationToMovement = true;
//	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
//	GetCharacterMovement()->JumpZVelocity = 700.f;
//	GetCharacterMovement()->AirControl = 0.35f;
//
//	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
//	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
//
//	//Mesh
//	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
//	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
//	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
//
//	//Camera
//	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
//	Camera->SetupAttachment(RootComponent);
//	Camera->bUsePawnControlRotation = true;
//
//
//	TeleportTraceNiagaraSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraSystem"));
//
//
//
//	//Get Mesh
//	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/ArtVenture/TempPlayer/FirstPersonArms/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms"));
//	if (CharacterMeshRef.Object)
//	{
//		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
//	}
//
//	//Get Animation
//	static ConstructorHelpers::FClassFinder<UAnimInstance> AniminstanceClassRef(TEXT("/Game/ArtVenture/TempPlayer/FirstPersonArms/Animations/FirstPerson_AnimBP.FirstPerson_AnimBP_C"));
//	if (AniminstanceClassRef.Class)
//	{
//		GetMesh()->SetAnimInstanceClass(AniminstanceClassRef.Class);
//	}
//
//	//Mapping Section
//	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Game/ArtVenture/Blueprint/Player/IMC_PCVersion.IMC_PCVersion"));
//	if (InputMappingContextRef.Object)
//	{
//		DefaultMappingContext = InputMappingContextRef.Object;
//	}
//	ensure(InputMappingContextRef.Object);
//
//	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Game/ArtVenture/Blueprint/Player/IA_Move.IA_Move"));
//	if (InputActionMoveRef.Object)
//	{
//		MoveAction = InputActionMoveRef.Object;
//	}
//	ensure(InputActionMoveRef.Object);
//
//	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Game/ArtVenture/Blueprint/Player/IA_Look.IA_Look"));
//	if (InputActionLookRef.Object)
//	{
//		LookAction = InputActionLookRef.Object;
//	}
//	ensure(InputActionLookRef.Object);
//
//	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Game/ArtVenture/Blueprint/Player/IA_Jump.IA_Jump"));
//	if (InputActionJumpRef.Object)
//	{
//		JumpAction = InputActionJumpRef.Object;
//	}
//	ensure(InputActionJumpRef.Object);
//
//	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionInteractRef(TEXT("/Game/ArtVenture/Blueprint/Player/IA_Interact.IA_Interact"));
//	if (InputActionInteractRef.Object)
//	{
//		InteractAction = InputActionInteractRef.Object;
//	}
//	ensure(InputActionInteractRef.Object);
//
//	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionDropRef(TEXT("/Game/ArtVenture/Blueprint/Player/IA_Drop.IA_Drop"));
//	if (InputActionDropRef.Object)
//	{
//		DropAction = InputActionDropRef.Object;
//	}
//	ensure(InputActionDropRef.Object);
//
//	
//}
//
//// Called when the game starts or when spawned
//void AAVCharacter::BeginPlay()
//{
//	Super::BeginPlay();
//	APlayerController* PlayerController = Cast<APlayerController>(GetController());
//	if (PlayerController)
//	{
//		EnableInput(PlayerController);
//	}
//
//	//Get CameraManager
//	PlayerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
//}
//
//void AAVCharacter::Move(const FInputActionValue& Value)
//{
//	FVector2D MovementVector = Value.Get<FVector2D>();
//
//	const FRotator Rotation = Controller->GetControlRotation();
//	const FRotator YawRotation(0, Rotation.Yaw, 0);
//
//	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//
//	AddMovementInput(ForwardDirection, MovementVector.X);
//	AddMovementInput(RightDirection, MovementVector.Y);
//}
//
//void AAVCharacter::Look(const FInputActionValue& Value)
//{
//	FVector2D LookAxisVector = Value.Get<FVector2D>();
//
//	AddControllerYawInput(LookAxisVector.X);
//	AddControllerPitchInput(LookAxisVector.Y);
//}
//
//void AAVCharacter::CheckInteractableObject(const FInputActionValue& Value)
//{
//	FHitResult OutHit;
//	FCollisionQueryParams Params(SCENE_QUERY_STAT(INTERACT), false, this);
//
//
//
//	FVector Start = PlayerCameraManager->GetCameraLocation();
//	FRotator Rotation =  PlayerCameraManager->GetCameraRotation();
//	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Rotation);
//	FVector End= Start + (ForwardVector * 300.0f); 
//
//
//
//	bool IsHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_GameTraceChannel2, Params);
//	if (IsHit)
//	{
//		IAVInteractableInterface* InteractableObject = Cast<IAVInteractableInterface>(OutHit.GetActor());
//		if (InteractableObject == NULL) { return; }		
//
//		InteractableObject->Interact();
//		if (InteractableObject->IsGrabbale == true)
//		{
//			Equip(InteractableObject);
//		}
//	}
//}
//
//void AAVCharacter::Equip(IAVInteractableInterface* InteractableObject)
//{
//	GrabbaleItem = Cast<AActor>(InteractableObject);
//	GrabbaleItem->SetActorEnableCollision(false);
//	GrabbaleItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,"Hand");
//}
//
//void AAVCharacter::Drop()
//{
//	if (GrabbaleItem == NULL) { return; }
//	GrabbaleItem->SetActorEnableCollision(true);
//	GrabbaleItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
//	FVector PlayerLocation = GetActorLocation();
//	FVector ForwardVector = GetActorForwardVector();
//	FVector DropLocation = PlayerLocation + (ForwardVector * 200.0f);
//
//	FVector Start = DropLocation;
//	FVector End = Start - FVector(0, 0, 100);
//	FHitResult HitResult;
//	FCollisionQueryParams CollisionParams;
//
//	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
//	{
//		DropLocation.Z = HitResult.Location.Z;
//	}
//
//
//	GrabbaleItem->SetActorLocation(DropLocation);
//	GrabbaleItem = NULL;
//}
//
//void AAVCharacter::StartTeleportTrace()
//{
//	bTeleportTraceActive = true;
//	TeleportTraceNiagaraSystem->SetVisibility(true,false);
//
//	FActorSpawnParameters SpawnInfo;
//	SpawnInfo.Owner = this;
//	TeleportVisualizerReference = GetWorld()->SpawnActor<AAVVRTeleportVisualizer>(AAVVRTeleportVisualizer::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
//	ensure(TeleportVisualizerReference);
//}
//
//void AAVCharacter::TeleportTrace(FVector StartPos, FVector ForwardVector)
//{
//	FHitResult OutHit;
//	TArray<FVector> OutPathPositions;
//	FVector OutLastTraceDestination;
//	float LocalTeleportLaunchSpeed = 650.0f;
//	FVector LaunchVelocity = FVector(LocalTeleportLaunchSpeed) * ForwardVector;
//	bool bTracePath = true;
//	float LocalTeleportProjectileRadius = 3.6;
//	TArray<TEnumAsByte<EObjectTypeQuery> > ObjectTypes;
//	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
//	bool bTraceComplex = false;
//	const TArray<AActor*> ActorsToIgnore;
//	float DrawDebugTime = 0.0;
//	float SimFrequency = 15.0;
//	float MaxSimTime = 2.0;
//	float OverrideGravityZ = 0.0;
//
//	UGameplayStatics::Blueprint_PredictProjectilePath_ByObjectType(
//		GetWorld(),
//		OutHit,
//		OutPathPositions,
//		OutLastTraceDestination,
//		StartPos,
//		LaunchVelocity,
//		bTracePath,
//		LocalTeleportProjectileRadius,
//		ObjectTypes,
//		bTraceComplex,
//		ActorsToIgnore,
//		EDrawDebugTrace::None,
//		DrawDebugTime,
//		SimFrequency,
//		MaxSimTime,
//		OverrideGravityZ
//	);
//
//	TeleportTracePathPositions = &OutPathPositions;
//	TeleportTracePathPositions->Insert(StartPos,0);
//
//	
//}
//
//bool AAVCharacter::IsValidTeleportLocation(FHitResult& OutHit)
//{
//	//UNavigationSystemV1* UNavigationSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
//	//OutHit.Location;
//	//FNavLocation OutLocation;
//
//	//UNavigationSystem->UNavigationSystemV1::ProjectPointToNavigation(OutHit.Location, OutLocation);
//
//	return false;
//}
//
//
//// Called every frame
//void AAVCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//// Called to bind functionality to input
//void AAVCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
//	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
//	{
//		Subsystem->ClearAllMappings();
//		UInputMappingContext* NewMappingContext = DefaultMappingContext;
//		if (NewMappingContext)
//		{
//			Subsystem->AddMappingContext(NewMappingContext, 0);
//		}
//	}
//
//	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
//	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAVCharacter::Move);
//	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAVCharacter::Look);
//	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
//	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
//	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAVCharacter::CheckInteractableObject);
//	EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Triggered, this, &AAVCharacter::Drop);
//}
//
