/*
 * SCI.h
 *
 *  Created on: 24-Jun-2019
 */

#ifndef _SCI_H
#define _SCI_H 1
#define TX_BUFFER_LENGTH 167
#define RX_BUFFER_LENGTH 30

void SCI_init(void);
void SCI_update (void);
void SCI_writeCharToBuffer(char dato);
void SCI_writeStringToBuffer(char datos[]);
char SCI_getCharFromBuffer (char *character);
void SCI_sendChar (char dato);
char SCI_reciveData(char *dato);
char SCI_getCommand(char *command);
#endif /* SCI_H_ */
