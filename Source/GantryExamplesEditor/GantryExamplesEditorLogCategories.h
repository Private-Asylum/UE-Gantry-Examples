// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Logging/LogMacros.h"

/**
 * Editor-only log channels.
 *
 * Separate from the runtime module's channels so editor tooling noise can be silenced without
 * touching gameplay logging, and so nothing here accidentally ships.
 */
DECLARE_LOG_CATEGORY_EXTERN(LogGantryExamplesEditor, Log, All);

/** Asset and level validation. */
DECLARE_LOG_CATEGORY_EXTERN(LogGTEditorValidation, Log, All);

/** Editor utilities and commandlets. */
DECLARE_LOG_CATEGORY_EXTERN(LogGTEditorTools, Log, All);
