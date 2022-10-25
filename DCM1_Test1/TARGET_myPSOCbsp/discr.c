/*
 * discr.c
 *
 *  Created on: Jun. 10, 2022
 *      Author: jkrynski1
 */

#include "discr.h"

/*
 * @desc Sets discriminator 0 threshold
 * @returns Nothing
 */
void setDiscr0Thresh(float discrThresh)
{

	dacValue = convertDiscrThreshtoDACVoltage(discrThresh);
	dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_E, AD56x8_WR_IN_UPD_ALL); // Discr  0
	transmitToDiscrDAC(dacDataPacket);
}

/*
 * @desc Sets discriminator 1 threshold
 * @returns Nothing
 */
void setDiscr1Thresh(float discrThresh)
{

	dacValue = convertDiscrThreshtoDACVoltage(discrThresh);
	dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_A, AD56x8_WR_IN_UPD_ALL); // Discr  1
	transmitToDiscrDAC(dacDataPacket);
}

/*
 * @desc Sets discriminator 2 threshold
 * @returns Nothing
 */
void setDiscr2Thresh(float discrThresh)
{

	dacValue = convertDiscrThreshtoDACVoltage(discrThresh);
	dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_B, AD56x8_WR_IN_UPD_ALL); // Discr  2
	transmitToDiscrDAC(dacDataPacket);
}

/*
 * @desc Sets discriminator 3 threshold
 * @returns Nothing
 */
void setDiscr3Thresh(float discrThresh)
{

	dacValue = convertDiscrThreshtoDACVoltage(discrThresh);
	dacDataPacket = prepareDACDataPacket(dacValue, AD56x8_DAC_CH_F, AD56x8_WR_IN_UPD_ALL); // Discr  3
	transmitToDiscrDAC(dacDataPacket);
}
