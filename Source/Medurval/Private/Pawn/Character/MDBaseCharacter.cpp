// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/Character/MDBaseCharacter.h"

// Sets default values
AMDBaseCharacter::AMDBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMDBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMDBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMDBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

