#include "xspi.h"
#include "xgpio.h"
#include "xparameters.h"
#include "xil_printf.h"

XSpi Spi;
XGpio SW_GPIO;

/* NRF Write Register */
void NRF_WriteReg(u8 reg, u8 value)
{
    u8 TxBuf[2];
    u8 RxBuf[2];

    TxBuf[0] = 0x20 | reg;
    TxBuf[1] = value;

    XSpi_Transfer(&Spi, TxBuf, RxBuf, 2);
}

/* NRF Send Payload */
void NRF_SendByte(u8 data)
{
    u8 TxBuf[2];
    u8 RxBuf[2];

    TxBuf[0] = 0xA0; // W_TX_PAYLOAD
    TxBuf[1] = data;

    XSpi_Transfer(&Spi, TxBuf, RxBuf, 2);
}

int main()
{
    int Status;
    u32 sw;
    u32 prev_sw = 2;

    xil_printf("\r\n");
    xil_printf("===== NRF24 TX DEMO =====\r\n\r\n");

    /* SPI Init */
    Status = XSpi_Initialize(&Spi, XPAR_XSPI_0_DEVICE_ID);

    if(Status != XST_SUCCESS)
    {
        xil_printf("SPI Init Failed\r\n");
        while(1);
    }

    XSpi_SetOptions(&Spi,
                    XSP_MASTER_OPTION |
                    XSP_MANUAL_SSELECT_OPTION);

    XSpi_SetSlaveSelect(&Spi, 0x01);
    XSpi_Start(&Spi);
    XSpi_IntrGlobalDisable(&Spi);

    xil_printf("SPI Ready\r\n");

    /* NRF Configuration */
    NRF_WriteReg(0x00, 0x0A); // CONFIG
    NRF_WriteReg(0x01, 0x00); // EN_AA OFF
    NRF_WriteReg(0x02, 0x01); // EN_RXADDR
    NRF_WriteReg(0x05, 40);   // RF_CH = 2440 MHz
    NRF_WriteReg(0x06, 0x07); // RF_SETUP

    xil_printf("NRF Ready\r\n");

    /* Switch GPIO */
    Status = XGpio_Initialize(&SW_GPIO,
                              XPAR_AXI_GPIO_0_DEVICE_ID);

    if(Status != XST_SUCCESS)
    {
        xil_printf("SW GPIO Error\r\n");
        while(1);
    }

    XGpio_SetDataDirection(&SW_GPIO, 1, 1);

    xil_printf("SW GPIO Ready\r\n\r\n");

    while(1)
    {
        sw = XGpio_DiscreteRead(&SW_GPIO, 1);

        if(sw != prev_sw)
        {
            prev_sw = sw;

            if(sw == 0)
            {
                NRF_SendByte('0');

                xil_printf(
                    "SW=0 -> Transmitting Data = 0\r\n");

                xil_printf(
                    "Packet Sent : 0\r\n\r\n");
            }
            else
            {
                NRF_SendByte('1');

                xil_printf(
                    "SW=1 -> Transmitting Data = 1\r\n");

                xil_printf(
                    "Packet Sent : 1\r\n\r\n");
            }
        }

        for(volatile int i = 0; i < 1000000; i++);
    }

    return 0;
}
