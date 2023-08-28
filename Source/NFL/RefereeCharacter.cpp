// Fill out your copyright notice in the Description page of Project Settings.


#include "RefereeCharacter.h"

// Sets default values
ARefereeCharacter::ARefereeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARefereeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARefereeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARefereeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

