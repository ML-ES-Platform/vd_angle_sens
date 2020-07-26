/*
 * vd_angle_sens.h
 *
 *  Created on: Apr 23, 2020
 *      Author: Andrei Bragarenco
 */

#ifndef _VD_ANGLE_SENS_H_
#define _VD_ANGLE_SENS_H_

#include "vd_angle_sens_cfg.h"

#ifndef VD_ANGLE_SENS_CONFIG
enum VD_ANGLE_SENS_IdType {ANGSNS__CHANNEL_NR_OF = 0 };
#endif


typedef struct ANGSNS_ChannelType_t {

	Std_ChannelIdType devChannelId = 0;

	Std_PhyDataType POS_MIN = 0;
	Std_PhyDataType POS_MAX = 100;
	Std_PhyDataType positionVal = 0;

	Std_PhyDataType ANGLE_MIN = 0;
	Std_PhyDataType ANGLE_MAX = 180;
	Std_PhyDataType angleVal = 0;

	Std_PhyGetterType GetPosition = NULL;

} ANGSNS_ChannelType;


ANGSNS_ChannelType* ANGSNS_GetChannelRef(Std_ChannelIdType angChannelId);
Std_ReturnType VD_ANGLE_SENS_ChannelSetup(Std_ChannelIdType angChannelId, uint8_t posChannelId);
Std_ReturnType ANGSNS_GroupSetup(Std_ChannelIdType *srcIds, Std_ChannelIdType *targhetIds, uint8_t nr_of_channels);
Std_ReturnType VD_ANGLE_SENS_SetPullMethod( Std_ChannelIdType posChannelId,  Std_PhyGetterType GetPos);
Std_ReturnType ANGSNS_SetGroupSourceGetter(Std_ChannelIdType *srcIds, Std_PhyGetterType sourceGetter, uint8_t nr_of_channels);


void ANGSNS_SetAngleLimits(Std_PhyDataType ANGLE_MIN, Std_PhyDataType ANGLE_MAX);
void ANGSNS_SetPosLimits(Std_PhyDataType POS_MIN, Std_PhyDataType POS_MAX);

Std_PhyDataType ANGSNS_GetPosition(ANGSNS_ChannelType *angRef);
Std_PhyDataType ANGSNS_GetPosition(Std_ChannelIdType posChannelId);
Std_PhyDataType ANGSNS_GetAngle(ANGSNS_ChannelType *angRef);
Std_PhyDataType ANGSNS_GetAngle(Std_ChannelIdType angChannelId);



#endif /* _VD_ANGLE_SENS_H_ */
