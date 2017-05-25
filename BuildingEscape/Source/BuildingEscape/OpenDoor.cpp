// (c)2017

#include "BuildingEscape.h"
#include "OpenDoor.h"


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

	//Find the owner actor
	/*AActor* Owner = GetOwner();*/
	//FindThe pawn that opens the door
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	
}

void UOpenDoor::OpenDoor()
{
	//Set door rotation with Rotator built at runtime
	//Find the owner actor
	AActor* Owner = GetOwner();

	FRotator NewRotator = FRotator(0.0f, 0.0f, 0.0f);

	Owner->SetActorRotation(NewRotator);
}

void UOpenDoor::CloseDoor(){
	//Set door rotation with Rotator built at runtime
	AActor* Owner = GetOwner();

	FRotator NewRotator = FRotator(0.0f, 90.0f, 0.0f);

	Owner->SetActorRotation(NewRotator);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll Trigger VOlume
	//If Actor on Trigger Volume OPen Door
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		//LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
}


