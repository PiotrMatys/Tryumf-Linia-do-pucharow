#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// --- Konfiguracja pinów RS485 ---
#define RS485_DIR_DDR DDRD
#define RS485_DIR_PORT PORTD
#define PIN_DE PD6
#define PIN_RE PD7

#define RS485_TX_MODE()                                  \
    {                                                    \
        RS485_DIR_PORT |= (1 << PIN_DE) | (1 << PIN_RE); \
    }
#define RS485_RX_MODE()                                     \
    {                                                       \
        RS485_DIR_PORT &= ~((1 << PIN_DE) | (1 << PIN_RE)); \
    }

// --- Konfiguracja Modbus Delta ASDA-A2 ---
#define SLAVE_ID 127 // Wartość z parametru P3-00 (0x7F)

// --- Funkcja obliczania sumy kontrolnej CRC16 Modbus ---
unsigned int modbus_crc(unsigned char *buf, int len)
{
    unsigned int crc = 0xFFFF;
    for (int pos = 0; pos < len; pos++)
    {
        crc ^= (unsigned int)buf[pos];
        for (int i = 8; i != 0; i--)
        {
            if ((crc & 0x0001) != 0)
            {
                crc >>= 1;
                crc ^= 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

// --- Inicjalizacja UART1 dla ASDA-A2 (38400 bps, 8-E-1) ---
void UART1_init(void)
{
    // Konfiguracja pinów kierunku RS485
    RS485_DIR_DDR |= (1 << PIN_DE) | (1 << PIN_RE);
    RS485_RX_MODE();

    // ubrr = (16000000 / (16 * 38400)) - 1 = 25
    UBRR1H = 0;
    UBRR1L = 25;

    // Włączenie nadajnika (TX) i odbiornika (RX)
    UCSR1B = (1 << TXEN1) | (1 << RXEN1);

    // 8-E-1 : parzystość parzysta, 1 bit stopu, 8 bitów danych (P3-02 = 6)
    UCSR1C = (1 << UPM11) | (1 << UCSZ11) | (1 << UCSZ10);

    // Reset flagi TXC1
    UCSR1A = (1 << TXC1);
}

// --- Transmisja pojedynczego bajtu przez UART1 ---
void UART1_send(unsigned char data)
{
    while (!(UCSR1A & (1 << UDRE1)))
        ;
    UDR1 = data;
}

// --- Odbiór bajtu z timeoutem (ms) ---
unsigned char UART1_recv(unsigned char *data, uint16_t ms)
{
    uint32_t max = (uint32_t)ms * 4000;
    for (uint32_t i = 0; i < max; i++)
    {
        if (UCSR1A & (1 << RXC1))
        {
            *data = UDR1;
            return 1;
        }
    }
    return 0; // Timeout
}

// --- Wysyłanie ramki Modbus z CRC ---
void send_frame(unsigned char *frame, int len)
{
    unsigned int crc = modbus_crc(frame, len);
    frame[len] = crc & 0xFF;   // CRC Low
    frame[len + 1] = crc >> 8; // CRC High

    // Opróżnienie bufora odbiorczego przed wysłaniem
    while (UCSR1A & (1 << RXC1))
        (void)UDR1;

    RS485_TX_MODE();
    _delay_us(200);        // Czas stabilizacji sterownika RS485
    UCSR1A |= (1 << TXC1); // Reset flagi TXC1 przed wysłaniem

    for (int i = 0; i < len + 2; i++)
        UART1_send(frame[i]);

    // Czekaj aż ostatni bit fizycznie opuści pin TX
    while (!(UCSR1A & (1 << TXC1)))
        ;
    _delay_us(200);
    RS485_RX_MODE();
    _delay_us(200);
}

// --- Zapis parametru Delta ASDA-A2 (funkcja Modbus 0x06) ---
// group : numer grupy parametru (np. 0x05 dla P5-XX)
// index : numer parametru      (np. 0x07 dla P5-07)
// value : wartość do zapisania
unsigned char delta_write_param(unsigned char group, unsigned char index, unsigned int value)
{
    unsigned char frame[8], resp[8];
    unsigned char n = 0;

    frame[0] = SLAVE_ID;
    frame[1] = 0x06;           // Funkcja: zapis pojedynczego rejestru
    frame[2] = group;          // Starszy bajt adresu
    frame[3] = index;          // Młodszy bajt adresu
    frame[4] = (value >> 8);   // Wartość High
    frame[5] = (value & 0xFF); // Wartość Low

    send_frame(frame, 6);

    // Odbiór potwierdzenia (8 bajtów)
    for (int i = 0; i < 8; i++)
    {
        if (UART1_recv(&resp[i], 100))
            n++;
        else
            break;
    }
    return (n == 8) ? 1 : 0;
}

// --- Odczyt parametru Delta ASDA-A2 (funkcja Modbus 0x03) ---
// group  : numer grupy parametru
// index  : numer parametru
// result : wskaźnik na zmienną wynikową (wartość odczytana)
// Zwraca 1 jeśli sukces, 0 jeśli timeout
unsigned char delta_read_param(unsigned char group, unsigned char index, unsigned int *result)
{
    unsigned char frame[8], resp[7];
    unsigned char n = 0;

    frame[0] = SLAVE_ID;
    frame[1] = 0x03;  // Funkcja: odczyt rejestrów
    frame[2] = group; // Starszy bajt adresu
    frame[3] = index; // Młodszy bajt adresu
    frame[4] = 0x00;
    frame[5] = 0x01; // Liczba rejestrów do odczytu: 1

    send_frame(frame, 6);

    // Odbiór odpowiedzi (7 bajtów)
    for (int i = 0; i < 7; i++)
    {
        if (UART1_recv(&resp[i], 100))
            n++;
        else
            break;
    }

    if (n < 7)
        return 0; // Timeout

    *result = (resp[3] << 8) | resp[4]; // Wartość w bajtach 3 i 4
    return 1;
}

int main(void)
{
    UART1_init();
    _delay_ms(500); // Pauza stabilizacyjna po starcie

    while (1)
    {
        // Przykład zapisu: wartość 1000 do rejestru P5-07
        delta_write_param(0x05, 0x07, 1000);
        _delay_ms(2000);

        // Przykład zapisu: wartość 0 do rejestru P5-00
        delta_write_param(0x05, 0x00, 0);
        _delay_ms(2000);

        // Przykład odczytu: odczyt wartości z rejestru P5-07
        unsigned int val = 0;
        if (delta_read_param(0x05, 0x07, &val))
        {
            // Odczyt zakończony sukcesem, val zawiera wartość rejestru
            (void)val;
        }
        _delay_ms(2000);
    }
}