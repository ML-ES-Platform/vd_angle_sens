/*
 * dd_pot_demo.cpp
 *
 *  Created on: May 8, 2020
 *      Author: Andrei Bragarenco
 */


#include <MCAL/mcal_adc/mcal_adc.h>
#include <ESW/dd_pot/dd_pot.h>
#include <ESW/vd_angle_sens/vd_angle_sens.h>


//The setup function is called once at startup of the sketch
void vd_angle_sens_demo_setup() {
// Add your initialization code here
	Serial.begin(9600);
	Std_ReturnType error = E_OK;

	error+= MCAL_ADC_ChannelSetup(ADC_1, A3);
	error+= MCAL_ADC_ChannelSetup(ADC_2, A4);
	error+= MCAL_ADC_ChannelSetup(ADC_3, A5);


	error+= DD_POT_ChannelSetup(POT_1, ADC_3);
	error+= DD_POT_ChannelSetup(POT_2, ADC_2);
	error+= DD_POT_ChannelSetup(POT_3, ADC_1);

	error+= DD_POT_SetPullMethod(POT_1, ADC_ReadChannel);
	error+= DD_POT_SetPullMethod(POT_2, ADC_ReadChannel);
	error+= DD_POT_SetPullMethod(POT_3, ADC_ReadChannel);


	error+= VD_ANGLE_SENS_ChannelSetup(ANGSNS_1,POT_1);
	error+= VD_ANGLE_SENS_ChannelSetup(ANGSNS_2,POT_2);
	error+= VD_ANGLE_SENS_ChannelSetup(ANGSNS_3,POT_3);

	error+= VD_ANGLE_SENS_SetPullMethod(ANGSNS_1, POT_GetPosition);
	error+= VD_ANGLE_SENS_SetPullMethod(ANGSNS_2, POT_GetPosition);
	error+= VD_ANGLE_SENS_SetPullMethod(ANGSNS_3, POT_GetPosition);


	Serial.print("Errors: ");
	Serial.println(error);


}

// The loop function is called in an endless loop
void vd_angle_sens_demo_loop() {
//Add your repeated code here
	for (int i = 0; i < MCAL_ADC_CHANNEL_NR_OF; i++) {

		Std_RawDataType adcVal = ADC_ReadChannel(i);
		Serial.print(" : ");
		Serial.print(adcVal);
	}
	Serial.print(" : <--->");

	for (int i = 0; i < DD_POT_CHANNEL_NR_OF; i++) {

		Std_PhyDataType potVal = POT_GetPosition(i);
		Serial.print(" : ");
		Serial.print(potVal);
	}
	Serial.print(" : <--->");

	for (int i = 0; i < VD_ANGLE_SENS_CHANNEL_NR_OF; i++) {

		Std_PhyDataType angVal = ANGSNS_GetAngle(i);
		Serial.print(" : ");
		Serial.print(angVal);
	}

	Serial.println();
	delay(100);
}
