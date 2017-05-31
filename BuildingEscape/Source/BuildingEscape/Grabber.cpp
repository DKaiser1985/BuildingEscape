// (c)2017

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();

	SetupInputComponent();
}

///Look for attched Physics Handle created at runtime
void UGrabber::FindPhysicsHandleComponent() {

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandler Found on %s."), *GetOwner()->GetName());
	}
}

///Find the InputComponent created at runtime
void UGrabber::SetupInputComponent(){

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found on %s."), *GetOwner()->GetName());

		///Bind the Grab Input Action
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if the Physics Handle is attached
	if (PhysicsHandle->GrabbedComponent) {
		//Move Object we're holding
		PhysicsHandle->SetTargetLocation(EndOfReach());
	}
		

}

//Return Hit for first Physics Body in Reach
const FHitResult UGrabber::GetFirstPhysicsBodyInReach(){

	///get the player Viewpoint
	FVector  PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation

	);

	///Draw Debug Line to visualize grabber
	OUT FHitResult Hit;
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	DrawDebugLine(
		GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0, 10.0f);
	///Setup Query Params
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	///Raycast out to reach distance
	GetWorld()->LineTraceSingleByObjectType(
		Hit, PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters);


	///see what we "hit"
	if (Hit.GetActor()) {
		UE_LOG(LogTemp, Warning, TEXT("Hit Object: %s"), *Hit.GetActor()->GetName());
	}
	return Hit;
}

FVector UGrabber::EndOfReach() {
	///get the player Viewpoint
	FVector  PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation

	);

	///Draw Debug Line to visualize grabber
	OUT FHitResult Hit;
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	return (LineTraceEnd);
}

//Pickup the first The PhysicsBody in reach
void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));

	///LineTrace and Try and reach any actors with PhysicsBody collision channel set
	
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	
	//Create blank Rotator so object doesn't rotate
	FRotator Rotator = FRotator();
	
	//Attach Physics Handle
	if (ActorHit) {
		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, 
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			Rotator);
	}
}

//Release Grabbed Physics Body
void UGrabber::Release() {
	//TODO Released Physics Handle
	PhysicsHandle->ReleaseComponent();
	UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
}


