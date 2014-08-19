/*
 * profiler.S
 *
 *  Created on: 15.8.2014
 *      Author: peterj
 */

    .syntax unified
    .arch armv7-m

.globl __gnu_mcount_nc
        .type __gnu_mcount_nc, %function
__gnu_mcount_nc:
        mov    ip, lr
        pop    { lr }
        bx     ip
