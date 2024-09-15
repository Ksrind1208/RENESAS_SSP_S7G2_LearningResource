/***********************************************************************************************************************
 * Copyright [2015-2024] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 * 
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : hw_sci_common.h
* @brief    SCI LLD definitions, common portion
***********************************************************************************************************************/

#ifndef HW_SCI_COMMON_H
#define HW_SCI_COMMON_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "bsp_api.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/** SCI SCR register bit masks */
#define SCI_SCR_TE_MASK         (0x20U)     ///< transmitter enable
#define SCI_SCR_RE_MASK         (0x10U)     ///< receiver enable
#define SCI_SCR_TE_RE_MASK      (0x30U)     ///< transmitter & receiver enable
#define SCI_SCR_CKE_VALUE_MASK  (0x03U)     ///< CKE: 2 bits

/** SCI SEMR register bit masks */
#define SCI_SEMR_BGDM_VALUE_MASK    (0x01U)     ///< BGDM: 1 bit
#define SCI_SEMR_ABCS_VALUE_MASK    (0x01U)     ///< ABCS: 1 bit
#define SCI_SEMR_ABCSE_VALUE_MASK   (0x01U)     ///< ABCSE: 1 bit

/** SCI SMR register bit masks */
#define SCI_SMR_CKS_VALUE_MASK      (0x03U)     ///< CKS: 2 bits

/** SCI SSR register receiver error bit masks */
#define SCI_SSR_ORER_MASK   (0x20U)     ///< overflow error
#define SCI_SSR_FER_MASK    (0x10U)     ///< framing error
#define SCI_SSR_PER_MASK    (0x08U)     ///< parity err
#define SCI_RCVR_ERR_MASK   (SCI_SSR_ORER_MASK | SCI_SSR_FER_MASK | SCI_SSR_PER_MASK)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/** Baud rate divisor information
 * BRR(N) = (PCLK / (divisor * Baudrate(B))) - 1
 * when ABCSE=1,                         divisor = 12*pow(2,2N-1)
 * when ABCSE=1, BGDM=1&&ABCS=1,         divisor = 16*pow(2,2N-1)
 * when ABCSE=0, one of BGDM or ABCS =1, divisor = 32*pow(2,2N-1)
 * when ABCSE=0, BGDM=0&&ABCS=0,         divisor = 64*pow(2,2N-1)
 */
typedef struct st_baud_setting_t
{
    uint16_t    div_coefficient;   /**< Divisor coefficient */
    uint8_t     bgdm;               /**< BGDM value to get divisor */
    uint8_t     abcs;               /**< ABCS value to get divisor */
    uint8_t     abcse;              /**< ABCSE value to get divisor */
    uint8_t     cks;                /**< CKS  value to get divisor (CKS = N) */
} baud_setting_t;

/** Noise filter setting definition */
typedef enum e_noise_cancel_lvl
{
    NOISE_CANCEL_LVL1,          /**< Noise filter level 1(weak) */
    NOISE_CANCEL_LVL2,          /**< Noise filter level 2 */
    NOISE_CANCEL_LVL3,          /**< Noise filter level 3 */
    NOISE_CANCEL_LVL4           /**< Noise filter level 4(strong) */
} noise_cancel_lvl_t;

/***********************************************************************************************************************
Private function prototypes
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Private Functions
***********************************************************************************************************************/

/*******************************************************************************************************************//**
* @brief    Enables transmission for the specified SCI channel
* @param[in] channel  SCI channel
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_TransmitterEnable (R_SCI0_Type * p_reg)
{
    p_reg->SCR |= SCI_SCR_TE_MASK;
}  /* End of function HW_SCI_TransmitterEnable() */

/*******************************************************************************************************************//**
* Disables transmission for the specified SCI channel
* @param[in] channel  SCI channel
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_TransmitterDisable (R_SCI0_Type * p_reg)
{
    p_reg->SCR &= (uint8_t)(~SCI_SCR_TE_MASK);
}  /* End of function HW_SCI_TransmitterDisable() */

/*******************************************************************************************************************//**
* Enables reception for the specified SCI channel
* @param[in] channel  SCI channel
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_ReceiverEnable (R_SCI0_Type * p_reg)
{
    p_reg->SCR |= SCI_SCR_RE_MASK;
}  /* End of function HW_SCI_ReceiverEnable() */

/*******************************************************************************************************************//**
* Disables reception for the specified SCI channel
* @param[in] hdl handle to SCI control block of each channel
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_ReceiverDisable (R_SCI0_Type * p_reg)
{
    p_reg->SCR &= (uint8_t)(~SCI_SCR_RE_MASK);
}  /* End of function HW_SCI_ReceiverDisable() */

/*******************************************************************************************************************//**
* Enables reception and transmission for the specified SCI channel
* @param[in] channel  SCI channel
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_TransmitterReceiverEnable (R_SCI0_Type * p_reg)
{
    p_reg->SCR |= SCI_SCR_TE_RE_MASK;
}  /* End of function HW_SCI_ReceiverEnable() */

/*******************************************************************************************************************//**
* Disables reception  and transmission for the specified SCI channel
* @param[in] channel  SCI channel
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_TransmitterReceiverDisable (R_SCI0_Type * p_reg)
{
    p_reg->SCR &= (uint8_t)(~SCI_SCR_TE_RE_MASK);
}  /* End of function HW_SCI_TransmitterReceiverDisable() */

/*******************************************************************************************************************//**
* Disable FIFO mode
* @param[in] channel   SCI channel
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_FifoDisable (R_SCI0_Type * p_reg)
{
    p_reg->FCR_b.FM = 0U;    /* FCRL.FM (select non-FIFO mode) */
}  /* End of function HW_SCI_FifoDisable() */

/*******************************************************************************************************************//**
* This function writes data to transmit data register.
* @param[in] channel  SCI channel
* @param[in] data     Data to be sent
* @retval    void
* @note      All the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_Write (R_SCI0_Type * p_reg, uint8_t const data)
{
    while (0U == p_reg->SSR_b.TDRE)
    {
        /* Wait until TDRE is cleared */
    }

    /* Write 1byte data to data register */
    p_reg->TDR = data;
}  /* End of function HW_SCI_Write() */

/*******************************************************************************************************************//**
* This function reads data from receive data register
* @param[in] channel    SCI Channel number
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_SCI_Read (R_SCI0_Type * p_reg)
{
    return p_reg->RDR;
}  /* End of function HW_SCI_Read() */

/*******************************************************************************************************************//**
* This function initializes all SCI registers.
* @param[in] channel    SCI Channel number
* @retval    none
* @note      All the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_RegisterReset (R_SCI0_Type * p_reg)
{
    p_reg->SMR = 0U;
    p_reg->SCR = 0U;
    p_reg->SSR = 0U;
    p_reg->SCMR = 0xF2U;
    p_reg->BRR = 0xFFU;
    p_reg->MDDR = 0xFFU;
    p_reg->SEMR = 0U;
    p_reg->SNFR = 0U;
    p_reg->SIMR1 = 0U;
    p_reg->SIMR2 = 0U;
    p_reg->SIMR3 = 0U;
    p_reg->SISR = 0U;
    p_reg->SPMR = 0U;
    p_reg->SISR = 0U;
    p_reg->FCR = 0xF800U;
    p_reg->CDR = 0U;
    p_reg->DCCR = 0x40U;
    p_reg->SPTR = 0x03U;
}  /* End of function HW_SCI_RegisterReset() */


/*******************************************************************************************************************//**
* This function gives delay time for the clock signal output through the SCKn pin
* @param[in] channel   SCI channel
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
*            Do not call this function from other than simple SPI mode and clock synchronous mode.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_ClockPhaseDelayEnable (R_SCI0_Type * p_reg)
{
        /* Set the SPMR.CKPH bit to 1
         * (Clock Phase Select 1: Clock is delayed)
         */
        p_reg->SPMR_b.CKPH  = 1U;
}  /* End of function HW_SCI_ClockPhaseDelayEnable() */

/*******************************************************************************************************************//**
* This function gives no delay for the clock signal output through the SCKn pin
* @param[in] channel   SCI channel
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_ClockPhaseDelayDisable (R_SCI0_Type * p_reg)
{
        /* Set the SPMR.CKPH bit to 1
         * (Clock Phase Select 1: Clock is delayed)
         */
        p_reg->SPMR_b.CKPH  = 0U;
}  /* End of function HW_SCI_ClockPhaseDelayDisable() */

/*******************************************************************************************************************//**
* This function selects inverted polarity of the clock signal output through the SCKn pin.
* @param[in] channel   SCI channel
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
*            Do not call this function from other than simple SPI mode and clock synchronous mode.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_ClockPorarityInvert (R_SCI0_Type * p_reg)
{
        /* Set the SPMR.CKPOL bit to 1
         * (Clock Polarity Select 1: Clock polarity is inverted)
         */
        p_reg->SPMR_b.CKPOL  = 1U;
}  /* End of function HW_SCI_ClockPorarityInvert() */

/*******************************************************************************************************************//**
* This function selects normal polarity of the clock signal output through the SCKn pin.
* @param[in] channel   SCI channel
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_ClockPorarityNormalSet (R_SCI0_Type * p_reg)
{
        /* Set the SPMR.CKPOL bit to 0
         * (Clock Polarity Select 0: Clock polarity is not inverted)
         */
        p_reg->SPMR_b.CKPOL  = 0U;
}  /* End of function HW_SCI_ClockPorarityNormalSet() */

/*******************************************************************************************************************//**
* Selects internal clock for baud rate generator
* @param[in] channel    SCI Channel number
* @retval    void
* @note      the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_BaudRateGenInternalClkSelect (R_SCI0_Type * p_reg)
{
    p_reg->SCR_b.CKE    = 0U;             /* Internal clock */
}  /* End of function HW_SCI_BaudRateGenInternalClkSelect() */

/*******************************************************************************************************************//**
* Selects external clock for baud rate generator
* @param[in] channel    SCI Channel number
* @retval    void
* @note      the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_BaudRateGenExternalClkSelect (R_SCI0_Type * p_reg)
{
    /* Use external clock for baud rate */
    p_reg->SCR_b.CKE    = 0x2U;           /* External clock */
}  /* End of function HW_SCI_BaudRateGenExternalClkSelect() */

/*******************************************************************************************************************//**
* Checks if Internal clock is selected or not
* @param[in] channel    SCI Channel number
* @retval    true   Internal clock is selected
* @retval    false  External clock is selected
* @note      the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE bool HW_SCI_IsBaudRateInternalClkSelected (R_SCI0_Type * p_reg)
{
    return (p_reg->SCR_b.CKE == 0U);
}  /* End of function HW_SCI_IsBaudRateInternalClkSelected() */

/*******************************************************************************************************************//**
* Selects 8 base clock cycles for 1-bit period
* @param[in] channel    SCI Channel number
* @retval    void
* @note      the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_BaudRateGenExternalClkDivideBy8 (R_SCI0_Type * p_reg)
{
    p_reg->SEMR_b.ABCS = 1U;           /* set baud rate as (external clock / 8) */
}  /* End of function HW_SCI_BaudRateGenExternalClkDivideBy8() */

/*******************************************************************************************************************//**
* Selects 16 base clock cycles for 1-bit period
* @param[in] channel    SCI Channel number
* @retval    void
* @note      the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_BaudRateGenExternalClkDivideBy16 (R_SCI0_Type * p_reg)
{
    p_reg->SEMR_b.ABCS = 0U;           /* set baud rate as (external clock / 16) */
}  /* End of function HW_SCI_BaudRateGenExternalClkDivideBy16() */

/*******************************************************************************************************************//**
* Checks if 8 base clock cycles for 1-bit period is selected or not
* @param[in] channel    SCI Channel number
* @retval    true   8 clocks is selected
* @retval    false  16 clocks is selected
* @note      the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_SCI_IsBaudRateGenClkDivideBy8Selected (R_SCI0_Type * p_reg)
{
    return (p_reg->SEMR_b.ABCS);
}  /* End of function HW_SCI_IsBaudRateGenClkDivideBy8Selected() */

/*******************************************************************************************************************//**
* Sets baud rate generator related registers as configured
* @param[in] channel    SCI Channel number
* @param[in] brr        BRR register setting  value
* @param[in] pbaudinfo  Baud rate information to be configured
* @retval    void
* @note      the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_UartBitRateSet (R_SCI0_Type * p_reg, const uint8_t brr, baud_setting_t* const pbaudinfo)
{
    p_reg->BRR          = brr;
    p_reg->SEMR_b.BGDM  = (uint8_t)(SCI_SEMR_BGDM_VALUE_MASK & pbaudinfo->bgdm);
    p_reg->SEMR_b.ABCS  = (uint8_t)(SCI_SEMR_ABCS_VALUE_MASK & pbaudinfo->abcs);
    p_reg->SEMR_b.ABCSE = (uint8_t)(SCI_SEMR_ABCSE_VALUE_MASK & pbaudinfo->abcse);
    p_reg->SMR_b.CKS    = (uint8_t)(SCI_SMR_CKS_VALUE_MASK & pbaudinfo->cks);
}  /* End of function HW_SCI_UartBitRateSet() */

/*******************************************************************************************************************//**
* Sets baud rate generator related registers as default
* @param[in] channel    SCI Channel number
* @param[in] brr        BRR register setting  value
* @param[in] pbaudinfo  Baud rate information to be configured
* @retval    void
* @note      the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_BitRateDefaultSet (R_SCI0_Type * p_reg)
{
    /* Use external clock for baud rate */
    p_reg->BRR          = 0xFFU;
    p_reg->SEMR_b.BGDM  = 0U;
    p_reg->SEMR_b.ABCSE = 0U;
    p_reg->SMR_b.CKS    = 0U;
}  /* End of function HW_SCI_BitRateDefaultSet() */

/*******************************************************************************************************************//**
* Enables to output baud rate clock
* @param[in] channel    SCI Channel number
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_BaudClkOutputEnable (R_SCI0_Type * p_reg)
{
    p_reg->SCR_b.CKE |= (SCI_SCR_CKE_VALUE_MASK & 0x01U);    /* enable to output baud clock on SCK pin */
}  /* End of function HW_SCI_BaudClkOutputEnable() */

/*******************************************************************************************************************//**
* Disables to output baud rate clock
* @param[in] channel    SCI Channel number
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_BaudClkOutputDisable (R_SCI0_Type * p_reg)
{
    p_reg->SCR_b.CKE &= (SCI_SCR_CKE_VALUE_MASK & (uint8_t)~(uint8_t)0x01);   /* disable to output baud clock on SCK pin */
}  /* End of function HW_SCI_BaudClkOutputDisable() */

/*****************************************************************************************************************//**
 * @brief     Sets BRR for baud rate generator register
 * @param[in] channel    SCI Channel number
 * @param[in] brr        BRR register setting  value
 *            clk_div    Clock divisor (n value)
 * @retval    void
 * @note      the parameter check must be held by HLD
 *********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_BitRateBRRSet (R_SCI0_Type * p_reg, const uint8_t brr, const uint8_t clk_div)
{
    /* Setting the BRR bits for the baud rate register */
    p_reg->BRR       = brr;
    p_reg->SMR_b.CKS = (uint8_t)(SCI_SMR_CKS_VALUE_MASK & clk_div);
}  /* End of function HW_SCI_BitRateBRRSet() */

/*******************************************************************************************************************//**
* Sets Noise cancel filter
* @param[in] channel   SCI Channel number
* @param[in] level  Noise cancel level
* @retval    void
* @note      Channel number and argument check is omitted, must be checked by SCI HLD
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_NoiseFilterSet (R_SCI0_Type * p_reg, noise_cancel_lvl_t level)
{
    p_reg->SEMR_b.NFEN = 1U;      /* enable noise filter */
    p_reg->SNFR = level;
}  /* End of function HW_SCI_NoiseFilterSet() */

/*******************************************************************************************************************//**
* Clears Noise cancel filter
* @param[in] channel   SCI Channel number
* @retval    void
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_NoiseFilterClear (R_SCI0_Type * p_reg)
{
    p_reg->SEMR_b.NFEN = 0U;          /* disable noise filter */
    p_reg->SNFR = 0x0U;               /* clock divided by 1 (default) */
}  /* End of function HW_SCI_NoiseFilterClear() */

/*******************************************************************************************************************//**
* Checks if overrun error happen or not
* @param[in] channel    SCI Channel number
* @retval    true  : Overrun error happens
* @retval    false : Overrun error does not happen
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE bool HW_SCI_OverRunErrorCheck (R_SCI0_Type * p_reg)
{
    return (1U == p_reg->SSR_b.ORER);
}  /* End of function HW_SCI_OverRunErrorCheck() */

/*******************************************************************************************************************//**
* Checks if framing error happen or not
* @param[in] channel    SCI Channel number
* @retval    true  : Framing error happens
* @retval    false : Framing error does not happen
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE bool HW_SCI_FramingErrorCheck (R_SCI0_Type * p_reg)
{
    return (1U == p_reg->SSR_b.FER);
}  /* End of function HW_SCI_FramingErrorCheck() */

/*******************************************************************************************************************//**
* Checks if Break signal is found or not
* @param[in] channel    SCI Channel number
* @note      Channel number is not checked in this function, caller function must check it. This function is only valid
*            when called in case of HW_SCI_FramingErrorCheck() returns true just before calling this function. If level
*            of RxD pin is low when framing error happens, that means receiving break signal.
***********************************************************************************************************************/
__STATIC_INLINE bool HW_SCI_BreakDetectionCheck (R_SCI0_Type * p_reg)
{
  	return (0U == p_reg->SPTR_b.RXDMON);
}  /* End of function HW_SCI_BreakDetectionCheck() */

/*******************************************************************************************************************//**
* Checks if parity error happen or not
* @param[in] channel    SCI Channel number
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE bool HW_SCI_ParityErrorCheck (R_SCI0_Type * p_reg)
{
	return (1U == p_reg->SSR_b.PER);
}  /* End of function HW_SCI_ParityErrorCheck() */

/*******************************************************************************************************************//**
* Clears error status
* @param[in] channel    SCI Channel number
* @note     Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_ErrorConditionClear (R_SCI0_Type * p_reg)
{
    p_reg->SSR &= (uint8_t)(~SCI_RCVR_ERR_MASK);
}  /* End of function HW_SCI_ErrorConditionClear() */

/*******************************************************************************************************************//**
* Sets start bit detection when RXDn becomes low level.
* @param[in] channel   SCI channel
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_StartBitLowLevelSet (R_SCI0_Type * p_reg)
{
    p_reg->SEMR_b.RXDESEL = 0U;   /* detect start bit when RXDn becomes low level */
}  /* End of function HW_SCI_StartBitLowLevelSet() */

/*****************************************************************************************************************//**
 * @brief     This function selects transfer direction (MSB first or LSB first)
 * @param[in] channel   SCI channel
 * @retval    void
 * @note      Channel number is not checked in this function, caller function must check it.
 ********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_TransferDirection (R_SCI0_Type * p_reg, bool const direction)
{
    /* Set the SCMR.SDIR to 0 or 1 (0: transfer with LSB first; 1: transfer with MSB first) */
    if (direction)
    {
        p_reg->SCMR_b.SDIR = 1U;
    }
    else
    {
        p_reg->SCMR_b.SDIR = 0U;
    }
}  /* End of function HW_SCI_TransferDirection() */

/*******************************************************************************************************************//**
 * Function for enabling/disabling the data inversion in the Smart card mode register (SCMR).
 * @param   channel The hardware channel to access
 * @param   enable  true or false
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_DataInversionEnable(R_SCI0_Type * p_reg, bool const enable)
{
    /* enable/disable bit */
    p_reg->SCMR_b.SINV = (uint8_t) (enable & 1U);
}  /* End of function HW_SCI_SIIC_DataDirectionEnable() */

/*******************************************************************************************************************//**
 * Function for enabling/disabling the data inversion in the Smart card mode register (SCMR).
 * @param   channel The hardware channel to access
 * @param   enable  true or false
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_DataLengthSet(R_SCI0_Type * p_reg)
{
    /* enable/disable bit */
    p_reg->SCMR_b.CHR1 = 1U;

    p_reg->SMR_b.CHR = 0U;


}  /* End of function HW_SCI_SIIC_DataDirectionEnable() */


/*******************************************************************************************************************//**
 * Function for enabling/disabling bit rate modulation function in serial extended mode register (SEMR).
 * @param   channel The hardware channel to access
 * @param   enable  true or false
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_BitRateModulationEnable(R_SCI0_Type * p_reg, bool const enable)
{
    /* enable/disable bit */
    p_reg->SEMR_b.BRME = (uint8_t) (enable & 1U);
}  /* End of function HW_SCI_BitRateModulationEnable() */

/*******************************************************************************************************************//**
 * Function for enabling/disabling smart card function in the Smart card mode register (SCMR).
 * @param   channel The hardware channel to access
 * @param   enable  true or false
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_SmartCardEnable(R_SCI0_Type * p_reg, bool const enable)
{
    /* enable/disable bit */
    p_reg->SCMR_b.SMIF = (uint8_t) (enable & 1U);
}  /* End of function HW_SCI_SIIC_SmartCardEnable() */

/*****************************************************************************************************************//**
 * @brief     This function enables/disables FIFO mode (FM bit) in FCR register
 * @param[in] channel   SCI channel
 * @param     enable  true or false
 * @retval    void
 * @note      Channel number is not checked in this function, caller function must check it.
 ********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_FIFOModeEnable(R_SCI0_Type * p_reg, bool const enable)
{
    /* Set the FCR.FM bit to 0 or 1 (0: FIFO off 1: FIFO on) */
    p_reg->FCR_b.FM = (uint16_t) (enable & 1U);
}  /* End of function HW_SCI_FIFOModeEnable */

/*******************************************************************************************************************//**
 * Function for clearing the SPI mode register (SPMR).
 * @param   channel The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_SPIModeClear(R_SCI0_Type * p_reg)
{
    /* Clear register */
    p_reg->SPMR = 0U;

}  /* End of function HW_SCI_SIIC_SPIModeClear() */

/*******************************************************************************************************************//**
 * Function for setting the communication mode to be be clock synchronous mode in the SMR register.
 * @param   channel The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_ClockSynModeSet(R_SCI0_Type * p_reg)
{
    /* Clear register */
    p_reg->SMR_b.CM = 1U;

}  /* End of function HW_SCI_ClockSynModeSet() */

/*******************************************************************************************************************//**
 * Function for setting the communication mode to be be clock synchronous mode in the SMR register.
 * @param   channel The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_ClockSynModeClear(R_SCI0_Type * p_reg)
{
    /* Clear register */
    p_reg->SMR_b.CM = 0U;

}  /* End of function HW_SCI_ClockSynModeSet() */

/*******************************************************************************************************************//**
 * Function for clearing the serial mode register (SMR).
 * @param   channel The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_SerialModeClear(R_SCI0_Type * p_reg)
{
    /*  Clear register */
    p_reg->SMR = 0U;
}  /* End of function HW_SCI_SIIC_SerialModeClear() */

/*******************************************************************************************************************//**
 * Function for clearing the smart card mode register (SCMR).
 * @param   channel The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_SmartCardModeClear(R_SCI0_Type * p_reg)
{
    /* Clear register */
    p_reg->SCMR = 0U;
}  /* End of function HW_SCI_SIIC_SmartCardModeClear() */

/*******************************************************************************************************************//**
 * Function for clearing the serial control register (SCR).
 * @param   channel The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_SerialControlClear(R_SCI0_Type * p_reg)
{
    /* Clear register */
    p_reg->SCR = 0U;
}  /* End of function HW_SCI_SIIC_SerialControlClear() */

/*******************************************************************************************************************//**
 * Function for clearing the Serial Status register (SSR).
 * @param   channel The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_SerialStatusClear(R_SCI0_Type * p_reg)
{
    /* Clear SSR register */
    p_reg->SSR = 0U;
}  /* End of function HW_SCI_SerialStatusClear() */

/*******************************************************************************************************************//**
* Check BRME register valuse
* @param[in] channel    SCI Channel number
* @retval    bool       BRME bit value
* @note      the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE bool HW_SCI_BitRateModulationCheck (R_SCI0_Type * p_reg)
{
    /* Read BRME value */
    return (1U == p_reg->SEMR_b.BRME);
}  /* End of function HW_SCI_FramingErrorCheck() */

/*******************************************************************************************************************//**
* Sets MDDR register as calculated
* @param[in] channel    SCI Channel number
* @param[in] mddr        BRR register setting  value
* @retval    void
* @note      the parameter check must be held by HLD
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_UartBitRateModulationSet (R_SCI0_Type * p_reg, const uint8_t mddr)
{
    /* Set MBBR register value*/
    p_reg->MDDR          = mddr;

}  /* End of function HW_SCI_UartBitRateSet() */

#endif // HW_SCI_COMMON_H

/* End of file */
