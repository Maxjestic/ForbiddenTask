// Copyright Maxjestic

#include "DataAssets/FTSpawnConfigDataAsset.h"

#if WITH_EDITOR
void UFTSpawnConfigDataAsset::PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent )
{
	Super::PostEditChangeProperty( PropertyChangedEvent );

	for ( FFTSpawnZoneInfo& Zone : SpawnZones )
	{
		if ( Zone.StrengthRange.Max < Zone.StrengthRange.Min )
		{
			Zone.StrengthRange.Max = Zone.StrengthRange.Min;
		}

		if ( Zone.SpeedRange.Max < Zone.SpeedRange.Min )
		{
			Zone.SpeedRange.Max = Zone.SpeedRange.Min;
		}
	}
}
#endif // WITH_EDITOR
