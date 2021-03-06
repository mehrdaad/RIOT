/*
 * Copyright (C) 2016 Freie Universität Berlin
 *               2020 Philipp-Alexander Blum <philipp-blum@jakiku.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_nrf52
 * @{
 *
 * @file
 * @brief       nRF52 interrupt vector definitions
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Philipp-Alexander Blum <philipp-blum@jakiku.de>
 *
 * @}
 */

#include <stdint.h>

#include "cpu.h"
#include "vectors_cortexm.h"

/* define a local dummy handler as it needs to be in the same compilation unit
 * as the alias definition */
void dummy_handler(void) {
    dummy_handler_default();
}

/* nRF52 specific interrupt vectors */
WEAK_DEFAULT void isr_power_clock(void);
WEAK_DEFAULT void isr_radio(void);
WEAK_DEFAULT void isr_uart0(void);
WEAK_DEFAULT void isr_spi0(void);
WEAK_DEFAULT void isr_spi0_twi0(void);
WEAK_DEFAULT void isr_spi1_twi0(void);
WEAK_DEFAULT void isr_spi1_twi1(void);
WEAK_DEFAULT void isr_nfct(void);
WEAK_DEFAULT void isr_gpiote(void);
WEAK_DEFAULT void isr_saadc(void);
WEAK_DEFAULT void isr_timer0(void);
WEAK_DEFAULT void isr_timer1(void);
WEAK_DEFAULT void isr_timer2(void);
WEAK_DEFAULT void isr_rtc0(void);
WEAK_DEFAULT void isr_temp(void);
WEAK_DEFAULT void isr_rng(void);
WEAK_DEFAULT void isr_ecb(void);
WEAK_DEFAULT void isr_ccm_aar(void);
WEAK_DEFAULT void isr_wdt(void);
WEAK_DEFAULT void isr_rtc1(void);
WEAK_DEFAULT void isr_qdec(void);
WEAK_DEFAULT void isr_lpcomp(void);

#ifndef SOFTDEVICE_PRESENT
WEAK_DEFAULT void isr_swi0(void);
#else
/* For unknown reasons, setting PendSV pending within
 * the softdevice ISRs leads to a crash. This workaround
 * uses swi0 as trampoline.
 */
extern void thread_yield_higher(void);
void isr_swi0(void)
{
    thread_yield_higher();
}
#endif

WEAK_DEFAULT void isr_swi1(void);
WEAK_DEFAULT void isr_swi2(void);
WEAK_DEFAULT void isr_swi3(void);
WEAK_DEFAULT void isr_swi4(void);
WEAK_DEFAULT void isr_swi5(void);
WEAK_DEFAULT void isr_timer3(void);
WEAK_DEFAULT void isr_timer4(void);
WEAK_DEFAULT void isr_pwm0(void);
WEAK_DEFAULT void isr_pdm(void);
WEAK_DEFAULT void isr_mwu(void);
WEAK_DEFAULT void isr_pwm1(void);
WEAK_DEFAULT void isr_pwm2(void);
WEAK_DEFAULT void isr_spi2(void);
WEAK_DEFAULT void isr_rtc2(void);
WEAK_DEFAULT void isr_i2s(void);

#ifdef CPU_MODEL_NRF52840XXAA
WEAK_DEFAULT void isr_fpu(void);
WEAK_DEFAULT void isr_usbd(void);
WEAK_DEFAULT void isr_uarte1(void);
WEAK_DEFAULT void isr_qspi(void);
WEAK_DEFAULT void isr_cryptocell(void);
WEAK_DEFAULT void isr_spi3(void);
WEAK_DEFAULT void isr_pwm3(void);
#endif

#ifdef SOFTDEVICE_PRESENT
extern void SWI2_EGU2_IRQHandler(void);
#endif

#if defined(CPU_MODEL_NRF52811XXAA)
/* CPU specific interrupt vector table */
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    isr_power_clock,       /* power_clock */
    isr_radio,             /* radio */
    isr_uart0,             /* uart0 */
    isr_spi1_twi0,         /* spi1_twi0 */
    isr_spi0,              /* spi 0 */
    (0UL),                 /* reserved */
    isr_gpiote,            /* gpiote */
    isr_saadc,             /* adc */
    isr_timer0,            /* timer0 */
    isr_timer1,            /* timer1 */
    isr_timer2,            /* timer2 */
    isr_rtc0,              /* rtc0 */
    isr_temp,              /* temp */
    isr_rng,               /* rng */
    isr_ecb,               /* ecb */
    isr_ccm_aar,           /* ccm_aar */
    isr_wdt,               /* wdt */
    isr_rtc1,              /* rtc1 */
    isr_qdec,              /* qdec */
    isr_lpcomp,            /* lpcomp */
    isr_swi0,              /* swi0 */
    isr_swi1,              /* swi1 */
    isr_swi3,              /* swi3 */
    isr_swi4,              /* swi4 */
    isr_swi5,              /* swi5 */
    (0UL),                 /* reserved */
    (0UL),                 /* reserved */
    isr_pwm0,              /* pwm 0 */
    isr_pdm,               /* pdm */
};
#else
/* CPU specific interrupt vector table */
ISR_VECTOR(1)
const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    isr_power_clock,       /* power_clock */
    isr_radio,             /* radio */
    isr_uart0,             /* uart0 */
    isr_spi0_twi0,         /* spi0_twi0 */
    isr_spi1_twi1,         /* spi1_twi1 */
    isr_nfct,              /* nfct */
    isr_gpiote,            /* gpiote */
    isr_saadc,             /* adc */
    isr_timer0,            /* timer0 */
    isr_timer1,            /* timer1 */
    isr_timer2,            /* timer2 */
    isr_rtc0,              /* rtc0 */
    isr_temp,              /* temp */
    isr_rng,               /* rng */
    isr_ecb,               /* ecb */
    isr_ccm_aar,           /* ccm_aar */
    isr_wdt,               /* wdt */
    isr_rtc1,              /* rtc1 */
    isr_qdec,              /* qdec */
    isr_lpcomp,            /* lpcomp */
    isr_swi0,              /* swi0 */
    isr_swi1,              /* swi1 */
#ifdef SOFTDEVICE_PRESENT
    SWI2_EGU2_IRQHandler,  /* softdevice swi handler */
#else
    isr_swi2,              /* swi2 */
#endif
    isr_swi3,              /* swi3 */
    isr_swi4,              /* swi4 */
    isr_swi5,              /* swi5 */
    isr_timer3,            /* timer 3 */
    isr_timer4,            /* timer 4 */
    isr_pwm0,              /* pwm 0 */
    isr_pdm,               /* pdm */
    (0UL),                 /* reserved */
    (0UL),                 /* reserved */
    isr_mwu,               /* mwu */
    isr_pwm1,              /* pwm 1 */
    isr_pwm2,              /* pwm 2 */
    isr_spi2,              /* spi 2 */
    isr_rtc2,              /* rtc 2 */
    isr_i2s,               /* i2s */
#ifdef CPU_MODEL_NRF52840XXAA
    isr_fpu,               /* fpu */
    isr_usbd,              /* usbc */
    isr_uarte1,            /* uarte1 */
    isr_qspi,              /* qspi */
    isr_cryptocell,        /* cryptocell */
    isr_spi3,              /* spi3 */
    (0UL),                 /* reserved */
    isr_pwm3,              /* pwm3 */
#endif
};
#endif
