#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StairsBuilderActor.generated.h"

class USplineComponent;

UCLASS()
class STAIRSBUILDER_API AStairsBuilderActor : public AActor
{
	GENERATED_BODY()

public:
	AStairsBuilderActor();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Stairs Builder")
	void Regenerate();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stairs Builder|Steps")
	float StepHeightCm = 16.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stairs Builder|Steps")
	float StepDepthCm = 28.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stairs Builder|Steps")
	float StairWidthCm = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stairs Builder|Railings", meta = (EditCondition = "true"))
	bool bRailingsEnabled = true;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stairs Builder", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USplineComponent> SplineComponent;
};
