/*
 * ds18b20_definitions.h
 *
 *  Created on: 25 sep. 2022
 *      Author: IOFamilia
 */

#ifndef INC_DS18B20_DEFINITIONS_H_
#define INC_DS18B20_DEFINITIONS_H_

#define ROM_CMD_SEARCH_ROM		0xF0
#define ROM_CMD_READ_ROM		0x33
#define ROM_CMD_MATCH_ROM		0x55
#define ROM_CMD_SKIP_ROM		0xCC
#define ROM_CMD_ALARM_SEARCH	0xEC

#define CMD_CONVERT_T			0x44
#define CMD_WRITE_SCRATCHPAD	0x4E
#define CMD_READ_SCRATCHPAD		0xBE
#define CMD_COPY_SCRATCHPAD		0x48
#define CMD_RECALL_E2			0xB8
#define CMD_READ_POWER_SUPPLY	0xB4

#endif /* INC_DS18B20_DEFINITIONS_H_ */
