#include "OnlineCTR/updatetimes.c"
#ifdef USE_ONLINE
#include "OnlineCTR/global.h"
unsigned int checkpointTimes[(MAX_LAPS * CPS_PER_LAP) + 1];
#endif


extern void AssignMeterGrade(struct Driver * driver, int meterLeft);

extern const int gradeTreshold[];
extern const int gradeColors[];
#ifndef REBUILD_PC
#ifdef USE_ONLINE

void AssignMeterGrade(struct Driver * driver, int meterLeft)
{
	const int gradeTreshold[] = {SECONDS(1) * FP(0.50), SECONDS(1) * FP(0.65),
						SECONDS(1) * FP(0.80), SECONDS(1) * FP(0.90),
						SECONDS(1) * FP(0.95)};
	const int gradeColors[] = {CORTEX_RED, ROO_ORANGE, CRASH_BLUE, TROPY_LIGHT_BLUE, PAPU_YELLOW};

	driver->meterGradeTimer = SECONDS(0.5);
	driver->meterGrade[1] = '\0';

	char grades[] = "FDCBA";
	for (int i = 0; i < len(gradeTreshold); i++)
	{
		if (meterLeft > SECONDS(1) - FP_INT(gradeTreshold[i]))
		{
			driver->meterGrade[0] = grades[i];
			driver->gradeColor = gradeColors[i];
			return;
		}
	}
	driver->meterGrade[0] = 'S';
	driver->gradeColor = SILVER;
}
#endif
#endif

#ifdef USE_ONLINE
void FixReservesIncrement(struct Driver * driver, int reserves)
{
	if (driver->reserves > 30000) { driver->uncappedReserves += reserves; }
	else { driver->reserves += reserves; }
}
#endif



#ifdef USE_OXIDE
void Oxide_HookAppendLoadingQueue()
{
	int loop;
	struct LoadQueueSlot* lqs_next;
	struct LoadQueueSlot* lqs_curr;
	int packIndex = DECOMP_LOAD_GetAdvPackIndex();

	// set pointers
	lqs_curr = &sdata->queueSlots[sdata->queueLength-1];
	lqs_next = &lqs_curr[1];

	// only continue if you tried to load oxide in 1st place
	if(sdata->gGT->podium_modelIndex_First != 0x8D) return;

	// quit if not this condition
	if(lqs_curr->callback.funcPtr != DECOMP_LOAD_Callback_Podiums) return;

	// if most recent addition to the queue, is the last append for podiums

	// shift the request
	for(loop = 0; loop < 0x18/4; loop++)
	{
		// shift down one
		*(int*)((int*)lqs_next + loop) =
		*(int*)((int*)lqs_curr + loop);
	}

	// add oxide request
	lqs_curr->subfileIndex = packIndex + 0xf*2 + 0x18D;
	lqs_curr->ptrDestination = (void*)&data.podiumModel_firstPlace;
	lqs_curr->callback.flags = 0xfffffffe;

	// increase size
	sdata->queueLength++;
}
#endif