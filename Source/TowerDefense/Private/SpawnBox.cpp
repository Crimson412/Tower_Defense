// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBox.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "Spider.h"

// Sets default values
ASpawnBox::ASpawnBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASpawnBox::OnStartRound()
{
	UWorld* const World = GetWorld();
	round++;
	TArray<APawn*> pawn;
	GEngine->AddOnScreenDebugMessage(0, 30.0f, FColor::Cyan, FString::Printf(TEXT("Round Started, Round: %d"), round));
	//UGameplayStatics::GetAllActorsOfClass(World, Spider::Class(), pawn);

	const FVector SpawnLocation = GetActorLocation();
	const FRotator SpawnRotation = GetActorRotation();

	//World->SpawnActor<APawn>(pawn, SpawnLocation, SpawnRotation);
}