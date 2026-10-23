#include "StairsBuilderActor.h"
#include "Components/SplineComponent.h"
#include "Components/DynamicMeshComponent.h"
#include "UDynamicMesh.h"
#include "GeometryScript/MeshPrimitiveFunctions.h"

DEFINE_LOG_CATEGORY_STATIC(LogStairsBuilder, Log, All);

AStairsBuilderActor::AStairsBuilderActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;

	StairMesh = CreateDefaultSubobject<UDynamicMeshComponent>(TEXT("StairMesh"));
	StairMesh->SetupAttachment(RootComponent);
}

void AStairsBuilderActor::Regenerate()
{
	UDynamicMesh* Mesh = StairMesh ? StairMesh->GetDynamicMesh() : nullptr;
	if (!SplineComponent || !Mesh)
	{
		return;
	}

	Mesh->Reset();

	const float SplineLength = SplineComponent->GetSplineLength();
	if (SplineLength <= KINDA_SMALL_NUMBER)
	{
		UE_LOG(LogStairsBuilder, Warning, TEXT("Spline has no length, nothing generated."));
		StairMesh->NotifyMeshUpdated();
		return;
	}

	if (StepHeightCm <= 0.f || StepDepthCm <= 0.f || StairWidthCm <= 0.f)
	{
		UE_LOG(LogStairsBuilder, Warning, TEXT("Step height, depth and width must be greater than zero."));
		StairMesh->NotifyMeshUpdated();
		return;
	}

	// Step 1 (spike): the spline is treated as flat. Stairs start at the spline's start height.
	const double BaseZ = SplineComponent->GetLocationAtDistanceAlongSpline(0.f, ESplineCoordinateSpace::Local).Z;
	const int32 NumSteps = FMath::Max(1, FMath::FloorToInt(SplineLength / StepDepthCm));

	FGeometryScriptPrimitiveOptions Options;
	for (int32 i = 0; i < NumSteps; ++i)
	{
		const float MidDistance = FMath::Min((i + 0.5f) * StepDepthCm, SplineLength);
		const FVector Center = SplineComponent->GetLocationAtDistanceAlongSpline(MidDistance, ESplineCoordinateSpace::Local);
		const FVector Tangent = SplineComponent->GetTangentAtDistanceAlongSpline(MidDistance, ESplineCoordinateSpace::Local);
		const double YawDegrees = FMath::RadiansToDegrees(FMath::Atan2(Tangent.Y, Tangent.X));

		// Each step is a solid block from the base up to its tread height.
		const float TopHeight = (i + 1) * StepHeightCm;
		const FTransform StepTransform(FRotator(0.0, YawDegrees, 0.0), FVector(Center.X, Center.Y, BaseZ));

		UGeometryScriptLibrary_MeshPrimitiveFunctions::AppendBox(
			Mesh, Options, StepTransform,
			StepDepthCm, StairWidthCm, TopHeight,
			0, 0, 0,
			EGeometryScriptPrimitiveOriginMode::Base, nullptr);
	}

	StairMesh->NotifyMeshUpdated();
}
