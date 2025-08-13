// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/SpawnConfigDataAsset.h"

#if WITH_EDITOR
void USpawnConfigDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	for (FSpawnZoneInfo& Zone : SpawnZones)
	{
		if (Zone.StrengthRange.Max < Zone.StrengthRange.Min)
		{
			Zone.StrengthRange.Max = Zone.StrengthRange.Min;
		}
		
		if (Zone.SpeedRange.Max < Zone.SpeedRange.Min)
		{
			Zone.SpeedRange.Max = Zone.SpeedRange.Min;
		}
	}
}
#endif // WITH_EDITOR