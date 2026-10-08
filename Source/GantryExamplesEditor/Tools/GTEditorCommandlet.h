// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Commandlets/Commandlet.h"

#include "GTEditorCommandlet.generated.h"

/**
 * Headless project audit, for CI and for anyone who does not want to open the editor.
 *
 * Run with:
 *   UnrealEditor-Cmd <Project>.uproject -run=GTEditor -path=/Game
 *
 * Exit code is zero when clean and non-zero when violations were found, so a build server can
 * gate on it directly.
 */
UCLASS()
class UGTEditorCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:

	UGTEditorCommandlet();

	/* UCommandlet interface. */
	virtual int32 Main(const FString& Params) override;
	/* UCommandlet interface. */
};
