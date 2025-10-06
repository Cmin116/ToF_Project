/*
 * ROI.h
 *
 *  Created on: Sep 14, 2025
 *      Author: SCSM11
 */

#ifndef APPLICATION_USER_ROI_H_
#define APPLICATION_USER_ROI_H_

#include <stdint.h>
#include "53l8a1_ranging_sensor.h"   // For RANGING_SENSOR_Result_t

#ifdef __cplusplus
extern "C" {
#endif

/* Result of ROI evaluation */
typedef struct {
    int valid;              // 0 = no valid ROI found, 1 = valid
    uint8_t row;            // top-left row index (0..6)
    uint8_t col;            // top-left col index (0..6)
    int32_t avg_distance;   // averaged (or median) distance in mm
} ROI_Result_t;

/* Public API */
void ROI_Init(void);
ROI_Result_t ROI_Compute(const RANGING_SENSOR_Result_t *res);

#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_USER_ROI_H_ */
