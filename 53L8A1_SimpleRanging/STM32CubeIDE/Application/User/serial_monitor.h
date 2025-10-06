/*
 * serial_monitor.h
 *
 *  Created on: Sep 13, 2025
 *      Author: SCSM11
 */

#ifndef APPLICATION_USER_SERIAL_MONITOR_H_
#define APPLICATION_USER_SERIAL_MONITOR_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Public APIs (distinct from app_tof) */
void MX_SERIALMON_Init(void);
void MX_SERIALMON_Process(void);

#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_USER_SERIAL_MONITOR_H_ */
