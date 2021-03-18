#include "stm32f4xx.h"

#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_spi.h"

#include "spiflash.h"


void spiflash_init(void)
{
  LL_GPIO_InitTypeDef gpioInits;
  LL_SPI_InitTypeDef spiInits;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_SPI1_CLK_ENABLE();
  
  gpioInits.Pin = LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7;
  gpioInits.Mode = LL_GPIO_MODE_ALTERNATE;
  gpioInits.Alternate = LL_GPIO_AF_5;
  gpioInits.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  LL_GPIO_Init(GPIOA, &gpioInits);

  gpioInits.Pin = LL_GPIO_PIN_4;
  gpioInits.Mode = LL_GPIO_MODE_OUTPUT;
  gpioInits.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  gpioInits.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  gpioInits.Pull = LL_GPIO_PULL_DOWN;
  LL_GPIO_Init(GPIOA, &gpioInits);

  LL_SPI_StructInit(&spiInits);
  spiInits.TransferDirection = LL_SPI_FULL_DUPLEX;
  spiInits.Mode = LL_SPI_MODE_MASTER;
  spiInits.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  spiInits.ClockPolarity = LL_SPI_POLARITY_HIGH;
  spiInits.ClockPhase = LL_SPI_PHASE_2EDGE;
  spiInits.NSS = LL_SPI_NSS_SOFT;
  spiInits.BaudRate = 50 * 1000 * 1000;
  spiInits.BitOrder = LL_SPI_MSB_FIRST;
  spiInits.CRCCalculation = LL_SPI_CRCCALCULATION_ENABLE;
  spiInits.CRCPoly = 0x1010;

  LL_SPI_Disable(SPI1);
  LL_SPI_DeInit(SPI1);
  LL_SPI_Init(SPI1, &spiInits);
  LL_SPI_Enable(SPI1);
}

void spiflash_deinit(void)
{
  LL_SPI_Disable(SPI1);
  LL_SPI_DeInit(SPI1);
}

void spiflash_cs_low(void)
{
  LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_4);
}

void spiflash_cs_high(void)
{
  LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);
}

uint16_t spiflash_receive(void)
{
  return LL_SPI_ReceiveData16(SPI1);
}

void spiflash_transmit(uint8_t data)
{
  LL_SPI_TransmitData8(SPI1, data);
}
