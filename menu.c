/*
 * menu.c
 *
 *  Created on: 24-Jun-2019
 */
#include "sci.h"

void menu_showMenu(void)
{
    SCI_writeStringToBuffer("Menu:\n");
    SCI_writeStringToBuffer("100Hz(100) 300Hz(300) 500Hz(500) 1KHz(1K) 2KHz(2K)\n");
	SCI_writeStringToBuffer("5KHz(5K) 10KHz(10K) 12KHz(12K)\n");
    SCI_writeStringToBuffer("'reset' - reset.\n");
	SCI_writeStringToBuffer("'on' - sonido on.\n");
	SCI_writeStringToBuffer("'off' - sonido off.\n");
}

