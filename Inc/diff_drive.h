/*
 * diff_drive.h
 *
 *  Created on: Mar 11, 2026
 *      Author: ASUS
 */

#ifndef INC_DIFF_DRIVE_H_
#define INC_DIFF_DRIVE_H_

extern float wL_ref;
extern float wR_ref;

void diff_drive_compute(float v, float w);

#endif /* INC_DIFF_DRIVE_H_ */
