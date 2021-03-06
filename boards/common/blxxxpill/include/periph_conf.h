/*
 * Copyright (C) 2015 TriaGnoSys GmbH
 *               2017 Alexander Kurth, Sören Tempel, Tristan Bruns
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_common_blxxxpill
 * @{
 *
 * @file
 * @brief       Peripheral MCU configuration for the bluepill/blackpill boards
 *
 * @author      Víctor Ariño <victor.arino@triagnosys.com>
 * @author      Sören Tempel <tempel@uni-bremen.de>
 * @author      Tristan Bruns <tbruns@uni-bremen.de>
 * @author      Alexander Kurth <kurth1@uni-bremen.de>
 *
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "periph_cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Clock settings
 *
 * @note    This is auto-generated from
 *          `cpu/stm32_common/dist/clk_conf/clk_conf.c`
 * @{
 */
/* give the target core clock (HCLK) frequency [in Hz],
 * maximum: 72MHz */
#define CLOCK_CORECLOCK     (72000000U)
/* 0: no external high speed crystal available
 * else: actual crystal frequency [in Hz] */
#define CLOCK_HSE           (8000000U)
/* 0: no external low speed crystal available,
 * 1: external crystal available (always 32.768kHz) */
#define CLOCK_LSE           (1U)
/* peripheral clock setup */
#define CLOCK_AHB_DIV       RCC_CFGR_HPRE_DIV1
#define CLOCK_AHB           (CLOCK_CORECLOCK / 1)
#define CLOCK_APB1_DIV      RCC_CFGR_PPRE1_DIV2     /* max 36MHz */
#define CLOCK_APB1          (CLOCK_CORECLOCK / 2)
#define CLOCK_APB2_DIV      RCC_CFGR_PPRE2_DIV1     /* max 72MHz */
#define CLOCK_APB2          (CLOCK_CORECLOCK / 1)

/* PLL factors */
#define CLOCK_PLL_PREDIV     (1)
#define CLOCK_PLL_MUL        (9)
/** @} */

/**
 * @name    Real time counter configuration
 * @{
 */
#ifndef RTT_FREQUENCY
#define RTT_FREQUENCY       (16384)      /* in Hz */
#endif
/** @} */

/**
 * @name    ADC configuration
 * @{
 */
#define ADC_CONFIG {                                     \
    { .dev = 0, .pin = GPIO_PIN(PORT_A, 0), .chan = 0 }, \
    { .dev = 0, .pin = GPIO_PIN(PORT_A, 1), .chan = 1 }, \
    { .dev = 0, .pin = GPIO_PIN(PORT_A, 4), .chan = 4 }, \
    { .dev = 0, .pin = GPIO_PIN(PORT_A, 5), .chan = 5 }, \
    { .dev = 0, .pin = GPIO_PIN(PORT_A, 6), .chan = 6 }, \
    { .dev = 0, .pin = GPIO_PIN(PORT_A, 7), .chan = 7 }, \
    { .dev = 0, .pin = GPIO_PIN(PORT_B, 0), .chan = 8 }, \
    { .dev = 0, .pin = GPIO_PIN(PORT_B, 1), .chan = 9 }, \
    /* ADC Temperature channel */                        \
    { .dev = 0, .pin = GPIO_UNDEF, .chan = 16 },         \
    /* ADC VREF channel */                               \
    { .dev = 0, .pin = GPIO_UNDEF, .chan = 17 },         \
}

#define ADC_NUMOF           10
/** @} */

/**
 * @name    DMA streams configuration
 * @{
 */
static const dma_conf_t dma_config[] = {
    { .stream = 1 },    /* DMA1 Channel 2 - SPI1_RX / USART3_TX */
    { .stream = 2 },    /* DMA1 Channel 3 - SPI1_TX */
    { .stream = 3 },    /* DMA1 Channel 4 - SPI2_RX / USART1_TX */
    { .stream = 4 },    /* DMA1 Channel 5 - SPI2_TX */
    { .stream = 6 },    /* DMA1 Channel 7 - USART2_TX */
};

#define DMA_0_ISR   isr_dma1_channel2
#define DMA_1_ISR   isr_dma1_channel3
#define DMA_2_ISR   isr_dma1_channel4
#define DMA_3_ISR   isr_dma1_channel5
#define DMA_4_ISR   isr_dma1_channel7

#define DMA_NUMOF           ARRAY_SIZE(dma_config)
/** @} */

/**
 * @name   Timer configuration
 * @{
 */
static const timer_conf_t timer_config[] = {
    {
        .dev      = TIM2,
        .max      = 0x0000ffff,
        .rcc_mask = RCC_APB1ENR_TIM2EN,
        .bus      = APB1,
        .irqn     = TIM2_IRQn
    },
    {
        .dev      = TIM3,
        .max      = 0x0000ffff,
        .rcc_mask = RCC_APB1ENR_TIM3EN,
        .bus      = APB1,
        .irqn     = TIM3_IRQn
    },
    {
        .dev      = TIM4,
        .max      = 0x0000ffff,
        .rcc_mask = RCC_APB1ENR_TIM4EN,
        .bus      = APB1,
        .irqn     = TIM4_IRQn
    }
};

#define TIMER_0_ISR         isr_tim2
#define TIMER_1_ISR         isr_tim3
#define TIMER_2_ISR         isr_tim4

#define TIMER_NUMOF         ARRAY_SIZE(timer_config)
/** @} */

/**
 * @name    QDEC configuration
 * @{
 */

static const qdec_conf_t qdec_config[] = {
    {
        .dev      = TIM1,
        .max      = 0x0000ffff,
        .rcc_mask = RCC_APB2ENR_TIM1EN,
        .chan     = { { .pin = GPIO_PIN(PORT_A, 8),             .cc_chan = 0 },
                      { .pin = GPIO_PIN(PORT_A, 9),             .cc_chan = 1 } },
        .bus      = APB2,
        .irqn     = TIM1_UP_IRQn
    },
    {
        .dev      = TIM3,
        .max      = 0x0000ffff,
        .rcc_mask = RCC_APB1ENR_TIM3EN,
        .chan     = { { .pin = GPIO_PIN(PORT_A, 6),             .cc_chan = 0 },
                      { .pin = GPIO_PIN(PORT_A, 7),             .cc_chan = 1 } },
        .bus      = APB1,
        .irqn     = TIM3_IRQn
    },
    {
        .dev      = TIM4,
        .max      = 0x0000ffff,
        .rcc_mask = RCC_APB1ENR_TIM4EN,
        .chan     = { { .pin = GPIO_PIN(PORT_B, 6),             .cc_chan = 0 },
                      { .pin = GPIO_PIN(PORT_B, 7),             .cc_chan = 1 } },
        .bus      = APB1,
        .irqn     = TIM4_IRQn
    }
};

#define QDEC_NUMOF           ARRAY_SIZE(qdec_config)
/** @} */

/**
 * @name   UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {
        .dev        = USART1,
        .rcc_mask   = RCC_APB2ENR_USART1EN,
        .rx_pin     = GPIO_PIN(PORT_A, 10),
        .tx_pin     = GPIO_PIN(PORT_A, 9),
        .bus        = APB2,
        .irqn       = USART1_IRQn,
#ifdef MODULE_PERIPH_DMA
        .dma        = 2,
        .dma_chan   = DMA_CHAN_CONFIG_UNSUPPORTED
#endif
    },
    {
        .dev        = USART2,
        .rcc_mask   = RCC_APB1ENR_USART2EN,
        .rx_pin     = GPIO_PIN(PORT_A, 3),
        .tx_pin     = GPIO_PIN(PORT_A, 2),
        .bus        = APB1,
        .irqn       = USART2_IRQn,
#ifdef MODULE_PERIPH_DMA
        .dma        = 4,
        .dma_chan   = DMA_CHAN_CONFIG_UNSUPPORTED
#endif
    },
    {
        .dev        = USART3,
        .rcc_mask   = RCC_APB1ENR_USART3EN,
        .rx_pin     = GPIO_PIN(PORT_B, 11),
        .tx_pin     = GPIO_PIN(PORT_B, 10),
        .bus        = APB1,
        .irqn       = USART3_IRQn,
#ifdef MODULE_PERIPH_DMA
        .dma        = 0,
        .dma_chan   = DMA_CHAN_CONFIG_UNSUPPORTED
#endif
    }
};

#define UART_0_ISR          (isr_usart1)
#define UART_1_ISR          (isr_usart2)
#define UART_2_ISR          (isr_usart3)

#define UART_NUMOF          ARRAY_SIZE(uart_config)
/** @} */

/**
 * @name    I2C configuration
 * @note    This board may require external pullup resistors for i2c operation.
 * @{
 */
static const i2c_conf_t i2c_config[] = {
    {
        .dev            = I2C1,
        .speed          = I2C_SPEED_NORMAL,
        .scl_pin        = GPIO_PIN(PORT_B, 6),
        .sda_pin        = GPIO_PIN(PORT_B, 7),
        .bus            = APB1,
        .rcc_mask       = RCC_APB1ENR_I2C1EN,
        .clk            = CLOCK_APB1,
        .irqn           = I2C1_EV_IRQn
    },
    {
        .dev            = I2C2,
        .speed          = I2C_SPEED_NORMAL,
        .scl_pin        = GPIO_PIN(PORT_B, 10),
        .sda_pin        = GPIO_PIN(PORT_B, 11),
        .bus            = APB1,
        .rcc_mask       = RCC_APB1ENR_I2C2EN,
        .clk            = CLOCK_APB1,
        .irqn           = I2C2_EV_IRQn
    }
};

#define I2C_0_ISR           isr_i2c1_ev
#define I2C_1_ISR           isr_i2c2_ev

#define I2C_NUMOF           ARRAY_SIZE(i2c_config)
/** @} */

/**
 * @name   PWM configuration
 * @{
 */
static const pwm_conf_t pwm_config[] = {
    {
        .dev      = TIM1,
        .rcc_mask = RCC_APB2ENR_TIM1EN,
        .chan     = { { .pin = GPIO_PIN(PORT_A, 8),  .cc_chan = 0 },
                      { .pin = GPIO_PIN(PORT_A, 9),  .cc_chan = 1 },
                      { .pin = GPIO_PIN(PORT_A, 10), .cc_chan = 2 },
                      { .pin = GPIO_PIN(PORT_A, 11), .cc_chan = 3 } },
        .af       = GPIO_AF_OUT_PP,
        .bus      = APB2
    }
};

#define PWM_NUMOF ARRAY_SIZE(pwm_config)
/** @} */

/**
 * @name   SPI configuration
 * @{
 */
static const spi_conf_t spi_config[] = {
    {
        .dev      = SPI1,
        .mosi_pin = GPIO_PIN(PORT_A, 7),
        .miso_pin = GPIO_PIN(PORT_A, 6),
        .sclk_pin = GPIO_PIN(PORT_A, 5),
        .cs_pin   = GPIO_PIN(PORT_A, 4),
        .rccmask  = RCC_APB2ENR_SPI1EN,
        .apbbus   = APB2,
#ifdef MODULE_PERIPH_DMA
        .tx_dma   = 1,
        .tx_dma_chan = DMA_CHAN_CONFIG_UNSUPPORTED,
        .rx_dma   = 0,
        .rx_dma_chan = DMA_CHAN_CONFIG_UNSUPPORTED
#endif
    },
    {
        .dev      = SPI2,
        .mosi_pin = GPIO_PIN(PORT_B, 15),
        .miso_pin = GPIO_PIN(PORT_B, 14),
        .sclk_pin = GPIO_PIN(PORT_B, 13),
        .cs_pin   = GPIO_PIN(PORT_B, 12),
        .rccmask  = RCC_APB1ENR_SPI2EN,
        .apbbus   = APB1,
#ifdef MODULE_PERIPH_DMA
        .tx_dma   = 3,
        .tx_dma_chan = DMA_CHAN_CONFIG_UNSUPPORTED,
        .rx_dma   = 2,
        .rx_dma_chan = DMA_CHAN_CONFIG_UNSUPPORTED
#endif
    }
};

#define SPI_NUMOF           ARRAY_SIZE(spi_config)
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
