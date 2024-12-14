#include <common.h>
#include "global.h"


void ElapsedTimeToTotalTime(TotalTime * totalTime, int elapsedTime)
{
	totalTime->hours = elapsedTime / HOURS(1);
	elapsedTime -= HOURS(1) * totalTime->hours;
	totalTime->minutes = elapsedTime / MINUTES(1);
	elapsedTime -= MINUTES(1) * totalTime->minutes;
	totalTime->seconds = elapsedTime / SECONDS(1);
	elapsedTime -= SECONDS(1) * totalTime->seconds;
	totalTime->miliseconds = (elapsedTime * 1000) / SECONDS(1);
}