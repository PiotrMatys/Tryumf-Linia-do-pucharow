/*****************************************************
Project : ATmega128 + RS485 + Modbus (Delta ASDA-A2)
Clock   : 16 MHz
UART1   : 38400, 8-E-1
*****************************************************/

#include <mega128.h>
#include <delay.h>

// --- Konfiguracja pinów RS485 ---
#define RS485_DIR_DDR  DDRD
#define RS485_DIR_PORT PORTD
#define PIN_DE 6
#define PIN_RE 7

#define RS485_TX_MODE()  { RS485_DIR_PORT |= (1<<PIN_DE) | (1<<PIN_RE); }
#define RS485_RX_MODE()  { RS485_DIR_PORT &= ~((1<<PIN_DE) | (1<<PIN_RE)); }

// --- Konfiguracja Modbus ---
#define SLAVE_ID 127

// --- CRC16 Modbus ---
unsigned int modbus_crc(unsigned char *buf, int len)
{
    unsigned int crc = 0xFFFF;
    int pos, i;

    for (pos = 0; pos < len; pos++)
    {
        crc ^= (unsigned int)buf[pos];

        for (i = 0; i < 8; i++)
        {
            if (crc & 0x0001)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
                crc >>= 1;
        }
    }
    return crc;
}

// --- Inicjalizacja UART1 ---
void UART1_init(void)
{
    // RS485 piny jako wyjœcia
    RS485_DIR_DDR |= (1<<PIN_DE) | (1<<PIN_RE);
    RS485_RX_MODE();

    // 38400 przy 16 MHz › UBRR = 25
    UBRR1H = 0x00;
    UBRR1L = 25;

    // TX + RX enable
    UCSR1B = (1<<TXEN1) | (1<<RXEN1);

    // 8-E-1
    UCSR1C = (1<<UPM11) | (1<<UCSZ11) | (1<<UCSZ10);

    // skasuj flagê TXC1
    UCSR1A |= (1<<TXC1);
}

// --- Wyœlij bajt ---
void UART1_send(unsigned char data)
{
    while (!(UCSR1A & (1<<UDRE1)));
    UDR1 = data;
}

// --- Odbiór z timeout (ms) ---
unsigned char UART1_recv(unsigned char *data, unsigned int ms)
{
    unsigned long max = (unsigned long)ms * 4000UL;
    unsigned long i;

    for (i = 0; i < max; i++)
    {
        if (UCSR1A & (1<<RXC1))
        {
            *data = UDR1;
            return 1;
        }
    }
    return 0;
}

// --- Wysy³anie ramki ---
void send_frame(unsigned char *frame, int len)
{
    unsigned int crc;
    int i;

    crc = modbus_crc(frame, len);
    frame[len]   = crc & 0xFF;
    frame[len+1] = crc >> 8;

    // Opró¿nij RX
    while (UCSR1A & (1<<RXC1))
        (void)UDR1;

    RS485_TX_MODE();
    delay_us(200);

    UCSR1A |= (1<<TXC1);

    for (i = 0; i < len+2; i++)
        UART1_send(frame[i]);

    while (!(UCSR1A & (1<<TXC1)));
    delay_us(200);

    RS485_RX_MODE();
    delay_us(200);
}

// --- Zapis parametru (0x06) ---
unsigned char delta_write_param(unsigned char group,
                                unsigned char index,
                                unsigned int value)
{
    unsigned char frame[8], resp[8];
    unsigned char n = 0;
    int i;

    frame[0] = SLAVE_ID;
    frame[1] = 0x06;
    frame[2] = group;
    frame[3] = index;
    frame[4] = value >> 8;
    frame[5] = value & 0xFF;

    send_frame(frame, 6);

    for (i = 0; i < 8; i++)
    {
        if (UART1_recv(&resp[i], 100))
            n++;
        else
            break;
    }

    return (n == 8);
}

// --- Odczyt parametru (0x03) ---
unsigned char delta_read_param(unsigned char group,
                               unsigned char index,
                               unsigned int *result)
{
    unsigned char frame[8], resp[7];
    unsigned char n = 0;
    int i;

    frame[0] = SLAVE_ID;
    frame[1] = 0x03;
    frame[2] = group;
    frame[3] = index;
    frame[4] = 0x00;
    frame[5] = 0x01;

    send_frame(frame, 6);

    for (i = 0; i < 7; i++)
    {
        if (UART1_recv(&resp[i], 100))
            n++;
        else
            break;
    }

    if (n < 7)
        return 0;

    *result = ((unsigned int)resp[3] << 8) | resp[4];
    return 1;
}

// --- MAIN ---
void main(void)
{
    unsigned int val;

    UART1_init();
    delay_ms(500);

    while (1)
    {
        delta_write_param(0x05, 0x07, 1000);
        delay_ms(2000);

        delta_write_param(0x05, 0x00, 0);
        delay_ms(2000);

        if (delta_read_param(0x05, 0x07, &val))
        {
            // val zawiera odczytan¹ wartoœæ
        }

        delay_ms(2000);
    }
}