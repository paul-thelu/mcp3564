/***********************************************************************************
  * @file    mcp3564.h
  * @brief   C Library for configuring the MCP3561/2/4 1/2/4 channel
  *          24 Bit sigma-delta ADC on STM32
  * @version 0.1
  * @date    2021-11-29
  * @license Apache 2.0
  * @author  Simon Burkhardt
  *
  *          FHNW University of Applied Sciences and Arts Northwestern Switzerland
  *          https://www.fhnw.ch/ise/
  *          https://github.com/fhnw-ise-qcrypt/mcp3564
  *
  *          GAP Quantum Technologies University of Geneva
  *          https://www.unige.ch/gap/qic/qtech/
  *
  * @see     https://www.microchip.com/en-us/product/MCP3561
************************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MCP3564_H
#define __MCP3564_H

#ifdef __cplusplus
 extern "C" {
#endif

 /* Includes ------------------------------------------------------------------*/
#include "main.h"

 /* Private macros ------------------------------------------------------------*/
 /* Exported types ------------------------------------------------------------*/
 /* Exported constants --------------------------------------------------------*/
 /* Exported functions prototypes ---------------------------------------------*/
 void MCP3561_Init (SPI_HandleTypeDef *hspi);
 void MCP3561_Reset (SPI_HandleTypeDef *hspi);
 void MCP3561_Channels(SPI_HandleTypeDef *hspi, uint8_t ch_p, uint8_t ch_n);
 uint32_t MCP3561_ReadADCData    (SPI_HandleTypeDef *hspi);
 int32_t MCP3561_ReadADCData_24Bit (SPI_HandleTypeDef *hspi);
 int32_t MCP3561_ReadADCData_32Bit (SPI_HandleTypeDef *hspi);
 int32_t * MCP3561_ReadADCData_32Bit_Scan (SPI_HandleTypeDef *hspi);
 void    MCP3561_PrintRegisters (SPI_HandleTypeDef *hspi);
 // uint32_t MCP3561_ReadADCData_IT (SPI_HandleTypeDef *hspi);

 /* Private defines -----------------------------------------------------------*/
#define MCP3561_CHIP_SELECT_GPIO_Pin  (SPI1_CS_Pin)
#define MCP3561_CHIP_SELECT_GPIO_Port (SPI1_CS_GPIO_Port)
#define MCP3561_HAL_TIMEOUT           (3)

/* @note the device address is hardcoded and depends on the chip marking */
#define MCP3561_DEVICE_ADDRESS       (0x01)
#define MCP3561_DEVICE_ADDRESS_MASK  (MCP3561_DEVICE_ADDRESS << 6)
#define _MCP3561_COMMAND_ADDR_POS    (2)

// USEFUL MASKS FOR ADC COMMUNICATION
#define MCP3561_DATA_READY_SMASK   (0x04) // 0b00000100 // Tells us whether data is ready from an SPI transaction
#define MCP3561_ADDRESS_MASK       (0x38) // 0b00111000
#define MCP3561_WRITE_COMMAND_MASK (0x02) // 0b00000010
#define MCP3561_WRITE_COMMAND      (MCP3561_WRITE_COMMAND_MASK | MCP3561_DEVICE_ADDRESS_MASK)
#define MCP3561_IREAD_COMMAND_MASK (0x03) // 0b00000011 // Incremental read command
#define MCP3561_IREAD_COMMAND      (MCP3561_IREAD_COMMAND_MASK | MCP3561_DEVICE_ADDRESS_MASK)
#define MCP3561_SREAD_COMMAND_MASK (0x01) // 0b1 // Static read command
#define MCP3561_SREAD_DATA_COMMAND (MCP3561_SREAD_COMMAND_MASK | MCP3561_DEVICE_ADDRESS_MASK)

#define MCP3561_CONFIG0_ADDR             (0x01)
#define MCP3561_CONFIG0_WRITE            (MCP3561_CONFIG0_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_CONFIG0_SREAD            (MCP3561_CONFIG0_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_CONFIG0_IREAD            (MCP3561_CONFIG0_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define MCP3561_CONFIG0_CLK_SEL_MASK     (0x30) // 0b00110000
#define _MCP3561_CONFIG0_VREF_SEL_POS    (7)
#define MCP3561_CONFIG0_VREF_SEL_INT     (0x01 << _MCP3561_CONFIG0_VREF_SEL_POS)  // 0b01 << _CONFIG0_CLK_VREF_POS
#define MCP3561_CONFIG0_VREF_SEL_EXT     (0x00 << _MCP3561_CONFIG0_VREF_SEL_POS)  // 0b00 << _CONFIG0_CLK_VREF_POS
#define _MCP3561_CONFIG0_CLK_SEL_POS     (4)
#define MCP3561_CONFIG0_CLK_SEL_INT      (0x03 << _MCP3561_CONFIG0_CLK_SEL_POS)  // 0b11 << _CONFIG0_CLK_SEL_POS
#define MCP3561_CONFIG0_CLK_SEL_EXT      (0x00 << _MCP3561_CONFIG0_CLK_SEL_POS)  // 0b00 << _CONFIG0_CLK_SEL_POS
#define _MCP3561_CONFIG0_CS_SEL_POS      (2)
#define MCP3561_CONFIG0_CS_SEL_15uA      (0x03 << _MCP3561_CONFIG0_CS_SEL_POS)
#define MCP3561_CONFIG0_CS_SEL_3_7uA     (0x02 << _MCP3561_CONFIG0_CS_SEL_POS)
#define MCP3561_CONFIG0_CS_SEL_0_9uA     (0x01 << _MCP3561_CONFIG0_CS_SEL_POS)
#define MCP3561_CONFIG0_CS_SEL_NONE      (0x00 << _MCP3561_CONFIG0_CS_SEL_POS)
#define _MCP3561_CONFIG0_ADC_MODE_POS    (0)
#define MCP3561_CONFIG0_ADC_MODE_CONV    (0x03 << _MCP3561_CONFIG0_ADC_MODE_POS) // 0b11 << _CONFIG0_ADC_MODE_POS
#define MCP3561_CONFIG0_ADC_MODE_STANDBY (0x02 << _MCP3561_CONFIG0_ADC_MODE_POS)
#define MCP3561_CONFIG0_ADC_MODE_OFF     (0x00 << _MCP3561_CONFIG0_ADC_MODE_POS)

#define MCP3561_CONFIG1_ADDR       (0x02)
#define MCP3561_CONFIG1_WRITE      (MCP3561_CONFIG1_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_CONFIG1_SREAD      (MCP3561_CONFIG1_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_CONFIG1_IREAD      (MCP3561_CONFIG1_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define _MCP3561_CONFIG1_AMCLK_POS (6)
#define MCP3561_CONFIG1_AMCLK_DIV8 (0x03 << _MCP3561_CONFIG1_AMCLK_POS)
#define MCP3561_CONFIG1_AMCLK_DIV4 (0x02 << _MCP3561_CONFIG1_AMCLK_POS)
#define MCP3561_CONFIG1_AMCLK_DIV2 (0x01 << _MCP3561_CONFIG1_AMCLK_POS)
#define MCP3561_CONFIG1_AMCLK_DIV0 (0x00 << _MCP3561_CONFIG1_AMCLK_POS)
#define _MCP3561_CONFIG1_OSR_POS   (2)
#define MCP3561_CONFIG1_OSR_32     (0x00 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_64     (0x01 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_128    (0x02 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_256    (0x03 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_512    (0x04 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_1024   (0x05 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_2048   (0x06 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_4096   (0x07 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_8192   (0x08 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_16384  (0x09 << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_20480  (0x0A << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_24576  (0x0B << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_40960  (0x0C << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_49152  (0x0D << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_81920  (0x0E << _MCP3561_CONFIG1_OSR_POS)
#define MCP3561_CONFIG1_OSR_98304  (0x0F << _MCP3561_CONFIG1_OSR_POS)

#define MCP3561_CONFIG2_ADDR        (0x03)
#define MCP3561_CONFIG2_WRITE       (MCP3561_CONFIG2_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_CONFIG2_SREAD       (MCP3561_CONFIG2_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_CONFIG2_IREAD       (MCP3561_CONFIG2_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define _MCP3561_CONFIG2_BOOST_POS  (6)
#define MCP3561_CONFIG2_BOOST_x2    (0x03 << _MCP3561_CONFIG2_BOOST_POS)
#define MCP3561_CONFIG2_BOOST_x1    (0x02 << _MCP3561_CONFIG2_BOOST_POS)
#define MCP3561_CONFIG2_BOOST_2DIV3 (0x01 << _MCP3561_CONFIG2_BOOST_POS)
#define MCP3561_CONFIG2_BOOST_DIV2  (0x00 << _MCP3561_CONFIG2_BOOST_POS)
#define _MCP3561_CONFIG2_GAIN_POS   (3)
#define MCP3561_CONFIG2_GAIN_x64    (0x07 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x32    (0x06 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x16    (0x05 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x8     (0x04 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x4     (0x03 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x2     (0x02 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_x1     (0x01 << _MCP3561_CONFIG2_GAIN_POS)
#define MCP3561_CONFIG2_GAIN_DIV3   (0x00 << _MCP3561_CONFIG2_GAIN_POS)
#define _MCP3561_CONFIG2_AZ_MUX_POS (2)
#define MCP3561_CONFIG2_AZ_MUX_ON   (0x01 << _MCP3561_CONFIG2_AZ_MUX_POS)
#define MCP3561_CONFIG2_AZ_MUX_OFF  (0x00 << _MCP3561_CONFIG2_AZ_MUX_POS)
#define _MCP3561_CONFIG2_AZ_REF_POS (1)
#define MCP3561_CONFIG2_AZ_REF_ON   (0x01 << _MCP3561_CONFIG2_AZ_REF_POS)
#define MCP3561_CONFIG2_AZ_REF_OFF  (0x00 << _MCP3561_CONFIG2_AZ_REF_POS)

#define MCP3561_CONFIG3_ADDR                       (0x04)
#define MCP3561_CONFIG3_WRITE                      (MCP3561_CONFIG3_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_CONFIG3_SREAD                      (MCP3561_CONFIG3_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_CONFIG3_IREAD                      (MCP3561_CONFIG3_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define _MCP3561_CONFIG3_CONV_MODE_POS             (6)
#define MCP3561_CONFIG3_CONV_MODE_CONTINUOUS       (0x03 << _MCP3561_CONFIG3_CONV_MODE_POS) // 0b11 << _CONFIG3_CONV_MODE_POS
#define MCP3561_CONFIG3_CONV_MODE_ONE_SHOT_STANDBY (0x02 << _MCP3561_CONFIG3_CONV_MODE_POS)
#define MCP3561_CONFIG3_CONV_MODE_ONE_SHOT_OFF     (0x00 << _MCP3561_CONFIG3_CONV_MODE_POS)
#define _MCP3561_CONFIG3_DATA_FORMAT_POS           (4)
#define MCP3561_CONFIG3_DATA_FORMAT_32BIT_CHID_SGN (0x03 << _MCP3561_CONFIG3_DATA_FORMAT_POS) // right justified data + channel ID + sign extension
#define MCP3561_CONFIG3_DATA_FORMAT_32BIT_SGN      (0x02 << _MCP3561_CONFIG3_DATA_FORMAT_POS) // right justified data + sign extension
#define MCP3561_CONFIG3_DATA_FORMAT_32BIT          (0x01 << _MCP3561_CONFIG3_DATA_FORMAT_POS) // left justified data
#define MCP3561_CONFIG3_DATA_FORMAT_24BIT          (0x00 << _MCP3561_CONFIG3_DATA_FORMAT_POS)
#define _MCP3561_CONFIG3_CRC_POS                   (3)
#define MCP3561_CONFIG3_CRC_FORMAT_32              (1 << _MCP3561_CONFIG3_CRC_POS)
#define MCP3561_CONFIG3_CRC_FORMAT_16              (0 << _MCP3561_CONFIG3_CRC_POS)
#define _MCP3561_CONFIG3_CRCCOM_POS                (2)
#define MCP3561_CONFIG3_CRCCOM_ON                  (1 << _MCP3561_CONFIG3_CRCCOM_POS)
#define MCP3561_CONFIG3_CRCCOM_OFF                 (0 << _MCP3561_CONFIG3_CRCCOM_POS)
#define _MCP3561_CONFIG3_OFFCAL_POS                (1)
#define MCP3561_CONFIG3_OFFCAL_ON                  (1 << _MCP3561_CONFIG3_OFFCAL_POS)
#define MCP3561_CONFIG3_OFFCAL_OFF                 (0 << _MCP3561_CONFIG3_OFFCAL_POS)
#define _MCP3561_CONFIG3_GAINCAL_POS               (0)
#define MCP3561_CONFIG3_GAINCAL_ON                 (1 << _MCP3561_CONFIG3_GAINCAL_POS)
#define MCP3561_CONFIG3_GAINCAL_OFF                (0 << _MCP3561_CONFIG3_GAINCAL_POS)

#define MCP3561_IRQ_ADDR            (0x05)
#define MCP3561_IRQ_WRITE           (MCP3561_IRQ_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_IRQ_SREAD           (MCP3561_IRQ_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_IRQ_IREAD           (MCP3561_IRQ_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define _MCP3561_IRQ_DR_POS         (6)
#define _MCP3561_IRQ_CRCCFG_POS     (5)
#define _MCP3561_IRQ_POR_POS        (4)
#define _MCP3561_IRQ_MODE_POS       (2)
#define MCP3561_IRQ_MODE_MDAT_HIGHZ (2 << _MCP3561_IRQ_MODE_POS)
#define MCP3561_IRQ_MODE_MDAT_HIGH  (3 << _MCP3561_IRQ_MODE_POS)
#define MCP3561_IRQ_MODE_IRQ_HIGHZ  (0 << _MCP3561_IRQ_MODE_POS)
#define MCP3561_IRQ_MODE_IRQ_HIGH   (1 << _MCP3561_IRQ_MODE_POS)
#define MCP3561_IRQ_FASTCMD_ON      (1 << 1)
#define MCP3561_IRQ_FASTCMD_OFF     (0 << 1)
#define MCP3561_IRQ_STP_ON          (1 << 0)
#define MCP3561_IRQ_STP_OFF         (0 << 0)

#define MCP3561_MUX_ADDR         (0x06)
#define MCP3561_MUX_WRITE        (MCP3561_MUX_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_MUX_SREAD        (MCP3561_MUX_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_MUX_IREAD        (MCP3561_MUX_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define MCP3561_MUX_CH_IntVcm    (0xf)
#define MCP3561_MUX_CH_IntTemp_M (0xe)
#define MCP3561_MUX_CH_IntTemp_P (0xd)
#define MCP3561_MUX_CH_REFIN_n   (0xc)
#define MCP3561_MUX_CH_REFIN_p   (0xb)
#define MCP3561_MUX_CH_AVDD      (0x9)
#define MCP3561_MUX_CH_AGND      (0x8)
#define MCP3561_MUX_CH7          (0x7)
#define MCP3561_MUX_CH6          (0x6)
#define MCP3561_MUX_CH5          (0x5)
#define MCP3561_MUX_CH4          (0x4)
#define MCP3561_MUX_CH3          (0x3)
#define MCP3561_MUX_CH2          (0x2)
#define MCP3561_MUX_CH1          (0x1)
#define MCP3561_MUX_CH0          (0x0)
#define _MCP3561_MUX_VIN_P_POS   (4)
#define _MCP3561_MUX_VIN_N_POS   (0)

#define MCP3561_SCAN_CH_Offset    (1 << 0xF)
#define MCP3561_SCAN_CH_IntVcm    (1 << 0xE)
#define MCP3561_SCAN_CH_AVDD      (1 << 0xD)
#define MCP3561_SCAN_CH_TEMP      (1 << 0xC)
#define MCP3561_SCAN_CH_DIFF_D    (1 << 0xB)
#define MCP3561_SCAN_CH_DIFF_C    (1 << 0xA)
#define MCP3561_SCAN_CH_DIFF_B    (1 << 0x9)
#define MCP3561_SCAN_CH_DIFF_A    (1 << 0x8)
#define MCP3561_SCAN_CH7          (1 << 0x7)
#define MCP3561_SCAN_CH6          (1 << 0x6)
#define MCP3561_SCAN_CH5          (1 << 0x5)
#define MCP3561_SCAN_CH4          (1 << 0x4)
#define MCP3561_SCAN_CH3          (1 << 0x3)
#define MCP3561_SCAN_CH2          (1 << 0x2)
#define MCP3561_SCAN_CH1          (1 << 0x1)
#define MCP3561_SCAN_CH0          (1 << 0x0)

#define MCP3561_SCAN_ADDR      (0x07)
#define MCP3561_SCAN_WRITE     (MCP3561_SCAN_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_SCAN_SREAD     (MCP3561_SCAN_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_SCAN_IREAD     (MCP3561_SCAN_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND
#define _MCP3561_SCAN_DLY_POS  (21)
#define MCP3561_SCAN_DLY_512   (0x07 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_256   (0x06 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_128   (0x05 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_64    (0x04 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_32    (0x03 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_16    (0x02 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_8     (0x01 << _MCP3561_SCAN_DLY_POS)
#define MCP3561_SCAN_DLY_NONE  (0x00 << _MCP3561_SCAN_DLY_POS)

#define MCP3561_TIMER_ADDR      (0x08)
#define MCP3561_TIMER_WRITE     (MCP3561_TIMER_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_TIMER_SREAD     (MCP3561_TIMER_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_TIMER_IREAD     (MCP3561_TIMER_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND

#define MCP3561_OFFSETCAL_ADDR  (0x09)
#define MCP3561_OFFSETCAL_WRITE (MCP3561_OFFSETCAL_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_OFFSETCAL_SREAD (MCP3561_OFFSETCAL_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_OFFSETCAL_IREAD (MCP3561_OFFSETCAL_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND

#define MCP3561_GAINCAL_ADDR    (0x0A)
#define MCP3561_GAINCAL_WRITE   (MCP3561_GAINCAL_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_GAINCAL_SREAD   (MCP3561_GAINCAL_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_GAINCAL_IREAD   (MCP3561_GAINCAL_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND

#define MCP3561_LOCK_ADDR       (0x0D)
#define MCP3561_LOCK_WRITE      (MCP3561_LOCK_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_LOCK_SREAD      (MCP3561_LOCK_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_LOCK_IREAD      (MCP3561_LOCK_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND

#define MCP3561_CRCCFG_ADDR     (0x0F)
#define MCP3561_CRCCFG_WRITE    (MCP3561_CRCCFG_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_WRITE_COMMAND
#define MCP3561_CRCCFG_SREAD    (MCP3561_CRCCFG_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_SREAD_DATA_COMMAND
#define MCP3561_CRCCFG_IREAD    (MCP3561_CRCCFG_ADDR << _MCP3561_COMMAND_ADDR_POS) | MCP3561_IREAD_COMMAND

// USEFUL FAST COMMANDS AND OTHER COMMANDS
// Resets the device registers to their default  values
/ MCP3561_DEVICE_ADDRESS_BYTE | 0b111000
#define DEVICE_RESET_COMMAND (0xE << _MCP3561_COMMAND_ADDR_POS)




#ifdef __cplusplus
}
#endif

#endif /* __MCP3564_H */



