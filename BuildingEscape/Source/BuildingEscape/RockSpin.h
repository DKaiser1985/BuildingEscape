// (c)2017

#pragma once

#include "Components/ActorComponent.h"
#include "RockSpin.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API URockSpin : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URockSpin();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
