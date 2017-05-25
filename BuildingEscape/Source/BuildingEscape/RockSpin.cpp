// (c)2017

#include "BuildingEscape.h"
#include "RockSpin.h"


float Roll = 0.0f;

// Sets default values for this component's properties
URockSpin::URockSpin()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URockSpin::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URockSpin::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Roll = Roll + 0.5f;

	//Find the owner
	AActor* Rock = GetOwner();

	//Create Rotator
	FRotator RockSpinner = FRotator(Roll, 0.0f, 90.0f);

	//Spin on Update
	Rock->SetActorRotation(RockSpinner);
}

