/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
� Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 2016-11-18
Author  : 
Company : 
Comments: 


Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 16,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*****************************************************/

#include <io.h>
//#include <avr/io.h>

// Declare your global variables here

#define DATA_REGISTER_EMPTY (1<<UDRE0)
#define RX_COMPLETE (1<<RXC0)
#define FRAMING_ERROR (1<<FE0)
#define PARITY_ERROR (1<<UPE0)
#define DATA_OVERRUN (1<<DOR0)

// --- Konfiguracja Modbus ---
#define SLAVE_ID 0x01 //127
#define SLAVE_PI_ID 2     // ID Modbus Raspberry (Delta = 1, Pi = 2)
#define F_CPU 16000000UL
#define BAUD 38400
#define MYUBRR (F_CPU / 16UL / BAUD - 1)


// Get a character from the USART1 Receiver
#pragma used+
char getchar1(void)
{
unsigned char status;
char data;
while (1)
      {
      while (((status=UCSR1A) & RX_COMPLETE)==0);
      data=UDR1;
      if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
         return data;
      }
}
#pragma used-

// Write a character to the USART1 Transmitter
#pragma used+
void putchar1(char c)
{
while ((UCSR1A & DATA_REGISTER_EMPTY)==0);
UDR1=c;
}
#pragma used-



#include <stdio.h>
#include <mega128.h>
#include <delay.h>
//#include <alcd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// I2C Bus functions
#asm
   .equ __i2c_port=0x12 ;PORTD
   .equ __sda_bit=1
   .equ __scl_bit=0
#endasm
#include <i2c.h>

typedef union{
   struct{
      unsigned char b0:1;
      unsigned char b1:1;
      unsigned char b2:1;
      unsigned char b3:1;
      unsigned char b4:1;
      unsigned char b5:1;
      unsigned char b6:1;
      unsigned char b7:1;      
   }bits;
   unsigned char byte;
}BB;


BB PORT_F,PORTGG,PORTHH,PORTJJ,PORTKK;

int skonczony_proces[10];
int proces[10];
int monter_1_skonczyl,monter_2_skonczyl,monter_3_skonczyl,monterzy_skonczyli;
int start;
int licznik_pucharow;
int licznik;
int jest_pret_pod_czujnikami;
int czas_silnika_dokrecajacego_grzybki, czas_silnika_dokrecajacego_grzybki_stala;
int il_pretow_gwintowanych;
int dlugosc_preta_gwintowanego;
volatile long int sek0,sek1,sek2,sek3,sek4,sek5;
long int sek0_7s,sek1_7s,sek2_7s,sek3_7s;
long int czas_monterow,czas_na_transport_preta;
long int monter_1_time, monter_2_time, monter_3_time;
long int stala_czasowa;
int licznik_spoznien_monter_1,licznik_spoznien_monter_2, licznik_spoznien_monter_3;
int licznik_spoznien_monter_1_2, licznik_spoznien_monter_3_nowy;
int d,dd,gg,klej,klej_slave,monter_slave;
//char *dupa1;
//int i,ff;
int ff;
char z;
int grzybek;
int il_grzybkow,kontrola_grzybkow;
int licz;
int grzybek_biezacy_dokrecony;
int grzybek_dokrecony;
int oproznij_podajnik;
int metalowe_grzybki;
int zajechalem,sekwencja;
int pierwszy_raz;
int czas_monterow_stala;
int il_pretow_gwintowanych_stala;
int oczekiwanie_na_poprawienie;
int potw_zielonym_bo_pomyliles_pedal_z_potwierdz;
int czekaj_komunikat;
int przejechalem_czujnik_lub_jestem_na_nim;
int licznik_niezakreconych_grzybkow;
int grzybek_jest_nakrecony_na_precie;
int licznik_wylatujacych_grzybkow;
int licznik_wyzwolen_kurtyny;
int licznik_pucharow_global;
long int czas_zaloczonego_orientatora;
int zaloczono_kurtyne;
int anuluj_biezace_zlecenie;
int licznik_niewlozonych_pretow_z_grzybkiem;
int anuluj_biezace_zlecenie_const;
int msek_clock;
int sek_clock, min_clock, godz_clock;
int przez_sek_clock, przez_min_clock, przez_godz_clock;

int tryb_male_puchary;
int predkosc_wiezyczek_male_puchary;
int wynik_wyboru_male_puchary;
int wielkosc_kamienia;
int wielkosc_kamienia_duze_puchary;
int wielkosc_kamienia_duze_puchary_old;
int wiezyczka_prozniowa_global;
int na_pewno_przejechalem_grzebieniami_global;
int tryb_kontynuacji;



//int dupcia;
//int wynik;
//int wynik1;
//int oleole;


char sprawdz_pin0(BB PORT, int numer_pcf)
{
i2c_start();
i2c_write(numer_pcf);
PORT.byte = i2c_read(0);
i2c_stop();


return PORT.bits.b0; 
}

char sprawdz_pin1(BB PORT, int numer_pcf)
{
i2c_start();
i2c_write(numer_pcf);
PORT.byte = i2c_read(0);
i2c_stop();


return PORT.bits.b1; 
}

char sprawdz_pin2(BB PORT, int numer_pcf)
{
i2c_start();
i2c_write(numer_pcf);
PORT.byte = i2c_read(0);
i2c_stop();


return PORT.bits.b2; 
}


char sprawdz_pin3(BB PORT, int numer_pcf)
{
i2c_start();
i2c_write(numer_pcf);
PORT.byte = i2c_read(0);
i2c_stop();


return PORT.bits.b3; 
}

char sprawdz_pin4(BB PORT, int numer_pcf)
{
i2c_start();
i2c_write(numer_pcf);
PORT.byte = i2c_read(0);
i2c_stop();


return PORT.bits.b4; 
}

char sprawdz_pin5(BB PORT, int numer_pcf)
{
i2c_start();
i2c_write(numer_pcf);
PORT.byte = i2c_read(0);
i2c_stop();


return PORT.bits.b5; 
}

char sprawdz_pin6(BB PORT, int numer_pcf)
{
i2c_start();
i2c_write(numer_pcf);
PORT.byte = i2c_read(0);
i2c_stop();


return PORT.bits.b6; 
}

char sprawdz_pin7(BB PORT, int numer_pcf)
{
i2c_start();
i2c_write(numer_pcf);
PORT.byte = i2c_read(0);
i2c_stop();


return PORT.bits.b7; 
}


int odpytaj_parametr_panelu_duze_liczby(int adr1, int adr2)
{
int wynik = 0; 
int oleole = 0;

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(adr1);
putchar(adr2);  //adres zmiennej - 5010
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
oleole = getchar();
wynik = getchar();

if(oleole > 0)
        wynik = oleole * 255 + wynik + oleole;

return wynik;
}



int odpytaj_parametr_panelu(int adr1, int adr2)
{
int wynik = 0; 
int oleole = 0;

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(adr1);
putchar(adr2);  //adres zmiennej - 5010
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
oleole = getchar();
wynik = getchar();

if(oleole > 0)
        wynik = oleole * 255 + wynik + oleole;
     
return wynik;

}

////////////////////


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

// --- Envoyer octet ---
void UART1_send(unsigned char data)
{
    while (!(UCSR1A & (1<<UDRE1)));
    UDR1 = data;
}

// ============================================================
//   TELEMETRIA do Raspberry (async, NIE blokuje petli glownej)
// ============================================================
#define EVENT_MBX 200        // adres skrzynki zdarzen na Pi (= event_mailbox_addr)

// --- znacznik czasu: licznik tickow (1 tick = 16,384 ms, NIE zerowac) ---
volatile unsigned long mono_ticks = 0;     // inkrementowany w ISR Timer0

unsigned long czytaj_ticks(void)
{
    unsigned long t;
    unsigned char s = SREG;
    #asm("cli")
    t = mono_ticks;
    SREG = s;
    return t;
}

// --- bufor TX asynchronicznego (oprozniany przez przerwanie USART1_DRE) ---
#define TX_BUF_ROZMIAR 64                  // potega 2
volatile unsigned char txa_buf[TX_BUF_ROZMIAR];
volatile unsigned char txa_glowa = 0;      // zapis (petla glowna)
volatile unsigned char txa_ogon  = 0;      // odczyt (ISR)

interrupt [USART1_DRE] void usart1_dre_isr(void)
{
    if (txa_glowa != txa_ogon) {
        UDR1 = txa_buf[txa_ogon];
        txa_ogon = (txa_ogon + 1) & (TX_BUF_ROZMIAR - 1);
    } else {
        UCSR1B &= ~(1<<UDRIE1);            // pusto -> wylacz przerwanie
    }
}

unsigned char txa_wolne(void)
{
    return (TX_BUF_ROZMIAR - 1) - ((txa_glowa - txa_ogon) & (TX_BUF_ROZMIAR - 1));
}

// Wrzuca ramke zdarzenia + CRC do bufora async. NIE blokuje. 1=ok, 0=brak miejsca.
unsigned char wyslij_zdarzenie_async(unsigned int id, unsigned int value, unsigned long ts)
{
    unsigned char frame[15];
    unsigned int  crc;
    unsigned char i, s;

    if (txa_wolne() < 17) return 0;        // 15 + 2 CRC
    frame[0]=SLAVE_PI_ID; frame[1]=0x10;
    frame[2]=(EVENT_MBX>>8)&0xFF; frame[3]=EVENT_MBX&0xFF;
    frame[4]=0x00; frame[5]=0x04; frame[6]=0x08;
    frame[7]=(id>>8)&0xFF;    frame[8]=id&0xFF;
    frame[9]=(value>>8)&0xFF; frame[10]=value&0xFF;
    frame[11]=(ts>>24)&0xFF;  frame[12]=(ts>>16)&0xFF;
    frame[13]=(ts>>8)&0xFF;   frame[14]=ts&0xFF;
    crc = modbus_crc(frame, 15);
    for (i = 0; i < 15; i++) {
        txa_buf[txa_glowa] = frame[i];
        txa_glowa = (txa_glowa + 1) & (TX_BUF_ROZMIAR - 1);
    }
    txa_buf[txa_glowa] = crc & 0xFF; txa_glowa = (txa_glowa + 1) & (TX_BUF_ROZMIAR - 1);
    txa_buf[txa_glowa] = crc >> 8;   txa_glowa = (txa_glowa + 1) & (TX_BUF_ROZMIAR - 1);
    s = SREG;
    #asm("cli")
    UCSR1B |= (1<<UDRIE1);             // start nadawania w tle
    SREG = s;
    return 1;
}

// Wola send_frame PRZED ramka blokujaca: czeka az async TX skonczy, by go nie
// przerwac. Gdy nic nie czeka -> wychodzi natychmiast (zero kosztu).
void czekaj_na_async_tx(void)
{
    if (txa_glowa == txa_ogon) return;
    while (txa_glowa != txa_ogon);
    while (!(UCSR1A & (1<<TXC1)));
    delay_us(1000);                    // odstep RTU przed ramka blokujaca
}

// Envoi immediat (non bloquant).
unsigned char wyslij(unsigned int id, unsigned int value)
{
    return wyslij_zdarzenie_async(id, value, czytaj_ticks());
}

// --- lista zdarzen: {id, value, ts} ---
typedef struct { unsigned int id; unsigned int value; unsigned long ts; } zdarzenie_t;
#define LISTA_ROZMIAR 64
zdarzenie_t   lista[LISTA_ROZMIAR];
unsigned char lista_glowa = 0, lista_ogon = 0, lista_ile = 0;

unsigned char dodaj_do_listy(unsigned int id, unsigned int value)
{
    if (lista_ile >= LISTA_ROZMIAR) return 0;
    lista[lista_glowa].id    = id;
    lista[lista_glowa].value = value;
    lista[lista_glowa].ts    = czytaj_ticks();   // znacznik w chwili dodania
    lista_glowa = (lista_glowa + 1) & (LISTA_ROZMIAR - 1);
    lista_ile++;
    return 1;
}

// Wysyla liste NIEBLOKUJACO: tyle ile zmiesci sie w buforze TX, reszta pozniej.
void wyslij_liste(void)
{
    while (lista_ile > 0) {
        if (!wyslij_zdarzenie_async(lista[lista_ogon].id,
                                    lista[lista_ogon].value,
                                    lista[lista_ogon].ts))
            break;
        lista_ogon = (lista_ogon + 1) & (LISTA_ROZMIAR - 1);
        lista_ile--;
    }
}

// Dodaje do listy tylko gdy wartosc sie zmienila.
int mon_ostatnie[120];
void dodaj_jesli_zmiana(unsigned int id, int value)
{
    if (id < 120 && mon_ostatnie[id] != value) {
        mon_ostatnie[id] = value;
        dodaj_do_listy(id, (unsigned int)value);
    }
}

// ====== TU WYBIERASZ CO MONITOROWAC (id wg REGISTER_MAP.md) ======
void monitoruj_do_listy(void)
{
    dodaj_jesli_zmiana(10, sprawdz_pin0(PORTHH,0x73));   // czujnik_cisnienia
    dodaj_jesli_zmiana(40, PORTB.0);                     // przyklad: silownik
    dodaj_jesli_zmiana(100, licznik_pucharow);           // ilosc
    // ... dodaj wg potrzeb
}

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

// --- Envoyer trame (Version Sp�ciale Automatique) ---
void send_frame(unsigned char *frame, int len)
{
    unsigned int crc;
    int i;

    czekaj_na_async_tx();   // DODANE: nie zaczynaj ramki blokujacej w trakcie async TX
    crc = modbus_crc(frame, len);

    // IMPORTANT : On vide le flag TXC1 avant de commencer
    UCSR1A |= (1<<TXC1);

    // Envoi des donn�es (Pas de RS485_TX_MODE ici !)
    for (i = 0; i < len; i++)
        UART1_send(frame[i]);

    // Envoi du CRC
    UART1_send(crc & 0xFF);
    UART1_send(crc >> 8);

    // ATTENTE CRUCIALE : on attend que le dernier bit soit sorti
    // pour que l'adaptateur automatique puisse repasser en r�ception
    while (!(UCSR1A & (1<<TXC1)));
}

void delta_write_param(unsigned char group, unsigned char index, unsigned long value)
{
    unsigned char frame[11];
    frame[0]  = SLAVE_ID;
    frame[1]  = 0x10;
    frame[2]  = group;
    frame[3]  = index;
    frame[4]  = 0x00;
    frame[5]  = 0x02;
    frame[6]  = 0x04;
    // Low Word en premier, High Word en second
    frame[7]  = (value >> 8)  & 0xFF;   // Low Word High byte
    frame[8]  = (value)       & 0xFF;   // Low Word Low byte
    frame[9]  = (value >> 24) & 0xFF;   // High Word High byte
    frame[10] = (value >> 16) & 0xFF;   // High Word Low byte
    send_frame(frame, 11);
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


// Wysyla wartosc (int32) do rejestru 0 Raspberry (FC16, high_first) -> ekran.
void wyslij_ilosc_na_wyswietlacz(long int value)
{
    unsigned char frame[11];
    unsigned long u = (unsigned long)value;

    frame[0]  = SLAVE_PI_ID;
    frame[1]  = 0x10;                 // Write Multiple Registers
    frame[2]  = 0x00;  frame[3] = 0x00;   // rejestr 0
    frame[4]  = 0x00;  frame[5] = 0x02;   // 2 rejestry (int32)
    frame[6]  = 0x04;                     // 4 bajty
    frame[7]  = (u >> 24) & 0xFF;  frame[8]  = (u >> 16) & 0xFF;   // high word
    frame[9]  = (u >> 8)  & 0xFF;  frame[10] =  u        & 0xFF;   // low word
    send_frame(frame, 11);            // send_frame dolicza CRC
}

// Wysyla tylko, gdy ilosc sie zmienila (minimalny ruch na magistrali).
int ostatnia_wyslana_ilosc = -1;
void aktualizuj_wyswietlacz_ilosci(void)
{
    //if (licznik_pucharow != ostatnia_wyslana_ilosc)
    //{
    //    wyslij_ilosc_na_wyswietlacz((long int)licznik_pucharow);
    //    ostatnia_wyslana_ilosc = licznik_pucharow;
    //}
     
    //if (il_pretow_gwintowanych != ostatnia_wyslana_ilosc)
    //{
        wyslij_ilosc_na_wyswietlacz((long int)il_pretow_gwintowanych);
    //    ostatnia_wyslana_ilosc = il_pretow_gwintowanych;
    //}
        
}



void sterowanie_tasmociagami_monterow()
{
/*

if(sprawdz_pin0(PORTKK,0x79) == 0)
    PORTA.7 = 1;
else                //tasma 1
    PORTA.7 = 0;

if(sprawdz_pin1(PORTKK,0x79) == 0)
    PORTA.6 = 1;
else                //tasma 2
    PORTA.6 = 0;

*/
}

void zerowanie_czasu()
{
msek_clock = 0;
sek_clock = 0;
min_clock = 0;
godz_clock = 0;
}

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
sek0++;
sek1++;
sek2++;
sek3++;
sek4++;  //do nowego przenoszenia tasmociagu lanuchowego
sek5++;  //do orientatora grzybkow 

mono_ticks++;     // DODANE: znacznik czasu telemetrii (1 tick = 16,384 ms)
msek_clock++;
if(msek_clock == 60)
     {
     msek_clock = 0;
     sek_clock++;
     if(sek_clock == 60)
        {
        sek_clock = 0;
        min_clock++;
        if(min_clock == 60)
            {
            min_clock = 0;
            godz_clock++;
            }         
        }   
     }

//16 mhz = 
//co 1/16000s wykonywana jest operacja
//co 1/15,625 whodzi tam
//co 1024 jest 1s

}



void orientator_grzybkow()
{

if(sprawdz_pin1(PORTHH,0x73) == 1)
    {
    PORTA.4 = 1;
    sek5 = 0;   
    }
//if(PORTA.4 == 1 && sprawdz_pin1(PORTHH,0x73) == 0)
//    czas_zaloczonego_orientatora++;    
    
//if(sprawdz_pin1(PORTHH,0x73) == 0 & czas_zaloczonego_orientatora > 100000) //zmieniam z 10000
//    {
//    czas_zaloczonego_orientatora = 0;
//    PORTA.4 = 0;
//    grzybek = 0;
//    }

if(sprawdz_pin1(PORTHH,0x73) == 0 && sek5 > 7300)  //okolo 2 min
    {
    PORTA.4 = 0;
    sek5 = 0;   
    }

}


void inicjalizacja_orientator_grzybkow()
{
int g;
g = 0;


while(sprawdz_pin1(PORTHH,0x73) == 1)
   PORTA.4 = 1;
delay_ms(2000);
PORTA.4 = 0;

while(g<20)
    {
    if(sprawdz_pin1(PORTHH,0x73) == 1)
        {
        while(sprawdz_pin1(PORTHH,0x73) == 1)
            PORTA.4 = 1;
        delay_ms(2000);
        PORTA.4 = 0;
        }
    g++;
    }


 
il_grzybkow = 20;
}


void wylacz_maszyne()
{
putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    
putchar(0);    //00
putchar(48);   //adres zmiennej 30
putchar(0);    //00
putchar(0);   //0
}

int czekaj_na_guzik_start()
{
z = 0;
putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(0);
putchar(48);  //adres zmiennej - 30
putchar(1);
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
z = getchar();
//itoa(z,dupa1);       
//lcd_puts(dupa1);

return z;
}


void ustaw_na_nie_anulacje_zlecenia()
{
putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    //zmienie na anulowanie zlecenia
putchar(0);    //00
putchar(96);   //60
putchar(0);    //00
putchar(1);   //1
}

void kontrola_lampki_brak_pretow()
{
if(sprawdz_pin6(PORTHH,0x73) == 0)
    PORTA.7 = 0;
else
    PORTA.7 = 1;
}

int wyczysc_grzebienie()
{
int wynik;
wynik = 0;

//czyszczenie grzebieni zawsze na falowniku

switch(proces[1])
    {
    case 0:
        sek1_7s = 0;
        sek1 = 0;
        PORTA.5 = 0;
        proces[1] = 1;    
    break;
    
    case 1:
            if(sek1 > 100)
                {
                //if(sprawdz_pin3(PORTGG,0x71) == 0)
                if(sprawdz_pin4(PORTHH,0x73) == 0)
                    {
                    PORTB.7 = 0;  //zakoncz dociskanie preta
                    PORTA.0 = 1; //rozpcznij przeniesienie pret do nakladania kleju
                    }
                else
                    {
                    PORTA.0 = 1; //czujnik juz nie swieci, czyli jade dalej
                    sek1 = 0;
                    proces[1] = 2;
                    }
                } 
    break;
    case 2:
            //if(sprawdz_pin3(PORTGG,0x71) == 0)
            if(sprawdz_pin4(PORTHH,0x73) == 0)  //dojechalem znowu do czujnika
                {
                PORTA.0 = 0; //wylacz silnik (falownik)
                PORTA.5 = 0; //wylacz silnik (optoprzekaznik)
                proces[1] = 3;
                }
    break;
                       
    case 3:
                sek1 = 0;
                proces[1] = 0;
                wynik = 1;                                
    break;
    }

return wynik;
}

void wydaj_dzwiek()
{
licz++;
if(licz >= 100);
    {
    licz = 0;
    putchar(90);  //5A
    putchar(165); //A5
    putchar(3);//03
    putchar(128);  //80    //dzwiek
    putchar(2);    //02
    putchar(16);   //10
    }
}




void komunikat_1_na_panel()
{
putchar(90);
putchar(165);
putchar(35);       //ilosc liter 43 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("                                        ");

putchar(90);
putchar(165);
putchar(23);       //ilosc liter 20 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Inicjalizuje maszyne");
}

void komunikat_2_na_panel()
{
putchar(90);
putchar(165);
putchar(23);       //ilosc liter 20 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Wyczyszczono maszyne");
}

void komunikat_3_na_panel()
{
putchar(90);
putchar(165);
putchar(27);       //ilosc liter 20 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Maszyna zainicjalizowana");
}

void komunikat_4_na_panel()
{
putchar(90);
putchar(165);
putchar(28);       //ilosc liter 25 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Czekam na pret gwintowany");
}

void komunikat_5_na_panel()
{
putchar(90);
putchar(165);
putchar(35);       //ilosc liter 43 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("                                        ");

putchar(90);
putchar(165);
putchar(8);       //ilosc liter 5 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Praca");
}

void komunikat_6_na_panel()
{
putchar(90);
putchar(165);
putchar(27);       //ilosc liter 24 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("                        ");

putchar(90);
putchar(165);
putchar(38);       //ilosc liter 35 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Zakrecilem wszystkie zadane puchary");
}

void komunikat_7_na_panel()
{
putchar(90);
putchar(165);
putchar(34);       //ilosc liter 31 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Brak wymaganego cisnienia 6 bar");
}

void komunikat_8_na_panel(int i)
{
if(i == 0)
    {
    putchar(90);
    putchar(165);
    putchar(35);       //ilosc liter 32 + 3
    putchar(130);  //82
    putchar(0);    //0
    putchar(144);  //adres 70 - 112
    printf("Dozownik kleju pretow nie gotowy");
    }
if(i == 1)
    {
    putchar(90);
    putchar(165);
    putchar(37);       //ilosc liter 34 + 3
    putchar(130);  //82
    putchar(0);    //0
    putchar(144);  //adres 90 - 144
    printf("Dozownik kleju nakretek nie gotowy");
    }
}

void komunikat_9_na_panel()
{
putchar(90);
putchar(165);                    
putchar(37);       //ilosc liter 34 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Wylacz maszyne i poczekaj 1 minute");
}

void komunikat_10_na_panel()
{
putchar(90);
putchar(165);                    
putchar(28);       //ilosc liter 25 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Odslon i zresetuj kurtyne");
}

void komunikat_11_na_panel()
{
putchar(90);
putchar(165);                    
putchar(31);       //ilosc liter 28 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Monter 3 nie nacisnal pedala");
}

void komunikat_12_na_panel()
{
putchar(90);
putchar(165);                    
putchar(26);       //ilosc liter 23 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Czekam na ruch lancucha");
}

void komunikat_14_na_panel()
{
putchar(90);
putchar(165);                    
putchar(43);       //ilosc liter 40 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Popraw pret z grzybkiem i nacisnij guzik");
}

void komunikat_13_na_panel()
{
putchar(90);
putchar(165);                    
putchar(39);       //ilosc liter 36 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Usun pret ze szczek i nacisnij guzik");
}

void komunikat_15_na_panel()
{
putchar(90);
putchar(165);                    
putchar(52);       //ilosc liter 42 + 3  //49+3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Wymien lub nakrec/dokrec grzybek i nacisnij guzik");
}

void komunikat_16_na_panel()
{
putchar(90);
putchar(165);                    
putchar(42);       //ilosc liter 39 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Monter 3 - zdemontuj puchar i potwierdz");
}

void komunikat_17_na_panel()
{
putchar(90);
putchar(165);                    
putchar(44);       //ilosc liter 41 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Monter 3 - wyzwol recznie czujnik puchara");  //41
}


void komunikat_18_na_panel()
{
putchar(90);
putchar(165);                    
putchar(41);       //ilosc liter 38 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("SLAVE nie potwierdzil podania nakretki");  //41
}

void komunikat_19_na_panel()
{
putchar(90);
putchar(165);                    
putchar(46);       //ilosc liter 43 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("SLAVE nie potwierdzil zezwolenia na szczeki");  //43
}

void komunikat_20_na_panel()
{
putchar(90);
putchar(165);                    
putchar(46);       //ilosc liter 43 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Wez preta z grzebieni i nacisnij guzik bialy");  //43
}

void komunikat_21_panel()
{
putchar(90);
putchar(165);                    
putchar(46);       //ilosc liter 43 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Nie wykryto wiezyczki zielonej - zresetuj");  //43
}

void komunikat_22_panel()
{
putchar(90);
putchar(165);                    
putchar(46);       //ilosc liter 43 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Nie wykryto wiezyczki czerwonej - zresetuj");  //43
}


void komunikat_23_panel()
{
putchar(90);
putchar(165);                    
putchar(40);       //ilosc liter 37 + 3
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 90 - 144
printf("Podaj ilosc pucharow i nacisnij start");  //37
}



void komunikat_czysc_na_panel()
{
putchar(90);
putchar(165);
putchar(53); //38      //ilosc liter 50 + 3 //TU ZMIENIAM NORMALNIE SIE DODAJE??
putchar(130);  //82
putchar(0);    //0
putchar(144);  //adres 70 - 112
printf("                                                  ");


//putchar(90);
//putchar(165);
//putchar(68); //38      //ilosc liter 50 + 3 //TU ZMIENIAM NORMALNIE SIE DODAJE??
//putchar(130);  //82
//putchar(0);    //0
//putchar(144);  //adres 70 - 112
//printf("                                                                 ");


}

void przeslij_parametry_do_slave(char pomocnicza,char numer)
{                                                

int spr;

PORTE.7 = 1;//do komunikacji �adanie
putchar1(numer);  
putchar1(pomocnicza);
spr = getchar1();
if(spr == 3)
    PORTE.7 = 0;//do komunikacji koniec �adania
else
    {
    if(numer == 3)
        komunikat_18_na_panel();  //nie potwierdzil podania nakretki
    if(numer == 5)
        komunikat_19_na_panel();  //nie potwierdzil zezwolenia na szczeki
    PORTE.7 = 0;//do komunikacji koniec �adania    
    }
}




int odpytaj_czy_grzebienie_przez_falownik()
{
int obrot_przez_falownik = 0;
int obrot_przez_optoprzekaznik = 0;


putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(80);
putchar(128);  //adres zmiennej
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
obrot_przez_falownik = getchar();



if(obrot_przez_falownik == 1)
    {
    obrot_przez_optoprzekaznik = 0;
    PORTA.5 = 0; //obrot przez przekaznik
    }
else
    {
    obrot_przez_optoprzekaznik = 1;
    PORTA.0 = 0; //obrot przez falownik
    }


return obrot_przez_falownik; 
}


void odpytaj_dlugosc_preta()
{
putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(0);
putchar(64);  //adres zmiennej - 40
putchar(1);   //dlugosc preta gwintowanego
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
dlugosc_preta_gwintowanego = getchar();
if(dlugosc_preta_gwintowanego == 60)
    dlugosc_preta_gwintowanego = 61;
}


void odpytaj_parametry_z_panelu(int k)
{
char pomocnicza;
int hh;
int oleole;
oleole = 0;
z = 0;
pomocnicza = 0;

if(k == 1)
{
putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(0);
putchar(64);  //adres zmiennej - 40
putchar(1);   //dlugosc preta gwintowanego
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
dlugosc_preta_gwintowanego = getchar();
if(dlugosc_preta_gwintowanego == 60)
    dlugosc_preta_gwintowanego = 61;

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(16);
putchar(16);  //adres zmiennej - 1010
putchar(1);   //czy metalowe grzybki
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
hh = getchar();
if(hh == 0)
    metalowe_grzybki = 1;
else
    metalowe_grzybki = 0;

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(16);
putchar(32);  //adres zmiennej - 1020
putchar(1);   //czy oproznic podajnik grzybkow
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
hh = getchar();
if(hh == 0)
    oproznij_podajnik = 1;
else
    oproznij_podajnik = 0;
}

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(0);
putchar(80);  //adres zmiennej - 50
putchar(1);   //czas po jakim wylaczony silnik
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
czas_silnika_dokrecajacego_grzybki = getchar();

if(k == 1 | (k == 0 & il_pretow_gwintowanych > 4))
{
putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(0);
putchar(96);  //adres zmiennej - 60
putchar(1);     //odczyt czy anulowac zlecenie
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
hh = getchar();

if(hh == 0)
    anuluj_biezace_zlecenie = 1;
else
    anuluj_biezace_zlecenie = 0;



//czas_monterow = (long int)pomocnicza * stala_czasowa; 
czas_monterow = 7 * stala_czasowa;
}

if(pierwszy_raz == 0) 
    {
    //przeslij_parametry_do_slave(pomocnicza, 2);
    pierwszy_raz = 1;
    czas_monterow_stala = czas_monterow;
    }

if(czas_monterow_stala != czas_monterow)
   pierwszy_raz = 0; 

if(start == 0 & k == 1)
    {
    putchar(90);
    putchar(165);
    putchar(4);
    putchar(131);
    putchar(0);
    putchar(112);  //adres zmiennej - 70
    putchar(1);     //odczyt ilosci pucharow do zmontowania
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    getchar();
    oleole = getchar();
    il_pretow_gwintowanych = getchar();
    
    if(oleole > 0)
        il_pretow_gwintowanych = oleole * 255 + il_pretow_gwintowanych + oleole;

    
    
    il_pretow_gwintowanych_stala = il_pretow_gwintowanych;
    }


if(k == 1)
{
putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(32);
putchar(48);  //adres zmiennej - 2030
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
hh = getchar();
if(hh == 0)
    tryb_male_puchary = 1;
else
   tryb_male_puchary = 0;
}


putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(32);
putchar(64);  //adres zmiennej - 2040
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
predkosc_wiezyczek_male_puchary = getchar();



putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(32);
putchar(80);  //adres zmiennej - 2050
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
wielkosc_kamienia = getchar();   

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(32);
putchar(96);  //adres zmiennej - 20
putchar(1);   
getchar();                         //wielkosc kamienia duze puchary
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
wielkosc_kamienia_duze_puchary = getchar();   






if(tryb_male_puchary == 0)
     {
     switch(wielkosc_kamienia_duze_puchary)
     {
     case 125:
        wynik_wyboru_male_puchary = 3;
     break;
     
     case 120:
        wynik_wyboru_male_puchary = 4;
     break;
     
     case 115:
        wynik_wyboru_male_puchary = 5;
     break;
     
     case 110:
        wynik_wyboru_male_puchary = 6;
     break;
     
     case 105:
        wynik_wyboru_male_puchary = 7;
     break;
     
     case 100:
        wynik_wyboru_male_puchary = 8;
     break;
     
     case 95:
        wynik_wyboru_male_puchary = 9;
     break;
     
     case 90:
        wynik_wyboru_male_puchary = 24;
     break;
     
     case 85:
        wynik_wyboru_male_puchary = 25;
     break;
     
     case 80:
        wynik_wyboru_male_puchary = 26;
     break;
     
     case 75:
        wynik_wyboru_male_puchary = 27;
     break;
     
     case 70:
        wynik_wyboru_male_puchary = 28;
     break;
     
     case 65:
        wynik_wyboru_male_puchary = 29;
     break;
     
     case 60:
        wynik_wyboru_male_puchary = 30;
     break;
     
     case 55:
        wynik_wyboru_male_puchary = 31;
     break;
     
     case 50:
        wynik_wyboru_male_puchary = 32;
     break;
     
     }
     
     }




else
    {
    if(predkosc_wiezyczek_male_puchary == 1 & wielkosc_kamienia == 50)
       wynik_wyboru_male_puchary = 17;
    if(predkosc_wiezyczek_male_puchary == 1 & wielkosc_kamienia == 55)
       wynik_wyboru_male_puchary = 18;
    if(predkosc_wiezyczek_male_puchary == 1 & wielkosc_kamienia == 60)
       wynik_wyboru_male_puchary = 19;
    if(predkosc_wiezyczek_male_puchary == 1 & wielkosc_kamienia == 65)
       wynik_wyboru_male_puchary = 20;   
    if(predkosc_wiezyczek_male_puchary == 1 & wielkosc_kamienia == 70)
       wynik_wyboru_male_puchary = 21;   
    if(predkosc_wiezyczek_male_puchary == 1 & wielkosc_kamienia == 75)
       wynik_wyboru_male_puchary = 22;   
    
    
    if(predkosc_wiezyczek_male_puchary == 2 & wielkosc_kamienia == 50)
          wynik_wyboru_male_puchary = 11;
    if(predkosc_wiezyczek_male_puchary == 2 & wielkosc_kamienia == 55)
          wynik_wyboru_male_puchary = 12;
    if(predkosc_wiezyczek_male_puchary == 2 & wielkosc_kamienia == 60)
          wynik_wyboru_male_puchary = 13;
    if(predkosc_wiezyczek_male_puchary == 2 & wielkosc_kamienia == 65)
          wynik_wyboru_male_puchary = 14;
    if(predkosc_wiezyczek_male_puchary == 2 & wielkosc_kamienia == 70)
          wynik_wyboru_male_puchary = 15;
    if(predkosc_wiezyczek_male_puchary == 2 & wielkosc_kamienia == 75)
          wynik_wyboru_male_puchary = 16;
           
    }



}

void wartosci_wstepne_panelu()
{
putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    //dlugosc preta gwintowanego
putchar(0);    //00
putchar(64);   //40
putchar(0);    //00
putchar(dlugosc_preta_gwintowanego);   //80

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    //czas po jakim wylaczamy silnik
putchar(0);    //00
putchar(80);   //50
putchar(0);    //00
putchar(czas_silnika_dokrecajacego_grzybki);   

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    //zmienie na anulowanie zlecenia
putchar(0);    //00
putchar(96);   //60
putchar(0);    //00
putchar(1);   //1

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    //ilosc pucharow do zmontowania
putchar(0);    //00
putchar(112);   //70
putchar(0);    //00
putchar(5);   //5

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05                              0-tak
putchar(130);  //82    /Czy grzybki metalowe 1-nie
putchar(16);    //10
putchar(16);   //10
putchar(0);    //00
putchar(1);   //1

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05                              0-tak
putchar(130);  //82    /Czy oproznic podajnik grzybkow 1-nie
putchar(16);    //10
putchar(32);   //80
putchar(0);    //00
putchar(1);   //1

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05                              0-tak
putchar(130);  //82    /Czy tryb kontynuacji 1-nie
putchar(16);    //10
putchar(128);   //80
putchar(0);    //00
putchar(1);   //1

//tu obrabiam tryb male puchary pod adresem 2030

putchar(90);
putchar(165);
putchar(5);        
putchar(130);  //82
putchar(32);    //20
putchar(48);  //adres 30
putchar(0);    //00
putchar(1);   //1          Czy tryb male puchary 1-nie 0-tak


//tu obrabiam predkosc wiezyczek male puchary           

putchar(90);
putchar(165);
putchar(5);        
putchar(130);  //82
putchar(32);    //20
putchar(64);  //adres 40
putchar(0);    //00
putchar(2);   //1          predkosc wiezyczek male puchary 2-maks 1-min

//tu obrabiam wielkosc kamienia male puchary           

putchar(90);
putchar(165);
putchar(5);        
putchar(130);  //82
putchar(32);    //20
putchar(80);  //adres 50
putchar(0);    //00
putchar(50);   //   //50 55 60 65 70 75  


//tu obrabiam wielkosc kamienia duze_puchary           

putchar(90);
putchar(165);
putchar(5);        
putchar(130);  //82
putchar(32);    //20
putchar(96);  //adres 60
putchar(0);    //00
putchar(125);   //   //50 55 60 65 70 75  


//tu obrabiam tryb falownik lub bez falownika           

putchar(90);
putchar(165);
putchar(5);        
putchar(130);  //82
putchar(80);    //50
putchar(128);  //adres 
putchar(0);    //00
putchar(0);   //   //50 55 60 65 70 75  


//przyspieszenie lancuchowy
putchar(90);
putchar(165);
putchar(5);        
putchar(130);  //82
putchar(96);    //20
putchar(0);  //adres 60
putchar(0);    //00
putchar(150);   //   //50 55 60 65 70 75  


//predkosc lancuchowy
putchar(90);
putchar(165);
putchar(5);        
putchar(130);  //82
putchar(96);    //20
putchar(16);  //adres 60
putchar(0);    //00
putchar(155);   //   //50 55 60 65 70 75  



//opoznienie lancuchowy
putchar(90);
putchar(165);
putchar(5);        
putchar(130);  //82
putchar(96);    //20
putchar(32);  //adres 60
putchar(0);    //00
putchar(25);   //   //50 55 60 65 70 75  

}


void wyswietl_ilosc_zmontowanych_pucharow(int i,int j)
{
int gg,hh;

if(i>255)
    {
    gg = i/255;
    hh = i%255;
    }
else
    {
    gg = 0;
    hh = 0;
    }
    
putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    
putchar(0);    //00
putchar(128);   //80
putchar(gg);    //00
if(i>255)
    putchar(gg*255+hh);   //7
else
    if(i>=0)
        putchar(i);
    else
        putchar(0);
    
    
if(j>255)
    {
    gg = j/255;
    hh = j%255;
    }
else
    {
    gg = 0;
    hh = 0;
    }

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    
putchar(16);    //10      
putchar(64);   //40
putchar(gg);    //00
if(j>255)
    putchar(gg*255+hh);
else
    putchar(j);   //7  //j na razie bo mam problem z 255
}

void wyswietl_czas_procesu()
{
putchar(90);
putchar(165);
putchar(11);       //ilosc liter 8+3 
putchar(130);  //82
putchar(32);    //20
putchar(16);  //adres 10

if(sek_clock < 10)
    printf("0%d",sek_clock);
else
    printf("%d",sek_clock);
printf(":");

if(min_clock < 10)
    printf("0%d",min_clock);
else
    printf("%d",min_clock);
printf(":");

if(godz_clock < 10)
    printf("0%d",godz_clock);
else
    printf("%d",godz_clock);
}


void wyswietl_czas_przezbrojenia()
{
putchar(90);
putchar(165);
putchar(11);       //ilosc liter 8+3 
putchar(130);  //82
putchar(32);    //20
putchar(00);  //adres 10

if(sek_clock < 10)
    printf("0%d",sek_clock);
else
    printf("%d",sek_clock);
printf(":");

if(min_clock < 10)
    printf("0%d",min_clock);
else
    printf("%d",min_clock);
printf(":");

if(godz_clock < 10)
    printf("0%d",godz_clock);
else
    printf("%d",godz_clock);

}

void wyswietl_czas_laczny_przezbrajan()
{
putchar(90);
putchar(165);
putchar(11);       //ilosc liter 8+3 
putchar(130);  //82
putchar(16);    //10
putchar(144);  //adres 90

przez_sek_clock = przez_sek_clock + sek_clock;
if(przez_sek_clock > 60)
    {
    przez_sek_clock = przez_sek_clock - 60;
    przez_min_clock++;
    }
     
przez_min_clock = przez_min_clock + min_clock;
if(przez_min_clock > 60)
    {
    przez_min_clock = przez_min_clock - 60;
    przez_godz_clock++;
    }

przez_godz_clock = przez_godz_clock + godz_clock; 
if(przez_godz_clock > 60)
    {
    przez_godz_clock = przez_godz_clock - 60;
    przez_godz_clock = 0;
    }



if(przez_sek_clock < 10)
    printf("0%d",przez_sek_clock);
else
    printf("%d",przez_sek_clock);
printf(":");

if(przez_min_clock < 10)
    printf("0%d",przez_min_clock);
else
    printf("%d",przez_min_clock);
printf(":");

if(przez_godz_clock < 10)
    printf("0%d",przez_godz_clock);
else
    printf("%d",przez_godz_clock);
}

void wyswietl_parametry(int i,int j,int k,int l, int m, int n)
{
int gg,hh;

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    
putchar(0);    //00
putchar(16);   //10
putchar(0);    //00
//if(i>=0)
    putchar(i);   //
//else
//    putchar(i);
    
putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    
putchar(0);    //00
putchar(32);   //20
putchar(0);    //00
//if(j>=0)
    putchar(j);   //
//else
//    putchar(0);

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    
putchar(16);    //10
putchar(48);   //30
putchar(0);    //00
putchar(k);   //7

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    
putchar(16);    //10   //ilosc niewlozonych pretow z grzybkami do wiezy, czyli raczej krzywa wieza
putchar(80);   //50
putchar(0);    //00
putchar(l);   //7



if(m>255)
    {
    gg = m/255;
    hh = m%255;
    }
else
    {
    gg = 0;
    hh = 0;
    }


//wylacz dwa ostatnie parametry aby miec mozliwosc wysiwetlenia ilosc impulsow licznika kolorow
/*

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    
putchar(16);    //10   //liczba spozniem monter 1 i 2
putchar(96);   //60    
putchar(gg);    //00
if(m>255)
    putchar(gg*255+hh);   //7
else
    if(m>=0)
        putchar(m);
    else
        putchar(0);


if(n>255)
    {
    gg = n/255;
    hh = n%255;
    }
else
    {
    gg = 0;
    hh = 0;
    }

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    
putchar(16);    //10   //liczba spoznien monter 3
putchar(112);   //70
putchar(gg);    //00

if(n>255)
    putchar(gg*255+hh);   //7
else
    if(n>=0)
        putchar(n);
    else
        putchar(0);

*/

}


void wyswietl_czas_czujnikow_kolorow(int m, int n)
{
int gg,hh;

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    
putchar(16);    //10   //liczba spozniem monter 1 i 2
putchar(96);   //60    
putchar(gg);    //00
if(m>255)
    putchar(gg*255+hh);   //7
else
    if(m>=0)
        putchar(m);
    else
        putchar(0);


if(n>255)
    {
    gg = n/255;
    hh = n%255;
    }
else
    {
    gg = 0;
    hh = 0;
    }

putchar(90);  //5A
putchar(165); //A5
putchar(5);//05
putchar(130);  //82    
putchar(16);    //10   //liczba spoznien monter 3
putchar(112);   //70
putchar(gg);    //00

if(n>255)
    putchar(gg*255+hh);   //7
else
    if(n>=0)
        putchar(n);
    else
        putchar(0);

}



void obsluga_startowa_dozownika_kleju()
{
//PORTA.5 = 1;  //zasilanie 220V na dozownik kleju - juz nie aktualne, teraz tu jest zasilanie cewki przekaxnika i stycznika od puszczania 
//silnika grzebienie bez falownika
}

void obsluga_startowa_dozownika_kleju_slave()
{
int spr;
spr = 0;

PORTE.7 = 1;
delay_ms(100);
spr = getchar1();
if(spr == 0)   //jak na poczatku podal 0 to jeszcze raz getchar
    {
    komunikat_8_na_panel(1);
    getchar1();  //tu utyka i czeka az ok z dozownikiem            //wtedy ten getchar puszcza
    }
PORTE.7 = 0;  //koniec komunikacji

}

int pusc_pierwszego_preta()
{
int wynik;
wynik = 0;

//PORTC.5   si�ownik 3 kolejkuj�cy na rynnie
//PORTC.6   si�ownik 2 kolejkuj�cy na rynnie  //na pewno podupcona kolejno��
//PORTC.7   si�ownik 1 kolejkuj�cy na rynnie

switch(proces[0])
    {
    case 0:
        proces[0] = 1;
    break;
    
    case 1:       
                
        sek0_7s = 0;
        sek0 = 0;       
        proces[0] = 4;
    
    break;
        
    case 4:
            if(sek0 > 100)
                {
                PORTB.4 = 1; //silownik pozycjonujacy na zjezdzalni wzdloz
                sek0 = 0;
                proces[0] = 5;
                } 
    break;
    
    case 5:
            if(sek0 > 100)
                {
                PORTB.4 = 0; //silownik pozycjonujacy na zjezdzalni wzdloz
                sek0 = 0;
                proces[0] = 6;
                }
    
    break; 
    
    
    case 6:
            if(sek0 > 100)
                {
                PORTC.5 = 1; //silownik 3 w gore
                sek0 = 0;
                proces[0] = 7;
                } 
    break;
    
    case 7:
            if(sek0 > 100)
                {
                PORTC.5 = 0; //silownik 3 w dol
                sek0 = 0;
                proces[0] = 8;
                } 
    break;
    
    case 8:
            if(sek0 > 100)
               proces[0] = 9; 
    break;
    
    case 9:
                   
         sek0 = 0;
         proces[0] = 0;
         wynik = 1;               
                                    
    break;
    }

return wynik;
}


void wyczysc_maszyne_z_pretow_gwintowanych()
{
int i;
i=0;


while(i == 0)
    i = wyczysc_grzebienie();  //przenies raz grzebienie
i = 0;
while(i == 0)
    i = pusc_pierwszego_preta();
i = 0;
while(i == 0)
    i = wyczysc_grzebienie();  //przenies raz grzebienie - po tym jest pod klejem
i = 0;
while(i == 0)
    i = wyczysc_grzebienie();  //przenies raz grzebienie - po tym jest pod zakrecaniem
i = 0;

while(i == 0)
    i = wyczysc_grzebienie();  //przenies raz grzebienie - po tym spada

//dorzucic czujnika indukcyjnego do tej �apki, kt�ra chwyta
//czyli maszyna ma si� nie uruchomi� dopoki ktos nie wyczyscil tych precikow
//JEZELI SA PRETY TO KOMUNIKAT - ZABIERZ PRETY

//po tym sprawdzeniu nastepuje komunikat:
//WYCZYSZCZONO MASZYNE
komunikat_2_na_panel();

}


int obsluga_startowa_tasmy_lancuchowej()
{
static int czekaj_na_reset;
static int wiezyczka_prozniowa;
static int wykrylem_normalna;
static int wykrylem_prozniowa;


int hh = 0;

//int zaloczono_kurtyne;
//zaloczono_kurtyne = 0;

//sprawdz_pin6(PORTKK,0x79)    czujnik ze jedzie lancuchowy
//0 - jedzie
//1 - stoi

//sprawdz_pin7(PORTKK,0x79)    sygnal ze kurtyna zadzialala - jak ktos wlozyl lape to bedzie 0
            //jak monterzy zresetuja to sama mi sie pojawi 1
            //zmieniam opis dnia 06.07.2022:
            //sygnal ze kurtyna zadzialala - jak ktos wlozyl lape to bedzie 1
            //jak monterzy zresetuja to sama mi sie pojawi 0



//uproszczona obsluga
//PORTE.5   sekwencja startowa pivexin
//PORTE.6   manipulator wykonal pivexin
//if(sprawdz_pin7(PORTKK,0x79) == 1)
//            {
//            zw = 99;
//            wydaj_dzwiek();


//PORTE.5 = 1;
//delay_ms(300);
//PORTE.5 = 0;
//delay_ms(300);
//PORTE.6 = 1;
//delay_ms(300);
//PORTE.6 = 0;
 
switch(sprawdz_pin7(PORTKK,0x79))
    {
case 0:  //zmieniam 28.06 bylo 0
        switch(sekwencja)       
           {
           case 0:
                    if(czekaj_na_reset == 0)
                    {
                    komunikat_czysc_na_panel();
                    
                    putchar(90);
                    putchar(165);
                    putchar(4);
                    putchar(131);
                    putchar(64);
                    putchar(32);  //adres zmiennej - 4020
                    putchar(1);   //czy oproznic podajnik grzybkow
                    getchar();
                    getchar();
                    getchar();
                    getchar();
                    getchar();
                    getchar();
                    getchar();
                    getchar();
                    hh = getchar();
                    if(hh == 0)
                        wiezyczka_prozniowa = 0;
                    else
                        wiezyczka_prozniowa = 1;
                    
                    if(wiezyczka_prozniowa == 0)
                       {
                       PORT_F.bits.b3 = 0;   //informacja do szaly kolo nakracenia ze jest proznia
                       PORTF = PORT_F.byte;
                       }
                    else
                        {
                        PORT_F.bits.b3 = 1;   //informacja do szaly kolo nakracenia ze jest proznia
                        PORTF = PORT_F.byte;
                        }
                    
                    
                    zaloczono_kurtyne = 0;
                    PORTE.5 = 1;
                    PORT_F.bits.b2 = 1;   //zadanie zzsuniecia lapek
                    PORTF = PORT_F.byte;
                    delay_ms(400);  //delay_ms(400);
                    sekwencja = 1;
                    }
           break;
           case 1:
                    PORTE.5 = 0;
                    delay_ms(400);
                    sekwencja = 2;          
           break;
           
           case 2:
                    PORTE.6 = 1;
                    if(sprawdz_pin6(PORTKK,0x79) == 0)  //ze jedzie
                        {
                        komunikat_czysc_na_panel();
                        PORT_F.bits.b2 = 0;   //zadanie zzsuniecia lapek koniec
                        PORTF = PORT_F.byte;
                        sekwencja = 3;
                        PORTE.6 = 0;
                        }
                    else
                        {
                        komunikat_12_na_panel();    
                        //delay_ms(100);
                        }
           break;
           
           case 3:   
                    
                    
                    wiezyczka_prozniowa_global = wiezyczka_prozniowa;
                    
                    switch(wiezyczka_prozniowa)
                    {
                    case 0:
                    
                        if(sprawdz_pin0(PORTGG,0x71) == 0)
                        {
                        wykrylem_normalna = 1;
                        PORT_F.bits.b0 = 1;   //czujniki aktywne
                        PORT_F.bits.b1 = 1;   //czujnik pojemnosciowy aktywny
                        PORTF = PORT_F.byte;
                        }
                    
                        if(sprawdz_pin2(PORTGG,0x71) == 0)
                        {
                        wykrylem_prozniowa = 1;
                        PORT_F.bits.b0 = 0;   //czujniki deaktywacja         
                        PORT_F.bits.b1 = 0;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                    
                    
                    
                    break;
                    
                    case 1:
                    
                        if(sprawdz_pin0(PORTGG,0x71) == 0)
                        {
                        wykrylem_normalna = 1;
                        PORT_F.bits.b0 = 0;   //czujniki deaktywacja wykrywania wiezyczki
                        PORT_F.bits.b1 = 0;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                    
                        if(sprawdz_pin2(PORTGG,0x71) == 0)
                        {
                        wykrylem_prozniowa = 1;
                        PORT_F.bits.b0 = 1;   //czujniki aktywacja
                        PORT_F.bits.b1 = 1;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                        
                    
                    break;
                    }
                    
                    
                    
                    
                    
                                                        //jak swieci to jeszcz jedzie - dodatkowy pin z szafy nkodera   
                                                        //&& (sprawdz_pin5(PORTGG,0x71)== 0) - wylaczam bo powoduje problem przy plrzelanaczniu proznia/nie proznia
                    if(sprawdz_pin6(PORTKK,0x79) == 1 )  //ze stoi
                    {
                    komunikat_czysc_na_panel();
                    if(zajechalem == 2)
                        zajechalem = 3;
                    if(zajechalem == 0)
                        zajechalem = 2;
                    
                    //if(wykrylem_prozniowa == 1 && wykrylem_normalna == 1)
                    sekwencja = 4;
                    
                    if(wykrylem_normalna == 0)
                       komunikat_21_panel(); 
                    
                    if(wykrylem_prozniowa == 0)
                       komunikat_22_panel();
                    }
           break;
           
           case 4:
                    
                    if(zajechalem == 2)
                        {
                          if(wiezyczka_prozniowa_global == 1)
                            {
                            PORT_F.bits.b6 = 1;   //psikanie powietrzenbem na wiezyczke
                            PORTF = PORT_F.byte;
                            }
                        delay_ms(400);
                        delay_ms(400);
                            
                            if(wiezyczka_prozniowa_global == 1)
                            {
                            PORT_F.bits.b6 = 0;   //psikanie powietrzenbem na wiezyczke
                            PORTF = PORT_F.byte;
                            }
                        
                        
                        delay_ms(400);
                        delay_ms(400);
                        
                         if(wiezyczka_prozniowa_global == 1)
                            {
                            PORT_F.bits.b5 = 1;   //mgielka wodna
                            PORTF = PORT_F.byte;
                            }
                        
                        delay_ms(400);
                        delay_ms(400); //czekaj chwile zeby lapki zdazyly zajechac
                        PORT_F.bits.b2 = 1;   //zadanie zzsuniecia lapek  
                        PORTF = PORT_F.byte;
                        
                         if(wiezyczka_prozniowa_global == 1)
                            {
                            PORT_F.bits.b5 = 0;   //mgielka wodna
                            PORTF = PORT_F.byte;
                            }
                        
                        
                        delay_ms(400);
                        delay_ms(400);
                        delay_ms(400);
                        sekwencja = 2;
                        }
                    else
                        {    
                        zajechalem = 1;
                        wykrylem_normalna = 0;
                        wykrylem_prozniowa = 0;
                        sekwencja = 0;
                        }                              
           break;
           }

 
break;

case 1: //zmieniam 28.06 bylo 1
        komunikat_10_na_panel();
        PORTE.5 = 0;
        PORTE.6 = 0;  
        PORT_F.bits.b2 = 0;   //zadanie zzsuniecia lapek koniec
        PORTF = PORT_F.byte;
        zajechalem = 0;
        sekwencja = 0;
        if(zaloczono_kurtyne == 0)
            {
            zaloczono_kurtyne = 1;
            licznik_wyzwolen_kurtyny++;
            }
        wyswietl_parametry(licznik_wylatujacych_grzybkow,licznik_niezakreconych_grzybkow,licznik_wyzwolen_kurtyny,licznik_niewlozonych_pretow_z_grzybkiem,licznik_spoznien_monter_1_2,licznik_spoznien_monter_3_nowy);
        
        
        //19_01_2024 - wylaczam to bo sie pojawia Odslon i zresetuj kurtyne
            //pali sie zolty guzik
        //if(sprawdz_pin0(PORTKK,0x79) == 1)
        //      czekaj_na_reset = 1;
        
        delay_ms(1000);        
        break;
    }


return zajechalem; 
}


/*
void przenies_pret_gwintowany_old()
{
int zwrot;
int liczenie;
int rozpoczalem_ruch_preta;
int zwloka_czasowa;
long int time,time1;
int przenies_przez_falownik = 0;
static int czekaj_na_reset;
int hh = 0;
static int wiezyczka_prozniowa;
//int zaloczono_kurtyne;

//zaloczono_kurtyne = 0;

liczenie = 0;
rozpoczalem_ruch_preta = 0;
licz = 0;
time = 0;
time1 = 0;
zwrot = 1;  //wylaczam to na razie bo testuje czekam na ruch lanucha 27.06
//zwrot = 5;   //do testu czekam na ruch lanuchya
sekwencja = 0;
zwloka_czasowa = 0;



      //wylaczam to na razie bo testuje czekam na ruch lanucha 27.06


if(start >=8)
    //zw = 99;   //na razie do testow
    //zw = 1;
    sekwencja = 0;  
else
    sekwencja = 5;
    //zw = 0;


  


//to ponizej dziala na pewno ale kombinuje z kurtyna 22.03.2017

//while(zwrot == 1 | zwrot == 2 | zw == 1 | zw == 2 | zw == 3 | zw == 4 | zw == 5 | zw == 99)
while(zwrot == 1 | zwrot == 2 | zwrot == 3 | zwrot == 4 | sekwencja == 0 | sekwencja == 1 | sekwencja == 2 | sekwencja == 3 | sekwencja == 4)
    {
    if(zwrot == 1 | zwrot == 2 | zwrot == 3 | zwrot == 4)
            {
            switch(zwrot)
                {
                case 1:                                                       //30000 04.07
                        if((rozpoczalem_ruch_preta == 1 & start >=8 & time1 > 2000) | (start < 8 & time1 > 1000))                
                            {                                                //20000 10.10.2025          //3000 10.10.2025
                            if(start < 8)
                                PORTB.5 = 1;  //si�ownik ma�y chwytania pr�cika - chwycenie
                            zwrot = 2;
                            time1 = 0;
                            }
                break;
                case 2:
                        //if((sprawdz_pin5(PORTHH,0x73) == 0 & start < 8) | (sprawdz_pin5(PORTHH,0x73) == 1 & start >= 8)) //kontrola ok - wywalam kontrolwe 14.09 bo koliduje jak sie zapetli nakretka
                        if((sprawdz_pin5(PORTHH,0x73) == 0 & start < 8) | (sprawdz_pin5(PORTHH,0x73) == 1 & start >= 8))
                            {
                            PORTB.5 = 0; //si�ownik ma�y chwytania pr�cika - puszczenie
                            PORTB.2 = 0; //wkladanie do lancy precika z grzybkiem - powrot silownikiem
                            PORTB.6 = 0; //silownik obrotowy na ktorym jest maly chwytajacy precik - powrot
                            zwrot = 3;
                            } 
                        else
                            {          //tu
                            if(time1 > 2000 & sprawdz_pin7(PORTHH,0x73) == 1)
                                {
                                wydaj_dzwiek();
                                komunikat_13_na_panel();
                                PORTB.5 = 0;
                                time1 = 20001; //tu
                                }      //tu
                            if(time1 > 2000 & sprawdz_pin7(PORTHH,0x73) == 0)   
                                {
                                komunikat_czysc_na_panel();
                                time1 = 0;
                                PORTB.2 = 0; //wkladanie do lancy precika z grzybkiem - powrot silownikiem
                                PORTB.6 = 0; //silownik obrotowy na ktorym jest maly chwytajacy precik - powrot
                                zwrot = 3;
                                }
                            
                            }
                    
                break;
                
                case 3:    
                        
                        
                        if(przejechalem_czujnik_lub_jestem_na_nim == 1)
                            {
                            //if(dlugosc_preta_gwintowanego < 70 & il_pretow_gwintowanych > 1 & start >= 6 & metalowe_grzybki == 0)
                            //  PORTE.3 = 1;
                            PORTB.7 = 0;  //zakoncz dociskanie preta
                            przenies_przez_falownik = odpytaj_czy_grzebienie_przez_falownik();
                            if(przenies_przez_falownik == 1)
                                {
                                PORTA.0 = 1; //rozpcznij przeniesienie pret do nakladania kleju przez falownik
                                PORTA.5 = 0;
                                }
                            else
                                {
                                PORTA.5 = 1;
                                PORTA.0 = 0;
                                }
                            przejechalem_czujnik_lub_jestem_na_nim = 0;
                            }
                        if(sprawdz_pin4(PORTHH,0x73) == 1 & przejechalem_czujnik_lub_jestem_na_nim == 0)
                            {
                             if(przenies_przez_falownik == 1)
                                {
                                PORTA.0 = 1; //rozpcznij przeniesienie pret do nakladania kleju przez falownik
                                PORTA.5 = 0; //czujnik juz nie swieci, czyli jade dalej
                                }
                            else
                                {
                                PORTA.5 = 1;   //czujnik juz nie swieci, czyli jade dalej
                                PORTA.0 = 0;
                                }
                              
                            przejechalem_czujnik_lub_jestem_na_nim = 1;
                            grzybek_jest_nakrecony_na_precie = 0;
                            sek1 = 0;
                            zwrot = 4;
                            }
                                   
                break;
            
                case 4:
                
                    if(sprawdz_pin2(PORTKK,0x79) == 0)
                        grzybek_jest_nakrecony_na_precie = 1;     
                    //else                                      // Matys 2024.10.01
                    //    grzybek_jest_nakrecony_na_precie = 1; //
                
                    
                    if(sprawdz_pin4(PORTHH,0x73) == 0)  //dojechalem znowu do czujnika
                        {
                        sek1 = 0;
                        zwloka_czasowa = 1;
                        }
                        
                    if(zwloka_czasowa == 1 & sek1 > 5)
                        {
                        PORTA.0 = 0; //wylacz silnik falownik
                        PORTA.5 = 0; //wylacz silnik optoprzekanik;
                        sek1 = 0;
                        zwloka_czasowa = 0;
                        zwrot = 5;
                        }      
                        
                        
                break;
                }
            }

//sprawdz_pin7(PORTKK,0x79)    sygnal ze kurtyna zadzialala - jak ktos wlozyl lape to bedzie 0
                        //jak monterzy zresetuja to sama mi sie pojawi 1     
                         //zmieniam opis dnia 06.07.2022:
            //sygnal ze kurtyna zadzialala - jak ktos wlozyl lape to bedzie 1
            //jak monterzy zresetuja to sama mi sie pojawi 0



    

    switch(sprawdz_pin7(PORTKK,0x79))
    {
    case 0:    //zmieniam 28.06 bylo 0
        switch(sekwencja)       
           {
           case 0:                
                    if(sprawdz_pin7(PORTKK,0x79) == 0 & sprawdz_pin3(PORTKK,0x79) == 0 && czekaj_na_reset == 0)
                    {
                    
                    putchar(90);
                    putchar(165);
                    putchar(4);
                    putchar(131);
                    putchar(64);
                    putchar(32);  //adres zmiennej - 4020
                    putchar(1);   //czy oproznic podajnik grzybkow
                    getchar();
                    getchar();
                    getchar();
                    getchar();
                    getchar();
                    getchar();
                    getchar();
                    getchar();
                    hh = getchar();
                    if(hh == 0)
                        wiezyczka_prozniowa = 0;
                    else
                        wiezyczka_prozniowa = 1;
                    
                    
                    
                    zaloczono_kurtyne = 0;
                    komunikat_czysc_na_panel();
                    PORT_F.bits.b2 = 1;   //zadanie zzsuniecia lapek
                    PORTF = PORT_F.byte;
                    PORTE.5 = 1;
                    time = 0;
                    sekwencja = 1;
                    }
                    else
                        {  //
                        if(sprawdz_pin3(PORTKK,0x79) == 1 & liczenie == 0)
                            {
                            licznik_spoznien_monter_1_2++;
                            liczenie = 1;
                            }   
                        break;
                        }
           break;                                 //& sprawdz_pin1(PORTKK,0x79) == 0
           case 1:                    //silownik chwytania lancy
                    if(sprawdz_pin7(PORTKK,0x79) == 0 & PORTB.1 == 0)
                    {
                    //if(time > 1000)  //7500 04.07.2017 dziala bez zarzutu, to byla wina chyba przekaznikow i opoznien na nich, zmieniam tak jak bylo
                    if(time > 100) //10.10.2025
                        {
                        PORTE.5 = 0;
                        sekwencja = 2;
                        time = 0;
                        }
                    
                    }
                    else
                        break;           
           break;
           
           case 2:                 //& sprawdz_pin1(PORTKK,0x79) == 0
                    if(sprawdz_pin7(PORTKK,0x79) == 0)
                    {
                    //if(time > 1000)   ////7500  04.07.2017
                    if(time > 100) //10.10.2025
                    {
                    PORTE.6 = 1;
                    if(sprawdz_pin6(PORTKK,0x79) == 0)  //ze jedzie
                        {
                        rozpoczalem_ruch_preta = 1;
                        time1 = 0;   //zeby sekunde odczekac z chwyceniem
                        komunikat_czysc_na_panel();
                        sekwencja = 3;
                        PORTE.6 = 0; 
                        PORT_F.bits.b2 = 0;   //zadanie zzsuniecia lapek
                        PORTF = PORT_F.byte;
                        time = 0;
                        }
                    else
                        {
                        komunikat_12_na_panel();    
                        }
                    }
                    }
                    else
                        {
                        PORTB.1 = 0;
                        break;
                        }
                    
           break;
           
           case 3: 
           
           
                    switch(wiezyczka_prozniowa)
                    {
                    case 0:
                    
                        if(sprawdz_pin0(PORTGG,0x71) == 0)
                        {
                        PORT_F.bits.b0 = 0;   //czujniki aktywne
                        PORT_F.bits.b1 = 0;   //czujnik pojemnosciowy aktywny
                        PORTF = PORT_F.byte;
                        }
                    
                        if(sprawdz_pin2(PORTGG,0x71) == 0)
                        {
                        PORT_F.bits.b0 = 1;   //czujniki deaktywacja         
                        PORT_F.bits.b1 = 1;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                    
                    
                    
                    break;
                    
                    case 1:
                    
                        if(sprawdz_pin0(PORTGG,0x71) == 0)
                        {
                        PORT_F.bits.b0 = 1;   //czujniki deaktywacja wykrywania wiezyczki
                        PORT_F.bits.b1 = 1;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                    
                        if(sprawdz_pin2(PORTGG,0x71) == 0)
                        {
                        PORT_F.bits.b0 = 0;   //czujniki aktywacja
                        PORT_F.bits.b1 = 0;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                        
                    
                    break;
                    }
           
           
           
           
             
                    if(sprawdz_pin6(PORTKK,0x79) == 1)  //ze stoi
                    {
                    komunikat_czysc_na_panel();
                    PORTE.6 = 0;
                    //if(time > 6000)      //to b�dzie chyba to......to powoduje jechanie dwa razy...zmieniam to na 6000..bylo 60000  12.20.2017 
                    if(time > 60) //10.10.2025
                        sekwencja = 4;
                    else
                        sekwencja = 0;
                    }
           break;
           case 4:
                    sekwencja = 5;
                    if(start >= 10 & tryb_male_puchary == 0)
                        PORTA.2 = 1;  //komunikacja bez rs232 zgodna na zacisniecie szczek
                    if(start >= 9 & tryb_male_puchary == 1)
                        PORTA.2 = 1;  //komunikacja bez rs232 zgodna na wysuniecie silownika otwierajacego wieze                                    
           break;
        
           }

 
    break;

    case 1: //zmieniam 28.06 bylo 1
        komunikat_czysc_na_panel();
        komunikat_10_na_panel();
        
        PORTE.5 = 0;   
        PORT_F.bits.b2 = 0;   //koniec zadanie zzsuniecia lapek
        PORTF = PORT_F.byte;
        PORTE.6 = 0;
        PORTA.2 = 0;   //koniec zezwolenia na zacisniecie szczek
        sekwencja = 0;
        time = 0;
        if(zaloczono_kurtyne == 0)
            {
            zaloczono_kurtyne = 1;
            licznik_wyzwolen_kurtyny++;
            }
            
        //pali sie zolty guzik  19_01_2024
        //if(sprawdz_pin0(PORTKK,0x79) == 1)
        //    czekaj_na_reset = 1;
        
    break;
    }//switch

    
    
    //wylaczam 19_01_2024 to byla ta modyfikacja przexz Sobolewskiego                           //zresetowano
    //if(czekaj_na_reset == 1 && sprawdz_pin0(PORTKK,0x79) == 0 && zwrot == 5)
    //{
    ////wydanie dzwiekow zanim rusze
    //PORTC.0 = 1;
    //delay_ms(1000);
    //PORTC.0 = 0;
    //delay_ms(1000);
    //PORTC.0 = 1;
    //delay_ms(1000);
    //PORTC.0 = 0;
    //delay_ms(1000);
    //PORTC.0 = 1;
    //delay_ms(1000);
    //PORTC.0 = 0;
    //czekaj_na_reset == 0;
    //}

    
    
    
    
    
    time++;
    time1++;
    }//while

   


}


*/

int sprawdz_czy_wiezyczka_prozniowa()
{
int hh = 0;
int wiezyczka_prozniowa = 0;

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(64);
putchar(32);  //adres zmiennej - 4020
putchar(1);   //czy oproznic podajnik grzybkow
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
hh = getchar();
if(hh == 0)
    wiezyczka_prozniowa = 0;
else
    wiezyczka_prozniowa = 1;
return wiezyczka_prozniowa;
}



void komunikacja_startowa_male_puchary(int wynik_wyboru_male_puchary)
{
int licznik_impulsow_male_puchary;
int znacznik;

licznik_impulsow_male_puchary = 0;
znacznik = 0;

PORTA.6 = 1;
delay_ms(500);
while(licznik_impulsow_male_puchary < wynik_wyboru_male_puchary)    //3 oznacza brak malych pucharow
{
if(sprawdz_pin1(PORTKK,0x79) == 1)
    {
    PORTA.3 = 1;
    znacznik = 1;
    }
    
if(sprawdz_pin1(PORTKK,0x79) == 0 & znacznik == 1)
    {            //czekaj
    PORTA.3 = 0;
    znacznik = 2;
    }

if(znacznik == 2)
    {
    licznik_impulsow_male_puchary++;            
    znacznik = 3;
    }

}
delay_ms(500);
PORTA.6 = 0;

}



void porownaj_wielkosc_kamienia_old()
{

wielkosc_kamienia_duze_puchary_old = wielkosc_kamienia_duze_puchary;

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(32);
putchar(96);  //adres zmiennej - 20
putchar(1);   
getchar();                         //wielkosc kamienia duze puchary
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
wielkosc_kamienia_duze_puchary = getchar();   


if(wielkosc_kamienia_duze_puchary_old != wielkosc_kamienia_duze_puchary)
    {

     switch(wielkosc_kamienia_duze_puchary)
     {
     case 125:
        wynik_wyboru_male_puchary = 3;
     break;
     
     case 120:
        wynik_wyboru_male_puchary = 4;
     break;
     
     case 115:
        wynik_wyboru_male_puchary = 5;
     break;
     
     case 110:
        wynik_wyboru_male_puchary = 6;
     break;
     
     case 105:
        wynik_wyboru_male_puchary = 7;
     break;
     
     case 100:
        wynik_wyboru_male_puchary = 8;
     break;
     
     case 95:
        wynik_wyboru_male_puchary = 9;
     break;
     
     case 90:
        wynik_wyboru_male_puchary = 24;
     break;
     
     case 85:
        wynik_wyboru_male_puchary = 25;
     break;
     
     case 80:
        wynik_wyboru_male_puchary = 26;
     break;
     
     case 75:
        wynik_wyboru_male_puchary = 27;
     break;
     
     case 70:
        wynik_wyboru_male_puchary = 28;
     break;
     
     case 65:
        wynik_wyboru_male_puchary = 29;
     break;
     
     case 60:
        wynik_wyboru_male_puchary = 30;
     break;
     
     case 55:
        wynik_wyboru_male_puchary = 31;
     break;
     
     case 50:
        wynik_wyboru_male_puchary = 32;
     break;
     
     }
    
    komunikacja_startowa_male_puchary(wynik_wyboru_male_puchary);
    delay_ms(500); //do tej komunikacji
    }
    
        

}


void przenies_pret_gwintowany_old_13_01()
{
int zwrot;
int liczenie;
int rozpoczalem_ruch_preta;
int zwloka_czasowa;
long int time,time1;
int przenies_przez_falownik = 0;
static int czekaj_na_reset;
static int wiezyczka_prozniowa;
static int wykrylem_normalna;
static int wykrylem_prozniowa;
static int licznik_wykrylem_normalna;
static int  licznik_wykrylem_prozniowa;
//int zaloczono_kurtyne;

//zaloczono_kurtyne = 0;

liczenie = 0;
rozpoczalem_ruch_preta = 0;
licz = 0;
time = 0;
time1 = 0;
zwrot = 1;  //wylaczam to na razie bo testuje czekam na ruch lanucha 27.06
//zwrot = 5;   //do testu czekam na ruch lanuchya
sekwencja = 0;
zwloka_czasowa = 0;



      //wylaczam to na razie bo testuje czekam na ruch lanucha 27.06


if(start >=8)
    //zw = 99;   //na razie do testow
    //zw = 1;
    sekwencja = 0;  
else
    sekwencja = 5;
    //zw = 0;


  


//to ponizej dziala na pewno ale kombinuje z kurtyna 22.03.2017

//while(zwrot == 1 | zwrot == 2 | zw == 1 | zw == 2 | zw == 3 | zw == 4 | zw == 5 | zw == 99)
while(zwrot == 1 | zwrot == 2 | zwrot == 3 | zwrot == 4 | sekwencja == 0 | sekwencja == 1 | sekwencja == 2 | sekwencja == 3 | sekwencja == 4)
    {
    if(zwrot == 1 | zwrot == 2 | zwrot == 3 | zwrot == 4)
            {
            switch(zwrot)
                {
                case 1:                                                       
                        if((rozpoczalem_ruch_preta == 1 & start >=8)  | (start < 8))                
                            {                                                
                            if(start < 8)
                                PORTB.5 = 1;  //si�ownik ma�y chwytania pr�cika - chwycenie
                            zwrot = 2;
                            time1 = 0;
                            }
                break;
                case 2:
                        
                        if((sprawdz_pin5(PORTHH,0x73) == 0 & start < 8) | (sprawdz_pin5(PORTHH,0x73) == 1 & start >= 8))
                            {
                            PORTB.5 = 0; //si�ownik ma�y chwytania pr�cika - puszczenie
                            //PORTB.2 = 0; //wkladanie do lancy precika z grzybkiem - powrot silownikiem
                            //PORTB.6 = 0; //silownik obrotowy na ktorym jest maly chwytajacy precik - powrot
                            zwrot = 3;
                            } 
                        else
                            {          //tu
                            if(time1 > 2000 & sprawdz_pin7(PORTHH,0x73) == 1)
                                {
                                wydaj_dzwiek();
                                komunikat_13_na_panel();
                                PORTB.5 = 0;
                                time1 = 20001; //tu
                                }      //tu
                            if(time1 > 2000 & sprawdz_pin7(PORTHH,0x73) == 0)   
                                {
                                komunikat_czysc_na_panel();
                                time1 = 0;
                                PORTB.2 = 0; //wkladanie do lancy precika z grzybkiem - powrot silownikiem
                                PORTB.6 = 0; //silownik obrotowy na ktorym jest maly chwytajacy precik - powrot
                                zwrot = 3;
                                }
                            
                            }
                    
                break;
                
                case 3:    
                        
                        
                        if(przejechalem_czujnik_lub_jestem_na_nim == 1)
                            {
                            //if(dlugosc_preta_gwintowanego < 70 & il_pretow_gwintowanych > 1 & start >= 6 & metalowe_grzybki == 0)
                            //  PORTE.3 = 1;
                            PORTB.7 = 0;  //zakoncz dociskanie preta
                            przenies_przez_falownik = odpytaj_czy_grzebienie_przez_falownik();
                            if(przenies_przez_falownik == 1)
                                {
                                PORTA.0 = 1; //rozpcznij przeniesienie pret do nakladania kleju przez falownik
                                PORTA.5 = 0;
                                }
                            else
                                {
                                PORTA.5 = 1;
                                PORTA.0 = 0;
                                }
                            przejechalem_czujnik_lub_jestem_na_nim = 0;
                            }
                        if(sprawdz_pin4(PORTHH,0x73) == 1 & przejechalem_czujnik_lub_jestem_na_nim == 0)
                        //if(sprawdz_pin3(PORTGG,0x71) == 1 & przejechalem_czujnik_lub_jestem_na_nim == 0)
                            {
                             if(przenies_przez_falownik == 1)
                                {
                                PORTA.0 = 1; //rozpcznij przeniesienie pret do nakladania kleju przez falownik
                                PORTA.5 = 0; //czujnik juz nie swieci, czyli jade dalej
                                }
                            else
                                {
                                PORTA.5 = 1;   //czujnik juz nie swieci, czyli jade dalej
                                PORTA.0 = 0;
                                }
                              
                            przejechalem_czujnik_lub_jestem_na_nim = 1;
                            grzybek_jest_nakrecony_na_precie = 0;
                            sek1 = 0;
                            zwrot = 4;
                            }
                                   
                break;
            
                case 4:
                
                    if(sprawdz_pin2(PORTKK,0x79) == 0)
                        grzybek_jest_nakrecony_na_precie = 1;     
                    //else                                      // Matys 2024.10.01
                    //    grzybek_jest_nakrecony_na_precie = 1; //
                
                    //if(sprawdz_pin3(PORTGG,0x71) == 0)
                    if(sprawdz_pin4(PORTHH,0x73) == 0)  //dojechalem znowu do czujnika
                        {
                        sek1 = 0;
                        PORTB.6 = 0; //silownik obrotowy na ktorym jest maly chwytajacy precik - powrot  08.01.2025
                        PORTB.2 = 0; //wkladanie do lancy precika z grzybkiem - powrot silownikiem 08.01.2025
                        zwloka_czasowa = 1;
                        }
                        
                    if(zwloka_czasowa == 1 & sek1 > 5)
                        {
                        PORTA.0 = 0; //wylacz silnik falownik
                        PORTA.5 = 0; //wylacz silnik optoprzekanik;
                        sek1 = 0;
                        zwloka_czasowa = 0;
                        zwrot = 5;
                        }      
                        
                        
                break;
                }
            }

//sprawdz_pin7(PORTKK,0x79)    sygnal ze kurtyna zadzialala - jak ktos wlozyl lape to bedzie 0
                        //jak monterzy zresetuja to sama mi sie pojawi 1     
                         //zmieniam opis dnia 06.07.2022:
            //sygnal ze kurtyna zadzialala - jak ktos wlozyl lape to bedzie 1
            //jak monterzy zresetuja to sama mi sie pojawi 0



    

    switch(sprawdz_pin7(PORTKK,0x79))
    {
    case 0:    //zmieniam 28.06 bylo 0
        switch(sekwencja)       
           {
           case 0:                
                    if(sprawdz_pin7(PORTKK,0x79) == 0 & sprawdz_pin3(PORTKK,0x79) == 0 && czekaj_na_reset == 0)
                    {
                    wiezyczka_prozniowa = sprawdz_czy_wiezyczka_prozniowa();
                    if(wiezyczka_prozniowa == 0)
                       {
                       PORT_F.bits.b3 = 0;   //informacja do szaly kolo nakracenia ze jest proznia
                       PORTF = PORT_F.byte;
                       }
                    else
                        {
                        PORT_F.bits.b3 = 1;   //informacja do szaly kolo nakracenia ze jest proznia
                        PORTF = PORT_F.byte;
                        }
                     
                    
                    porownaj_wielkosc_kamienia_old();  //to spowalnia o okolo 1s jezeli jest zmiana kamienia
                    zaloczono_kurtyne = 0;
                    komunikat_czysc_na_panel();
                    PORT_F.bits.b2 = 1;   //zadanie zzsuniecia lapek
                    PORTF = PORT_F.byte;
                    PORTE.5 = 1;    //sekwencja startowa
                    time = 0;
                    sek4 = 0;
                    sekwencja = 1;
                    }
                    else
                        {  //
                        if(sprawdz_pin3(PORTKK,0x79) == 1 & liczenie == 0)
                            {
                            licznik_spoznien_monter_1_2++;
                            liczenie = 1;
                            }   
                        break;
                        }
           break;                                 //& sprawdz_pin1(PORTKK,0x79) == 0
           case 1:                    //silownik chwytania lancy
                    if(sprawdz_pin7(PORTKK,0x79) == 0 & PORTB.1 == 0)
                    {
                    if(sek4 > 5) 
                        {
                        PORTE.5 = 0;
                        sekwencja = 2;
                        sek4 = 0;
                        time = 0;
                        }
                    
                    }
                    else
                        break;           
           break;
           
           case 2:                 
                    if(sprawdz_pin7(PORTKK,0x79) == 0)
                    {
                    if(sek4 > 5) //10.10.2025
                    {
                    PORTE.6 = 1;
                    if(sprawdz_pin6(PORTKK,0x79) == 0)  //ze jedzie
                        {
                        rozpoczalem_ruch_preta = 1;
                        time1 = 0;   //zeby sekunde odczekac z chwyceniem
                        komunikat_czysc_na_panel();
                        sekwencja = 3;
                        sek4 = 0;
                        PORTE.6 = 0; 
                        PORT_F.bits.b2 = 0;   //zadanie zzsuniecia lapek
                        PORTF = PORT_F.byte;
                        time = 0;
                        }
                    else
                        {
                        komunikat_12_na_panel();    
                        }
                    }
                    }
                    else
                        {
                        PORTB.1 = 0;
                        break;
                        }
                    
           break;
           
           case 3: 
           
           
                    switch(wiezyczka_prozniowa)
                    {
                    case 0:
                    
                        if(sprawdz_pin0(PORTGG,0x71) == 0)
                        {
                        wykrylem_normalna = 1;
                        licznik_wykrylem_normalna++;
                        PORT_F.bits.b0 = 1;   //czujniki aktywne
                        PORT_F.bits.b1 = 1;   //czujnik pojemnosciowy aktywny
                        PORTF = PORT_F.byte;
                        }
                            
                        if(sprawdz_pin2(PORTGG,0x71) == 0)
                        {
                        wykrylem_prozniowa = 1;
                        licznik_wykrylem_prozniowa++;
                        PORT_F.bits.b0 = 0;   //czujniki deaktywacja         
                        PORT_F.bits.b1 = 0;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                    
                    
                    
                    break;
                    
                    case 1:
                    
                        if(sprawdz_pin0(PORTGG,0x71) == 0)
                        {
                        wykrylem_normalna = 1; 
                        licznik_wykrylem_normalna++;
                        PORT_F.bits.b0 = 0;   //czujniki deaktywacja wykrywania wiezyczki
                        PORT_F.bits.b1 = 0;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                    
                        if(sprawdz_pin2(PORTGG,0x71) == 0)
                        {
                        wykrylem_prozniowa = 1;      
                        licznik_wykrylem_prozniowa++;
                        PORT_F.bits.b0 = 1;   //czujniki aktywacja
                        PORT_F.bits.b1 = 1;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                        
                    
                    break;
                    }
           
           
           
           
             
                    if(sprawdz_pin6(PORTKK,0x79) == 1 && (sprawdz_pin5(PORTGG,0x71)== 0))  //ze stoi
                    {
                    komunikat_czysc_na_panel();
                    PORTE.6 = 0; 
                    //if(sek4 > 120) 
                     if(wykrylem_prozniowa == 1 && wykrylem_normalna == 1)
                        sekwencja = 4;
                    
                    if(wykrylem_normalna == 0)
                       komunikat_21_panel(); 
                    
                    if(wykrylem_prozniowa == 0)
                       komunikat_22_panel();
                    
                    
                    }
           break;
           case 4:
                    sekwencja = 5;
                    wykrylem_prozniowa = 0;  
                    wykrylem_normalna = 0;
                    wyswietl_czas_czujnikow_kolorow(licznik_wykrylem_normalna,licznik_wykrylem_prozniowa);
                    licznik_wykrylem_normalna = 0;
                    licznik_wykrylem_prozniowa = 0;
                    
                    if(start >= 10 & tryb_male_puchary == 0)
                        PORTA.2 = 1;  //komunikacja bez rs232 zgodna na zacisniecie szczek
                    if(start >= 9 & tryb_male_puchary == 1)
                        PORTA.2 = 1;  //komunikacja bez rs232 zgodna na wysuniecie silownika otwierajacego wieze                                    
           break;
        
           }

 
    break;

    case 1: //zmieniam 28.06 bylo 1
        komunikat_czysc_na_panel();
        komunikat_10_na_panel();
        
        PORTE.5 = 0;   
        PORT_F.bits.b2 = 0;   //koniec zadanie zzsuniecia lapek
        PORTF = PORT_F.byte;
        PORTE.6 = 0;
        PORTA.2 = 0;   //koniec zezwolenia na zacisniecie szczek
        sekwencja = 0;
        time = 0;     
        sek4 = 0;
        if(zaloczono_kurtyne == 0)
            {
            zaloczono_kurtyne = 1;
            licznik_wyzwolen_kurtyny++;
            }
            
        //pali sie zolty guzik  19_01_2024
        //if(sprawdz_pin0(PORTKK,0x79) == 1)
        //    czekaj_na_reset = 1;
        
    break;
    }//switch

    
    

    
    
    
    
    time++;
    time1++;
    }//while

   


}


unsigned char wybierz_X_opoznienie(int opoznienie)
{
    unsigned char X;

    if(opoznienie < 10)
        X = 0x0;
    else if(opoznienie < 15)
        X = 0x0;
    else if(opoznienie < 20)
        X = 0x0;
    else if(opoznienie < 25)
        X = 0x1;
    else if(opoznienie < 30)
        X = 0x2;
    else if(opoznienie < 35)
        X = 0x3;
    else if(opoznienie < 40)
        X = 0x4;
    else if(opoznienie < 45)
        X = 0x5;
    else if(opoznienie < 50)
        X = 0x6;
    else if(opoznienie < 55)
        X = 0x7;
    else if(opoznienie < 60)
        X = 0x8;
    else if(opoznienie < 65)
        X = 0x9;
    else if(opoznienie < 70)
        X = 0xA;
    else if(opoznienie < 75)
        X = 0xB;
    else if(opoznienie < 80)
        X = 0xC;
    else
        X = 0xD;

    return X;
}

void przenies_pret_gwintowany()
{
int zwrot = 0;
int liczenie = 0;
int rozpoczalem_ruch_preta = 0;
int zwloka_czasowa = 0;
int predkosc = 0;
int predkosc_obliczona = 0;
int opoznienie = 0;
bit ruch_grzebini = 0; //Pierre
bit ruch_lancucha = 0; //Pierre
static int opoznienie_old;

    
long int time = 0;
long int time1 = 0;
int przenies_przez_falownik = 0;
static int czekaj_na_reset;
static int wiezyczka_prozniowa;
static int wykrylem_normalna;
static int wykrylem_prozniowa;
static int licznik_wykrylem_normalna;
static int licznik_wykrylem_prozniowa;

unsigned long base_value = 0x00000801; 
unsigned char X = 0xA; 
unsigned long final_value = (base_value & 0xFFFF0FFF) | ((unsigned long)(X &0x0F) << 12);


liczenie = 0;
rozpoczalem_ruch_preta = 0;
licz = 0;
time = 0;
time1 = 0;
zwrot = 1;  //wylaczam to na razie bo testuje czekam na ruch lanucha 27.06
//zwrot = 5;   //do testu czekam na ruch lanuchya
sekwencja = 0;
zwloka_czasowa = 0;



      //wylaczam to na razie bo testuje czekam na ruch lanucha 27.06


if(start >=8)
    //zw = 99;   //na razie do testow
    //zw = 1;
    sekwencja = 0;  
else
    sekwencja = 5;
    //zw = 0;


  


//to ponizej dziala na pewno ale kombinuje z kurtyna 22.03.2017

//while(zwrot == 1 | zwrot == 2 | zw == 1 | zw == 2 | zw == 3 | zw == 4 | zw == 5 | zw == 99)
while(zwrot == 1 || zwrot == 2 || zwrot == 3 || zwrot == 4 || sekwencja == 0 || sekwencja == 1 || sekwencja == 2 || sekwencja == 3 || sekwencja == 4)
    {
    if(zwrot == 1 || zwrot == 2 || zwrot == 3 || zwrot == 4)
            {
            switch(zwrot)
                {
                case 1:                                                       
                        if((rozpoczalem_ruch_preta == 1 && start >=8)  || (start < 8))                
                            {                                                
                            if(start < 8)
                                PORTB.5 = 1;  //si�ownik ma�y chwytania pr�cika - chwycenie
                            ruch_grzebini = 1; //Pierre
                            wyslij(105, 1);        // event etapu -> Pi
                            zwrot = 2;
                            time1 = 0;
                            }
                break;
                case 2:
                        
                        if((sprawdz_pin5(PORTHH,0x73) == 0 && start < 8) || (sprawdz_pin5(PORTHH,0x73) == 1 && start >= 8))
                            {
                            aktualizuj_wyswietlacz_ilosci();
                            PORTB.5 = 0; //si�ownik ma�y chwytania pr�cika - puszczenie
                            //PORTB.2 = 0; //wkladanie do lancy precika z grzybkiem - powrot silownikiem
                            //PORTB.6 = 0; //silownik obrotowy na ktorym jest maly chwytajacy precik - powrot
                            zwrot = 3;
                            } 
                        else
                            {          //tu
                            if(time1 > 2000 && sprawdz_pin7(PORTHH,0x73) == 1)
                                {
                                wydaj_dzwiek();
                                komunikat_13_na_panel();
                                PORTB.5 = 0;
                                time1 = 20001; //tu
                                }      //tu
                            if(time1 > 2000 && sprawdz_pin7(PORTHH,0x73) == 0)   
                                {
                                komunikat_czysc_na_panel();
                                time1 = 0;
                                PORTB.2 = 0; //wkladanie do lancy precika z grzybkiem - powrot silownikiem
                                PORTB.6 = 0; //silownik obrotowy na ktorym jest maly chwytajacy precik - powrot
                                zwrot = 3;
                                }
                            
                            }
                    
                break;
                
                case 3:    
                        
                            PORTB.7 = 0;  //zakoncz dociskanie preta
                            przenies_przez_falownik = odpytaj_czy_grzebienie_przez_falownik();
                            if(przenies_przez_falownik == 1)
                                {
                                PORTA.0 = 1; //rozpcznij przeniesienie pret do nakladania kleju przez falownik
                                PORTA.5 = 0;
                                }
                            else
                                {
                                PORTA.5 = 1;
                                PORTA.0 = 0;
                                }
                            
                            grzybek_jest_nakrecony_na_precie = 0;
                            sek1 = 0;
                            zwrot = 4;
                            
                                   
                break;
            
                case 4:
                
                    if(sprawdz_pin2(PORTKK,0x79) == 0)
                        grzybek_jest_nakrecony_na_precie = 1;     
                    
                     
                    /*
                    if(sprawdz_pin3(PORTGG,0x71) == 0  && sek0 < 80) 
                        {
                        komunikat_czysc_na_panel();
                        komunikat_20_na_panel();
                        PORTA.0 = 0; //wylacz silnik falownik
                        PORTA.5 = 0; //wylacz silnik optoprzekanik;
                        
                        while(1)
                        {
                            if(sprawdz_pin7(PORTHH,0x73) == 0)
                            {
                            komunikat_czysc_na_panel();
                              if(przenies_przez_falownik == 1)
                                {
                                PORTA.0 = 1; //rozpcznij przeniesienie pret do nakladania kleju przez falownik
                                PORTA.5 = 0;
                                }
                            else
                                {
                                PORTA.5 = 1;
                                PORTA.0 = 0;
                                }
                            sek1 = 0;
                            break;
                            }
                        }
                        
                        
                        
                        }
                    */
                    
                    //if(sprawdz_pin3(PORTGG,0x71) == 0)    //podmieniam kabel od czujnika
                    if(sprawdz_pin4(PORTHH,0x73) == 0)  //dojechalem znowu do czujnika
                        {
                        sek1 = 0;
                        PORTB.6 = 0; //silownik obrotowy na ktorym jest maly chwytajacy precik - powrot  08.01.2025
                        PORTB.2 = 0; //wkladanie do lancy precika z grzybkiem - powrot silownikiem 08.01.2025
                        zwloka_czasowa = 1;
                        }
                        
                    if(zwloka_czasowa == 1 & sek1 > 10)
                        {
                        PORTA.0 = 0; //wylacz silnik falownik
                        PORTA.5 = 0; //wylacz silnik optoprzekanik;
                        ruch_grzebini = 0; //Pierre
                        wyslij(105, 0);        // event etapu -> Pi
                        na_pewno_przejechalem_grzebieniami_global = 1;
                        sek1 = 0;
                        zwloka_czasowa = 0;
                        zwrot = 5;
                        }      
                        
                        
                break;
                }
            }

//sprawdz_pin7(PORTKK,0x79)    sygnal ze kurtyna zadzialala - jak ktos wlozyl lape to bedzie 0
                        //jak monterzy zresetuja to sama mi sie pojawi 1     
                         //zmieniam opis dnia 06.07.2022:
            //sygnal ze kurtyna zadzialala - jak ktos wlozyl lape to bedzie 1
            //jak monterzy zresetuja to sama mi sie pojawi 0



    

    switch(sprawdz_pin7(PORTKK,0x79))
    {
    case 0:    //zmieniam 28.06 bylo 0
        switch(sekwencja)       
           {
           case 0:                
                    if(sprawdz_pin7(PORTKK,0x79) == 0 & sprawdz_pin3(PORTKK,0x79) == 0 && czekaj_na_reset == 0)
                    {
                    ruch_lancucha = 1; //Pierre
                    wyslij(106, 1);        // event etapu -> Pi
                    predkosc = odpytaj_parametr_panelu(96,16);
                    predkosc_obliczona = -100 * predkosc; 
                    delta_write_param(0x07, 0x06, predkosc_obliczona);    //zapis do tasmociagu lancuchowego
                    
                    
                    opoznienie = odpytaj_parametr_panelu(96,32);
                    if(opoznienie_old != opoznienie)     
                        {
                        opoznienie_old = opoznienie;
                        X = wybierz_X_opoznienie(opoznienie);
                        final_value = (base_value & 0xFFFF0FFF) | ((unsigned long)(X &0x0F) << 12);
                        delta_write_param(0x07, 0x08, final_value);
                        } 
                    
                    
                    wiezyczka_prozniowa = sprawdz_czy_wiezyczka_prozniowa();
                    if(wiezyczka_prozniowa == 0)
                       {
                       PORT_F.bits.b3 = 0;   //informacja do szaly kolo nakracenia ze jest proznia
                       PORTF = PORT_F.byte;
                       }
                    else
                        {
                        PORT_F.bits.b3 = 1;   //informacja do szaly kolo nakracenia ze jest proznia
                        PORTF = PORT_F.byte;
                        }
                    
                    
                    wiezyczka_prozniowa_global = wiezyczka_prozniowa; 
                    porownaj_wielkosc_kamienia_old();  //to spowalnia o okolo 1s jezeli jest zmiana kamienia
                    zaloczono_kurtyne = 0;
                    komunikat_czysc_na_panel();
                    PORT_F.bits.b2 = 1;   //zadanie zzsuniecia lapek
                    PORTF = PORT_F.byte;
                    PORTE.5 = 1;    //sekwencja startowa
                    time = 0;
                    sek4 = 0;
                    sekwencja = 1;
                    }
                    else
                        {  //
                        if(sprawdz_pin3(PORTKK,0x79) == 1 & liczenie == 0)
                            {
                            licznik_spoznien_monter_1_2++;
                            liczenie = 1;
                            }   
                        break;
                        }
           break;                                 //& sprawdz_pin1(PORTKK,0x79) == 0
           case 1:                    //silownik chwytania lancy
                    if(sprawdz_pin7(PORTKK,0x79) == 0 & PORTB.1 == 0)
                    {
                    if(sek4 > 5) 
                        {
                        PORTE.5 = 0;
                        sekwencja = 2;
                        sek4 = 0;
                        time = 0;
                        }
                    
                    }
                    else
                        break;           
           break;
           
           case 2:                 
                    if(sprawdz_pin7(PORTKK,0x79) == 0)
                    {
                    if(sek4 > 5) //10.10.2025
                    {
                    PORTE.6 = 1;
                    if(sprawdz_pin6(PORTKK,0x79) == 0)  //ze jedzie
                        {
                        rozpoczalem_ruch_preta = 1;
                        time1 = 0;   //zeby sekunde odczekac z chwyceniem
                        komunikat_czysc_na_panel();
                        sekwencja = 3;
                        sek4 = 0;
                        PORTE.6 = 0; 
                        PORT_F.bits.b2 = 0;   //zadanie zzsuniecia lapek
                        PORTF = PORT_F.byte;
                        time = 0;
                        }
                    else
                        {
                        komunikat_12_na_panel();    
                        }
                    }
                    }
                    else
                        {
                        PORTB.1 = 0;
                        break;
                        }
                    
           break;
           
           case 3: 
                     
           
                    if(sek4 > 10)     //dodatkowe 02.17 bo uderza� w nastepna wiezyczke nie prozniowa
                    {
                    PORTB.6 = 0; //silownik obrotowy na ktorym jest maly chwytajacy precik - powrot  08.01.2025
                    PORTB.2 = 0; //wkladanie do lancy precika z grzybkiem - powrot silownikiem 08.01.2025
                    }
                    
           
           
                    switch(wiezyczka_prozniowa)
                    {
                    case 0:
                    
                        if(sprawdz_pin0(PORTGG,0x71) == 0)
                        {
                        wykrylem_normalna = 1;
                        licznik_wykrylem_normalna++;
                        PORT_F.bits.b0 = 1;   //czujniki aktywne
                        PORT_F.bits.b1 = 1;   //czujnik pojemnosciowy aktywny
                        PORTF = PORT_F.byte;
                        }
                        
                      
                          
                   
                        
                        //if(wykrylem_prozniowa == 0)
                        //{
                        if(sprawdz_pin2(PORTGG,0x71) == 0)
                        {
                        wykrylem_prozniowa = 1;
                        licznik_wykrylem_prozniowa++;
                        PORT_F.bits.b0 = 0;   //czujniki deaktywacja         
                        PORT_F.bits.b1 = 0;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                        //}
                    
                    
                    break;
                    
                    case 1:
                                                              //to sek4 jest po to zeby byla zwloka czasowa, zeby wiezyczka prozniowa kto
                                                              //pod wkladaniem nie miala aktywnego czujnika
                        if(sprawdz_pin0(PORTGG,0x71) == 0)
                        {
                        wykrylem_normalna = 1;
                        licznik_wykrylem_normalna++;
                        PORT_F.bits.b0 = 0;   //czujniki deaktywacja wykrywania wiezyczki
                        PORT_F.bits.b1 = 0;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                    
                        if(sprawdz_pin2(PORTGG,0x71) == 0)
                        {
                        wykrylem_prozniowa = 1;  
                        licznik_wykrylem_prozniowa++;
                        PORT_F.bits.b0 = 1;   //czujniki aktywacja
                        PORT_F.bits.b1 = 1;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                        
                    
                    break;
                    }
           
           
           
           
                                                      //&& (sprawdz_pin5(PORTGG,0x71)== 0)
                    if(sprawdz_pin6(PORTKK,0x79) == 1)  //ze stoi
                    {
                        //if(sek4 < 12) //minelo 0.2s od uruchoemienia, jechal za krotko
                        //    {
                        //    sekwencja = 1;
                        //    PORTE.5 = 1;  //sekwkencja startowa
                        //    sek4 = 0;
                        //    }
                        
                        
                        
                        if(sprawdz_pin5(PORTGG,0x71)== 0 && start >1)
                            {
                            komunikat_czysc_na_panel();
                            sek4 = 0;
                            PORTE.6 = 0;
                            sekwencja = 4;               
                            }
                     
                        if(start <= 1)
                            {
                            sekwencja = 4;
                            }
                            
                    
                    
                    
                    //if(sek4 > 120) 
                    
                    //if(wykrylem_prozniowa == 1 && wykrylem_normalna == 1)
                    //    sekwencja = 4;
                    
                    //if(wykrylem_normalna == 0)
                    //   komunikat_21_panel(); 
                    
                    //if(wykrylem_prozniowa == 0)
                    //   komunikat_22_panel(); 
                    
                    
                        
                    //else
                    //    sekwencja = 0;
                    }
           break;
           case 4:
                    sekwencja = 5;
                    wykrylem_prozniowa = 0;  
                    wykrylem_normalna = 0;
                    wyswietl_czas_czujnikow_kolorow(licznik_wykrylem_normalna,licznik_wykrylem_prozniowa);
                    licznik_wykrylem_normalna = 0;
                    licznik_wykrylem_prozniowa = 0;
                    ruch_lancucha = 0; //Pierre                    
                    wyslij(106, 0);        // event etapu -> Pi
                    
                    if(start >= 10 & tryb_male_puchary == 0)
                        PORTA.2 = 1;  //komunikacja bez rs232 zgodna na zacisniecie szczek
                    if(start >= 9 & tryb_male_puchary == 1)
                        PORTA.2 = 1;  //komunikacja bez rs232 zgodna na wysuniecie silownika otwierajacego wieze                                    
           break;
        
           }

 
    break;

    case 1: //zmieniam 28.06 bylo 1
        komunikat_czysc_na_panel();
        komunikat_10_na_panel();
        
        PORTE.5 = 0;   
        PORT_F.bits.b2 = 0;   //koniec zadanie zzsuniecia lapek
        PORTF = PORT_F.byte;
        PORTE.6 = 0;
        PORTA.2 = 0;   //koniec zezwolenia na zacisniecie szczek
        sekwencja = 0;
        time = 0;     
        sek4 = 0;
        if(zaloczono_kurtyne == 0)
            {
            zaloczono_kurtyne = 1;
            licznik_wyzwolen_kurtyny++;
            }
            
        //pali sie zolty guzik  19_01_2024
        //if(sprawdz_pin0(PORTKK,0x79) == 1)
        //    czekaj_na_reset = 1;
        
    break;
    }//switch

    
    
    //wylaczam 19_01_2024 to byla ta modyfikacja przexz Sobolewskiego                           //zresetowano
    //if(czekaj_na_reset == 1 && sprawdz_pin0(PORTKK,0x79) == 0 && zwrot == 5)
    //{
    ////wydanie dzwiekow zanim rusze
    //PORTC.0 = 1;
    //delay_ms(1000);
    //PORTC.0 = 0;
    //delay_ms(1000);
    //PORTC.0 = 1;
    //delay_ms(1000);
    //PORTC.0 = 0;
    //delay_ms(1000);
    //PORTC.0 = 1;
    //delay_ms(1000);
    //PORTC.0 = 0;
    //czekaj_na_reset == 0;
    //}

    
    
    
    
    
    time++;
    time1++;
    orientator_grzybkow();
    }//while

   


}


int obsluga_tryb_manualny()
{
int zwracana = 0;
int obroc_grzebienie = 0;
int silnik_dokrecania_grzybka = 0;
int silownik_chwytania_preta = 0;
int silownik_otwierania_lufy_na_zakrecie = 0;
int silownik_obracanie_preta = 0;
int silownik_wkladania_preta_do_lufy = 0;
int silownik_chwytania_lufy = 0;
int silownik_kolejkujacy_pierwszy = 0;
int silownik_kolejkujacy_drugi = 0;
int silownik_kolejkujacy_trzeci = 0;
int orientator_grzybkow = 0;
int krok_tasmociagu_z_lufami = 0;
int docisk_preta_na_grzeb = 0;
int bramka_na_grzeb = 0;
int wyrownywanie_preta = 0;
int obrot_przez_falownik = 0;
int obrot_przez_optoprzekaznik = 0;
int silownik_dokrecania_grzybka = 0;
int przyspiesznie = 0;
int predkosc = 0;
int predkosc_obliczona = 0;
int opoznienie = 0;
unsigned long base_value = 0x00000801; 
unsigned char X = 0xA; 
unsigned long final_value = (base_value & 0xFFFF0FFF) | ((unsigned long)(X &0x0F) << 12);


PORT_F.bits.b4 = 1;   //przekaznik uruchamiajacy dozownik kleju
PORTF = PORT_F.byte;


//niedokonczone
putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(64);
putchar(48);  //adres zmiennej - 4030
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
silnik_dokrecania_grzybka = getchar();


if(silnik_dokrecania_grzybka == 1)
    PORTA.1 = 1;
else
    PORTA.1 = 0;

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(64);
putchar(64);  //adres zmiennej - 4040
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
silownik_chwytania_preta = getchar();

if(silownik_chwytania_preta == 1)
    PORTB.5 = 1;
else
    PORTB.5 = 0;

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(64);
putchar(80);  //adres zmiennej - 4050
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
silownik_otwierania_lufy_na_zakrecie = getchar();

if(silownik_otwierania_lufy_na_zakrecie == 1)
    PORTB.0 = 1;
else
    PORTB.0 = 0;         
    

/////////////////////////////////////////////////////////
if(obroc_grzebienie == 0)
{

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(80);
putchar(128);  //adres zmiennej
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
obrot_przez_falownik = getchar();



if(obrot_przez_falownik == 1)
    {
    obrot_przez_optoprzekaznik = 0;
    PORTA.5 = 0; //obrot przez przekaznik
    }
else
    {
    obrot_przez_optoprzekaznik = 1;
    PORTA.0 = 0; //obrot przez falownik
    }

}//jak nie obracaja sie aktualnie grzebienie

///////////////////////////////////////////////////////////
putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(64);
putchar(96);  //adres zmiennej - 4060
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
obroc_grzebienie = getchar();


if(obroc_grzebienie == 1)
    {
    if(obrot_przez_falownik == 1)
        {
        PORTA.0 = 1; //obrot przez falownik
        PORTA.5 = 0; //obrot przez przekazik
        }
    if(obrot_przez_optoprzekaznik == 1)
        {
        PORTA.0 = 0; //obrot przez falownik
        PORTA.5 = 1; //obrot przez przekazik
        }
    }
else
    {
    PORTA.0 = 0;
    PORTA.5 = 0;
    }

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(64);
putchar(144);  //adres zmiennej - 5040
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
silownik_kolejkujacy_pierwszy = getchar();
    
if(silownik_kolejkujacy_pierwszy == 1)
    {
    PORT_F.bits.b5 = 1;   //lanie kleju
    PORTF = PORT_F.byte;
    PORTC.7 = 1;
    }
else
    {
    PORTC.7 = 0;
    PORT_F.bits.b5 = 0;   //lanie kleju
    PORTF = PORT_F.byte;
    } 
    

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(64);
putchar(128);  //adres zmiennej - 5040
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
silownik_kolejkujacy_drugi = getchar();
    
if(silownik_kolejkujacy_drugi == 1)
    {
    PORT_F.bits.b6 = 1;   //psikanie powietrzenbem na wiezyczke
    PORTF = PORT_F.byte;
    PORTC.6 = 1;
    //PORTC.1 = 1; //pobierz grzybek - pojedz po grzybek od biura
    }
else
    {
    PORT_F.bits.b6 = 0;   //psikanie powietrzenbem na wiezyczke
    PORTF = PORT_F.byte;
    PORTC.6 = 0; 
    //PORTC.1 = 0; //pobierz grzybek czyli jedz do biura
    }

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(64);
putchar(112);  //adres zmiennej - 5040
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
silownik_kolejkujacy_trzeci = getchar();
    
if(silownik_kolejkujacy_trzeci == 1)
    PORTC.5 = 1;
else
    PORTC.5 = 0; 


putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(80);
putchar(0);  //adres zmiennej - 5040
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
orientator_grzybkow = getchar();
    
if(orientator_grzybkow == 1)
    PORTA.4 = 1;
else
    PORTA.4 = 0; 




/////////////////////////////////////////////
putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(32);
putchar(96);  //adres zmiennej - 20
putchar(1);   
getchar();                         //wielkosc kamienia duze puchary
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
wielkosc_kamienia_duze_puchary = getchar();   


     switch(wielkosc_kamienia_duze_puchary)
     {
     case 125:
        wynik_wyboru_male_puchary = 3;
     break;
     
     case 120:
        wynik_wyboru_male_puchary = 4;
     break;
     
     case 115:
        wynik_wyboru_male_puchary = 5;
     break;
     
     case 110:
        wynik_wyboru_male_puchary = 6;
     break;
     
     case 105:
        wynik_wyboru_male_puchary = 7;
     break;
     
     case 100:
        wynik_wyboru_male_puchary = 8;
     break;
     
     case 95:
        wynik_wyboru_male_puchary = 9;
     break;
     
     case 90:
        wynik_wyboru_male_puchary = 24;
     break;
     
     case 85:
        wynik_wyboru_male_puchary = 25;
     break;
     
     case 80:
        wynik_wyboru_male_puchary = 26;
     break;
     
     case 75:
        wynik_wyboru_male_puchary = 27;
     break;
     
     case 70:
        wynik_wyboru_male_puchary = 28;
     break;
     
     case 65:
        wynik_wyboru_male_puchary = 29;
     break;
     
     case 60:
        wynik_wyboru_male_puchary = 30;
     break;
     
     case 55:
        wynik_wyboru_male_puchary = 31;
     break;
     
     case 50:
        wynik_wyboru_male_puchary = 32;
     break;
     
     }
     
     
/////////////////////////////////////////////







//////////////////////////////////////////////

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(80);
putchar(16);  //adres zmiennej - 5010
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
krok_tasmociagu_z_lufami = getchar();

    
if(krok_tasmociagu_z_lufami == 1)
     {
     
     //testwo na prosbe eweliny ilosc pucharow do zmontoqania 
     ///////////////////////////////////////////////////////////////////////////////////////////////
     //il_pretow_gwintowanych = odpytaj_parametr_panelu_duze_liczby(0,112);
     //il_pretow_gwintowanych = odpytaj_parametr_panelu(0,112);
     //wyswietl_ilosc_zmontowanych_pucharow(il_pretow_gwintowanych,il_pretow_gwintowanych);
     //licznik_pucharow++;
     //aktualizuj_wyswietlacz_ilosci();
     //////////////////////////////////////////////////////////////////////////////////////////////
     
     przyspiesznie = odpytaj_parametr_panelu(96,0);
     predkosc = odpytaj_parametr_panelu(96,16);
     predkosc_obliczona = -100 * predkosc; 
     opoznienie = odpytaj_parametr_panelu(96,32);
          
     //przyspieszanie
     //delta_write_param(0x05, 0x07, przyspiesznie);      //zapis do tasmociagu lancuchowego
     //delay_ms(2000);      
      
     //predkosc
     delta_write_param(0x07, 0x06, predkosc_obliczona);    //zapis do tasmociagu lancuchowego
     delay_ms(1000);
     
     //opoznienie
     X = wybierz_X_opoznienie(opoznienie);
     final_value = (base_value & 0xFFFF0FFF) | ((unsigned long)(X &0x0F) << 12);
     delta_write_param(0x07, 0x08, final_value);
     
     
     
     komunikacja_startowa_male_puchary(wynik_wyboru_male_puchary);
     delay_ms(500); //do tej komunikacji
     
     zajechalem = 0;                             
     while(zajechalem == 0 )
        zajechalem = obsluga_startowa_tasmy_lancuchowej();
     zajechalem = 0;
     
     putchar(90);  //5A
     putchar(165); //A5
     putchar(5);//05
     putchar(130);  //82    
     putchar(80);    //50
     putchar(16);   //adres zmiennej 30            //wylaczenie guzika
     putchar(0);    //00
     putchar(0);   //0
     
     krok_tasmociagu_z_lufami = 0;
     
     }


///////////////////////////////////////////////

    
putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(80);
putchar(32);  //adres zmiennej - 4050
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
silownik_obracanie_preta = getchar();
    
if(silownik_obracanie_preta == 1)
    PORTB.6 = 1;
else
    PORTB.6 = 0; 


putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(80);
putchar(48);  //adres zmiennej - 4050
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
silownik_wkladania_preta_do_lufy = getchar();
    
if(silownik_wkladania_preta_do_lufy == 1)
    PORTB.2 = 1;
else
    PORTB.2 = 0; 
                     

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(80);
putchar(64);  //adres zmiennej - 5040
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
silownik_chwytania_lufy = getchar();
    
if(silownik_chwytania_lufy == 1)
    PORTB.1 = 1;
else
    PORTB.1 = 0; 


putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(80);
putchar(80);  //adres zmiennej - 5040
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
docisk_preta_na_grzeb = getchar();
    
if(docisk_preta_na_grzeb == 1)
    PORTB.7 = 1;
else
    PORTB.7 = 0; 


        

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(80);
putchar(96);  //adres zmiennej - 5040
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
bramka_na_grzeb = getchar();
    
if(bramka_na_grzeb == 1)
    PORTC.4 = 1;
else
    PORTC.4 = 0; 
    
    
    
    
    
    
putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(80);
putchar(112);  //adres zmiennej - 5040
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
wyrownywanie_preta = getchar();
    
if(wyrownywanie_preta == 1)
    PORTB.4 = 1;
else
    PORTB.4 = 0; 

/////////////////////////////////

putchar(90);
putchar(165);
putchar(4);
putchar(131);
putchar(80);
putchar(144);  //adres zmiennej - 5090
putchar(1);   
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
getchar();
silownik_dokrecania_grzybka = getchar();
    
if(silownik_dokrecania_grzybka == 1)
    {
    PORTB.3 = 0; //silownik dociskajacy grzybki - na wszelki wypadek w gore gdyby nie byl
    PORTC.2 = 0; //maly silownik grzybka - droga DO grzebieni  
    PORTE.2 = 1; //wroc malym silownik grzybka
    PORTC.1 = 1; //wroc duzym pobieraniem grzybka
    PORTB.7 = 1; //docisnij preta
    //delay
    delay_ms(3000);
    PORTC.1 = 0; //pobierz grzybek
    
    delay_ms(3000);
    PORTB.3 = 1;   //docisnij grzybek z gory
    PORTE.2 = 0;  //maly silownik grzybka na luz
    
    delay_ms(3000);
    
    PORTA.1 = 1;  //silnik dokrecajacy grzybki
    PORTC.3 = 1; //przysun silnik
    
    delay_ms(5000);
    
    PORTA.1 = 0;  //silnik dokrecajacy grzybki
    
    
    PORTA.1 = 0;  //silnik dokrecajacy grzybki
    PORTC.3 = 0; //odsun silnik
    
    PORTB.7 = 0; //pusc preta
    PORTB.3 = 0; //silownik dociskajacy grzybki - na wszelki wypadek w gore gdyby nie byl
    
    delay_ms(3000);
    
    PORTC.2 = 0; //maly silownik grzybka - droga OD grzebieni
    
    delay_ms(3000);
    
    putchar(90);
    putchar(165);
    putchar(5);        
    putchar(130);  //82
    putchar(80);    //50
    putchar(144);  //adres 90
    putchar(0);    //00
    putchar(0);   //1          zgas guzik
    }

if(silnik_dokrecania_grzybka == 1  || silownik_chwytania_preta == 1 || silownik_otwierania_lufy_na_zakrecie == 1 
   || obroc_grzebienie == 1 || silownik_kolejkujacy_pierwszy == 1 || silownik_kolejkujacy_drugi == 1 
   || silownik_kolejkujacy_trzeci == 1 || orientator_grzybkow == 1 || krok_tasmociagu_z_lufami == 1
   || silownik_obracanie_preta == 1 || silownik_wkladania_preta_do_lufy == 1 || silownik_chwytania_lufy == 1
   || docisk_preta_na_grzeb == 1 || bramka_na_grzeb == 1
   || wyrownywanie_preta == 1 || silownik_dokrecania_grzybka == 1)
   
   zwracana = 1;
else
   zwracana = 0;
    



return zwracana;

}





int ustawienia_startowe()
{
int xx;
xx = 0;


wartosci_wstepne_panelu();

while(sprawdz_pin0(PORTHH,0x73) == 0)//brak cisnienia
    komunikat_7_na_panel();
komunikat_czysc_na_panel();      

obsluga_startowa_dozownika_kleju();
komunikat_czysc_na_panel();
komunikat_1_na_panel();
//obsluga_startowa_dozownika_kleju_slave();
komunikat_czysc_na_panel();

//while(sprawdz_pin3(PORTGG,0x71) == 1)
while(sprawdz_pin4(PORTHH,0x73) == 1)  //jak nie widzi czujnika przenosnik pretow czyli nie wiadomo gdzie jestesmy
    PORTA.0 = 1; //silnik przenosnika pretow
przejechalem_czujnik_lub_jestem_na_nim = 1;


PORTA.0 = 0;  //obrot przez falownik;
PORTA.5 = 0;  //obrot przez optoprzekaznik;
PORTC.3 = 0;  //silownik na ktorym jest silnik dokrecajacy grzybki
PORTC.1 = 0;  //silownik pobierania grzybow duzy
PORTC.2 = 1;  //silownik pobierania grzybow maly - droga DO grzebienie pod ci�nieniem
PORTE.2 = 0;  //silownik pobierania grzybow maly - droga OD grzebienie pod ci�nieniem
PORTB.7 = 0;   //silownik dociskajacy pret na grzybkach

inicjalizacja_orientator_grzybkow();
komunikat_czysc_na_panel();
komunikat_3_na_panel();

while(z == 0)
{
//obsluga oproznienia grzybkow
odpytaj_parametry_z_panelu(1);
if(oproznij_podajnik == 1)
    {
    delay_ms(1000);
    PORTC.2 = 0;  //silownik pobierania grzybow maly - droga DO grzebienie pod ci�nieniem
    PORTE.2 = 1;  //silownik pobierania grzybow maly - droga OD grzebienie pod ci�nieniem
    delay_ms(3000);
    PORTC.1 = 1;  //silownik pobierania grzybow duzy - cofamy sie
    delay_ms(3000);
    PORTC.2 = 1;  //silownik pobierania grzybow maly - droga DO grzebienie pod ci�nieniem
    PORTE.2 = 0;  //silownik pobierania grzybow maly - droga OD grzebienie pod ci�nieniem
    delay_ms(2000);
    PORTC.2 = 0;  //silownik pobierania grzybow maly - droga DO grzebienie pod ci�nieniem
    PORTE.2 = 1;  //silownik pobierania grzybow maly - droga OD grzebienie pod ci�nieniem
    delay_ms(3000);
    PORTC.1 = 0;  //silownik pobierania grzybow duzy

    komunikat_9_na_panel();
    
    /*
    while(1)
        {
        delay_ms(1000);
        PORTC.1 = 0;  //silownik pobierania grzybow duzy
        delay_ms(1000);
        PORTC.1 = 1;  //silownik pobierania grzybow duzy
        }
    */
    
    while(1);
        {
        }
    }

//obsluga guzika start
if(xx == 0)
    z = czekaj_na_guzik_start();

xx = obsluga_tryb_manualny();

}
z = 0;


przenies_pret_gwintowany_old_13_01(); //teraz mozemy spasc pierwszym pretem ze zjezdzalni
PORTC.5 = 1; //silownik ostatni otwarcie
delay_ms(1000);
PORTC.5 = 0;
przenies_pret_gwintowany_old_13_01();
delay_ms(1000);
przenies_pret_gwintowany_old_13_01();
delay_ms(1000);
przenies_pret_gwintowany_old_13_01();

zajechalem = 0;
sekwencja = 0;

while(zajechalem == 0 | zajechalem == 2 | zajechalem == 3)
    zajechalem = obsluga_startowa_tasmy_lancuchowej();
zajechalem = 0;


delay_ms(1000);
odpytaj_parametry_z_panelu(1);

//if(tryb_male_puchary == 1) 18_01_2024
    komunikacja_startowa_male_puchary(wynik_wyboru_male_puchary);

PORTC.4 = 1;  //bramka grzybkow z precikiem znowu sie blokuje

return 1;
}

int czekaj_na_klej()
{
/*
if(sprawdz_pin6(PORTHH,0x73) == 1)
  {
  komunikat_8_na_panel(0); //dozownik kleju nie gotowy
  delay_ms(1000);
  klej = 0;
  d = 1;
  }
*/

/*

if(sprawdz_pin6(PORTHH,0x73) == 0 | sprawdz_pin6(PORTHH,0x73) == 1)
  {
  if(d == 1)
     {
     komunikat_czysc_na_panel();
     d = 0;
     }
     
  klej = 1;
  }  
*/

klej = 1;
return klej;
}


int czekaj_na_odpuszczenie_szczek()
{
int spr;

PORTE.7 = 1;//do komunikacji �adanie

//putchar1(4);  //ze dotyczy szczek
//spr = getchar1();
//PORTE.7 = 0;//do komunikacji koniec �adania

if(sprawdz_pin1(PORTKK,0x79) == 0)
    spr = 1;
else
   spr = 0; 


if(spr == 0)
  {
  if(czekaj_komunikat == 5)
        {
        komunikat_11_na_panel(); //monter nie nacisnal pedala
        czekaj_komunikat = 0;
        }
  czekaj_komunikat++;
  monter_slave = 0;
  gg = 1; 
  }
  
if(spr == 1)
  {
  czekaj_komunikat = 0;
  if(gg == 1)
     {
     komunikat_czysc_na_panel();
     gg = 0;
     }
     
  monter_slave = 1;
  PORTE.7 = 0;
  PORTA.2 = 0;  //komunikacja bez rs232 KONIEC zgody na zacisniecie szczek
  }
    
return monter_slave;

}


int czekaj_na_widzenie_puchara_przez_czujnik()
{
int spr;

PORTE.7 = 1;//do komunikacji �adanie
putchar1(6);  //ze dotyczy czujnika widzenia puchara
spr = getchar1();
PORTE.7 = 0;//do komunikacji koniec �adania

if(spr == 0)
  {
  if(czekaj_komunikat == 5)
        {
        komunikat_17_na_panel(); //czujnik nie zobaczyl
        czekaj_komunikat = 0;
        }
  czekaj_komunikat++;
  //delay_ms(1000);
  monter_slave = 0;
  gg = 1;
  }
  
if(spr == 1)
  {
  czekaj_komunikat = 0;
  if(gg == 1)
     {
     komunikat_czysc_na_panel();
     gg = 0;
     }
     
  monter_slave = 1;
  }
    
return monter_slave;

}



int czekaj_na_klej_slave()
{
int spr;

PORTE.7 = 1;//do komunikacji �adanie
putchar1(1);  //ze dotyczy kleju
spr = getchar1();
PORTE.7 = 0;//do komunikacji koniec �adania

if(spr == 0)
  {
  komunikat_8_na_panel(1); //dozownik kleju nie gotowy
  delay_ms(1000);
  klej_slave = 0;
  dd = 1;
  }
  
if(spr == 1)
  {
  if(dd == 1)
     {
     komunikat_czysc_na_panel();
     dd = 0;
     }
     
  klej_slave = 1;
  }
    
return klej_slave;

}


void dekatywuj_czujniki_gdy_wiezyczka_stoi()
{
  switch(wiezyczka_prozniowa_global)
                    {
                    case 0:
                    
                        if(sprawdz_pin0(PORTGG,0x71) == 0)
                        {
                        PORT_F.bits.b0 = 0;   //czujniki aktywne
                        PORT_F.bits.b1 = 0;   //czujnik pojemnosciowy aktywny
                        PORTF = PORT_F.byte;
                        }
                    
                        if(sprawdz_pin2(PORTGG,0x71) == 0)
                        {
                        PORT_F.bits.b0 = 1;   //czujniki deaktywacja         
                        PORT_F.bits.b1 = 1;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                    
                    
                    
                    break;
                    
                    case 1:
                    
                        if(sprawdz_pin0(PORTGG,0x71) == 0)
                        {
                        PORT_F.bits.b0 = 1;   //czujniki deaktywacja wykrywania wiezyczki
                        PORT_F.bits.b1 = 1;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                    
                        if(sprawdz_pin2(PORTGG,0x71) == 0)
                        {
                        PORT_F.bits.b0 = 0;   //czujniki aktywacja
                        PORT_F.bits.b1 = 0;   //czujnik pojemnosciowy deaktywacja
                        PORTF = PORT_F.byte;
                        }
                        
                    
                    break;
                    }
}


int proces_0()
{
int wynik;
bit kolejkowanie_na_zjezdzalni = 0;
wynik = 0;


switch(proces[0])
    {
    case 0:
        proces[0] = 1;
        zerowanie_czasu();
        kolejkowanie_na_zjezdzalni = 1; //Pierre
        wyslij(107, 1);        // event etapu -> Pi
        
    break;
    
    case 1: 
            PORTC.7 = 1;      //silownik 1 w gore
            
            //dekatywuj_czujniki_gdy_wiezyczka_stoi();
            
            if(sprawdz_pin2(PORTHH,0x73) == 0 && sprawdz_pin3(PORTHH,0x73) == 0)  //widzi preta      
                {
                sek0_7s = 0;
                sek0 = 0;       
                proces[0] = 2;
                jest_pret_pod_czujnikami = 1;
                komunikat_5_na_panel();
                }
            else
                {
                if(sek0 > 20)
                    {
                    komunikat_4_na_panel();
                    sek0 = 0;
                    }
                }
    break;
        
    case 2:  
            if(sek0 > 40)  //silownik 1 w dol
                {
                PORTC.7 = 0;
                sek0 = 0;
                proces[0] = 3;
                }
    break;
    case 3:
            if(sek0 > 20)  //20 13.09  //60   //40 11.23
                {
                PORTC.6 = 1; //silownik 2 w gore
                sek0 = 0;
                proces[0] = 4;
                }          
                  
    break;
    case 4:
            if(sek0 > 20) //20 13.09  //60    //40 11.23
                {
                PORTC.6 = 0; //silownik 2 w dol
                PORTB.4 = 1; //silownik pozycjonujacy na zjezdzalni wzdloz
                sek0 = 0;
                proces[0] = 5;
                } 
    break;
    
    case 5:
            if(sek0 > 40)       //60
                {
                PORTB.4 = 0; //silownik pozycjonujacy na zjezdzalni wzdloz
                sek0 = 0;
                proces[0] = 6;
                }
    
    break;
    
    case 6:
            if(sprawdz_pin2(PORTHH,0x73) == 0 && sprawdz_pin3(PORTHH,0x73) == 1)    //       
                {
                //proces[0] = 3;
                proces[0] = 1;
                sek0 = 21;
                }
                
            if(sprawdz_pin2(PORTHH,0x73) == 1 && sprawdz_pin3(PORTHH,0x73) == 0)       
                {
                //proces[0] = 3;
                proces[0] = 1;
                sek0 = 21;
                }
                
            if(sprawdz_pin2(PORTHH,0x73) == 0 & sprawdz_pin3(PORTHH,0x73) == 0)       
                {
                proces[0] = 3;
                sek0 = 21;
                }    
                    
            if(sprawdz_pin2(PORTHH,0x73) == 1 && sprawdz_pin3(PORTHH,0x73) == 1)   // 
                {
                proces[0] = 7;
                }    
            
    
    break;
    

    case 7:
            if(sek0 > 20)    //60  tu byla chyba akcja jak dalem na 20, zwiekszam czas na 40, 20 bylo ok chwilowo daje 30    //30 11.23
                {
                PORTC.5 = 1; //silownik 3 w gore
                sek0 = 0;
                proces[0] = 8;
                } 
    break;
    
    case 8:
            if(sek0 > 20)      //60
                {
                PORTC.5 = 0; //silownik 3 w dol
                PORTB.4 = 1; //silownik pozycjonujacy na zjezdzalni wzdloz
                sek0 = 0;
                proces[0] = 9;
                } 
    break;
    
    case 9:
            if(sek0 > 50)  //10
               {
               PORTB.4 = 0; //silownik pozycjonujacy na zjezdzalni wzdloz
               proces[0] = 10;
               //proces[0] = 1;
               }                
    break;
    
    case 10:
            //if(sek0_7s > czas_monterow)
            //    {
                kolejkowanie_na_zjezdzalni = 0; //Pierre
                wyslij(107, 0);        // event etapu -> Pi
                sek0 = 0;
                proces[0] = 0;
                wynik = 1;
                if(start == 1)  //do sytuacji startowej
                    start = 2;
            //    }   
                                    
    break;
    }


return wynik;
}


int proces_1()
{
int wynik;
bit przygotowanie_nakrecanie = 0; //Pierre
wynik = 0;
//zwrotka = 0;

switch(proces[1])
    {
    case 0:
        przygotowanie_nakrecanie = 1; //Pierre
        wyslij(108, 1);        // event etapu -> Pi
        sek1_7s = 0;
        sek1 = 0;
        proces[1] = 1;    
    break;
    
        
    case 1: 
            //if(sek1 > 40)
            //    {
            //    PORTC.4 = 1;      //silownik z glowica kleju nad pret nie ma juz na razie kleju
            //    }
            // dekatywuj_czujniki_gdy_wiezyczka_stoi();
            
            if(sek1 > 60)  //150 01.08  
                {
                //lej klej
                //PORTE.4 = 1;  //lej klej  //wylaczam calkowicie lanie klejem 15.07.2024
                sek1 = 0;       
                proces[1] = 2;
                }              
    break;
        
    case 2:  
            if(sek1 > 30) //100  
                {
                //przestan lac klej
                //PORTE.4 = 0;  //lej klej //wylaczam calkowicie lanie klejem 15.07.2024
                sek1 = 0;
                proces[1] = 3;
                }
    break;
    case 3:
            if(sek1 > 50)
                {
                //PORTC.4 = 0; //cofnij silownik z klejem  //nie ma juz na razie kleju
                sek1 = 0;
                proces[1] = 4;
                }          
                  
    break;
    case 4:
            if(sek1 > 50)  //czekaj az sie cofnie
                proces[1] = 5;
                 
    break;
                   
    case 5:
            //if(sek1_7s > czas_monterow)
            //    {
                przygotowanie_nakrecanie = 0; //Pierre
                wyslij(108, 0);        // event etapu -> Pi
                sek1 = 0;
                proces[1] = 0;
                wynik = 1;
                if(start == 3)  //do sytuacji startowej
                    start = 4;
            //    }   
                                    
    break;
    }




return wynik;
}


// wersja fast ale koliduje to ze przenosze pret na poczotku
int proces_2()
{
int wynik;
bit nakrecanie = 0; //Pierre
wynik = 0;

switch(proces[2])
    {
    case 0:
        nakrecanie = 1; //Pierre
        wyslij(109, 1);        // event etapu -> Pi
        sek2_7s = 0;
        sek2 = 0;
        PORTB.3 = 0; //silownik dociskajacy grzybki - na wszelki wypadek w gore gdyby nie byl
        PORTC.2 = 0; //maly silownik grzybka - droga DO grzebieni
        proces[2] = 1;    
    break;
    
    case 1:    
            
            // dekatywuj_czujniki_gdy_wiezyczka_stoi();
    
            if(sek2 > 1 && na_pewno_przejechalem_grzebieniami_global == 1)
                {
                na_pewno_przejechalem_grzebieniami_global = 0;
                PORTE.2 = 1; //wroc malym silownik grzybka
                sek2 = 0;
                proces[2] = 2;
                } 
    break;
    
    case 2:  
            
            if(metalowe_grzybki == 1)
                {
                grzybek_biezacy_dokrecony = 1;
                sek2 = 0;       
                proces[2] = 9;
                }
                
            if(sek2 > 10)  //30
                {
                PORTC.1 = 1; //wroc duzym pobieraniem grzybka
                PORTB.7 = 1; //docisnij preta
                sek2 = 0;
                
                //dmuchnij
                if(wiezyczka_prozniowa_global == 1)
                    {
                    PORT_F.bits.b6 = 1;   //psikanie powietrzenbem na wiezyczke
                    PORTF = PORT_F.byte;
                    }
                proces[2] = 3;
                } 
    break;
    
    
    case 3:
            if(sek2 > 50)  //30   bylo ale stukalo, zwolnie  
                {
                PORTC.1 = 0; //pobierz grzybek
                il_grzybkow--;
                sek2 = 0;
                proces[2] = 4;
                } 
    break;
    
    case 4:
            //if(sprawdz_pin4(PORTHH,0x73) == 0 | )  //upewnij sie ze grzebienie na dole
            //    {
                //PORTB.7 = 1; //docisnij preta
                if(wiezyczka_prozniowa_global == 1)
                    {
                    PORT_F.bits.b6 = 0;   //psikanie powietrzenbem na wiezyczke - koniec
                    PORTF = PORT_F.byte;
                    }
                sek2 = 0;
                proces[2] = 5;
            //    } 
    break;
    
    
    case 5:
            if(sek2 > 20)  //70
                {
                PORTB.3 = 1;   //docisnij grzybek z gory
                PORTE.2 = 0;  //maly silownik grzybka na luz
                if(wiezyczka_prozniowa_global == 1)
                    {
                    PORT_F.bits.b5 = 1;   //mgielka wodna
                    PORTF = PORT_F.byte;
                    }
                grzybek_biezacy_dokrecony = 0;
                sek2 = 0;
                proces[2] = 6;
                }
    break;
    
    case 6:
            if(sek2 > 40)  //30  
                {
                if(wiezyczka_prozniowa_global == 1)
                    {
                    PORT_F.bits.b5 = 0;   //mgielka wodna koniec
                    PORTF = PORT_F.byte;
                    }
                //while(1)
                //    {
                //    }
                
                PORTA.1 = 1;  //silnik dokrecajacy grzybki
                PORTC.3 = 1; //przysun silnik
                sek2 = 0;
                proces[2] = 7;
                }
    
    break;
    
    case 7: 
            
            if(sprawdz_pin5(PORTKK,0x79) == 0 & grzybek_biezacy_dokrecony == 0)
                {
                grzybek_biezacy_dokrecony = 1;
                sek2 = 0;
                }
            
          
            if(grzybek_biezacy_dokrecony == 1 & sek2 >= czas_silnika_dokrecajacego_grzybki)
                {
                PORTB.3 = 0;   //silownik dociskajacy grzybek z gory
                PORTA.1 = 0;  //silnik dokrecajacy grzybki 
                sek2 = 0;                                  
                proces[2] = 8;
                }
                
            if(sek2 > czas_silnika_dokrecajacego_grzybki_stala)       //maks 200, min 20
                {
                PORTB.3 = 0;   //silownik dociskajacy grzybek z gory
                PORTA.1 = 0;  //silnik dokrecajacy grzybki
                licznik_niezakreconych_grzybkow++;
                grzybek_biezacy_dokrecony = 0;
                sek2 = 0;
                proces[2] = 8;
                }
            
    
    break;
    
    case 8:
             if(sek2 > 0 & grzybek_biezacy_dokrecony == 1)   //NOWE 18.09.2018   
                 PORTC.2 = 1; //maly silownik grzybka - droga DO grzebieni       
             if(sek2 > 0 & grzybek_biezacy_dokrecony == 0)   //NOWE 18.09.2018   
                 PORTC.2 = 1; //maly silownik grzybka - droga DO grzebieni
             
             if(sek2 > 5 & grzybek_biezacy_dokrecony == 1)    
                {
                //PORTC.3 = 0; //odsun silnik  
                PORTB.7 = 0; //przestan dociskac pret////////
                //PORTC.2 = 1; //maly silownik grzybka - droga DO grzebieni
                if(sek2 > 13)
                    {
                    PORTB.7 = 1;  //docisnij pret
                    sek2 = 0;       
                    proces[2] = 9;
                    }
                }
             
             if(sek2 > 5 & grzybek_biezacy_dokrecony == 0)    
                {
                //PORTC.3 = 0; //odsun silnik  
                PORTB.7 = 0; //przestan dociskac pret////////
                //PORTC.2 = 1; //maly silownik grzybka - droga DO grzebieni
                if(sek2 > 13)
                    {
                    PORTB.7 = 1;    //docisnij pret
                    sek2 = 0;       
                    proces[2] = 9;
                    }
                }
                
             
                            
    break;
    
    
    case 9: 
            if(sek2 > 5)    
                {
                PORTC.3 = 0; //odsun silnik  
                if(sek2 > 33)    //zmieniam 5 na 30 zeby trzymalo dluzej az odjedzie silnik
                    {
                    PORTB.7 = 0; //pusc preta
                    sek2 = 0;       
                    proces[2] = 10;
                    }
                }
    break;
                   
    case 10:
            //if(sek2_7s > czas_monterow)
            //    {
                nakrecanie = 0; //Pierre
                wyslij(109, 0);        // event etapu -> Pi
                grzybek_dokrecony = grzybek_biezacy_dokrecony;
                sek2 = 0;
                proces[2] = 0;
                wynik = 1;
                if(start == 5)  //do sytuacji startowej
                    start = 6;
            //    }   
                                    
    break;
    }




return wynik;
}

int proces_3()
{
int wynik;
bit wkladanie_do_lufy = 0; //Pierre
wynik = 0;

switch(proces[3])
    {
    case 0:
        wkladanie_do_lufy = 1; //Pierre
        wyslij(110, 1);        // event etapu -> Pi
        sek3_7s = 0;
        sek3 = 0;
        proces[3] = 1;
        licz = 0;    
    break;
    
    case 1:
            
           // dekatywuj_czujniki_gdy_wiezyczka_stoi();
            
            sek3 = 0;
            PORTC.4 = 0;     //bramka grzybkow w gore
            odpytaj_dlugosc_preta();
            if(dlugosc_preta_gwintowanego < 70 || wiezyczka_prozniowa_global == 1)
                  {
                  PORTE.3 = 1;
                  PORTE.4 = 1;
                  }
            proces[3] = 2;
            
                 
    break;
    
    case 2:
            
            
            
            if(sek3 > 50)    //80 02.08
                {
                if(dlugosc_preta_gwintowanego < 70 || wiezyczka_prozniowa_global == 1)
                  {
                  PORTE.3 = 0;
                  PORTE.4 = 0;
                  }
                }             //dodatkowy warunek ze na pewno nkoder nie dziala
            if(sek3 > 60)    
                {
                //if(dlugosc_preta_gwintowanego != 60)    - nie wiem po co to 15.07.2024
                //if(sprawdz_pin5(PORTGG,0x71)== 0 && start >= 7)
                
                
                PORT_F.bits.b0 = 0;   //czujniki deaktywacja         
                PORTF = PORT_F.byte;            
                
                
                PORTB.1 = 1; //si�ownik chwytania lancy
                
                
                
                
                //if(start < 7)
                //    PORTB.1 = 1;    
                    
                PORTB.0 = 1; //otwarcie szczek w lancy - silownik z boku
                sek3 = 0;
                proces[3] = 3;
                }
            
    
    break;
    
    
    case 3: 
            if(grzybek_dokrecony == 1 & metalowe_grzybki == 0 & oczekiwanie_na_poprawienie == 0 & grzybek_jest_nakrecony_na_precie == 1) 
                {
                proces[3] = 4;
                sek3 = 0;
                }
            else
                {
                wydaj_dzwiek();
                komunikat_15_na_panel();
                oczekiwanie_na_poprawienie = 1;
                if(sprawdz_pin7(PORTHH,0x73) == 0)
                    {
                    if(grzybek_jest_nakrecony_na_precie == 0 & start >= 7)
                        licznik_wylatujacych_grzybkow++;
                    proces[3] = 4;
                    sek3 = 0;
                    }    
                }
    break;
    
    case 4:
                           
                
                    
                    if(dlugosc_preta_gwintowanego != 60)
                        {
                        komunikat_czysc_na_panel();
                        oczekiwanie_na_poprawienie = 0;
                        PORTB.5 = 1; //si�ownik ma�y chwytania pr�cika
                        }
                    
                    if(dlugosc_preta_gwintowanego == 60 & sprawdz_pin7(PORTHH,0x73) == 0)
                        {
                        skonczony_proces[0] = 0;
                        skonczony_proces[1] = 0;
                        skonczony_proces[2] = 0;
                        skonczony_proces[3] = 0;
                        zerowanie_czasu();
                        jest_pret_pod_czujnikami = 0;
                        proces[3] = 0;
                        start = 7;
                        przenies_pret_gwintowany();
                        }
                        
                        
                   if(dlugosc_preta_gwintowanego != 60)
                        {
                        sek3 = 0;
                        proces[3] = 5; //WYWALAM NA RAZIE PRZEJSCIE DALEJ ABY UPROSCIC              
                        }
    break;
    
    case 5:
            
            if(sek3 > 25 & sprawdz_pin5(PORTHH,0x73) == 1 & PORTB.5 == 1) //nie dojechal do konca czyli jest precik  //50 02.08
                {
                //PORTB.1 = 1; //si�ownik chwytania lancy
                //PORTB.0 = 1; //otwarcie szczek w lancy - silownik z boku
                PORTB.6 = 1; //silownik obrotowy na ktorym jest maly chwytajacy precik 
                sek3 = 0;
                proces[3] = 6;
                }
            if(sek3 > 50 & sprawdz_pin5(PORTHH,0x73) == 0) // dojechal do konca czyli jest precika nie ma
                {
                sek3 = 0;
                wydaj_dzwiek();
                komunikat_14_na_panel();
                PORTB.5 = 0; //si�ownik ma�y chwytania pr�cika
                }
            if(PORTB.5 == 0 & sprawdz_pin7(PORTHH,0x73) == 0)
                 {
                 komunikat_czysc_na_panel();
                 proces[3] = 4;
                 }
            
             
    break;

    case 6:
            
            if(sek3 > 25)  //50 02.08  
                {
                //PORTB.1 = 1; //si�ownik chwytania lancy
                PORTB.2 = 1; //wkladanie do lancy precika z grzybkiem
                sek3 = 0;
                proces[3] = 7;
                } 
    break;
    
    case 7:
            
            if(sek3 > 30)  //50 02.08  
                {
                //if(sprawdz_pin0(PORTKK,0x79) == 1)       
                //    licznik_niewlozonych_pretow_z_grzybkiem++;    
                PORTB.0 = 0; //zacisniecie szczek w lancy - silownik z boku
                sek3 = 0;
                proces[3] = 8;
                } 
    break;
    
    case 8:
           
            if(sek3 > 30)  //50  02.08  
                {
                PORTB.5 = 0; //si�ownik ma�y chwytania pr�cika - puszczenie precika
                //PORTB.1 = 0; //si�ownik chwytania lancy - puszczenie
                sek3 = 0;
                proces[3] = 9;  ///bylo 9 omijam teraz te dwa ponizej  //jednak finalnie nie omijam
                                //jednal omijam tylko jednego ponizej
                }
    break;
    
    
        
    case 9: 
            if(sek3 > 20)        //zmieniam dnia 19.12.2025 - by�o 10
                {
                if(wiezyczka_prozniowa_global == 0)
                    PORTB.2 = 0; //wkladanie do lancy precika z grzybkiem - powrot silownikiem -wylaczam dnia 08.01.2025 dla prozni 
                sek3 = 0;       
                proces[3] = 10;
                }
    break;
       
    case 10: 
            if(sek3 > 20)       //zmieniam dnia 19.12.2025 - by�o 10
                {  
                PORTB.1 = 0; //si�ownik chwytania lancy - puszczenie
                //PORTB.6 = 0; //silownik obrotowy na ktorym jest maly chwytajacy precik - powrot
                PORTC.4 = 1;  //bramka grzybkow z precikiem znowu sie blokuje 
                sek3 = 0;       
                proces[3] = 11;
                }
    break;
    
    
    
                   
    case 11:                             
                         //& sprawdz_pin1(PORTKK,0x79) == 0               
            if(sek3 > 20 )
                {
                wkladanie_do_lufy = 0; //Pierre
                wyslij(110, 0);        // event etapu -> Pi
                sek3 = 0;
                proces[3] = 0;
                wynik = 1;
                il_pretow_gwintowanych--;  
                aktualizuj_wyswietlacz_ilosci();
                 
                if(start == 7)  //do sytuacji startowej
                    {
                    start = 8;
                    monter_1_time = 0;
                    monter_2_time = 0;
                    monter_3_time = 0;
                    }
                }   
                                    
    break;
    }


return wynik;
}


void procesy()
{
if(skonczony_proces[0] == 0 & start != 0)
  skonczony_proces[0] = proces_0();  
        
if(skonczony_proces[1] == 0 & start != 0 & start != 1 & jest_pret_pod_czujnikami == 1)
  skonczony_proces[1] = proces_1();        
      
if(skonczony_proces[2] == 0 & start != 0 & start != 1 & start != 2 & start != 3 & start != 4 & jest_pret_pod_czujnikami == 1)
    skonczony_proces[2] = proces_2();
          
if(skonczony_proces[3] == 0 & start != 0 & start != 1 & start != 2 & start != 3 & start != 4 & start != 5 & start != 6 & jest_pret_pod_czujnikami == 1)
  skonczony_proces[3] = proces_3();
}

void wyzeruj_monterow()
{
monterzy_skonczyli = 0;
monter_1_skonczyl = 0;
monter_2_skonczyl = 0;
monter_3_skonczyl = 0;
monter_1_time = 0;
monter_2_time = 0;
monter_3_time = 0;
wyswietl_czas_procesu();
zerowanie_czasu();
//if(skonczony_proces[0] == 0)
//    wyswietl_czas_procesu();
}



void zerowanie_procesow()
{
int wznowienie_pracy_bo_wlozyla_prety = 0;
int liczenie;
long int czestosc_komunikacji;
czestosc_komunikacji = 0;
liczenie = 0;

if(skonczony_proces[0] == 1 & start == 2)
        {
        z = czekaj_na_guzik_start();
        klej = czekaj_na_klej();
        //klej_slave = czekaj_na_klej_slave();
        klej_slave = 1;
        if(z == 1 & klej == 1 & klej_slave == 1)
            {
            przenies_pret_gwintowany();  //chodzi w whilu dopoki nie zrobi
            wyswietl_czas_procesu();
            odpytaj_parametry_z_panelu(0);
            skonczony_proces[0] = 0;
            zerowanie_czasu();
            jest_pret_pod_czujnikami = 0;
            start = 3;
            }
        }
        
if(skonczony_proces[0] == 1 & skonczony_proces[1] == 1 & start == 4) 
        {
        z = czekaj_na_guzik_start();
        klej = czekaj_na_klej();
        //klej_slave = czekaj_na_klej_slave();
        klej_slave = 1;   
        if(z == 1 & klej == 1 & klej_slave == 1)
            {
            przenies_pret_gwintowany();  //chodzi w whilu dopoki nie zrobi
            wyswietl_czas_procesu();
            odpytaj_parametry_z_panelu(0);
            skonczony_proces[0] = 0;
            skonczony_proces[1] = 0;
            zerowanie_czasu();
            start = 5;
            jest_pret_pod_czujnikami = 0;
            }
        }
      
if(skonczony_proces[0] == 1 & skonczony_proces[1] == 1 & skonczony_proces[2] == 1 & start == 6) 
        {
        z = czekaj_na_guzik_start();
        klej = czekaj_na_klej();
        //klej_slave = czekaj_na_klej_slave();
        klej_slave = 1;   
        if(z == 1 & klej == 1 & klej_slave == 1)
            { 
            //ksp = 0;
            przenies_pret_gwintowany();  //chodzi w whilu dopoki nie zrobi
            wyswietl_czas_procesu();
            odpytaj_parametry_z_panelu(0);
            skonczony_proces[0] = 0;
            skonczony_proces[1] = 0;
            skonczony_proces[2] = 0;
            zerowanie_czasu();
            jest_pret_pod_czujnikami = 0;
            start = 7;
            }
        }

//to ju� jest ten glowny co chodzi w kolko      
if(skonczony_proces[0] == 1 & skonczony_proces[1] == 1 & skonczony_proces[2] == 1 & skonczony_proces[3] == 1 & start >= 8) 
        {
        z = czekaj_na_guzik_start();
        klej = czekaj_na_klej();
        //klej_slave = czekaj_na_klej_slave();
        klej_slave = 1;                             
        if(monterzy_skonczyli == 1 & z == 1 & klej == 1 & klej_slave == 1)
            {
            monter_slave = 0;
            czestosc_komunikacji = 0;
            while(monter_slave == 0 & start >=11 & tryb_male_puchary == 0)   
                {                                                                
                czestosc_komunikacji++;
                if(czestosc_komunikacji == 1)
                    monter_slave = czekaj_na_odpuszczenie_szczek();
                if(czestosc_komunikacji > 100)
                    czestosc_komunikacji = 0;
                          
                if(monter_slave == 0 & liczenie == 0)   //nie nacisnal o czasie szczek
                      {
                      licznik_spoznien_monter_3_nowy++;
                      liczenie = 1;
                      }
                }
            
            while(monter_slave == 0 & start >=10 & tryb_male_puchary == 1)
                {
                czestosc_komunikacji++;
                if(czestosc_komunikacji == 1)
                    monter_slave = czekaj_na_odpuszczenie_szczek();
                    //tasma lancuchowa powinna ruszyc monter 2 nacisnie pedal i minie okolo 1s
                if(czestosc_komunikacji > 100)
                    czestosc_komunikacji = 0;
                }
                
                
                
                
             
            przenies_pret_gwintowany();  //chodzi w whilu dopoki nie zrobi
                                          //nie dawca zezwolenia na szczeki
                             
            
            
            
            if(il_pretow_gwintowanych == 3)
            {
            tryb_kontynuacji = odpytaj_parametr_panelu(16,128);  //nowe
            if(tryb_kontynuacji == 0)  //jest na odwrot w panelu
                {
                wylacz_maszyne();
                komunikat_czysc_na_panel();
                komunikat_23_panel();
                while(1)
                    {
                    orientator_grzybkow();
                    wznowienie_pracy_bo_wlozyla_prety = odpytaj_parametr_panelu(0,48);
                    
                    putchar(90);  //5A
                    putchar(165); //A5
                    putchar(3);//03  //znak dzwiekowy ze jestem
                    putchar(128);  //80
                    putchar(2);    //02
                    putchar(16);   //10
                    
                    
                    if(wznowienie_pracy_bo_wlozyla_prety == 1)
                        {
                        dlugosc_preta_gwintowanego = odpytaj_parametr_panelu(0,64);
                        //il_pretow_gwintowanych = odpytaj_parametr_panelu_duze_liczby(0,112);
                        il_pretow_gwintowanych = 3 + odpytaj_parametr_panelu(0,112);
                        il_pretow_gwintowanych_stala = il_pretow_gwintowanych;  
                        licznik_pucharow = 1;
                        wyswietl_ilosc_zmontowanych_pucharow(licznik_pucharow,licznik_pucharow_global);
                        komunikat_czysc_na_panel();
                        break;
                        }
                    }
                }
            }
            
            
            
            odpytaj_parametry_z_panelu(0);       //jak il_pretow == 4
           
            if(anuluj_biezace_zlecenie == 1 & anuluj_biezace_zlecenie_const == 0)
                {
                anuluj_biezace_zlecenie = 0;
                anuluj_biezace_zlecenie_const = 1;
                ustaw_na_nie_anulacje_zlecenia();
                il_pretow_gwintowanych = 4;
                il_pretow_gwintowanych_stala = il_pretow_gwintowanych; 
                licznik_pucharow = -2;  //0
                }        
            
            
            start++;
            if(start > 1000)
               start = 100;  //zeby sie nie zapetlil start 
            
            if(il_pretow_gwintowanych > 3 & jest_pret_pod_czujnikami == 1)
                {
                jest_pret_pod_czujnikami = 0;
                skonczony_proces[0] = 0;
                skonczony_proces[1] = 0;
                skonczony_proces[2] = 0;
                skonczony_proces[3] = 0;
                }
        
                     
             if(il_pretow_gwintowanych > 2)////////chyba tu zmieniac 26.03.2026
                {
                jest_pret_pod_czujnikami = 1;//bo procesu 0 juz nie ma
                skonczony_proces[1] = 0;
                skonczony_proces[2] = 0;
                skonczony_proces[3] = 0;
                }
                
             if(il_pretow_gwintowanych > 1)
                {
                jest_pret_pod_czujnikami = 1; //bo procesu 0 juz nie ma
                skonczony_proces[2] = 0;
                skonczony_proces[3] = 0;
                }
                
             if(il_pretow_gwintowanych > 0)
                {
                jest_pret_pod_czujnikami = 1; //bo procesu 0 juz nie ma
                skonczony_proces[3] = 0;
                }
            
            wyzeruj_monterow();
                               
            if((licznik_pucharow - 1) == il_pretow_gwintowanych_stala & potw_zielonym_bo_pomyliles_pedal_z_potwierdz == 0)
                    {
                    komunikat_6_na_panel();
                    msek_clock = 0;
                    sek_clock = 0;
                    min_clock = 0;
                    godz_clock = 0;            
                    PORTA.4 = 0;  //wylacz orientator bo wyl
                    PORTA.2 = 0;  //koniec zezwolenia na szczeki
                    ustaw_na_nie_anulacje_zlecenia();
                    wylacz_maszyne();
                    z = 0;
                    start = 0;
                    }
            }
            
        }
}
                 

void kontrola_monterow()
{
//brak monterow

if(start == 8 & monterzy_skonczyli == 0)
      monterzy_skonczyli = 1;

//praca ciagla monterow

if(start >= 9 & monterzy_skonczyli == 0)
    {
    if(monter_1_skonczyl == 0)  //zmianiam & na | i powinno nie byc potrzebne naciskanie guzika monter 1
        {
        if(monter_1_time > czas_monterow & start >= 10)
           licznik_spoznien_monter_1++; 
        monter_1_skonczyl = 1;
        }

    if(monter_2_skonczyl == 0)    //zmianiam & na | i powinno nie byc potrzebne naciskanie guzika monter 2
        {
        if(monter_2_time > czas_monterow & start >= 10)
           licznik_spoznien_monter_2++;
        monter_2_skonczyl = 1;    
        }
    
    
                                              
    if(sprawdz_pin4(PORTKK,0x79) == 0 & monter_3_skonczyl == 0 & start < 11 & tryb_male_puchary == 0)
        {
        if(monter_3_time > czas_monterow & start >= 10)
           licznik_spoznien_monter_3++;
        if(start >=10)   //12 23.03.2016
            {
            licznik_pucharow++;
            licznik_pucharow_global++;    
            wyswietl_ilosc_zmontowanych_pucharow(licznik_pucharow-1,licznik_pucharow_global-1);
            wyswietl_parametry(licznik_wylatujacych_grzybkow,licznik_niezakreconych_grzybkow,licznik_wyzwolen_kurtyny,licznik_niewlozonych_pretow_z_grzybkiem,licznik_spoznien_monter_1_2,licznik_spoznien_monter_3_nowy);
            }
        monter_3_skonczyl = 1;    
        }
    
     
    
     if(sprawdz_pin4(PORTKK,0x79) == 0 & monter_3_skonczyl == 0 & start == 9 & tryb_male_puchary == 1)
        {
        monter_3_skonczyl = 1;
        }
     
     
     if((sprawdz_pin4(PORTKK,0x79) == 0 | monter_3_skonczyl == 0) & start >= 10 & tryb_male_puchary == 1)      
        {
        if(monter_3_time > czas_monterow & start >= 10)
           licznik_spoznien_monter_3++;
        if(start >=10)   //12 23.03.2016
            {
            licznik_pucharow++;
            licznik_pucharow_global++;
            wyswietl_ilosc_zmontowanych_pucharow(licznik_pucharow-1,licznik_pucharow_global-1);
            wyswietl_parametry(licznik_wylatujacych_grzybkow,licznik_niezakreconych_grzybkow,licznik_wyzwolen_kurtyny,licznik_niewlozonych_pretow_z_grzybkiem,licznik_spoznien_monter_1_2,licznik_spoznien_monter_3_nowy);
            }
        monter_3_skonczyl = 1;    
        }
     
     
     
     
     
     
     
    
     if((sprawdz_pin4(PORTKK,0x79) == 0 | monter_3_skonczyl == 0) & start >= 11 & tryb_male_puchary == 0)      //nowe cale if 31.07
        {
        if(monter_3_time > czas_monterow & start >= 10)
           licznik_spoznien_monter_3++;
        if(start >=10)   //12 23.03.2016
            {
            licznik_pucharow++;
            licznik_pucharow_global++;
            wyswietl_ilosc_zmontowanych_pucharow(licznik_pucharow-1,licznik_pucharow_global-1);
            wyswietl_parametry(licznik_wylatujacych_grzybkow,licznik_niezakreconych_grzybkow,licznik_wyzwolen_kurtyny,licznik_niewlozonych_pretow_z_grzybkiem,licznik_spoznien_monter_1_2,licznik_spoznien_monter_3_nowy);
            }
        monter_3_skonczyl = 1;    
        }
    

    if(monter_1_skonczyl == 1 & monter_2_skonczyl == 1 & monter_3_skonczyl == 1)
       {
       monterzy_skonczyli = 1; 
       }
    }

}


void wznowienie_pracy_po_wykonaniu_zadania()
{
if(start == 0)
         {  
         if(z == 0)
            {
            z = czekaj_na_guzik_start();
            wyswietl_czas_przezbrojenia();
            }
         else
            {
            odpytaj_parametry_z_panelu(1);
            //if(tryb_male_puchary == 1)
            komunikacja_startowa_male_puchary(wynik_wyboru_male_puchary);
            
            //zajechalem = 0;                             
            //while(zajechalem == 0 )
            //    zajechalem = obsluga_startowa_tasmy_lancuchowej();   //wylaczam to jeden bo powodowalo koniecznosc jeszcze resetu po kazdym zleceniu
            //zajechalem = 0;
             
            
            
            zajechalem = 0;
            sekwencja = 0;

            while(zajechalem == 0 | zajechalem == 2 | zajechalem == 3)
                zajechalem = obsluga_startowa_tasmy_lancuchowej();
            zajechalem = 0;
            
            
            licznik_pucharow = 0;
            licznik_spoznien_monter_1 = -1;
            licznik_spoznien_monter_2 = -1;
            licznik_spoznien_monter_3 = -1;
            skonczony_proces[0] = 0;
            skonczony_proces[1] = 0;
            skonczony_proces[2] = 0;
            skonczony_proces[3] = 0;
            komunikat_czysc_na_panel();
            PORTA.4 = 0; //wylacz orientatorchy gdyby chodzil
            anuluj_biezace_zlecenie_const = 0;
            wyswietl_ilosc_zmontowanych_pucharow(licznik_pucharow,licznik_pucharow_global);
            wyswietl_czas_laczny_przezbrajan();
            PORTC.4 = 1;  //bramka grzybkow z precikiem znowu sie blokuje
            start = 1;
            
            }
         }
}


void main(void)
{
// Declare your local variables here
unsigned int val;

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
//PORTA=0x00;
//DDRA=0x00;

// Port A initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRA=(1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);


// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTC=0x00;
DDRC=0xFF;

// Port D initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
//PORTD=0x00;
//DDRD=0xFF;

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Port E initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTE=0x00;
DDRE=0xFF;

// Port F initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T  
//PORTF=0x00;
//DDRF=0x00;

// Port F initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRF=(1<<DDF7) | (1<<DDF6) | (1<<DDF5) | (1<<DDF4) | (1<<DDF3) | (1<<DDF2) | (1<<DDF1) | (1<<DDF0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTF=(0<<PORTF7) | (0<<PORTF6) | (0<<PORTF5) | (0<<PORTF4) | (0<<PORTF3) | (0<<PORTF2) | (0<<PORTF1) | (0<<PORTF0);





// Port G initialization
// Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State4=0 State3=0 State2=0 State1=0 State0=0 
PORTG=0x00;
DDRG=0x1F;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 15,625 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
ASSR=0x00;
TCCR0=0x07;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// OC1C output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;
OCR1CH=0x00;
OCR1CL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// Timer/Counter 3 initialization
// Clock source: System Clock
// Clock value: Timer3 Stopped
// Mode: Normal top=0xFFFF
// OC3A output: Discon.
// OC3B output: Discon.
// OC3C output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer3 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
// Compare C Match Interrupt: Off
TCCR3A=0x00;
TCCR3B=0x00;
TCNT3H=0x00;
TCNT3L=0x00;
ICR3H=0x00;
ICR3L=0x00;
OCR3AH=0x00;
OCR3AL=0x00;
OCR3BH=0x00;
OCR3BL=0x00;
OCR3CH=0x00;
OCR3CL=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
// INT3: Off
// INT4: Off
// INT5: Off
// INT6: Off
// INT7: Off
EICRA=0x00;
EICRB=0x00;
EIMSK=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x01;

ETIMSK=0x00;



// USART0 initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART0 Receiver: On
// USART0 Transmitter: On
// USART0 Mode: Asynchronous
// USART0 Baud Rate: 9600
UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
UCSR0C=(0<<UMSEL0) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
UBRR0H=0x00;
UBRR0L=0x67;

// USART0 initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART0 Receiver: On
// USART0 Transmitter: On
// USART0 Mode: Asynchronous
// USART0 Baud Rate: 115200
//UCSR0A=(0<<RXC0) | (0<<TXC0) | (0<<UDRE0) | (0<<FE0) | (0<<DOR0) | (0<<UPE0) | (0<<U2X0) | (0<<MPCM0);
//UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);
//UCSR0C=(0<<UMSEL0) | (0<<UPM01) | (0<<UPM00) | (0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00) | (0<<UCPOL0);
//UBRR0H=0x00;
//UBRR0L=0x08;


UBRR1H = (unsigned char)(MYUBRR >> 8);
UBRR1L = (unsigned char)(MYUBRR);

UCSR1B = (1<<TXEN1) | (1<<RXEN1);
UCSR1C = (1 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10);

UCSR1A |= (1<<TXC1);



// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI disabled
SPCR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

//////////////////////////
licznik_pucharow = 0;

// Global enable interrupts (WYMAGANE: asynchroniczny TX dziala przez ISR USART1_DRE)
//#asm("sei")

//while (1)
//    {
//        
//        delta_write_param(0x07, 0x06, -5000);
//        delay_ms(1000);
//        licznik_pucharow++;
//        aktualizuj_wyswietlacz_ilosci();
//        delay_ms(1000);
//        monitoruj_do_listy();   // DODANE: zbierz wybrane wartosci do listy
//        wyslij_liste();         // DODANE: wyslij je nieblokujaco (async)
//        //wyslij(10,1);
//        delay_ms(1000);
        
        
  
        
//    }
//////////////////////////







// I2C Bus initialization
i2c_init();

// Global enable interrupts
#asm("sei")

//WE
//IN1 na karcie 8
//IN2 na pcf
//sprawdz_pin0(PORTHH,0x73)//PINA.0    czujnik ci�nienia
//sprawdz_pin1(PORTHH,0x73)//PINA.1    czujnik widzenia grzybka
//sprawdz_pin2(PORTHH,0x73)//PINA.2    czujnik 1 widzenia pr�ta gwintowanego na rynnie
//sprawdz_pin3(PORTHH,0x73)//PINA.3   czujnik 2 widzenia pr�ta gwintowanego na rynnie
//sprawdz_pin4(PORTHH,0x73)//PINA.4    czujnik od silnika grzebieni
//sprawdz_pin5(PORTHH,0x73)//PINA.5    sygnal braku kleju - informacja z dozownika kleju - nie wykorzystuje, zmieniam na czujnik chwycenia preta
//sprawdz_pin6(PORTHH,0x73)//PINA.6    sygnal gotowosci do pracy dozownika kleju - zmieniam na czujnik czy sa prety gorne
//sprawdz_pin7(PORTHH,0x73)//PINA.7    guzik czy monter dokrecil grzybka, je�eli by�a taka potrzeba



//IN2 na karcie 8
//IN3 na pcf
//sprawdz_pin0(PORTKK,0x79)//PINF.0   wlacznik tasmociagu monterow 1 dawnij, teraz: czujnik czy w�o�y� grzybek do lufy //zmieniam dnia 06.07.2022 na informacje z zoltego o zapaleniu zoltej lampki
            //czyli jak 1 to zapalona lampka, jak 0 to zgaszona
//sprawdz_pin1(PORTKK,0x79)//PINF.1    teraz czy si�ownik chwytaj�cy wie�e jest zamkniety  //znowu idzie out//teraz sygnal odpowiedzi od Slave 
//sprawdz_pin2(PORTKK,0x79)//PINF.2   monter 1 wykonal dawniej //tu teraz podpinamy czujnik czy jest grzybek 
//sprawdz_pin3(PORTKK,0x79)//PINF.3    monter 2 wykonal dawnij //teraz sygnal ze kurtyna jest aktywna 
//sprawdz_pin4(PORTKK,0x79)//PINF.4   monter 3 wykonal (dawniej czujnik indukcyjny widzacy wieze - ju� go nie ma)
//sprawdz_pin5(PORTKK,0x79)//PINF.5    czujnik czy dokrecil grzybka
//sprawdz_pin6(PORTKK,0x79)//PINF.6    czujnik ze jedzie lancuchowy
//sprawdz_pin7(PORTKK,0x79)//PINF.7    sygnal ze kurtyna zadzialala - jak ktos wlozyl lape to bedzie 0
            //jak monterzy zresetuja to sama mi sie pojawi 1

//IN3 na karcie 8
//IN4 na pcf
//(sprawdz_pin0(PORTGG,0x71)  //czujnik wykrywajacy kolor zielony
//(sprawdz_pin1(PORTGG,0x71)  //guzik osoby dokladajacej prety - potwierdza ze wlozyla w przypadku trybu kontunacji
//(sprawdz_pin2(PORTGG,0x71)  //czujnik wykrywajacy kolor czerwony
//(sprawdz_pin3(PORTGG,0x71)  //nowy kabel do czujnika zatrzymywania grzebieni - odpinam
//(sprawdz_pin4(PORTGG,0x71)  //nowy kabel kolor niebieski
//(sprawdz_pin5(PORTGG,0x71)  //nowy kabel kolor zolty



//WY
//OUT1
//PORTB.0   zaciskanie grzybka w lancy
//PORTB.1   si�ownik chwytania lancy
//PORTB.2   wkladanie do lancy precika z grzybkiem
//PORTB.3   silownik przytrzymujacy grzybka od gory
//PORTB.4   silownik pozycjonujacy preta jeszcze na zjezdzalni
//PORTB.5   si�ownik ma�y chwytania pr�cika
//PORTB.6   silownik obrotowy na ktorym jest maly chwytajacy precik
//PORTB.7   silownik dociskajacy pret na grzebieniach

//OUT2
//PORTC.0   ZMIANA - SYGNALIZATOR DZWIEKOWY
//PORTC.1   silownik pobierania grzybow duzy
//PORTC.2   silownik pobierania grzybow maly - droga DO grzebienie pod ci�nieniem
//PORTC.3   silownik na ktorym jest silnik dokrecajacy grzybki
//PORTC.4   dawniej silownik trzymajcy strzelanie klejem - zmieniam na silownik bramki precikow z grzybkiem
//PORTC.5   si�ownik 3 kolejkuj�cy na rynnie
//PORTC.6   si�ownik 2 kolejkuj�cy na rynnie  
//PORTC.7   si�ownik 1 kolejkuj�cy na rynnie

//OUT4
//PORTA.0//PORTD.0   silnik przenosnika pretow 
//PORTA.1//PORTD.1   silnik dokrecajacy grzybki
//PORTA.2//PORTD.2   DAWNIEJ kana� 1 RS232, TERAZ   zgoda na zacisniecie szczek w wersji komunikacja uproszczona    
//PORTA.3//PORTD.3   DAWNIEJ kana� 1 RS232, TERAZ sygnal do przesylania informacji malych pucharach
//PORTA.4//PORTD.4   orientator grzybkow
//PORTA.5//PORTD.5   dozownik kleju zasilanie 220V //juz nie - teraz obrot przez optoprzekaznik 
//PORTA.6//PORTD.6   SPALONY DAWNIEJ, TERAZ DAJE TU SYGNAL JAKO PRZECINEK MIEDZY PACZKAMI DANYCH - informacja o malych puchyarach 
//PORTA.7//PORTD.7   LAMPA BRAK PRETOW

//OUT3
//PORTE.0   kana� 0 RS232
//PORTE.1   kana� 0 RS232
//PORTE.2   silownik pobierania grzybow maly - droga OD grzebienie pod ci�nieniem  
//PORTE.3   PSIKANIE NA GRZYBEK zeby nie spadl przy malych pretach
//PORTE.4   wlaczenie lania kleju  - moge cos tu dawac!!!!!!!!25.07.2022    //tu daje wysuniecie psikania na male prety
//PORTE.5   sekwencja startowa pivexin
//PORTE.6   manipulator wykonal pivexin
//PORTE.7   sygnal synchronizacji dla procesora slave

//OUT5
//PORTF.0    deaktywacja czujnikow wykrywajacych wiezyczke
//PORTF.1    deaktywacja czujnikow pojemnosciowych wykrywajacych wiezyczke
//PORTF.2    sygnal do procesora ciezkiego kamienia zadania zsuniecia ciasno lapek
//PORTF.3    sygnal do procesora ciezkiego kamienia dodatkowy kolor brazowy
//PORTF.4    zasilanie na dozownik kleju (dozownik wody) przez przekaznik
//PORTF.5    lanie kleju/wody
//PORTF.6    psikanie powietrzem 
 
//PROCESY
//proces_0 - kolejkowanie pr�ta na zje�d�alni
//proces_1 - nak�adanie kleju
//proces_2 - nakrecanie grzybka
//proces_3 - pobieranie grzybka i wsadzanie do lancy

delay_ms(2000); //bo panel sie inicjalizuje
delay_ms(2000); //bo panel sie inicjalizuje


putchar(90);  //5A
putchar(165); //A5
putchar(3);//03  //znak dzwiekowy ze jestem
putchar(128);  //80
putchar(2);    //02
putchar(16);   //10

komunikacja_startowa_male_puchary(3);//brak malych pucharow
//komunikacja_startowa_male_puchary(32); testowo do zapalenia wszywtkic lampek

//przeslanie danych do slave
//wnioski do komunikacji - wcale nie trzeba czekac czy monter 3 nie nacisnal szczek
//sygnalem aby tasmociag ruszyl ponownie jest nacisniecie pedala tego nowego przez montera 


//zmienne startowe
start = 0;
czas_monterow = 0;
monter_1_skonczyl = 0;
monter_2_skonczyl = 0;
monter_3_skonczyl = 0;
monterzy_skonczyli = 0;
czas_na_transport_preta = 100;
jest_pret_pod_czujnikami = 0;
stala_czasowa = 62;
//il_pretow_gwintowanych = 5;  //minimum dac 5 w panelu
zajechalem = 0;
sekwencja = 0;
czas_silnika_dokrecajacego_grzybki_stala = 220;
czas_silnika_dokrecajacego_grzybki = 0;  //zmianiam z 35 na 55 bo sie wyrobila guma
dlugosc_preta_gwintowanego = 80;
licznik = 0;
licznik_pucharow = 0;
licznik_spoznien_monter_1 = -1;
licznik_spoznien_monter_2 = -1;
licznik_spoznien_monter_3 = -1;  
ff = 0;
pierwszy_raz = 0;
czas_monterow_stala = 0;
oczekiwanie_na_poprawienie = 0;
czekaj_komunikat = 0;
potw_zielonym_bo_pomyliles_pedal_z_potwierdz = 0;
przejechalem_czujnik_lub_jestem_na_nim = 0;
licznik_niezakreconych_grzybkow = 0;
licznik_wylatujacych_grzybkow = 0;
grzybek_jest_nakrecony_na_precie = 0;
licznik_wyzwolen_kurtyny = 0;
licznik_pucharow_global = 0;
czas_zaloczonego_orientatora = 0;
zaloczono_kurtyne = 0;
anuluj_biezace_zlecenie_const = 0;
wynik_wyboru_male_puchary = 0;
wielkosc_kamienia = 0;
wielkosc_kamienia_duze_puchary = 0;

//PORT_F.bits.b0 = 0;   //podloga w dol//test
//PORTF = PORT_F.byte;

z = 0; //do panela
d = 0;
dd = 0;
gg = 0;
klej = 0;
klej_slave = 0;
monter_slave = 0;



///////////////////////////////////////////
while(start == 0)
    start = ustawienia_startowe();
    
while (1)
      { 
      orientator_grzybkow();
      wznowienie_pracy_po_wykonaniu_zadania();
      procesy();
      kontrola_monterow();
      zerowanie_procesow();
      kontrola_lampki_brak_pretow();   
      }
}








 