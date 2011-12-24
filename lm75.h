#include <linux/hwmon.h>

/* straight from the datasheet */
#define LM75_TEMP_MIN (-55000)
#define LM75_TEMP_MAX 125000
#define LM75_SHUTDOWN 0x01

/* TEMP: 0.001C/bit (-55C to +125C)
   REG: (0.5C/bit, two's complement) << 7 */
static inline u16 LM75_TEMP_TO_REG(long temp)
{
        int ntemp = SENSORS_LIMIT(temp, LM75_TEMP_MIN, LM75_TEMP_MAX);
        ntemp += (ntemp<0 ? -250 : 250);
        return (u16)((ntemp / 500) << 7);
}

static inline int LM75_TEMP_FROM_REG(u16 reg)
{
        /* use integer division instead of equivalent right shift to
           guarantee arithmetic shift and preserve the sign */
        return ((s16)reg / 128) * 500;
}

