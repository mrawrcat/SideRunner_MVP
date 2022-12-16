// Fill out your copyright notice in the Description page of Project Settings.


#include "Runner_Character.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Spike.h"
#include "Death_Wall.h"
#include "Engine.h"

// Sets default values
ARunner_Character::ARunner_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f); //Gets Capsule Component and sets it's size to 42.f wide and 96.f height
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap); //Makes the Capsule component detect collison

	//Creates camera component side camera.
	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Side View Camera"));
	SideViewCamera->bUsePawnControlRotation = false;

	//Makes it so that camera stays side view, not rotating like in 3rd person
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Player facing -> makes player rotate to left and right
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	//Player "rigidbody" values (similar to rigidbody in unity) encompassing gravityscale, velocity, and friction, etc.
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 1000.0f;
	GetCharacterMovement()->JumpZVelocity = 1000.0f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;

	tempPos = GetActorLocation(); //current position of player's character
	zPos = tempPos.Z + 300.0f; //camera offset from player (300f away from player along the z pos)

}

// Called when the game starts or when spawned
void ARunner_Character::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARunner_Character::OnOverlapBegin);
	CanMove = true;
	
}

// Called every frame
void ARunner_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	tempPos = GetActorLocation(); //gets current actor location (player pos) and stores it in temp pos (used to position camera)
	tempPos.X -= 850.0f; //modifies temp pos's X to -850.0f
	tempPos.Z = zPos; //same z pos
	SideViewCamera->SetWorldLocation(tempPos); //sets camera to this position.
}

// Called to bind functionality to input
void ARunner_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump); //action jump when player presses jump(spacebar)
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping); //stops applying jump when player releases jump(spacebar) even if player is not all the way up stops going up

	PlayerInputComponent->BindAxis("MoveRight", this, &ARunner_Character::MoveRight);
}

void ARunner_Character::MoveRight(float value)
{
	if (CanMove) {
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), value);
	}
}

void ARunner_Character::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}

void ARunner_Character::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr) {
		ASpike* Death_Wall = Cast<ADeath_Wall>(OtherActor);
		ASpike* Spike = Cast<ASpike>(OtherActor);

		if (Death_Wall || Spike) {
			GetMesh()->Deactivate();
			GetMesh()->SetVisibility(false);

			CanMove = false;

			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunner_Character::RestartLevel, 2.0f, false);
		}
	}
}

