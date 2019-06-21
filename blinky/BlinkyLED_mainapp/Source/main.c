/***************************************************************************//**
* \file main.c
* \version 1.0
*
* \brief
* Demonstrates blinking an LED under firmware control. The Cortex-M4 toggles
* the Red LED. The Cortex-M0+ starts the Cortex-M4 and enters sleep.
*
* Compatible Kits:
*   CY8CKIT-062-BLE
*   CY8CKIT-062-WIFI-BT
*
* Migration to CY8CPROTO-062-4343W kit (ModusToolbox IDE):
*   1. Create this project targeting the CY8CPROTO-062-4343W kit.
*   2. Open design.modus file and replicate P0[3] configuration on P13[7]. Give
*      this pin the alias "LED_RED". Disable P0[3].
*   3. Build and Program
* 
* Migration to CY8CPROTO-062-4343W kit (command line make):
*   1. Launch the Device Configurator tool from 
*      ModusToolbox_1.0\tools\device-configurator-1.0\
*   2. In Device Configurator, open design.modus file  
*      (ModusToolbox_1.0\libraries\psoc6sw-1.0\examples\BlinkyLED\design.modus) 
*      and replicate P0[3] configuration on P13[7]. 
*      Give this pin the alias "LED_RED". Disable P0[3].
*   3. Perform "make clean"
*   4. Build and Program the device with "make DEVICE=CY8C624ABZI-D44 program"
*      Note that depending on the method used to program the device, you may 
*      need to manually reset it by pressing the SW1 RESET button on the kit.
*   4. Observe the red blinking LED.
*   5. To switch back to CY8CKIT-062-BLE or CY8CKIT-062-WIFI-BT, 
*      perform steps 1 through 3 to reconfigure the "LED_RED" to P0[3]. 
*      Then use "make program".
*
********************************************************************************
* \copyright
* Copyright 2017-2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_pdl.h"
#include "cycfg.h"
#include "./blah.h"

int main(void)
{
	trigger_set_t blah = {
			false, 0, 1, 7, 9, 1.3, 10000, 5000
	};
	myFunc(&blah);

    /* Set up internal routing, pins, and clock-to-peripheral connections */
    init_cycfg_all();

    
    /* enable interrupts */
    __enable_irq();

    for (;;)
    {
        Cy_GPIO_Inv(LED_RED_PORT, LED_RED_PIN); /* toggle the pin */
        Cy_SysLib_Delay(1000/*msec*/);
    }
}
