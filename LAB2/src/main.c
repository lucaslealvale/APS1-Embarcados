#include "asf.h"

#define NOTE_C4  262   //Defining note frequency
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5 988
#define c  261
#define d  294
#define e  329
#define f  349
#define g  391
#define gS  415
#define a  440
#define aS  455
#define b  466
#define cH  523
#define cSH  554
#define dH  587
#define dSH  622
#define eH  659
#define fH  698
#define fSH  740
#define gH  784
#define gSH  830
#define aH  880
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define MAXSIZE 200

// Config LED
#define LED_PIO           PIOC                 // periferico que controla o LED
#define LED_PIO_ID        12                  // ID do periférico PIOC (controla LED)
#define LED_PIO_IDX       8                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1 << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED

#define LED1_PIO			PIOA
#define LED1_PIO_ID			ID_PIOA
#define LED1_PIO_IDX		0
#define LED1_PIO_IDX_MASK	(1 << LED1_PIO_IDX)

#define LED2_PIO			PIOC
#define LED2_PIO_ID			ID_PIOC
#define LED2_PIO_IDX		30
#define LED2_PIO_IDX_MASK	(1 << LED2_PIO_IDX)

#define LED3_PIO			PIOB
#define LED3_PIO_ID			ID_PIOB
#define LED3_PIO_IDX		2
#define LED3_PIO_IDX_MASK	(1 << LED3_PIO_IDX)

//Condig Buzzer
#define BUZ_PIO				PIOC 
#define BUZ_PIO_ID			ID_PIOC
#define BUZ_PIO_IDX			13
#define BUZ_PIO_IDX_MASK    (1 << BUZ_PIO_IDX)

// Configuracoes do botoes
#define BUT_PIO PIOA
#define BUT_PIO_ID 10
#define BUT_PIO_IDX 11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)


#define BUT1_PIO			PIOD
#define BUT1_PIO_ID			16
#define BUT1_PIO_IDX		28
#define BUT1_PIO_IDX_MASK	(1u << BUT1_PIO_IDX)

#define BUT3_PIO			PIOA
#define BUT3_PIO_ID			10
#define BUT3_PIO_IDX		19
#define BUT3_PIO_IDX_MASK	(1u << BUT3_PIO_IDX)

#define BUT2_PIO			PIOC
#define BUT2_PIO_ID			12
#define BUT2_PIO_IDX		31
#define BUT2_PIO_IDX_MASK	(1u << BUT2_PIO_IDX)
/************************************************************************/
/* constants                                                            */
/************************************************************************/
int pirate_melody[] = {
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,
	
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,
	
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
	NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
	
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_D5, NOTE_E5, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
	NOTE_C5, NOTE_A4, NOTE_B4, 0,

	NOTE_A4, NOTE_A4,
	//Repeat of first part
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,

	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
	NOTE_A4, NOTE_G4, NOTE_A4, 0,
	
	NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
	NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
	
	NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0,
	NOTE_D5, NOTE_E5, NOTE_A4, 0,
	NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
	NOTE_C5, NOTE_A4, NOTE_B4, 0,
	//End of Repeat

	NOTE_E5, 0, 0, NOTE_F5, 0, 0,
	NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
	NOTE_D5, 0, 0, NOTE_C5, 0, 0,
	NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

	NOTE_E5, 0, 0, NOTE_F5, 0, 0,
	NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
	NOTE_D5, 0, 0, NOTE_C5, 0, 0,
	NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};
int pirate_tempo[] = {
	83, 83, 83, 83,
	83, 83, 166,
	333,
	83, 83, 83, 83,
	83, 83, 166,
	333,
	83, 83, 83, 83,
	83, 83, 166,
	333,
	83, 83, 83, 83,
	83, 83, 166,
	166, 55, 55, 55,
	166, 166,
	166, 166,
	166, 166,
	55, 55, 55, 55, 55, 55,
	100, 100, 100,
	100, 100, 100,
	333, 333, 333
};
int underworld_melody[] = {
	NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
	NOTE_AS3, NOTE_AS4, 0,
	0,
	NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
	NOTE_AS3, NOTE_AS4, 0,
	0,
	NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	NOTE_DS3, NOTE_DS4, 0,
	0,
	NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	NOTE_DS3, NOTE_DS4, 0,
	0, NOTE_DS4, NOTE_CS4, NOTE_D4,
	NOTE_CS4, NOTE_DS4,
	NOTE_DS4, NOTE_GS3,
	NOTE_G3, NOTE_CS4,
	NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
	NOTE_GS4, NOTE_DS4, NOTE_B3,
	NOTE_AS3, NOTE_A3, NOTE_GS3,
	0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
	83, 83, 83, 83,
	83, 83, 166,
	333,
	83, 83, 83, 83,
	83, 83, 166,
	333,
	83, 83, 83, 83,
	83, 83, 166,
	333,
	83, 83, 83, 83,
	83, 83, 166,
	166, 55, 55, 55,
	166, 166,
	166, 166,
	166, 166,
	55, 55, 55, 55, 55, 55,
	100, 100, 100,
	100, 100, 100,
	333, 333, 333
};
int starWars_melody[] = {
	a,a,a,f,cH,a,f,cH,a,0,eH,eH,eH,fH,cH,gS,f,cH,a,0
};
int starWars_tempo[] = {
	500,500,500,350,150,500,350,150,650,500,500,500,500,350,150,500,350,150,650,500
};

typedef struct {
	int *notes;
	int *tempo;
	int size;
	int order;
} music;






/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/
void play_song(music music, char *PAUSE, char *status){
	
	if (music.order ==1){
		pio_clear(LED1_PIO,LED1_PIO_IDX_MASK);
		pio_set(LED2_PIO,LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO,LED3_PIO_IDX_MASK);
	}
	else if (music.order==2){
		pio_clear(LED1_PIO,LED1_PIO_IDX_MASK);
		pio_clear(LED2_PIO,LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO,LED3_PIO_IDX_MASK);

	} else {
		pio_clear(LED1_PIO,LED1_PIO_IDX_MASK);
		pio_clear(LED2_PIO,LED2_PIO_IDX_MASK);
		pio_clear(LED3_PIO,LED3_PIO_IDX_MASK);

	}
	

		for (int i=0;i <music.size;i++){
				if (music.notes[i] ==0){
					pio_set(LED_PIO,LED_PIO_IDX_MASK);
					delay_ms(music.tempo[i]);
				} else{
				float temp = (1.0/(float)music.notes[i])*1000.0;
				for (int j=0;j<(music.tempo[i]/temp)*0.9;j++){
					*status = pio_get(BUT_PIO,PIO_DEFAULT,BUT_PIO_IDX_MASK);
					pio_clear(LED_PIO,LED_PIO_IDX_MASK);
				
					if (!*status){
						//pio_clear(BUZ_PIO,BUZ_PIO_IDX_MASK);
						*PAUSE = !*PAUSE;
						delay_ms(700);
						}
					if(*PAUSE) j--; 
					else {
						if(music.notes[i]!=0){
							pio_set(BUZ_PIO,BUZ_PIO_IDX_MASK);
							delay_us(temp*1000.0);
							pio_clear(BUZ_PIO,BUZ_PIO_IDX_MASK);
							delay_us(temp*1000.0);
						}				
					}
				}
				pio_set(LED_PIO,LED_PIO_IDX_MASK);
				delay_ms(80);
			}

		}
	
}

// Função de inicialização do uC
void init(void){
	// Initialize the board clock
	sysclk_init();
	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(LED_PIO_ID);
	pmc_enable_periph_clk(BUZ_PIO_ID);
	pmc_enable_periph_clk(BUT1_PIO_ID);
	pmc_enable_periph_clk(BUT_PIO_ID);
	//pmc_enable_periph_clk();

	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED1_PIO, LED1_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED2_PIO, LED2_PIO_IDX_MASK, 0, 0, 0);
	pio_set_output(LED3_PIO, LED3_PIO_IDX_MASK, 0, 0, 0);


	pio_set_output(BUZ_PIO, BUZ_PIO_IDX_MASK,0,0,0);

	pio_set_input(BUT_PIO, BUT_PIO_IDX_MASK, PIO_PULLUP & PIO_DEBOUNCE);
	pio_pull_up(BUT_PIO,BUT_PIO_IDX_MASK,1);	

	pio_set_input(BUT1_PIO, BUT1_PIO_IDX_MASK, PIO_PULLUP & PIO_DEBOUNCE);
	pio_pull_up(BUT1_PIO,BUT1_PIO_IDX_MASK,1);

	pio_set_input(BUT2_PIO, BUT2_PIO_IDX_MASK, PIO_PULLUP & PIO_DEBOUNCE);
	pio_pull_up(BUT2_PIO,BUT2_PIO_IDX_MASK,1);

	pio_set_input(BUT3_PIO, BUT3_PIO_IDX_MASK, PIO_PULLUP & PIO_DEBOUNCE);
	pio_pull_up(BUT3_PIO,BUT3_PIO_IDX_MASK,1);
	
	//pio_pull_up(BUZ_PIO,BUZ_PIO_IDX_MASK,1);
	
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
	// inicializa sistema e IOs
	init();
	
	music music1;
	music music2;
	music music3;

	music1.notes = &starWars_melody;
	music1.tempo = &starWars_tempo;
	music1.size = (sizeof(starWars_melody)/sizeof(starWars_melody[0]));
	music1.order = 1;

	music2.notes = &underworld_melody;
	music2.tempo = &underworld_tempo;
	music2.size = (sizeof(underworld_melody)/sizeof(underworld_melody[0]));
	music2.order = 2;

	music3.notes = &pirate_melody;
	music3.tempo = &pirate_tempo;
	music3.size = (sizeof(pirate_melody)/sizeof(pirate_melody[0]));
	music3.order = 3;

	char status;
	char PAUSE=0;
	char but_status = 0;
	pio_set(LED_PIO,LED_PIO_IDX_MASK);
	pio_set(LED1_PIO,LED1_PIO_IDX_MASK);
	pio_set(LED2_PIO,LED2_PIO_IDX_MASK);
	pio_set(LED3_PIO,LED3_PIO_IDX_MASK);
	// super loop
	// aplicacoes embarcadas não devem sair do while(1).
	while (1) {
		but_status = pio_get(BUT1_PIO,PIO_DEFAULT, BUT1_PIO_IDX_MASK);
		if (!but_status){
			delay_ms(500);
			play_song(music1,&PAUSE, &status);
		}
		but_status = pio_get(BUT2_PIO,PIO_DEFAULT, BUT2_PIO_IDX_MASK);
		if (!but_status){
			delay_ms(500);
			play_song(music2,&PAUSE, &status);
		}
		but_status = pio_get(BUT3_PIO,PIO_DEFAULT, BUT3_PIO_IDX_MASK);
		if (!but_status){
			delay_ms(500);
			play_song(music3,&PAUSE, &status);
		}
		
			

		//play_song(music2,&STOP,&PAUSE, &status);
		//play_song(music3,&STOP,&PAUSE, &status);
	
		}
			
	return 0;
}