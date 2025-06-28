// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletShell.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/SoundCue.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
ABulletShell::ABulletShell()
{
	PrimaryActorTick.bCanEverTick = false;

	ShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShellMesh"));
	SetRootComponent(ShellMesh);
	ShellEjectionImpuls = 5.0f;
	SetLifeSpan(3.f);
}

void ABulletShell::BeginPlay()
{
	Super::BeginPlay();
	ShellMesh->OnComponentHit.AddDynamic(this, &ABulletShell::OnHit);

	ShellMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	ShellMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	ShellMesh->SetSimulatePhysics(true);
	ShellMesh->SetEnableGravity(true);
	ShellMesh->SetNotifyRigidBodyCollision(true);

	FVector RandomShell = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(GetActorForwardVector(), 20.f);
	ShellMesh->AddImpulse(RandomShell * ShellEjectionImpuls);
}

void ABulletShell::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (ShellSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ShellSound, GetActorLocation());
	}
	ShellMesh->SetNotifyRigidBodyCollision(false);
}

