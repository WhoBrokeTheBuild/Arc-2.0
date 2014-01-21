#include "MemoryTracker.h"

Arc::MemoryTracker* gp_MemoryTracker = nullptr;

bool Arc_InitMemoryTracker( void )
{
	if (gp_MemoryTracker == nullptr)
	{
		gp_MemoryTracker = new Arc::MemoryTracker();
		return true;
	}

	return false;
}

void Arc_CleanupMemoryTracker( void )
{
	delete gp_MemoryTracker;
}