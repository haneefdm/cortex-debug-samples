/*******************************************************************************
* File Name: cycfg_platform.c
*
* Description:
* Platform configuration
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

#include "cycfg_platform.h"

#define CY_CFG_SYSCLK_ECO_ERROR 1
#define CY_CFG_SYSCLK_ALTHF_ERROR 2
#define CY_CFG_SYSCLK_PLL_ERROR 3
#define CY_CFG_SYSCLK_FLL_ERROR 4
#define CY_CFG_SYSCLK_WCO_ERROR 5
#define CY_CFG_SYSCLK_CLKFAST_ENABLED 1
#define CY_CFG_SYSCLK_FLL_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF0_ENABLED 1
#define CY_CFG_SYSCLK_CLKHF0_FREQ_MHZ 100UL
#define CY_CFG_SYSCLK_CLKHF0_CLKPATH CY_SYSCLK_CLKHF_IN_CLKPATH0
#define CY_CFG_SYSCLK_ILO_ENABLED 1
#define CY_CFG_SYSCLK_IMO_ENABLED 1
#define CY_CFG_SYSCLK_CLKLF_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH0_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH0_SOURCE CY_SYSCLK_CLKPATH_IN_IMO
#define CY_CFG_SYSCLK_CLKPATH1_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH1_SOURCE CY_SYSCLK_CLKPATH_IN_IMO
#define CY_CFG_SYSCLK_CLKPATH2_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH2_SOURCE CY_SYSCLK_CLKPATH_IN_IMO
#define CY_CFG_SYSCLK_CLKPATH3_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH3_SOURCE CY_SYSCLK_CLKPATH_IN_IMO
#define CY_CFG_SYSCLK_CLKPATH4_ENABLED 1
#define CY_CFG_SYSCLK_CLKPATH4_SOURCE CY_SYSCLK_CLKPATH_IN_IMO
#define CY_CFG_SYSCLK_CLKPERI_ENABLED 1
#define CY_CFG_SYSCLK_CLKSLOW_ENABLED 1
#define CY_CFG_PWR_ENABLED 1
#define CY_CFG_PWR_USING_LDO 1
#define CY_CFG_PWR_USING_PMIC 0
#define CY_CFG_PWR_VBAC_SUPPLY CY_CFG_PWR_VBAC_SUPPLY_VDD
#define CY_CFG_PWR_LDO_VOLTAGE CY_SYSPM_LDO_VOLTAGE_1_1V
#define CY_CFG_PWR_USING_ULP 0

static const cy_stc_fll_manual_config_t srss_0_clock_0_fll_0_fllConfig = 
{
	.fllMult = 500U,
	.refDiv = 20U,
	.ccoRange = CY_SYSCLK_FLL_CCO_RANGE4,
	.enableOutputDiv = true,
	.lockTolerance = 10U,
	.igain = 9U,
	.pgain = 5U,
	.settlingCount = 8U,
	.outputMode = CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT,
	.cco_Freq = 355U,
};

__WEAK void cycfg_ClockStartupError(uint32_t error)
{
    (void)error; /* Suppress the compiler warning */
    while(1);
}
__STATIC_INLINE void Cy_SysClk_ClkFastInit()
{
    Cy_SysClk_ClkFastSetDivider(0U);
}
__STATIC_INLINE void Cy_SysClk_FllInit()
{
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_FllManualConfigure(&srss_0_clock_0_fll_0_fllConfig))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_FLL_ERROR);
    }
    if (CY_SYSCLK_SUCCESS != Cy_SysClk_FllEnable(200000UL))
    {
        cycfg_ClockStartupError(CY_CFG_SYSCLK_FLL_ERROR);
    }
}
__STATIC_INLINE void Cy_SysClk_ClkHf0Init()
{
    Cy_SysClk_ClkHfSetSource(0U, CY_CFG_SYSCLK_CLKHF0_CLKPATH);
    Cy_SysClk_ClkHfSetDivider(0U, CY_SYSCLK_CLKHF_NO_DIVIDE);
}
__STATIC_INLINE void Cy_SysClk_IloInit()
{
    /* The WDT is unlocked in the default startup code */
    Cy_SysClk_IloEnable();
    Cy_SysClk_IloHibernateOn(true);
}
__STATIC_INLINE void Cy_SysClk_ClkLfInit()
{
    /* The WDT is unlocked in the default startup code */
    Cy_SysClk_ClkLfSetSource(CY_SYSCLK_CLKLF_IN_ILO);
}
__STATIC_INLINE void Cy_SysClk_ClkPath0Init()
{
    Cy_SysClk_ClkPathSetSource(0U, CY_CFG_SYSCLK_CLKPATH0_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath1Init()
{
    Cy_SysClk_ClkPathSetSource(1U, CY_CFG_SYSCLK_CLKPATH1_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath2Init()
{
    Cy_SysClk_ClkPathSetSource(2U, CY_CFG_SYSCLK_CLKPATH2_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath3Init()
{
    Cy_SysClk_ClkPathSetSource(3U, CY_CFG_SYSCLK_CLKPATH3_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPath4Init()
{
    Cy_SysClk_ClkPathSetSource(4U, CY_CFG_SYSCLK_CLKPATH4_SOURCE);
}
__STATIC_INLINE void Cy_SysClk_ClkPeriInit()
{
    Cy_SysClk_ClkPeriSetDivider(1U);
}
__STATIC_INLINE void Cy_SysClk_ClkSlowInit()
{
    Cy_SysClk_ClkSlowSetDivider(0U);
}


void init_cycfg_platform(void)
{
	/* Set worst case memory wait states (! ultra low power, 150 MHz), will update at the end */
	Cy_SysLib_SetWaitStates(false, 150UL);
	#if (CY_CFG_PWR_VBAC_SUPPLY == CY_CFG_PWR_VBAC_SUPPLY_VDD)
	if (0u == Cy_SysLib_GetResetReason() /* POR, XRES, or BOD */)
	{
	    Cy_SysLib_ResetBackupDomain();
	    Cy_SysClk_IloDisable();
	    Cy_SysClk_IloInit();
	}
	#endif
	#ifdef CY_CFG_PWR_ENABLED
	/* Configure power mode */
	#if CY_CFG_PWR_USING_LDO
	Cy_SysPm_LdoSetVoltage(CY_CFG_PWR_LDO_VOLTAGE);
	#else
	Cy_SysPm_BuckEnable(CY_CFG_PWR_BUCK_VOLTAGE);
	#endif
	/* Configure PMIC */
	Cy_SysPm_UnlockPmic();
	#if CY_CFG_PWR_USING_PMIC
	Cy_SysPm_PmicEnableOutput();
	#else
	Cy_SysPm_PmicDisableOutput();
	#endif
	#endif
	
	/* Reset the core clock path to default and disable all the FLLs/PLLs */
	Cy_SysClk_ClkHfSetDivider(0U, CY_SYSCLK_CLKHF_NO_DIVIDE);
	Cy_SysClk_ClkFastSetDivider(0U);
	Cy_SysClk_ClkPeriSetDivider(1U);
	Cy_SysClk_ClkSlowSetDivider(0U);
	Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH1);
	Cy_SysClk_ClkPathSetSource(CY_SYSCLK_CLKHF_IN_CLKPATH1, CY_SYSCLK_CLKPATH_IN_IMO);
	
	if ((CY_SYSCLK_CLKHF_IN_CLKPATH0 == Cy_SysClk_ClkHfGetSource(0UL)) &&
	    (CY_SYSCLK_CLKPATH_IN_WCO == Cy_SysClk_ClkPathGetSource(CY_SYSCLK_CLKHF_IN_CLKPATH0)))
	{
	    Cy_SysClk_ClkHfSetSource(0U, CY_SYSCLK_CLKHF_IN_CLKPATH1);
	}
	
	Cy_SysClk_FllDisable();
	Cy_SysClk_ClkPathSetSource(CY_SYSCLK_CLKHF_IN_CLKPATH0, CY_SYSCLK_CLKPATH_IN_IMO);
	Cy_SysClk_ClkHfSetSource(0UL, CY_SYSCLK_CLKHF_IN_CLKPATH0);
	#ifdef CY_IP_MXBLESS
	(void)Cy_BLE_EcoReset();
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL1_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH2);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL2_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH3);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL3_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH4);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL4_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH5);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL5_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH6);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL6_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH7);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL7_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH8);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL8_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH9);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL9_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH10);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL10_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH11);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL11_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH12);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL12_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH13);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL13_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH14);
	#endif
	
	#ifdef CY_CFG_SYSCLK_PLL14_AVAILABLE
	(void)Cy_SysClk_PllDisable(CY_SYSCLK_CLKHF_IN_CLKPATH15);
	#endif
	
	/* Enable all source clocks */
	#ifdef CY_CFG_SYSCLK_PILO_ENABLED
	Cy_SysClk_PiloInit();
	#endif
	
	#ifdef CY_CFG_SYSCLK_WCO_ENABLED
	Cy_SysClk_WcoInit();
	#endif
	
	#ifdef CY_CFG_SYSCLK_CLKLF_ENABLED
	Cy_SysClk_ClkLfInit();
	#endif
	
	#ifdef CY_CFG_SYSCLK_ALTHF_ENABLED
	Cy_SysClk_AltHfInit();
	#endif
	
	#ifdef CY_CFG_SYSCLK_ECO_ENABLED
	Cy_SysClk_EcoInit();
	#endif
	
	#ifdef CY_CFG_SYSCLK_EXTCLK_ENABLED
	Cy_SysClk_ExtClkInit();
	#endif
	
	/* Configure CPU clock dividers */
	#ifdef CY_CFG_SYSCLK_CLKFAST_ENABLED
	Cy_SysClk_ClkFastInit();
	#endif
	
	#ifdef CY_CFG_SYSCLK_CLKPERI_ENABLED
	Cy_SysClk_ClkPeriInit();
	#endif
	
	#ifdef CY_CFG_SYSCLK_CLKSLOW_ENABLED
	Cy_SysClk_ClkSlowInit();
	#endif
	
	#if ((CY_CFG_SYSCLK_CLKPATH0_SOURCE == CY_SYSCLK_CLKPATH_IN_WCO) && (CY_CFG_SYSCLK_CLKHF0_CLKPATH == CY_SYSCLK_CLKHF_IN_CLKPATH0))
	    /* Configure HFCLK0 to temporarily run from IMO to initialize other clocks */
	    Cy_SysClk_ClkPathSetSource(1UL, CY_SYSCLK_CLKPATH_IN_IMO);
	    Cy_SysClk_ClkHfSetSource(0UL, CY_SYSCLK_CLKHF_IN_CLKPATH1);
	#else
	    #ifdef CY_CFG_SYSCLK_CLKPATH1_ENABLED
	        Cy_SysClk_ClkPath1Init();
	    #endif
	#endif
	
	/* Configure Path Clocks */
	#ifdef CY_CFG_SYSCLK_CLKPATH0_ENABLED
	Cy_SysClk_ClkPath0Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH2_ENABLED
	Cy_SysClk_ClkPath2Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH3_ENABLED
	Cy_SysClk_ClkPath3Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH4_ENABLED
	Cy_SysClk_ClkPath4Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH5_ENABLED
	Cy_SysClk_ClkPath5Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH6_ENABLED
	Cy_SysClk_ClkPath6Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH7_ENABLED
	Cy_SysClk_ClkPath7Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH8_ENABLED
	Cy_SysClk_ClkPath8Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH9_ENABLED
	Cy_SysClk_ClkPath9Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH10_ENABLED
	Cy_SysClk_ClkPath10Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH11_ENABLED
	Cy_SysClk_ClkPath11Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH12_ENABLED
	Cy_SysClk_ClkPath12Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH13_ENABLED
	Cy_SysClk_ClkPath13Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH14_ENABLED
	Cy_SysClk_ClkPath14Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKPATH15_ENABLED
	Cy_SysClk_ClkPath15Init();
	#endif
	
	/* Configure and enable FLL */
	#ifdef CY_CFG_SYSCLK_FLL_ENABLED
	Cy_SysClk_FllInit();
	#endif
	
	Cy_SysClk_ClkHf0Init();
	
	#if ((CY_CFG_SYSCLK_CLKPATH0_SOURCE == CY_SYSCLK_CLKPATH_IN_WCO) && (CY_CFG_SYSCLK_CLKHF0_CLKPATH == CY_SYSCLK_CLKHF_IN_CLKPATH0))
	    #ifdef CY_CFG_SYSCLK_CLKPATH1_ENABLED
	        /* Apply the ClkPath1 user setting */
	        Cy_SysClk_ClkPath1Init();
	    #endif
	#endif
	
	/* Configure and enable PLLs */
	#ifdef CY_CFG_SYSCLK_PLL0_ENABLED
	Cy_SysClk_Pll0Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL1_ENABLED
	Cy_SysClk_Pll1Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL2_ENABLED
	Cy_SysClk_Pll2Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL3_ENABLED
	Cy_SysClk_Pll3Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL4_ENABLED
	Cy_SysClk_Pll4Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL5_ENABLED
	Cy_SysClk_Pll5Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL6_ENABLED
	Cy_SysClk_Pll6Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL7_ENABLED
	Cy_SysClk_Pll7Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL8_ENABLED
	Cy_SysClk_Pll8Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL9_ENABLED
	Cy_SysClk_Pll9Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL10_ENABLED
	Cy_SysClk_Pll10Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL11_ENABLED
	Cy_SysClk_Pll11Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL12_ENABLED
	Cy_SysClk_Pll12Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL13_ENABLED
	Cy_SysClk_Pll13Init();
	#endif
	#ifdef CY_CFG_SYSCLK_PLL14_ENABLED
	Cy_SysClk_Pll14Init();
	#endif
	
	/* Configure HF clocks */
	#ifdef CY_CFG_SYSCLK_CLKHF1_ENABLED
	Cy_SysClk_ClkHf1Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF2_ENABLED
	Cy_SysClk_ClkHf2Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF3_ENABLED
	Cy_SysClk_ClkHf3Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF4_ENABLED
	Cy_SysClk_ClkHf4Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF5_ENABLED
	Cy_SysClk_ClkHf5Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF6_ENABLED
	Cy_SysClk_ClkHf6Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF7_ENABLED
	Cy_SysClk_ClkHf7Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF8_ENABLED
	Cy_SysClk_ClkHf8Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF9_ENABLED
	Cy_SysClk_ClkHf9Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF10_ENABLED
	Cy_SysClk_ClkHf10Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF11_ENABLED
	Cy_SysClk_ClkHf11Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF12_ENABLED
	Cy_SysClk_ClkHf12Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF13_ENABLED
	Cy_SysClk_ClkHf13Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF14_ENABLED
	Cy_SysClk_ClkHf14Init();
	#endif
	#ifdef CY_CFG_SYSCLK_CLKHF15_ENABLED
	Cy_SysClk_ClkHf15Init();
	#endif
	
	/* Configure miscellaneous clocks */
	#ifdef CY_CFG_SYSCLK_CLKTIMER_ENABLED
	Cy_SysClk_ClkTimerInit();
	#endif
	
	#ifdef CY_CFG_SYSCLK_CLKALTSYSTICK_ENABLED
	Cy_SysClk_ClkAltSysTickInit();
	#endif
	
	#ifdef CY_CFG_SYSCLK_CLKPUMP_ENABLED
	Cy_SysClk_ClkPumpInit();
	#endif
	
	#ifdef CY_CFG_SYSCLK_CLKBAK_ENABLED
	Cy_SysClk_ClkBakInit();
	#endif
	
	/* Configure default enabled clocks */
	#ifdef CY_CFG_SYSCLK_ILO_ENABLED
	Cy_SysClk_IloInit();
	#else
	Cy_SysClk_IloDisable();
	#endif
	
	#ifndef CY_CFG_SYSCLK_IMO_ENABLED
	#error the IMO must be enabled for proper chip operation
	#endif
	
	/* Set accurate flash wait states */
	#if (defined (CY_CFG_PWR_ENABLED) && defined (CY_CFG_SYSCLK_CLKHF0_ENABLED))
	Cy_SysLib_SetWaitStates(CY_CFG_PWR_USING_ULP != 0, CY_CFG_SYSCLK_CLKHF0_FREQ_MHZ);
	#endif
	
	/* Update System Core Clock values for correct Cy_SysLib_Delay functioning */
	SystemCoreClockUpdate();
}
