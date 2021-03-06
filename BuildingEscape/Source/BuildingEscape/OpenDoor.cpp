// (c)2017

#include "BuildingEscape.h"
#include "OpenDoor.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("%s misssing Pressure Plate"), *GetOwner()->GetName());
	}

	
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll Trigger VOlume
	//If Actor on Trigger Volume OPen Door
	
	if (GetTotalMassOfActorsOnPlate() >= TriggerMass){ //TODO Make a Parameter//
		OnOpen.Broadcast();
	}
	else {
		OnClose.Broadcast();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0;

	//Get total mass of each actor and add them together
	TArray <AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (auto* Actor : OverlappingActors) {
		
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass(); 
		UE_LOG(LogTemp, Warning, TEXT("%s is on Prssure plate"), *Actor->GetName());
	}

	

	return TotalMass;
}


