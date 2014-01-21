#include "ArcCore.h"

#include "RandomFunctions.h"
#include "MemoryTracker.h"

bool Arc_InitCore( void )
{
	bool success = false;

	Arc::Arc_InitRandom();
	success = Arc::Arc_InitMemoryTracker();

	if ( ! success)
		goto error;


error:

	return false;

}