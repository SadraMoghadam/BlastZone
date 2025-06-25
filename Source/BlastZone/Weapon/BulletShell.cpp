// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletShell.h"

// Sets default values
ABulletShell::ABulletShell()
{
	PrimaryActorTick.bCanEverTick = false;

	ShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShellMesh"));
	SetRootComponent(ShellMesh);
}

void ABulletShell::BeginPlay()
{
	Super::BeginPlay();
	
}

