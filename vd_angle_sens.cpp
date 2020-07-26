/*
 * vd_angle_sens.cpp
 *
 *  Created on: Apr 23, 2020
 *      Author: Andrei Bragarenco
 */

#include "vd_angle_sens.h"
//---------------------
ANGSNS_ChannelType ANGSNS_Channels[VD_ANGLE_SENS_CHANNEL_NR_OF];


ANGSNS_ChannelType *ANGSNS_GetChannelRef(Std_ChannelIdType angChannelId)
{
	ANGSNS_ChannelType *potChannelRef = &ANGSNS_Channels[angChannelId];
	return potChannelRef;
}

Std_ReturnType VD_ANGLE_SENS_ChannelSetup(Std_ChannelIdType angChannelId, uint8_t devChannelId)
{
	Std_ReturnType error;
	if (angChannelId < VD_ANGLE_SENS_CHANNEL_NR_OF)
	{
		ANGSNS_ChannelType *potChannelRef = ANGSNS_GetChannelRef(angChannelId);
		potChannelRef->devChannelId = devChannelId;
		error = E_OK;
	}
	else
	{
		error = E_NOT_OK;
	}
	return error;
}

Std_ReturnType VD_ANGLE_SENS_SetPullMethod(Std_ChannelIdType angChannelId,
										  Std_PhyGetterType GetPosition)
{
	Std_ReturnType error;
	if (angChannelId < VD_ANGLE_SENS_CHANNEL_NR_OF)
	{
		ANGSNS_ChannelType *potChannelRef = ANGSNS_GetChannelRef(angChannelId);
		potChannelRef->GetPosition = GetPosition;
		error = E_OK;
	}
	else
	{
		error = E_NOT_OK;
	}
	return error;
}

Std_ReturnType ANGSNS_GroupSetup(Std_ChannelIdType *srcIds, Std_ChannelIdType *targhetIds, uint8_t nr_of_channels)
{
	Std_ReturnType error = E_OK;

	for (size_t i = 0; i < nr_of_channels; i++)
	{
		Std_ChannelIdType srcId = srcIds[i];
		Std_ChannelIdType targhetId = targhetIds[i];
		error += VD_ANGLE_SENS_ChannelSetup(srcId, targhetId);
	}
	return error;
}

Std_ReturnType ANGSNS_SetGroupSourceGetter(Std_ChannelIdType *srcIds, Std_PhyGetterType sourceGetter, uint8_t nr_of_channels)
{
	Std_ReturnType error = E_OK;

	for (size_t i = 0; i < nr_of_channels; i++)
	{
		Std_ChannelIdType srcId = srcIds[i];
		error += VD_ANGLE_SENS_SetPullMethod(srcId, sourceGetter);
	}
	return error;
}

void ANGSNS_SetAngleLimits(ANGSNS_ChannelType *angRef, Std_PhyDataType ANGLE_MIN, Std_PhyDataType ANGLE_MAX)
{
	angRef->ANGLE_MIN = ANGLE_MIN;
	angRef->ANGLE_MAX = ANGLE_MAX;
}

void ANGSNS_SetPosLimits(ANGSNS_ChannelType *angRef, Std_PhyDataType POS_MIN, Std_PhyDataType POS_MAX)
{
	angRef->POS_MIN = POS_MIN;
	angRef->POS_MAX = POS_MAX;
}

Std_PhyDataType ANGSNS_GetPosition(ANGSNS_ChannelType *angRef)
{
	if (angRef->GetPosition)
		return angRef->GetPosition(angRef->devChannelId);
	else
		return 0;
}

Std_PhyDataType ANGSNS_GetAngle(Std_ChannelIdType angChannelId)
{
	ANGSNS_ChannelType *angRef = &ANGSNS_Channels[angChannelId];
	Std_PhyDataType angVal = ANGSNS_GetAngle(angRef);
	return angVal;
}

Std_PhyDataType ANGSNS_GetAngle(ANGSNS_ChannelType *angRef)
{
	Std_PhyDataType posVal = ANGSNS_GetPosition(angRef);
	Std_PhyDataType angVal = map_float(posVal, angRef->POS_MIN, angRef->POS_MAX,
									   angRef->ANGLE_MIN, angRef->ANGLE_MAX);
	return angVal;
}
