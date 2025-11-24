// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EncounterParticipant.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEncounterParticipant : public UInterface
{
	GENERATED_BODY()
};

/**
 *  This is the interface an Encounter Runner will interact to coordinate the encounter.
 *  No direct class calls.
 */
class PROJECTHAILMARY_API IEncounterParticipant
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
