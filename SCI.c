/*
 * SCI.c
 *
 *  Created on: 11-Jun-2019
 */
#include "derivative.h"
#include "SCI.h"

volatile char FLAG_RX = 0,
              FLAG_RX_respuesta = 0;

static char bufferRX[RX_BUFFER_LENGTH],
            bufferTX[TX_BUFFER_LENGTH];

static unsigned char indiceLecturaTX = 0,
                     indiceEscrituraTX = 0,
                     indiceLecturaRX = 0,
                     indiceEscrituraRX = 0;

static char hz100[] = {'1','0','0'},
            hz300[] = {'3','0','0'},
            hz500[] = {'5','0','0'},
            hz1k[] = {'1','K'},
            hz2k[] = {'2','K'},
            hz5k[] = {'5','K'},
            hz10k[] = {'1','0','K'},
            hz12k[] = {'1','2','K'},
            on[] = {'O','N'},
            off[] = {'O','F'},
            reset[] = {'R','E'};
            

void SCI_init ()
{
	SCI_writeStringToBuffer("AT+NAMEG1\r\n");
	while (!FLAG_RX_respuesta)
    {
		SCI_update();
    }
}

void SCI_update()
{
    char dato;
	if (indiceEscrituraTX > indiceLecturaTX) 
    {
		SCIC2_TIE = 1;
        SCI_sendChar(bufferTX[indiceLecturaTX]);
        indiceLecturaTX++;
	} 
    else 
    {
        SCIC2_TIE = 0;
		indiceEscrituraTX = 0;
		indiceLecturaTX = 0;
	}
	if (SCI_reciveData (&dato) != 0) 
    {
        if(indiceEscrituraRX < RX_BUFFER_LENGTH)
        {
            bufferRX[indiceEscrituraRX] = dato;
            indiceEscrituraRX++;
            FLAG_RX_respuesta = 1;
        }
	}
}

void SCI_writeCharToBuffer(char dato) 
{
    if (indiceEscrituraTX < TX_BUFFER_LENGTH)
    {
        bufferTX[indiceEscrituraTX] = dato;
        indiceEscrituraTX++;
    }   
}

void SCI_writeStringToBuffer(char datos[])
{
    char i = 0;
    while(datos[i] != '\0')
    {
        SCI_writeCharToBuffer(datos[i]);
        i++;
    }
}

char SCI_getCharFromBuffer (char *character)
{
    if (indiceLecturaRX < indiceEscrituraRX)
    {
        *character = bufferRX[indiceLecturaRX];
        indiceLecturaRX++;
        return 1;
    }
    else
    {
        indiceEscrituraRX = 0;
        indiceLecturaRX = 0;
        return 0;
    }
}

void SCI_sendChar(char dato)
{
    while (SCIS1_TDRE == 0);
    if (indiceEscrituraTX > indiceLecturaTX)
    {
        SCID = dato;
    }
}

char SCI_reciveData(char *dato)
{
    if(SCIS1_RDRF == 1)
    {
        *dato = SCID;
        return 1;
    }
    else
    {
        return 0;
    }  
}
char SCI_getCommand(char *command)
{
	unsigned char i;
	char result;
	if (indiceEscrituraRX < 1)
	{
		return 0;
	}
	for(i = 0; i < indiceEscrituraRX; i++)
	{
		if (hz1k[i] == bufferRX[i])
		{
			result = 'D';
			if (i == indiceEscrituraRX)
			{
				*command = result;
                indiceEscrituraRX = 0;              
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < indiceEscrituraRX; i++)
	{
		if (hz2k[i] == bufferRX[i])
		{
			result = 'E';
			if (i == indiceEscrituraRX)
			{
				*command = result;
                indiceEscrituraRX = 0;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < indiceEscrituraRX; i++)
	{
		if (hz5k[i] == bufferRX[i])
		{
			result = 'F';
			if (i == indiceEscrituraRX)
			{
				*command = result;
                indiceEscrituraRX = 0;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < indiceEscrituraRX; i++)
	{
		if (on[i] == bufferRX[i])
		{
			result = 'I';
			if (i == indiceEscrituraRX)
			{
				*command = result;
                indiceEscrituraRX = 0;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < indiceEscrituraRX; i++)
	{
		if (off[i] == bufferRX[i])
		{
			result = 'J';
			if (i == indiceEscrituraRX)
			{
				*command = result;
                indiceEscrituraRX = 0;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < indiceEscrituraRX; i++)
	{
		if (reset[i] == bufferRX[i])
		{
			result = 'K';
			if (i == indiceEscrituraRX)
			{
				*command = result;
                indiceEscrituraRX = 0; 
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}

	for(i = 0; i < indiceEscrituraRX; i++)
	{
		if (hz100[i] == bufferRX[i])
		{
			result = 'A';
			if (i == indiceEscrituraRX)
			{
				*command = result;
                indiceEscrituraRX = 0;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < indiceEscrituraRX; i++)
	{
		if (hz300[i] == bufferRX[i])
		{
			result = 'B';
			if (i == indiceEscrituraRX)
			{
				*command = result;
                indiceEscrituraRX = 0;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < indiceEscrituraRX; i++)
	{
		if (hz500[i] == bufferRX[i])
		{
			result = 'C';
			if (i == indiceEscrituraRX)
			{
				*command = result;
                indiceEscrituraRX = 0;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < indiceEscrituraRX; i++)
	{
		if (hz10k[i] == bufferRX[i])
		{
			result = 'G';
			if (i == indiceEscrituraRX)
			{
				*command = result;
                indiceEscrituraRX = 0;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
	for(i = 0; i < indiceEscrituraRX; i++)
	{
		if (hz12k[i] == bufferRX[i])
		{
			result = 'H';
			if (i == indiceEscrituraRX)
			{
				*command = result;
                indiceEscrituraRX = 0;
				return 1;
			}
		}
		else
		{
			result = 'X';
			break;
		}
	}
    indiceEscrituraRX = 0;
	*command = result;
	return 0;
}
