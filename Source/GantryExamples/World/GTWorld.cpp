// Copyright Private Asylum LLC, 2026, All Rights Reserved.

#include "World/GTWorld.h"

#include "GameFramework/GameMode.h"

namespace GTWorld
{
	EGTMatchPhase MatchStateToPhase(FName MatchState)
	{
		if (MatchState == MatchState::EnteringMap)			{ return EGTMatchPhase::EnteringMap; }
		if (MatchState == MatchState::WaitingToStart)		{ return EGTMatchPhase::WaitingToStart; }
		if (MatchState == MatchState::InProgress)			{ return EGTMatchPhase::InProgress; }
		if (MatchState == MatchState::WaitingPostMatch)		{ return EGTMatchPhase::WaitingPostMatch; }
		if (MatchState == MatchState::LeavingMap)			{ return EGTMatchPhase::LeavingMap; }
		if (MatchState == MatchState::Aborted)				{ return EGTMatchPhase::Aborted; }

		return EGTMatchPhase::Unknown;
	}

	FName PhaseToMatchState(EGTMatchPhase Phase)
	{
		switch (Phase)
		{
		case EGTMatchPhase::EnteringMap:		return MatchState::EnteringMap;
		case EGTMatchPhase::WaitingToStart:		return MatchState::WaitingToStart;
		case EGTMatchPhase::InProgress:			return MatchState::InProgress;
		case EGTMatchPhase::WaitingPostMatch:	return MatchState::WaitingPostMatch;
		case EGTMatchPhase::LeavingMap:			return MatchState::LeavingMap;
		case EGTMatchPhase::Aborted:			return MatchState::Aborted;
		default:								return NAME_None;
		}
	}
}
