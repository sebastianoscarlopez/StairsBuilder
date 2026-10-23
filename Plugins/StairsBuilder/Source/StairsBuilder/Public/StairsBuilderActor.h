#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StairsBuilderActor.generated.h"

class USplineComponent;
class UDynamicMeshComponent;

UCLASS()
class STAIRSBUILDER_API AStairsBuilderActor : public AActor
{
	GENERATED_BODY()

public:
	AStairsBuilderActor();

	/** Rebuilds the stairs from the spline and the step settings below. */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Stairs Builder")
	void Regenerate();

	UFUNCTION(BlueprintPure, Category = "Stairs Builder")
	USplineComponent* GetSplineComponent() const { return SplineComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stairs Builder|Steps")
	float StepHeightCm = 16.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stairs Builder|Steps")
	float StepDepthCm = 28.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stairs Builder|Steps")
	float StairWidthCm = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stairs Builder|Railings")
	bool bRailingsEnabled = true;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stairs Builder", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stairs Builder", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDynamicMeshComponent> StairMesh;
};
