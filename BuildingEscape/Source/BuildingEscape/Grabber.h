// (c)2017

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	//Arms Reach in cm
	float Reach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	 
	//Raycast and Grab whats in reach
	void Grab();

	//Release What is Grabbed
	void Release();

	void FindPhysicsHandleComponent();
	
	void SetupInputComponent();

	//Return Hit for first Physics Body in Reach
	const FHitResult GetFirstPhysicsBodyInReach();

	//Returns the End of Reach
	FVector GetStartOfReach();

	//Returns the End of Reach
	FVector GetEndOfReach();	
};
