/*******************************************************************************
* File Name: cycfg_pins.h
*
* Description:
* Pin configuration
* This file was automatically generated and should not be modified.
* 
********************************************************************************
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
********************************************************************************/

#if !defined(CYCFG_PINS_H)
#define CYCFG_PINS_H

#include "cycfg_notices.h"
#include "cy_gpio.h"
#include "cycfg_routing.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define LED_RED_ENABLED 1U
#define LED_RED_PORT GPIO_PRT0
#define LED_RED_PIN 3U
#define LED_RED_NUM 3U
#define LED_RED_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define LED_RED_INIT_DRIVESTATE 1
#ifndef ioss_0_port_0_pin_3_HSIOM
	#define ioss_0_port_0_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define LED_RED_HSIOM ioss_0_port_0_pin_3_HSIOM
#define LED_RED_IRQ ioss_interrupts_gpio_0_IRQn
#define ioss_0_port_6_pin_4_ENABLED 1U
#define ioss_0_port_6_pin_4_PORT GPIO_PRT6
#define ioss_0_port_6_pin_4_PIN 4U
#define ioss_0_port_6_pin_4_NUM 4U
#define ioss_0_port_6_pin_4_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define ioss_0_port_6_pin_4_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_4_HSIOM
	#define ioss_0_port_6_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_4_IRQ ioss_interrupts_gpio_6_IRQn
#define ioss_0_port_6_pin_6_ENABLED 1U
#define ioss_0_port_6_pin_6_PORT GPIO_PRT6
#define ioss_0_port_6_pin_6_PIN 6U
#define ioss_0_port_6_pin_6_NUM 6U
#define ioss_0_port_6_pin_6_DRIVEMODE CY_GPIO_DM_PULLUP
#define ioss_0_port_6_pin_6_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_6_HSIOM
	#define ioss_0_port_6_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_6_IRQ ioss_interrupts_gpio_6_IRQn
#define ioss_0_port_6_pin_7_ENABLED 1U
#define ioss_0_port_6_pin_7_PORT GPIO_PRT6
#define ioss_0_port_6_pin_7_PIN 7U
#define ioss_0_port_6_pin_7_NUM 7U
#define ioss_0_port_6_pin_7_DRIVEMODE CY_GPIO_DM_PULLDOWN
#define ioss_0_port_6_pin_7_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_7_HSIOM
	#define ioss_0_port_6_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define ioss_0_port_6_pin_7_IRQ ioss_interrupts_gpio_6_IRQn

extern const cy_stc_gpio_pin_config_t LED_RED_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_4_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_6_config;
extern const cy_stc_gpio_pin_config_t ioss_0_port_6_pin_7_config;

void init_cycfg_pins(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_PINS_H */
