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

	//FindThe pawn that opens the door
	//ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	
}

void UOpenDoor::OpenDoor()
{
	//Set door rotation with Rotator built at runtime
	//Find the owner actor
	AActor* Owner = GetOwner();
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor(){
	//Set door rotation with Rotator built at runtime
	AActor* Owner = GetOwner();
	Owner->SetActorRotation(FRotator(0.0f, ClosedAngle, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll Trigger VOlume
	//If Actor on Trigger Volume OPen Door
	
	if (GetTotalMassOfActorsOnPlate() >= 40.0f){ //TODO Make a Parameter//
		OpenDoor();
		DoorLastOpenTime = GetWorld()->GetTimeSeconds();
	}
	if((GetWorld()->GetTimeSeconds() - DoorLastOpenTime) > DoorCloseDelay){
		CloseDoor();
	}

}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0;

	//Get total mass of each actor and add them together
	TArray <AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (auto* Actor : OverlappingActors) {
		
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass(); 
		UE_LOG(LogTemp, Warning, TEXT("%s is on Prssure plate"), *Actor->GetName());
	}

	

	return TotalMass;
}


