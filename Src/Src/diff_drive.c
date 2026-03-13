/*
 * diff_drive.c
 *
 *  Created on: Mar 11, 2026
 *      Author: ASUS
 */


#include "diff_drive.h"

//float wheel_base = 0.5;
//float wheel_radius = 0.1;
//
//float wL_ref = 0;
//float wR_ref = 0;

void diff_drive_compute(float v, float w)
{
    wR_ref = (2*v + w*wheel_base) / (2*wheel_radius);
    wL_ref = (2*v - w*wheel_base) / (2*wheel_radius);
}
