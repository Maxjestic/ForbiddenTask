// Copyright Maxjestic

#include "Core/FTGameInstance.h"

#include "Blueprint/UserWidget.h"

void UFTGameInstance::Init()
{
	Super::Init();

	ensureMsgf(MainMenuWidgetClass, TEXT("MainMenuWidgetClass is not set in BP_GameInstance!"));
	ensureMsgf(HUDWidgetClass, TEXT("HUDWidgetClass is not set in BP_GameInstance!"));
	ensureMsgf(PauseMenuWidgetClass, TEXT("PauseMenuWidgetClass is not set in BP_GameInstance!"));
	ensureMsgf(EndScreenWidgetClass, TEXT("EndScreenWidgetClass is not set in BP_GameInstance!"));

#if !UE_BUILD_SHIPPING
	ensureMsgf(CheatMenuWidgetClass, TEXT("CheatMenuWidgetClass is not set in BP_GameInstance!"));
#endif // !UE_BUILD_SHIPPING
}
