#include "ArcNet.h"

#include <Arc/Log.h>

#if defined(ARC_OS_WINDOWS)

// Prevent conflict with namespace Arc and Arc()
#define NOGDI

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#endif

bool Arc::Arc_InitNet( void )
{
#if defined(ARC_OS_WINDOWS)

	int res = 0;
	WSAData wsa;

	res = WSAStartup(MAKEWORD(2,2), &wsa);
	if (res != 0)
	{
		Log::ErrorFmt("Arc_InitNet", "WSAStartup failed with error code: %d", res);
		return false;
	}
#endif 

	return true;
}

void Arc::Arc_TermNet( void )
{
#if defined(ARC_OS_WINDOWS)

	WSACleanup();

#endif 
}
