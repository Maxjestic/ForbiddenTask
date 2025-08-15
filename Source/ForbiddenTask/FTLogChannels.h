// Copyright Maxjestic

#pragma once

DECLARE_LOG_CATEGORY_EXTERN( LogFT, Log, All )


#define FT_LOG_INFO(Format, ...) UE_LOG(LogFT, Log, TEXT("[%s::%s:%d] " Format), *GetClass()->GetName(), *FString(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define FT_LOG_WARNING(Format, ...) UE_LOG(LogFT, Warning, TEXT("[%s::%s:%d] " Format), *GetClass()->GetName(), *FString(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#define FT_LOG_ERROR(Format, ...) UE_LOG(LogFT, Error, TEXT("[%s::%s:%d] " Format), *GetClass()->GetName(), *FString(__FUNCTION__), __LINE__, ##__VA_ARGS__)