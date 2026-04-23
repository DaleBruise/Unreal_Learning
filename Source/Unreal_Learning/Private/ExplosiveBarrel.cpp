// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->_mesh_comp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	this->_mesh_comp->SetSimulatePhysics(true);
	SetRootComponent(this->_mesh_comp);

	this->_force_comp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	this->_force_comp->SetupAttachment(this->_mesh_comp);
	this->_force_comp->SetAutoActivate(false);
	this->_force_comp->Radius = 750.f;
	this->_force_comp->ImpulseStrength = 2500.f;
	this->_force_comp->bImpulseVelChange = true;
	this->_force_comp->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	this->_mesh_comp->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnActorHit);
}

void AExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, const FHitResult& Hit)
{
	this->_force_comp->FireImpulse();
	
	UE_LOG(LogTemp, Log, 
		TEXT("OnActorHit in Explosive Barrel"));
	
	UE_LOG(LogTemp, Warning, 
		TEXT("OtherActor: %s, at game time: %f"), 
		*GetNameSafe(OtherActor),
		GetWorld()->TimeSeconds);
	
	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), 
		*Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), 
		Hit.ImpactPoint, 
		CombinedString, 
		nullptr, 
		FColor::Green, 
		2.0f, 
		true);
}
