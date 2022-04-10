/*
 * Sounds.c
 *
 *  Created on: 24-Jun-2019
 */
#include "Sounds.h"
#include "derivative.h"

void sounds_frecuency(unsigned int fr)
{
	TPM1C1V = fr;
	sounds_play();
}

void sounds_play()
{
	TPM1C1SC = 0x54u;
}

void sounds_stop()
{
    TPM1C1SC = 0;
}



