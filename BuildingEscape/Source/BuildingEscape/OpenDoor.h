// (c)2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	AActor* Owner;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



private:
	//UPROPERTYs show things in the Details Inspector and Create Variables to be used on the object
	UPROPERTY(EditAnywhere)
		float OpenAngle = 0.0f;
	UPROPERTY(EditAnywhere)
		float ClosedAngle = 90.0f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.0f;
	UPROPERTY(VisibleAnywhere)
		float DoorLastOpenTime;
	float GetTotalMassOfActorsOnPlate();
};
