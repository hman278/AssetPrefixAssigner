//  © 2021 hman278

#pragma once

#include "AssetProperties.generated.h"

USTRUCT()
struct FAssetProperties
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FName Class;

	UPROPERTY()
	FName Prefix;
};