// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#pragma once

#include "Logging/LogMacros.h"

/**
 * Project-wide log channels.
 *
 * One channel per top level category so verbosity can be tuned per subsystem from the console
 * or DefaultEngine.ini, e.g. `Log LogGTWorld Verbose`.
 */

/** Catch-all channel for module lifetime and anything that has no better home. */
DECLARE_LOG_CATEGORY_EXTERN(LogGantryExamples, Log, All);

/** Engine, game instance, asset manager and settings. */
DECLARE_LOG_CATEGORY_EXTERN(LogGTCore, Log, All);

/** Game mode, game state, world settings and world subsystems. */
DECLARE_LOG_CATEGORY_EXTERN(LogGTWorld, Log, All);

/** Player controller, local player, player state and camera. */
DECLARE_LOG_CATEGORY_EXTERN(LogGTPlayer, Log, All);

/** Pawns, characters and movement. */
DECLARE_LOG_CATEGORY_EXTERN(LogGTPawn, Log, All);

/** Enhanced Input mapping and binding. */
DECLARE_LOG_CATEGORY_EXTERN(LogGTInput, Log, All);

/** HUD and widget layers. */
DECLARE_LOG_CATEGORY_EXTERN(LogGTUI, Log, All);

/** AI controllers and perception. */
DECLARE_LOG_CATEGORY_EXTERN(LogGTAI, Log, All);

/** Networking, sessions and replication. */
DECLARE_LOG_CATEGORY_EXTERN(LogGTNet, Log, All);

/** Save games and persistence. */
DECLARE_LOG_CATEGORY_EXTERN(LogGTSave, Log, All);
