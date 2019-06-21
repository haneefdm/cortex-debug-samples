#include "cy_pdl.h"
#include "cycfg.h"

typedef struct
{
	bool en;
	uint32_t trig_cnt;
	uint32_t trig_cnt_tx;
	uint32_t trig_cnt_burst;
	uint32_t trig_cnt_subBurst;
	double rate;
	uint32_t triPeriod;
	uint32_t gptPeriod;
} trigger_set_t;

extern void myFunc(trigger_set_t *ptr);
