#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_
#include "CommonFunction.h"

typedef struct sImpTimer ImpTimer;
struct sImpTimer 
{
	int startTick;
	int pauseTick;
	bool isPaused;
	bool isStarted;

	void (*Start)(ImpTimer*);
	void (*Stop)(ImpTimer*);
	void (*Paused)(ImpTimer*);
	void (*UnPaused)(ImpTimer*);

	int (*GetTicks)(ImpTimer*);

	bool (*funcIsStarted)(ImpTimer*);
	bool (*funcIsPaused)(ImpTimer*);

};

ImpTimer ImpTimer_Create();
void ImpTimer_Destroy(ImpTimer* timer);

void ImpTimer_Start(ImpTimer* timer);
void ImpTimer_Stop(ImpTimer* timer);
void ImpTimer_Paused(ImpTimer* timer);
void ImpTimer_UnPaused(ImpTimer* timer);
int ImpTimer_GetTicks(ImpTimer* timer);

bool ImpTimer_funcIsStarted(ImpTimer* timer);
bool ImpTimer_funcIsPaused(ImpTimer* timer);

#endif