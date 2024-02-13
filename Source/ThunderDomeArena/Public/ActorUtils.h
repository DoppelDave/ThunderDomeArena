#pragma once

#include "CoreMinimal.h"

template <typename T>
T* FindObject(const FString a_sObjPath)
{
	return ConstructorHelpers::FObjectFinder<T>(*a_sObjPath).Object;
}