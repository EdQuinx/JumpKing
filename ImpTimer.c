#include "ImpTimer.h"

ImpTimer ImpTimer_Create() {
	ImpTimer timer;

	timer.startTick = 0;
	timer.pauseTick = 0;
	timer.isPaused = false;
	timer.isStarted = false;

	timer.Start = ImpTimer_Start;
	timer.Stop = ImpTimer_Stop;
	timer.Paused = ImpTimer_Paused;
	timer.UnPaused = ImpTimer_UnPaused;

	timer.GetTicks = ImpTimer_GetTicks;

	timer.funcIsStarted = ImpTimer_funcIsStarted;
	timer.funcIsPaused = ImpTimer_funcIsPaused;

	return timer;
}

void ImpTimer_Destroy(ImpTimer* timer) {
	if (timer)
	{
		free(timer);
	}		
}

void ImpTimer_Start(ImpTimer* timer) {
	timer->isStarted = 1;
	timer->isPaused = 1;
	timer->startTick = SDL_GetTicks();
}

void ImpTimer_Stop(ImpTimer* timer) {
	timer->isPaused = 0;
	timer->isStarted = 0;
}

void ImpTimer_Paused(ImpTimer* timer) {
	if (timer->isStarted && !timer->isPaused) {
		timer->isPaused = 1;
		timer->pauseTick = SDL_GetTicks() - timer->startTick;
	}
}

void ImpTimer_UnPaused(ImpTimer* timer) {
	if (timer->isPaused) {
		timer->isPaused = 0;
		timer->startTick = SDL_GetTicks() - timer->pauseTick;
		timer->pauseTick = 0;
	}
}

int ImpTimer_GetTicks(ImpTimer* timer) {
	if (timer->isStarted) {
		if (timer->isPaused) {
			return timer->pauseTick;
		}
		else {
			return SDL_GetTicks() - timer->startTick;
		}
	}
	return 0;
}

bool ImpTimer_funcIsStarted(ImpTimer* timer) {
	return timer->isStarted;
}

bool ImpTimer_funcIsPaused(ImpTimer* timer) {
	return timer->isPaused;
}