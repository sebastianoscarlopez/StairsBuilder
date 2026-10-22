#include "StairsBuilderActor.h"
#include "Components/SplineComponent.h"

AStairsBuilderActor::AStairsBuilderActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;
}

void AStairsBuilderActor::Regenerate()
{
}
