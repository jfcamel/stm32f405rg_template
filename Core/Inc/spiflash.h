#ifndef __SPIFLASH_H__
#define __SPIFLASH_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  void spiflash_init(void);
  void spiflash_deinit(void);

  void spiflash_cs_low(void);
  void spiflash_cs_high(void);

  uint16_t spiflash_receive(void);
  void spiflash_transmit(uint8_t data);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __SPIFLASH_H__
