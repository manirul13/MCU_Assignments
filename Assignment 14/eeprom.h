/* 
 * File:   eeprom.h
 * Author: MANIRUL
 *
 * Created on 14 June, 2025, 10:03 AM
 */

#ifndef EEPROM_H
#define	EEPROM_H

unsigned char eeprom_read(unsigned char address);
void eeprom_write(unsigned char address, unsigned char data);

#endif	/* EEPROM_H */

