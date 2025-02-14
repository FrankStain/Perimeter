
/* ---------------------------- INCLUDE SECTION ----------------------------- */

#include <cstring>
#include <cstdint>
#include <string>

#include "tweaks.h"
#include "xmath.h"
#include "xutl.h"
#include <SDL.h>

int64_t tick_per_sec=0;
int64_t beg_tick=0;

#if defined(_MSC_VER) && _MSC_VER >= 1310
__declspec (noinline)
#endif // _MSC_VER >= 1310

int64_t getRDTSC() {
    return static_cast<int64_t>(SDL_GetPerformanceCounter());
}

void initclock()
{
	if(tick_per_sec!=0)
		return;
	/*
	timeBeginPeriod(1);

	unsigned int t2=timeGetTime(), t1 = t2;

	while(t1==t2){ 
		t2=timeGetTime();
	};

    int64_t tickb=getRDTSC();
	t1=t2;
	while(t1+MS_PER_PERIOD > t2){
		t2=timeGetTime();
	}
    int64_t ticke=getRDTSC();
	tick_per_sec = (ticke-tickb)/MS_PER_PERIOD;
	beg_tick=getRDTSC();
	*/

	tick_per_sec = static_cast<int64_t>(SDL_GetPerformanceFrequency() / 1000);
    beg_tick=getRDTSC();

	//timeEndPeriod(1);
}

double clockf()
{
	return (double)(getRDTSC() - beg_tick) / (double)tick_per_sec;
} 

int clocki()
{
	return (int)((getRDTSC() - beg_tick) / tick_per_sec);
}

