/**
  ******************************************************************************
  * @file    DCMI/Camera/dcmi_ov9655.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    13-April-2012
  * @brief   This file includes the driver for OV9655 Camera module mounted on 
  *          STM322xG-EVAL board RevA and RevB.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "camera_api.h"
#include "dcmi_ov9655.h"

/** @addtogroup stm32f2xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup DCMI_Camera
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  TIMEOUT  2
#define Bank1_SRAM2_ADDR  ((uint32_t)0x64000000)  
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* QQVGA 160x120 */
static unsigned char OV9655_QQVGA[][2]=
{
  0x00, 0x00,
  0x01, 0x80,
  0x02, 0x80,
  0x03, 0x02,
  0x04, 0x03,
  0x09, 0x01,
  0x0b, 0x57,
  0x0e, 0x61,
  0x0f, 0x40,
  0x11, 0x01,
  0x12, 0x62,
  0x13, 0xc7,
  0x14, 0x3a,
  0x16, 0x24,
  0x17, 0x18,
  0x18, 0x04,
  0x19, 0x01,
  0x1a, 0x81,
  0x1e, 0x00,//0x20
  0x24, 0x3c,
  0x25, 0x36,
  0x26, 0x72,
  0x27, 0x08,
  0x28, 0x08,
  0x29, 0x15,
  0x2a, 0x00,
  0x2b, 0x00,
  0x2c, 0x08,
  0x32, 0xa4,
  0x33, 0x00,
  0x34, 0x3f,
  0x35, 0x00,
  0x36, 0x3a,
  0x38, 0x72,
  0x39, 0x57,
  0x3a, 0xcc,
  0x3b, 0x04,
  0x3d, 0x99,
  0x3e, 0x0e,
  0x3f, 0xc1,
  0x40, 0xc0,
  0x41, 0x41,
  0x42, 0xc0,
  0x43, 0x0a,
  0x44, 0xf0,
  0x45, 0x46,
  0x46, 0x62,
  0x47, 0x2a,
  0x48, 0x3c,
  0x4a, 0xfc,
  0x4b, 0xfc,
  0x4c, 0x7f,
  0x4d, 0x7f,
  0x4e, 0x7f,
  0x4f, 0x98,
  0x50, 0x98,
  0x51, 0x00,
  0x52, 0x28,
  0x53, 0x70,
  0x54, 0x98,
  0x58, 0x1a,
  0x59, 0x85,
  0x5a, 0xa9,
  0x5b, 0x64,
  0x5c, 0x84,
  0x5d, 0x53,
  0x5e, 0x0e,
  0x5f, 0xf0,
  0x60, 0xf0,
  0x61, 0xf0,
  0x62, 0x00,
  0x63, 0x00,
  0x64, 0x02,
  0x65, 0x20,
  0x66, 0x00,
  0x69, 0x0a,
  0x6b, 0x5a,
  0x6c, 0x04,
  0x6d, 0x55,
  0x6e, 0x00,
  0x6f, 0x9d,
  0x70, 0x21,
  0x71, 0x78,
  0x72, 0x22,
  0x73, 0x02,
  0x74, 0x10,
  0x75, 0x10,
  0x76, 0x01,
  0x77, 0x02,
  0x7A, 0x12,
  0x7B, 0x08,
  0x7C, 0x16,
  0x7D, 0x30,
  0x7E, 0x5e,
  0x7F, 0x72,
  0x80, 0x82,
  0x81, 0x8e,
  0x82, 0x9a,
  0x83, 0xa4,
  0x84, 0xac,
  0x85, 0xb8,
  0x86, 0xc3,
  0x87, 0xd6,
  0x88, 0xe6,
  0x89, 0xf2,
  0x8a, 0x24,
  0x8c, 0x80,
  0x90, 0x7d,
  0x91, 0x7b,
  0x9d, 0x02,
  0x9e, 0x02,
  0x9f, 0x7a,
  0xa0, 0x79,
  0xa1, 0x40,
  0xa4, 0x50,
  0xa5, 0x68,
  0xa6, 0x4a,
  0xa8, 0xc1,
  0xa9, 0xef,
  0xaa, 0x92,
  0xab, 0x04,
  0xac, 0x80,
  0xad, 0x80,
  0xae, 0x80,
  0xaf, 0x80,
  0xb2, 0xf2,
  0xb3, 0x20,
  0xb4, 0x20,
  0xb5, 0x00,
  0xb6, 0xaf,
  0xb6, 0xaf,
  0xbb, 0xae,
  0xbc, 0x7f,
  0xbd, 0x7f,
  0xbe, 0x7f,
  0xbf, 0x7f,
  0xbf, 0x7f,
  0xc0, 0xaa,
  0xc1, 0xc0,
  0xc2, 0x01,
  0xc3, 0x4e,
  0xc6, 0x05,
  0xc7, 0x82,
  0xc9, 0xe0,
  0xca, 0xe8,
  0xcb, 0xf0,
  0xcc, 0xd8,
  0xcd, 0x93,

  0x12, 0x63,
  0x40, 0x10,
  0x15, 0x08,
};

/* QVGA 360x240 */
static unsigned char OV9655_QVGA[][2]=
{
  0x00, 0x00,
  0x01, 0x80,
  0x02, 0x80,
  0x03, 0x02,
  0x04, 0x03,
  0x09, 0x01,
  0x0b, 0x57,
  0x0e, 0x61,
  0x0f, 0x40,
  0x11, 0x01,
  0x12, 0x62,
  0x13, 0xc7,
  0x14, 0x3a,
  0x16, 0x24,
  0x17, 0x18,
  0x18, 0x04,
  0x19, 0x01,
  0x1a, 0x81,
  0x1e, 0x00,
  0x24, 0x3c,
  0x25, 0x36,
  0x26, 0x72,
  0x27, 0x08,
  0x28, 0x08,
  0x29, 0x15,
  0x2a, 0x00,
  0x2b, 0x00,
  0x2c, 0x08,
  0x32, 0x12,
  0x33, 0x00,
  0x34, 0x3f,
  0x35, 0x00,
  0x36, 0x3a,
  0x38, 0x72,
  0x39, 0x57,
  0x3a, 0xcc,
  0x3b, 0x04,
  0x3d, 0x99,
  0x3e, 0x02,
  0x3f, 0xc1,
  0x40, 0xc0,
  0x41, 0x41,
  0x42, 0xc0,
  0x43, 0x0a,
  0x44, 0xf0,
  0x45, 0x46,
  0x46, 0x62,
  0x47, 0x2a,
  0x48, 0x3c,
  0x4a, 0xfc,
  0x4b, 0xfc,
  0x4c, 0x7f,
  0x4d, 0x7f,
  0x4e, 0x7f,
  0x4f, 0x98,
  0x50, 0x98,
  0x51, 0x00,
  0x52, 0x28,
  0x53, 0x70,
  0x54, 0x98,
  0x58, 0x1a,
  0x59, 0x85,
  0x5a, 0xa9,
  0x5b, 0x64,
  0x5c, 0x84,
  0x5d, 0x53,
  0x5e, 0x0e,
  0x5f, 0xf0,
  0x60, 0xf0,
  0x61, 0xf0,
  0x62, 0x00,
  0x63, 0x00,
  0x64, 0x02,
  0x65, 0x20,
  0x66, 0x00,
  0x69, 0x0a,
  0x6b, 0x5a,
  0x6c, 0x04,
  0x6d, 0x55,
  0x6e, 0x00,
  0x6f, 0x9d,
  0x70, 0x21,
  0x71, 0x78,
  0x72, 0x11,
  0x73, 0x01,
  0x74, 0x10,
  0x75, 0x10,
  0x76, 0x01,
  0x77, 0x02,
  0x7A, 0x12,
  0x7B, 0x08,
  0x7C, 0x16,
  0x7D, 0x30,
  0x7E, 0x5e,
  0x7F, 0x72,
  0x80, 0x82,
  0x81, 0x8e,
  0x82, 0x9a,
  0x83, 0xa4,
  0x84, 0xac,
  0x85, 0xb8,
  0x86, 0xc3,
  0x87, 0xd6,
  0x88, 0xe6,
  0x89, 0xf2,
  0x8a, 0x24,
  0x8c, 0x80,
  0x90, 0x7d,
  0x91, 0x7b,
  0x9d, 0x02,
  0x9e, 0x02,
  0x9f, 0x7a,
  0xa0, 0x79,
  0xa1, 0x40,
  0xa4, 0x50,
  0xa5, 0x68,
  0xa6, 0x4a,
  0xa8, 0xc1,
  0xa9, 0xef,
  0xaa, 0x92,
  0xab, 0x04,
  0xac, 0x80,
  0xad, 0x80,
  0xae, 0x80,
  0xaf, 0x80,
  0xb2, 0xf2,
  0xb3, 0x20,
  0xb4, 0x20,
  0xb5, 0x00,
  0xb6, 0xaf,
  0xb6, 0xaf,
  0xbb, 0xae,
  0xbc, 0x7f,
  0xbd, 0x7f,
  0xbe, 0x7f,
  0xbf, 0x7f,
  0xbf, 0x7f,
  0xc0, 0xaa,
  0xc1, 0xc0,
  0xc2, 0x01,
  0xc3, 0x4e,
  0xc6, 0x05,
  0xc7, 0x81,
  0xc9, 0xe0,
  0xca, 0xe8,
  0xcb, 0xf0,
  0xcc, 0xd8,
  0xcd, 0x93,

  0x12, 0x63,
  0x40, 0x10,
  0x15, 0x08,
};


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the hardware resources (I2C and GPIO) used to configure 
  *         the OV9655 camera.
  * @param  None
  * @retval None
  */
void OV9655_HW_Init(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef  I2C_InitStruct;

  /*** Configures the DCMI GPIOs to interface with the OV9655 camera module ***/
  /* Enable DCMI GPIOs clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOH |
                         RCC_AHB1Periph_GPIOI, ENABLE);

  /* Connect DCMI pins to AF13 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);

  GPIO_PinAFConfig(GPIOH, GPIO_PinSource8, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource9, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource12, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource14, GPIO_AF_DCMI);

  GPIO_PinAFConfig(GPIOI, GPIO_PinSource5, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource6, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource7, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource4, GPIO_AF_DCMI);
  
  /* DCMI GPIO configuration */
  /* D0..D4(PH9/10/11/12/14), HSYNC(PH8) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
                                GPIO_Pin_12 | GPIO_Pin_14| GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOH, &GPIO_InitStructure);

  /* D5..D7(PI4/6/7), VSYNC(PI5) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_5;
  GPIO_Init(GPIOI, &GPIO_InitStructure);

  /* PCLK(PA6) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /****** Configures the I2C1 used for OV9655 camera module configuration *****/
 /* I2C1 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

  /* GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 

  /* Connect I2C1 pins to AF4 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
  
  /* Configure I2C1 GPIOs */  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure I2C1 */
  /* I2C DeInit */
  I2C_DeInit(I2C1);
    
  /* Enable the I2C peripheral */
  I2C_Cmd(I2C1, ENABLE);
 
  /* Set the I2C structure parameters */
  I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStruct.I2C_OwnAddress1 = 0xFE;
  I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStruct.I2C_ClockSpeed = 30000;
  
  /* Initialize the I2C peripheral w/ selected parameters */
  I2C_Init(I2C1, &I2C_InitStruct);
}

/**
  * @brief  Resets the OV9655 camera.
  * @param  None
  * @retval None
  */
void OV9655_Reset(void)
{
  OV9655_WriteReg(OV9655_COM7, 0x80);
}

/**
  * @brief  Reads the OV9655 Manufacturer identifier.
  * @param  OV9655ID: pointer to the OV9655 Manufacturer identifier.
  * @retval None
  */
void OV9655_ReadID(OV9655_IDTypeDef* OV9655ID)
{
  OV9655ID->Manufacturer_ID1 = OV9655_ReadReg(OV9655_MIDH);
  OV9655ID->Manufacturer_ID2 = OV9655_ReadReg(OV9655_MIDL);
  OV9655ID->Version = OV9655_ReadReg(OV9655_VER);
  OV9655ID->PID = OV9655_ReadReg(OV9655_PID);
}

/**
  * @brief  Configures the DCMI/DMA to capture image from the OV9655 camera.
  * @param  ImageFormat: Image format BMP or JPEG
  * @param  BMPImageSize: BMP Image size  
  * @retval None
  */
void OV9655_Init(ImageFormat_TypeDef ImageFormat)
{
  DCMI_InitTypeDef DCMI_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;

  /*** Configures the DCMI to interface with the OV9655 camera module ***/
  /* Enable DCMI clock */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

  /* DCMI configuration */ 
  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
  DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
  DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
  DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;
  DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;

  /* Configures the DMA2 to transfer Data from DCMI */
  /* Enable DMA2 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  
  /* DMA2 Stream1 Configuration */
  DMA_DeInit(DMA2_Stream1);

  DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
  DMA_InitStructure.DMA_Memory0BaseAddr = FSMC_LCD_ADDRESS;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  switch(ImageFormat)
  {
    case BMP_QQVGA:
    {
      /* DCMI configuration */
      DCMI_Init(&DCMI_InitStructure);

      /* DMA2 IRQ channel Configuration */
      DMA_Init(DMA2_Stream1, &DMA_InitStructure);
      break;
    }
    case BMP_QVGA:
    {
      /* DCMI configuration */ 
      DCMI_Init(&DCMI_InitStructure);

      /* DMA2 IRQ channel Configuration */
      DMA_Init(DMA2_Stream1, &DMA_InitStructure); 
      break;
    }
    default:
    {
      /* DCMI configuration */ 
      DCMI_Init(&DCMI_InitStructure);

      /* DMA2 IRQ channel Configuration */
      DMA_Init(DMA2_Stream1, &DMA_InitStructure);
      break;
    }
  }    
}



void OV9655_InitSet()
{
    OV9655_WriteReg(0x12, 0x80);   /* com7 - SSCB reset */
	 Delay(3);
    OV9655_WriteReg(0x00, 0x00);   /* gain */
    OV9655_WriteReg(0x01, 0x80);   /* blue */
    OV9655_WriteReg(0x02, 0x80);   /* red */
    OV9655_WriteReg(0x03, 0x1b);   /* vref */
    OV9655_WriteReg(0x04, 0x03);   /* com1 - exposure low bits */
    OV9655_WriteReg(0x0b, 0x57);   /* ver */
    OV9655_WriteReg(0x0e, 0x61);   /* com5 */
    OV9655_WriteReg(0x0f, 0x42);   /* com6 */
    OV9655_WriteReg(0x11, 0x00);   /* clkrc */
    OV9655_WriteReg(0x12, 0x03);   /* com7 - 15fps VGA RGB */
    OV9655_WriteReg(0x13, 0xe7);//0xc7   /* com8 - everything (AGC, AWB and AEC) */
    OV9655_WriteReg(0x14, 0x28);//0x3a   /* com9 */
    OV9655_WriteReg(0x16, 0x24);   /* reg16 */
    OV9655_WriteReg(0x17, 0x1d);   /* hstart*/
    OV9655_WriteReg(0x18, 0xbd);   /* hstop */
    OV9655_WriteReg(0x19, 0x01);   /* vstrt */
    OV9655_WriteReg(0x1a, 0x81);   /* vstop*/
    OV9655_WriteReg(0x1e, 0x00);//0x00  /* mvfp */
    OV9655_WriteReg(0x24, 0x3c);   /* aew */
    OV9655_WriteReg(0x25, 0x36);   /* aeb */
    OV9655_WriteReg(0x26, 0x71);   /* vpt */
    OV9655_WriteReg(0x27, 0x08);   /* bbias */
    OV9655_WriteReg(0x28, 0x08);   /* gbbias */
    OV9655_WriteReg(0x29, 0x15);   /* gr com */
     OV9655_WriteReg(0x2a, 0x00);   /* exhch */
     OV9655_WriteReg(0x2b, 0x00);   /* exhcl */
     OV9655_WriteReg(0x2c, 0x08);   /* rbias */
     OV9655_WriteReg(0x32, 0xff);   /* href */
     OV9655_WriteReg(0x33, 0x00);   /* chlf */
     OV9655_WriteReg(0x34, 0x3f);   /* aref1 */
     OV9655_WriteReg(0x35, 0x00);   /* aref2 */
     OV9655_WriteReg(0x36, 0x3A);//0x3a   /* aref3 */
    OV9655_WriteReg(0x38, 0x72);   /* adc2 */
    OV9655_WriteReg(0x39, 0x57);   /* aref4 */
     OV9655_WriteReg(0x3a, 0xCC);//0xcc   /* tslb - yuyv */
     OV9655_WriteReg(0x3b, 0xc4);//0x04   /* com11 - night mode 1/4 frame rate */
     OV9655_WriteReg(0x3d, 0x99);   /* com13 */
     OV9655_WriteReg(0x3f, 0xc1);   /* edge */
     OV9655_WriteReg(0x40, 0xc0);   /* com15 */
     OV9655_WriteReg(0x41, 0x40); //0x41   /* com16 */
     OV9655_WriteReg(0x42, 0xc0);   /* com17 */
      OV9655_WriteReg(0x43, 0x0a);   /* rsvd */
      OV9655_WriteReg(0x44, 0xf0);
      OV9655_WriteReg(0x45, 0x46);
      OV9655_WriteReg(0x46, 0x62);
      
      
      OV9655_WriteReg(0x47, 0x2a);
      OV9655_WriteReg(0x48, 0x3c);
      OV9655_WriteReg(0x4a, 0xfc);
       OV9655_WriteReg(0x4b, 0xfc);
       OV9655_WriteReg(0x4c, 0x7f);
       OV9655_WriteReg(0x4d, 0x7f);
       OV9655_WriteReg(0x4e, 0x7f);
       OV9655_WriteReg(0x4f, 0x98);   /* matrix */
       OV9655_WriteReg(0x50, 0x98);
       OV9655_WriteReg(0x51, 0x00);
       OV9655_WriteReg(0x52, 0x28);
       OV9655_WriteReg(0x53, 0x70);
       OV9655_WriteReg(0x54, 0x98);
       OV9655_WriteReg(0x58, 0x1a);   /* matrix coef sign */
       OV9655_WriteReg(0x59, 0x85);   /* AWB control */
       OV9655_WriteReg(0x5a, 0xa9);
       OV9655_WriteReg(0x5b, 0x64);
       OV9655_WriteReg(0x5c, 0x84);
       OV9655_WriteReg(0x5d, 0x53);
       OV9655_WriteReg(0x5e, 0x0e);
       OV9655_WriteReg(0x5f, 0xf0);   /* AWB blue limit */
       OV9655_WriteReg(0x60, 0xf0);   /* AWB red limit */
       OV9655_WriteReg(0x61, 0xf0);   /* AWB green limit */
       OV9655_WriteReg(0x62, 0x00);   /* lcc1 */
       OV9655_WriteReg(0x63, 0x00);   /* lcc2 */
       OV9655_WriteReg(0x64, 0x02);   /* lcc3 */
       OV9655_WriteReg(0x65, 0x20);//0x20   /* lcc4 */
       OV9655_WriteReg(0x66, 0x00);//0x00   /* lcc5 */
       OV9655_WriteReg(0x69, 0x0A);//建议改成0x0a   /* hv */
       OV9655_WriteReg(0x6b, 0x5a);   /* dbvl */
       OV9655_WriteReg(0x6c, 0x04);
       OV9655_WriteReg(0x6d, 0x55);
       OV9655_WriteReg(0x6e, 0x00);
       OV9655_WriteReg(0x6f, 0x9d);
       OV9655_WriteReg(0x70, 0x21);   /* dnsth */
       OV9655_WriteReg(0x71, 0x78);
       OV9655_WriteReg(0x72, 0x00); //scale down  /* poidx */
       OV9655_WriteReg(0x73, 0x01);   /* pckdv */
       OV9655_WriteReg(0x74, 0x3a);//0x10   /* xindx */
       OV9655_WriteReg(0x75, 0x35);//0x10   /* yindx */
       OV9655_WriteReg(0x76, 0x01);
       OV9655_WriteReg(0x77, 0x02);
       OV9655_WriteReg(0x7a, 0x12);   /* gamma curve */
       OV9655_WriteReg(0x7b, 0x08);
       OV9655_WriteReg(0x7c, 0x16);
       OV9655_WriteReg(0x7d, 0x30);
       OV9655_WriteReg(0x7e, 0x5e);
       OV9655_WriteReg(0x7f, 0x72);
       OV9655_WriteReg(0x80, 0x82);
       OV9655_WriteReg(0x81, 0x8e);
       OV9655_WriteReg(0x82, 0x9a);
       OV9655_WriteReg(0x83, 0xa4);
       OV9655_WriteReg(0x84, 0xac);
       OV9655_WriteReg(0x85, 0xb8);
       OV9655_WriteReg(0x86, 0xc3);
       OV9655_WriteReg(0x87, 0xd6);
       OV9655_WriteReg(0x88, 0xe6);
       OV9655_WriteReg(0x89, 0xf2);
       OV9655_WriteReg(0x8a, 0x24);//0x24
       OV9655_WriteReg(0x8c, 0x80); //0x80  /* com19 */
       OV9655_WriteReg(0x14, 0x28);   /* com9 */
       OV9655_WriteReg(0x90, 0x7d);
       OV9655_WriteReg(0x91, 0x7b);
       OV9655_WriteReg(0x9d, 0x02);//0x02   /* lcc6 */
       OV9655_WriteReg(0x9e, 0x02);//0x02   /* lcc7 */
       OV9655_WriteReg(0x9f, 0x7a);
       OV9655_WriteReg(0xa0, 0x79);
       OV9655_WriteReg(0xa1, 0x40);   /* aechm */
       OV9655_WriteReg(0xa4, 0x50);   /* com21 */
       OV9655_WriteReg(0xa5, 0x68);   /* com26 */
       OV9655_WriteReg(0xa6, 0x4a);   /* AWB green */
       OV9655_WriteReg(0xa8, 0xc1);   /* refa8 */
       OV9655_WriteReg(0xa9, 0xef);   /* refa9 */
       OV9655_WriteReg(0xaa, 0x92);
       OV9655_WriteReg(0xab, 0x04);
       OV9655_WriteReg(0xac, 0x80);   /* black level control */
       OV9655_WriteReg(0xad, 0x80);
       OV9655_WriteReg(0xae, 0x80);
       OV9655_WriteReg(0xaf, 0x80);
       OV9655_WriteReg(0xb2, 0xf2);
       OV9655_WriteReg(0xb3, 0x20);
       OV9655_WriteReg(0xb4, 0x20);   /* ctrlb4 */
       OV9655_WriteReg(0xb5, 0x00);
       OV9655_WriteReg(0xb6, 0xaf);
       OV9655_WriteReg(0xbb, 0xae);
       OV9655_WriteReg(0xbc, 0x7f);   /* ADC channel offsets */
       OV9655_WriteReg(0xdb, 0x7f);
       OV9655_WriteReg(0xbe, 0x7f);
       OV9655_WriteReg(0xbf, 0x7f);
       OV9655_WriteReg(0xc0, 0xe2);//0xaa
       OV9655_WriteReg(0xc1, 0xc0);
       OV9655_WriteReg(0xc2, 0x01);
    
    OV9655_WriteReg(0xc3, 0x4e);
    OV9655_WriteReg(0xc6, 0x85);//0x05
    OV9655_WriteReg(0xc7, 0x81);//0x81 与之前某寄存器对应   /* com24 */
    OV9655_WriteReg(0xc9, 0xe0);
    OV9655_WriteReg(0xca, 0xe8);
    OV9655_WriteReg(0xcb, 0xf0);
    OV9655_WriteReg(0xcc, 0xd8);
    OV9655_WriteReg(0xcd, 0x93);//0x93
    
    
    
    
    //OV9655_WriteReg(0xff, 0x41);   /* read 41, write ff 00 */
    OV9655_WriteReg(0x41, 0x40);   /* com16 */
    OV9655_WriteReg(0xc5, 0x03);   /* 60 Hz banding filter */
    OV9655_WriteReg(0x6a, 0x02);   /* 50 Hz banding filter */
    
    /*vga初始化*/
    OV9655_WriteReg(0x12, 0x63);   /* com7 - 30fps VGA RGB */
    OV9655_WriteReg(0x36, 0xfa);   /* aref3 */
    OV9655_WriteReg(0x69, 0x0a);   /* hv */
    OV9655_WriteReg(0x8c, 0x89);   /* com22 */
    OV9655_WriteReg(0x14, 0x28);   /* com9 */
    OV9655_WriteReg(0x3e, 0x0c);
     OV9655_WriteReg(0x41, 0x40);   /* com16 */
    OV9655_WriteReg(0x72, 0x00);
    OV9655_WriteReg(0x73, 0x00);
    OV9655_WriteReg(0x74, 0x3a);
     OV9655_WriteReg(0x75, 0x35);
    OV9655_WriteReg(0x76, 0x01);
     OV9655_WriteReg(0xc7, 0x80);
    OV9655_WriteReg(0x03, 0x12);   /* vref */
    OV9655_WriteReg(0x17, 0x16);   /* hstart */
    OV9655_WriteReg(0x18, 0x02);   /* hstop */
    OV9655_WriteReg(0x19, 0x01);   /* vstrt */
    OV9655_WriteReg(0x1a, 0x3d);   /* vstop */
    OV9655_WriteReg(0x32, 0xff);   /* href */
    OV9655_WriteReg(0xc0, 0xaa);
}

/**
  * @brief  Configures the DCMI/DMA to capture image from the OV9655 camera.
  * @param  ImageFormat: Image format BMP or JPEG
  * @param  BMPImageSize: BMP Image size  
  * @retval None
  */
void OV9655_SinCapture(ImageFormat_TypeDef ImageFormat)
{
  DCMI_InitTypeDef DCMI_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;

  /*** Configures the DCMI to interface with the OV9655 camera module ***/
  /* Enable DCMI clock */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

  /* DCMI configuration */ 
  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot;
  DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
  DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
  DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;
  DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;

  /* Configures the DMA2 to transfer Data from DCMI */
  /* Enable DMA2 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  
  /* DMA2 Stream1 Configuration */
 DMA_DeInit(DMA2_Stream1);

  DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
  DMA_InitStructure.DMA_Memory0BaseAddr = Bank1_SRAM2_ADDR;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  
  
 


    /* DCMI configuration */
      DCMI_Init(&DCMI_InitStructure);

      /* DMA2 IRQ channel Configuration */
      DMA_Init(DMA2_Stream1, &DMA_InitStructure);
      
   
       
       
  switch(ImageFormat)
  {
    case BMP_QQVGA:
    {
      OV9655_QQVGAConfig();
      break;
    }
    case BMP_QVGA:
    {
     OV9655_QVGAConfig();
      break;
    }
   
    case BMP_VGA:
    {
     OV9655_VGAConfig();
      break;
    }
     case BMP_SXGA:
    {
       OV9655_SXGAConfig();
      break;
    }

    default:
    {
   
      break;
    }


  }    
}

/**
  * @brief  Configures the DCMI/DMA to capture image from the OV9655 camera.
  * @param  ImageFormat: Image format BMP or JPEG
  * @param  BMPImageSize: BMP Image size  
  * @retval None
  */
void OV9655_ZoomPreview(ImageFormat_TypeDef ImageFormat,uint8_t m)
{	
 	uint8_t temp = ImageFormat+m;
          if(temp <=3 && temp>=1)
 		{
  			OV9655_Init(ImageFormat);
                        DCMI_CROPInitTypeDef DCMI_CROPInitStructure;
			switch(temp)
			  {
			    case BMP_QQVGA:
			    {
			      	OV9655_QQVGAConfig();
				 	
			      break;
			    }
			    case BMP_QVGA:
			    {
			    	 OV9655_QVGAConfig();
                                 DCMI_CROPCmd(DISABLE);
					
			      break;
			    }
			   
			    case BMP_VGA:
			    {
			       	  OV9655_QVGAConfig();

					 // test_init();
					  test_vga();
					

					/*OV9655_WriteReg(0x72, 0x00);
					OV9655_WriteReg(0x73, 0x00);
					OV9655_WriteReg(0x36, 0xfa), 
					OV9655_WriteReg(0x3e, 0x0c);
					OV9655_WriteReg(0x41, 0x40);
					
					OV9655_WriteReg(0x74,0x3a);
					OV9655_WriteReg(0x75,0x35);
					OV9655_WriteReg(0x74,0x01);
					OV9655_WriteReg(0x75,0x01);
					OV9655_WriteReg(0xC7,0x81);

					OV9655_WriteReg(0X04,0X00);*/
					
					//OV9655_WriteReg(0x03, 0x02);   /* vref */
				        // OV9655_WriteReg(0x17, 0x18);   /* hstart */
					//OV9655_WriteReg(0x18, 0x04);   /* hstop */
					//OV9655_WriteReg(0x19, 0x01);   /* vstrt */
					//OV9655_WriteReg(0x1a, 0x81);   /* vstop */
					//OV9655_WriteReg(0x32, 0xff);   /* href */

                                       
				 	LCD_Clear(Black);
					DCMI_CROPInitStructure.DCMI_HorizontalOffsetCount = 0;
					DCMI_CROPInitStructure.DCMI_VerticalStartLine = 240;
					DCMI_CROPInitStructure.DCMI_CaptureCount = 639;
					DCMI_CROPInitStructure.DCMI_VerticalLineCount = 479;
                   /* DCMI_CROPInitStructure.DCMI_HorizontalOffsetCount = 0;
					DCMI_CROPInitStructure.DCMI_VerticalStartLine = 0;
					DCMI_CROPInitStructure.DCMI_CaptureCount = 640;
					DCMI_CROPInitStructure.DCMI_VerticalLineCount = 480;*/
					DCMI_CROPConfig(&DCMI_CROPInitStructure);
					//DCMI_CROPCmd(ENABLE);
                                        
                                        
                                     
			      break;
			    }
			     case BMP_SXGA:
			    {
			        OV9655_SXGAConfig();
				   	
					DCMI_CROPInitStructure.DCMI_HorizontalOffsetCount = 480 ; 
					DCMI_CROPInitStructure.DCMI_VerticalStartLine = 392;
					DCMI_CROPInitStructure.DCMI_CaptureCount = 320;
					DCMI_CROPInitStructure.DCMI_VerticalLineCount = 240;
					DCMI_CROPConfig(&DCMI_CROPInitStructure);
					DCMI_CROPCmd(ENABLE);
			      break;
			    }

			    default:
			    {
			   
			      break;
			    }
			}
			
 		}
  
}



/**
  * @brief  Configures the OV9655 camera in QQVGA mode.
  * @param  None
  * @retval None
  */
void OV9655_QQVGAConfig(void)
{
  uint32_t i;

  OV9655_Reset();
  Delay(200);

  /* Initialize OV9655 */
  for(i=0; i<(sizeof(OV9655_QQVGA)/2); i++)
  {
    OV9655_WriteReg(OV9655_QQVGA[i][0], OV9655_QQVGA[i][1]);
    Delay(2);
  }
}

/**
  * @brief  SConfigures the OV9655 camera in QVGA mode.
  * @param  None
  * @retval None
  */
void OV9655_QVGAConfig(void)
{
  uint32_t i;

  //OV9655_Reset();
  OV9655_WriteReg(OV9655_COM7, 0x80);
  //Delay(20);

  /* Initialize OV9655 */
  for(i=0; i<(sizeof(OV9655_QVGA)/2); i++)
  {
    OV9655_WriteReg(OV9655_QVGA[i][0], OV9655_QVGA[i][1]);
    //Delay(2);
  }
  
	OV9655_WriteReg(0x03, 0x12);   /* vref */
	OV9655_WriteReg(0x17, 0x16);   /* hstart */
	OV9655_WriteReg(0x18, 0x02);   /* hstop */
	OV9655_WriteReg(0x19, 0x01);   /* vstrt */
	OV9655_WriteReg(0x1a, 0x3d);   /* vstop */
	OV9655_WriteReg(0x32, 0xff);   /* href */
	
  

  
  
}

void test_init()
{
	//14.3fps
OV9655_WriteReg(0x12, 0x80);
OV9655_WriteReg(0xb5, 0x00);
OV9655_WriteReg(0x35, 0x00);
OV9655_WriteReg(0xa8, 0xc1);
OV9655_WriteReg(0x3a, 0x8c);    //0x80 to 0x8c, UYVY
OV9655_WriteReg(0x3d, 0x99);
OV9655_WriteReg(0x77, 0x02);
OV9655_WriteReg(0x13, 0xe7);
OV9655_WriteReg(0x26, 0x72);
OV9655_WriteReg(0x27, 0x08);
OV9655_WriteReg(0x28, 0x08);
OV9655_WriteReg(0x29, 0x15);
OV9655_WriteReg(0x2c, 0x08);
OV9655_WriteReg(0xab, 0x04);
OV9655_WriteReg(0x6e, 0x00);
OV9655_WriteReg(0x6d, 0x55);
OV9655_WriteReg(0x00, 0x32);
OV9655_WriteReg(0x10, 0x7b);
OV9655_WriteReg(0xbb, 0xae);
OV9655_WriteReg(0x72, 0x00);
OV9655_WriteReg(0x3e, 0x0c);
OV9655_WriteReg(0x74, 0x3a);
OV9655_WriteReg(0x76, 0x01);
OV9655_WriteReg(0x75, 0x35);
OV9655_WriteReg(0x73, 0x00);
OV9655_WriteReg(0xc7, 0x80);
OV9655_WriteReg(0xc3, 0x4e);
OV9655_WriteReg(0x33, 0x00);
OV9655_WriteReg(0xa4, 0x50);
OV9655_WriteReg(0xaa, 0x92);
OV9655_WriteReg(0xc2, 0x01);
OV9655_WriteReg(0xc1, 0xc8);
OV9655_WriteReg(0x1e, 0x04);
OV9655_WriteReg(0xa9, 0xef);
OV9655_WriteReg(0x0e, 0x61);
OV9655_WriteReg(0x39, 0x57);
OV9655_WriteReg(0x0f, 0x42);
OV9655_WriteReg(0x24, 0x3c);
OV9655_WriteReg(0x25, 0x36);
OV9655_WriteReg(0x12, 0x63);//0x62 to 0x63
OV9655_WriteReg(0x03, 0x12);
OV9655_WriteReg(0x32, 0xff);
OV9655_WriteReg(0x17, 0x16);
OV9655_WriteReg(0x18, 0x02);
OV9655_WriteReg(0x19, 0x01);
OV9655_WriteReg(0x1a, 0x3d);
OV9655_WriteReg(0x36, 0xfa);
OV9655_WriteReg(0x69, 0x0a);
OV9655_WriteReg(0x8c, 0x8d);
OV9655_WriteReg(0xc0, 0xaa);
OV9655_WriteReg(0x40, 0xc0);
OV9655_WriteReg(0xc6, 0x85);
OV9655_WriteReg(0xcb, 0xf0);
OV9655_WriteReg(0xcc, 0xd8);
OV9655_WriteReg(0x71, 0x78);
OV9655_WriteReg(0xa5, 0x68);
OV9655_WriteReg(0x6f, 0x9e);
OV9655_WriteReg(0x42, 0xc1);   //0xc0 to 0xc1, 50HZ banding filer
OV9655_WriteReg(0x3f, 0x82); 
OV9655_WriteReg(0x8a,0x23);
OV9655_WriteReg(0x14,0x18);   //0x1a to 0x18
OV9655_WriteReg(0x3b, 0x0c);
OV9655_WriteReg(0x2d, 0x00);
OV9655_WriteReg(0x2e, 0x00);
OV9655_WriteReg(0x34, 0x3d);
OV9655_WriteReg(0x41, 0x40);
OV9655_WriteReg(0xc9, 0xe0);
OV9655_WriteReg(0xca, 0xe8);
OV9655_WriteReg(0xcd, 0x93);
OV9655_WriteReg(0x7a, 0x20);
OV9655_WriteReg(0x7b, 0x1c);
OV9655_WriteReg(0x7c, 0x28);
OV9655_WriteReg(0x7d, 0x3c);
OV9655_WriteReg(0x7e, 0x5a);
OV9655_WriteReg(0x7f, 0x68);
OV9655_WriteReg(0x80, 0x76);
OV9655_WriteReg(0x81, 0x80);
OV9655_WriteReg(0x82, 0x88);
OV9655_WriteReg(0x83, 0x8f);
OV9655_WriteReg(0x84, 0x96);
OV9655_WriteReg(0x85, 0xa3);
OV9655_WriteReg(0x86, 0xaf);
OV9655_WriteReg(0x87, 0xc4);
OV9655_WriteReg(0x88, 0xd7);
OV9655_WriteReg(0x89, 0xe8);
OV9655_WriteReg(0x4f, 0x98);
OV9655_WriteReg(0x50, 0x98);
OV9655_WriteReg(0x51, 0x00);
OV9655_WriteReg(0x52, 0x28);
OV9655_WriteReg(0x53, 0x70);
OV9655_WriteReg(0x54, 0x98);
OV9655_WriteReg(0x58, 0x1a);
OV9655_WriteReg(0x90, 0x86);
OV9655_WriteReg(0x91, 0x84);
OV9655_WriteReg(0x9f, 0x75);
OV9655_WriteReg(0xa0, 0x73);
OV9655_WriteReg(0x16, 0x24);
OV9655_WriteReg(0x2a, 0x00);
OV9655_WriteReg(0x2b, 0x00);
OV9655_WriteReg(0xac, 0x80);
OV9655_WriteReg(0xad, 0x80);
OV9655_WriteReg(0xae, 0x80);
OV9655_WriteReg(0xaf, 0x80);
OV9655_WriteReg(0xb2, 0xf2);
OV9655_WriteReg(0xb3, 0x20);
OV9655_WriteReg(0xb4, 0x20);
OV9655_WriteReg(0xb6, 0xaf);
OV9655_WriteReg(0xb6, 0xaf);
OV9655_WriteReg(0x04, 0x03);
OV9655_WriteReg(0x05, 0x2b);
OV9655_WriteReg(0x06, 0x35);
OV9655_WriteReg(0x07, 0x36);
OV9655_WriteReg(0x08, 0x3b);
OV9655_WriteReg(0x2f, 0x35);
OV9655_WriteReg(0x4a, 0xea);
OV9655_WriteReg(0x4b, 0xe6);
OV9655_WriteReg(0x4c, 0xe6);
OV9655_WriteReg(0x4d, 0xe6);
OV9655_WriteReg(0x4e, 0xe6);
OV9655_WriteReg(0x70, 0x0b);
OV9655_WriteReg(0xa6, 0x40);
OV9655_WriteReg(0xbc, 0x04);
OV9655_WriteReg(0xbd, 0x01);
OV9655_WriteReg(0xbe, 0x03);
OV9655_WriteReg(0xbf, 0x01);
OV9655_WriteReg(0xbf, 0x01);
OV9655_WriteReg(0x43, 0x14);
OV9655_WriteReg(0x44, 0xf0);
OV9655_WriteReg(0x45, 0x46);
OV9655_WriteReg(0x46, 0x62);
OV9655_WriteReg(0x47, 0x2a);
OV9655_WriteReg(0x48, 0x3c);
OV9655_WriteReg(0x59, 0x85);
OV9655_WriteReg(0x5a, 0xa9);
OV9655_WriteReg(0x5b, 0x64);
OV9655_WriteReg(0x5c, 0x84);
OV9655_WriteReg(0x5d, 0x53);
OV9655_WriteReg(0x5e, 0x0e);
OV9655_WriteReg(0x6c, 0x0c);
OV9655_WriteReg(0x6d, 0x55);
OV9655_WriteReg(0x6e, 0x00);
OV9655_WriteReg(0x6f, 0x9e);
OV9655_WriteReg(0x62, 0x10);    //0x00 to 0x10
OV9655_WriteReg(0x63, 0xd0);    //0x00 to 0xd0
OV9655_WriteReg(0x64, 0x06);    //0x08 to 0x06
OV9655_WriteReg(0x65, 0x00);    //0x20 to 0x00
OV9655_WriteReg(0x66, 0x05);    
OV9655_WriteReg(0x9d, 0x06);    //0x08 to 0x06
OV9655_WriteReg(0x9e, 0x08);    //0x09 to 0x08
OV9655_WriteReg(0x29, 0x15);
OV9655_WriteReg(0xa9, 0xef);
OV9655_WriteReg(0x11, 0x00);

OV9655_WriteReg(0x6b, 0x5a);    //0x1a to 0x5a

OV9655_WriteReg(0x92, 0x18);
OV9655_WriteReg(0x93, 0x00);
OV9655_WriteReg(0xa2, 0x4a);    //0x4b to 0x4a
OV9655_WriteReg(0xa3, 0x3e);    //0x4b to 0x3e
OV9655_WriteReg(0x6a, 0x06);    //0x4b to 0x06
OV9655_WriteReg(0xc5, 0x07);    //add
OV9655_WriteReg(0x1e, 0x04);    //0x14 to 0x04, no flip/mirror
OV9655_WriteReg(0x55, 0x00);
OV9655_WriteReg(0x56, 0x40);
OV9655_WriteReg(0xc6, 0x05);
OV9655_WriteReg(0x24, 0x50);
OV9655_WriteReg(0x25, 0x48);
OV9655_WriteReg(0x26, 0x82);
}

void test_vga()
{
	OV9655_WriteReg(0x11, 0x01);  

OV9655_WriteReg(0x6b, 0x5a);    //0x1a to 0x5a
OV9655_WriteReg(0x72, 0x00);
OV9655_WriteReg(0x3e, 0x0c);
OV9655_WriteReg(0x74, 0x3a);
OV9655_WriteReg(0x75, 0x35);
OV9655_WriteReg(0x73, 0x00);
OV9655_WriteReg(0xc7, 0x80);

OV9655_WriteReg(0x12, 0x62);
OV9655_WriteReg(0x03, 0x12);
OV9655_WriteReg(0x32, 0xff);
OV9655_WriteReg(0x17, 0x16);
OV9655_WriteReg(0x18, 0x02);
OV9655_WriteReg(0x19, 0x01);
OV9655_WriteReg(0x1a, 0x3d);
OV9655_WriteReg(0x41, 0x40);

OV9655_WriteReg(0x36, 0xfa);
OV9655_WriteReg(0x69, 0x0a);
OV9655_WriteReg(0x8c, 0x8d);
OV9655_WriteReg(0xc0, 0xaa);
OV9655_WriteReg(0x92, 0x18);
OV9655_WriteReg(0x93, 0x00);
OV9655_WriteReg(0xa2, 0x4a);    //0x4b to 0x4a
OV9655_WriteReg(0xa3, 0x3e);    //0x4b to 0x3e
OV9655_WriteReg(0x6a, 0x06);    //0x4b to 0x06
OV9655_WriteReg(0xc5, 0x07);    //add
   
}
void test_qvga()
{
	OV9655_WriteReg(0x11, 0x01);

OV9655_WriteReg(0x6b, 0x5a);    //0x1a to 0x5a
   
OV9655_WriteReg(0x72, 0x11);    
OV9655_WriteReg(0x3e, 0x0e);   
OV9655_WriteReg(0x74, 0x10);    
OV9655_WriteReg(0x75, 0x10);    
OV9655_WriteReg(0x73, 0x01);    
OV9655_WriteReg(0xc7, 0x81);    

OV9655_WriteReg(0x12, 0x63);
OV9655_WriteReg(0x03, 0x02);
OV9655_WriteReg(0x32, 0x12);
OV9655_WriteReg(0x17, 0x18);
OV9655_WriteReg(0x18, 0x04);
OV9655_WriteReg(0x19, 0x01);
OV9655_WriteReg(0x1a, 0x81);
OV9655_WriteReg(0x41, 0x41);

OV9655_WriteReg(0x36, 0x3a);    
OV9655_WriteReg(0x69, 0x0a);
OV9655_WriteReg(0x8c, 0x80);   
OV9655_WriteReg(0xc0, 0xaa);
OV9655_WriteReg(0x92, 0x18);
OV9655_WriteReg(0x93, 0x00);
OV9655_WriteReg(0xa2, 0x4a);    
OV9655_WriteReg(0xa3, 0x3e);    
OV9655_WriteReg(0x6a, 0x06);    
OV9655_WriteReg(0xc5, 0x07);    
}
/**
  * @brief  SConfigures the OV9655 camera in VGA mode.
  * @param  None
  * @retval None
  */
void OV9655_VGAConfig(void)
{
  uint32_t i;
/*unsigned char OV9655_VGA[][2]=
{
//0x12,0x80,
0xb5,0x00,
0x35,0x00,
0xa8,0xc1,
0x3a,0x80,
0x3d,0x99,
0x77,0x02,
0x13,0xe7,
0x26,0x72,
0x27,0x08,
0x28,0x08,
0x29,0x15,
0x2c,0x08,
0xab,0x04,
0x6e,0x00,
0x6d,0x55,
0x00,0x32,
0x10,0x7b,
0xbb,0xae,
0x11,0x01,
0x72,0x00,
0x3e,0x0c,
0x74,0x3a,
0x76,0x01,
0x75,0x35,
0x73,0x00,
0xc7,0x80,

0xc3,0x4e,
0x33,0x00,
0xa4,0x50,
0xaa,0x92,
0xc2,0x01,
0xc1,0xc8,
0x1e,0x04,
0xa9,0xfa,
0x0e,0x61,
0x39,0x57,
0x0f,0x42,
0x24,0x3c,
0x25,0x36,
0x12,0x62,
0x03,0x12,
0x32,0xff,
0x17,0x16,
0x18,0x02,
0x19,0x01,
0x1a,0x3d,
0x36,0xfa,
0x69,0x0a,
0x8c,0x8d,
0xc0,0xaa,
0x40,0xc0,

0xc6,0x85,
0xcb,0xf0,
0xcc,0xd8,
0x71,0x78,
0xa5,0x68,
0x6f,0x9e,
0x42,0xc0,
0x3f,0x82,
0x8a,0x23,
0x14,0x3a,
0x3b,0xcc,
0x34,0x3d,
0x41,0x40,
0xc9,0xe0,
0xca,0xe8,
0xcd,0x93,
0x7a,0x20,
0x7b,0x1c,
0x7c,0x28,
0x7d,0x3c,
0x7e,0x5a,
0x7f,0x68,
0x80,0x76,
0x81,0x80,
0x82,0x88,
0x83,0x8f,
0x84,0x96,
0x85,0xa3,
0x86,0xaf,
0x87,0xc4,
0x88,0xd7,
0x89,0xe8,
0x4f,0x98,
0x50,0x98,
0x51,0x00,
0x52,0x28,
0x53,0x70,
0x54,0x98,
0x58,0x1a,
0x6b,0x5a,
0x90,0x86,
0x91,0x84,
0x9f,0x75,
0xa0,0x73,
0x16,0x24,
0x2a,0x00,
0x2b,0x00,


0xac,0x80,
0xad,0x80,
0xae,0x80,
0xaf,0x80,
0xb2,0xf2,
0xb3,0x20,
0xb4,0x20,
0xb6,0xaf,
0xb6,0xaf,
0x04,0x03,
0x05,0x2b,
0x06,0x35,
0x07,0x36,
0x08,0x3b,
0x2d,0xf4,
0x2e,0x01,
0x2f,0x35,
0x4a,0xea,
0x4b,0xe6,
0x4c,0xe6,
0x4d,0xe6,
0x4e,0xe6,
0x70,0x0b,
0xa6,0x40,
0xbc,0x04,
0xbd,0x01,
0xbe,0x03,
0xbf,0x01,
0xbf,0x01,

0x43,0x14,
0x44,0xf0,
0x45,0x46,
0x46,0x62,
0x47,0x2a,
0x48,0x3c,
0x59,0x85,
0x5a,0xa9,
0x5b,0x64,
0x5c,0x84,
0x5d,0x53,
0x5e,0xe,
0x6c,0x0c,
0x6d,0x55,
0x6e,0x0,
0x6f,0x9e,


0x62,0x0,
0x63,0x0,
0x64,0x2,
0x65,0x20,
0x66,0x1,
0x9d,0x2,
0x9e,0x2,


0x29,0x15,
0xa9,0xef


};*/



  /* Initialize OV9655 */
  //for(i=0; i<(sizeof(OV9655_VGA)/2); i++)
 // {
    //OV9655_WriteReg(OV9655_VGA[i][0], OV9655_VGA[i][1]);
  	OV9655_InitSet();

	OV9655_WriteReg(0x12, 0x63);   /* com7 - 30fps VGA RGB */
	OV9655_WriteReg(0x36, 0xfa);  /* aref3 */
	OV9655_WriteReg(0x69, 0x0a);   /* hv */
	OV9655_WriteReg(0x8c, 0x89);   /* com22 */
	OV9655_WriteReg(0x14, 0x28);   /* com9 */
	OV9655_WriteReg(0x3e, 0x0c);   /* com14 */
	OV9655_WriteReg(0x41, 0x40);   /* com16 */
	OV9655_WriteReg(0x72, 0x00);
	OV9655_WriteReg(0x73, 0x00);
	OV9655_WriteReg(0x74, 0x3a);
	OV9655_WriteReg(0x75, 0x35);
	OV9655_WriteReg(0x76, 0x01);
	OV9655_WriteReg(0xc7, 0x80);   /* com24 */
	OV9655_WriteReg(0x03, 0x12);   /* vref */
	OV9655_WriteReg(0x17, 0x16);   /* hstart */
	OV9655_WriteReg(0x18, 0x02);   /* hstop */
	OV9655_WriteReg(0x19, 0x01);   /* vstrt */
	OV9655_WriteReg(0x1a, 0x3d);   /* vstop */
	OV9655_WriteReg(0x32, 0xff);   /* href */
	OV9655_WriteReg(0xc0, 0xaa);
	 
 
    
  //}
  
  
 
}
/**
  * @brief  SConfigures the OV9655 camera in SXGA mode.
  * @param  None
  * @retval None
  */
void OV9655_SXGAConfig(void)
{
  uint32_t i;

unsigned char OV9655_SXGA[][2]=
{
  	0x12, 0x80,
	0x00, 0x00,
        0x01, 0x80,
	0x02, 0x80,
	0x03, 0x1b,
	0x04, 0x43,
	0x0b, 0x57,
	0x0e, 0x61,
	0x0f, 0x44,////40
	0x11, 0x08,///04 pclk=10M|05 pclk=8.33M|06 pclk=7.138M上可|07 pclk=6.25M|08 pclk=5.55M  good|
	0x12, 0x02,///09 pclk=5M|
	0x13, 0xc7,  // was e7 - turned banding filter off
	0x14, 0x3a,
	0x16, 0x24,
	0x17, 0x1d,
	0x18, 0xbd,
	0x19, 0x01,
	0x1a, 0x81,
	0x1e, 0x04,
	0x24, 0x3c,
	0x25, 0x36,
	0x26, 0x72,
	0x27, 0x08,
	0x28, 0x08,
	0x29, 0x15,
	0x2a, 0x00,
	0x2b, 0x00,
	0x2c, 0x08,
	0x32, 0xff,
	0x33, 0x00,
	0x34, 0x3d,///3d
	0x35, 0x00,
	0x36, 0xf8,///f8
	0x38, 0x72,
	0x39, 0x57,
	0x3a, 0x8c , // UYVY capture
	0x3b, 0x04,
	0x3d, 0x99,
	0x3e, 0x0c,
	0x3f, 0xc1,
	0x40, 0xc0,
	0x41, 0x00,
	0x42, 0xc0,
	0x43, 0x0a,
	0x44, 0xf0,
	0x45, 0x46,
	0x46, 0x62,
	0x47, 0x2a,
	0x48, 0x3c,
	0x4a, 0xfc,
	0x4b, 0xfc,
	0x4c, 0x7f,
	0x4d, 0x7f,
	0x4e, 0x7f,
	0x4f, 0x98,
	0x50, 0x98,
	0x51, 0x00,
	0x52, 0x28,
	0x53, 0x70,///88
	0x54, 0x98,///b0
	0x58, 0x1a,
	0x58, 0x1a,
	0x59, 0x85,
	0x5a, 0xa9,
	0x5b, 0x64,
	0x5c, 0x84,
	0x5d, 0x53,
	0x5e, 0x0e,
	0x5f, 0xf0,
	0x60, 0xf0,
	0x61, 0xf0,
	0x62, 0x00,
	0x63, 0x00,
	0x64, 0x02,
	0x65, 0x20,///16
	0x66, 0x00,
	0x69, 0x0a,
	0x6b, 0x5a,
	0x6c, 0x04,
	0x6d, 0x55,
	0x6e, 0x00,
	0x6f, 0x9d,
	0x70, 0x21,
	0x71, 0x78,
	0x72, 0x00,
	0x73, 0x00,
	0x74, 0x3a,
	0x75, 0x35,
	0x76, 0x01,
	0x77, 0x02,
	0x7A, 0x12,
	0x7B, 0x08,
	0x7C, 0x16,
	0x7D, 0x30,
	0x7E, 0x5e,
	0x7F, 0x72,
	0x80, 0x82,
	0x81, 0x8e,
	0x82, 0x9a,
	0x83, 0xa4,
	0x84, 0xac,
	0x85, 0xb8,
	0x86, 0xc3,
	0x87, 0xd6,
	0x88, 0xe6,
	0x89, 0xf2,

    0x8a, 0x24,///03
	0x8c, 0x8d,///0d
	0x90, 0x7d,
	0x91, 0x7b,
	0x9d, 0x02,///03
	0x9e, 0x02,///04
	0x9f, 0x7a,
	0xa0, 0x79,
	0xa1, 0x40, ///10  //  changes exposure time - default was 0x40
	0xa4, 0x50,
	0xa5, 0x68,
	0xa6, 0x4a,
	0xa8, 0xc1,
	0xa9, 0xef,
	0xaa, 0x92,
	0xab, 0x04,
	0xac, 0x80,
	0xad, 0x80,
	0xae, 0x80,
	0xaf, 0x80,
	0xb2, 0xf2,
	0xb3, 0x20,
	0xb4, 0x20,
	0xb5, 0x00,
	0xb6, 0xaf,
	0xbb, 0xae,
	0xbc, 0x7f,
	0xbd, 0x7f,
	0xbe, 0x7f,
	0xbf, 0x7f,
	0xc0, 0xaa,///e2
	0xc1, 0xc0,
	0xc2, 0x01,
	0xc3, 0x4e,
	0xc6, 0x05,
	0xc7, 0x80,
	0xc9, 0xe0,
	0xca, 0xe8,
	0xcb, 0xf0,
	0xcc, 0xd8,
	0xcd, 0x93
};
  OV9655_Reset();
  Delay(200);

  /* Initialize OV9655 */
  for(i=0; i<(sizeof(OV9655_SXGA)/2); i++)
  {
    OV9655_WriteReg(OV9655_SXGA[i][0], OV9655_SXGA[i][1]);
    Delay(2);
  }
}


/**
  * @brief  Configures the OV9655 camera brightness.
  * @param  Brightness: Brightness value, where Brightness can be: 
  *         positively (0x01 ~ 0x7F) and negatively (0x80 ~ 0xFF)
  * @retval None
  */
void OV9655_BrightnessConfig(uint8_t Brightness)
{
  OV9655_WriteReg(OV9655_BRTN, Brightness);
}

/**
  * @brief  Writes a byte at a specific Camera register
  * @param  Addr: OV9655 register address
  * @param  Data: data to be written to the specific register
  * @retval 0x00 if write operation is OK
  *         0xFF if timeout condition occured (device not connected or bus error).
  */
uint8_t OV9655_WriteReg(uint16_t Addr, uint8_t Data)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;
  
  /* Generate the Start Condition */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on I2C1 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
   
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(I2C1, OV9655_DEVICE_WRITE_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
 
  /* Send I2C1 location address LSB */
  I2C_SendData(I2C1, (uint8_t)(Addr));

  /* Test on I2C1 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
  
  /* Send Data */
  I2C_SendData(I2C1, Data);

  /* Test on I2C1 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }  
 
  /* Send I2C1 STOP Condition */
  I2C_GenerateSTOP(I2C1, ENABLE);
  
  /* If operation is OK, return 0 */
  return 0;
}

/**
  * @brief  Reads a byte from a specific Camera register
  * @param  Addr: OV9655 register address.
  * @retval data read from the specific register or 0xFF if timeout condition
  *         occured.
  */
uint8_t OV9655_ReadReg(uint16_t Addr)
{
  uint32_t timeout = DCMI_TIMEOUT_MAX;
  uint8_t Data = 0;

  /* Generate the Start Condition */
  I2C_GenerateSTART(I2C1, ENABLE);

  /* Test on I2C1 EV5 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
  
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(I2C1, OV9655_DEVICE_READ_ADDRESS, I2C_Direction_Transmitter);
 
  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }

  /* Send I2C1 location address LSB */
  I2C_SendData(I2C1, (uint8_t)(Addr));

  /* Test on I2C1 EV8 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  
  /* Clear AF flag if arised */
  I2C1->SR1 |= (uint16_t)0x0400;

  /* Generate the Start Condition */
  I2C_GenerateSTART(I2C1, ENABLE);
  
  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  } 
  
  /* Send DCMI selcted device slave Address for write */
  I2C_Send7bitAddress(I2C1, OV9655_DEVICE_READ_ADDRESS, I2C_Direction_Receiver);

  /* Test on I2C1 EV6 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }
 
  /* Prepare an NACK for the next data received */
  I2C_AcknowledgeConfig(I2C1, DISABLE);

  /* Test on I2C1 EV7 and clear it */
  timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
  {
    /* If the timeout delay is exeeded, exit with error code */
    if ((timeout--) == 0) return 0xFF;
  }

  /* Prepare Stop after receiving data */
  I2C_GenerateSTOP(I2C1, ENABLE);

  /* Receive the Data */
  Data = I2C_ReceiveData(I2C1);

  /* return the read data */
  return Data;
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
