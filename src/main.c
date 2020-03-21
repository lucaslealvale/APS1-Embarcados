#include "asf.h"
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#include "music.h"

// Config LED
#define LED_PIO           PIOC                 // periferico que controla o LED
#define LED_PIO_ID        12                  // ID do perif�rico PIOC (controla LED)
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

volatile char PAUSE;
volatile char ORDER;

/************************************************************************/
/* constants                                                            */
/************************************************************************/

typedef struct {
	int *notes;
	int *tempo;
	int size;
	char order;
	char *name;
} music;

/************************************************************************/
/* variaveis globais                                                    */
/************************************************************************/

/************************************************************************/
/* prototypes                                                           */
/************************************************************************/

void init(void);
void pause(void);
void order1(void);
void order2(void);
void order3(void);
void leds_song(music music);
void play_song(music music);

/************************************************************************/
/* interrupcoes                                                         */
/************************************************************************/

/************************************************************************/
/* funcoes                                                              */
/************************************************************************/
void pause(void){
	PAUSE = !PAUSE;
}
void order1(void){
	ORDER = 1;
}
void order2(void){
	ORDER = 2;
}
void order3(void){
	ORDER = 3;
}

void leds_song( music m){
	if (m.order ==1){
		pio_clear(LED1_PIO,LED1_PIO_IDX_MASK);
		pio_set(LED2_PIO,LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO,LED3_PIO_IDX_MASK);
	}
	else if (m.order==2){
		pio_clear(LED1_PIO,LED1_PIO_IDX_MASK);
		pio_clear(LED2_PIO,LED2_PIO_IDX_MASK);
		pio_set(LED3_PIO,LED3_PIO_IDX_MASK);

		} else {
		pio_clear(LED1_PIO,LED1_PIO_IDX_MASK);
		pio_clear(LED2_PIO,LED2_PIO_IDX_MASK);
		pio_clear(LED3_PIO,LED3_PIO_IDX_MASK);
	}
}



void play_song(music m){
	
	gfx_mono_draw_string(m.name, 10,10, &sysfont);
	for (int i=0;i <m.size;i++){

		if (m.notes[i] ==0){
			pio_set(LED_PIO,LED_PIO_IDX_MASK);
			delay_ms(m.tempo[i]);
			} else{
			float temp = (1.0/(float)m.notes[i])*1000.0;
			pio_clear(LED_PIO,LED_PIO_IDX_MASK);
			for (int j=0;j<(m.tempo[i]/temp)*0.9;j++){
				
				if(ORDER !=m.order)
				return;

				if(PAUSE)
				j=0;
				else {
					if(m.notes[i]!=0){
						pio_set(BUZ_PIO,BUZ_PIO_IDX_MASK);
						delay_us(temp*1000.0);
						pio_clear(BUZ_PIO,BUZ_PIO_IDX_MASK);
						delay_us(temp*1000.0);
					}
				}
			}
			pio_set(LED_PIO,LED_PIO_IDX_MASK);
			delay_ms(60);
		}
	}
	pio_set(LED1_PIO,LED1_PIO_IDX_MASK);
	pio_set(LED2_PIO,LED2_PIO_IDX_MASK);
	pio_set(LED3_PIO,LED3_PIO_IDX_MASK);
	ORDER=0;
	
}

// Fun��o de inicializa��o do uC
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

	//interrupt do pause
	pio_handler_set(BUT_PIO, BUT_PIO_ID, BUT_PIO_IDX_MASK, PIO_IT_RISE_EDGE, pause);
	pio_enable_interrupt(BUT_PIO, BUT_PIO_IDX_MASK);

	NVIC_EnableIRQ(BUT_PIO_ID);
	NVIC_SetPriority(BUT_PIO_ID, 4); // Prioridade 4
	
	//interrupt da muscic1
	pio_handler_set(BUT1_PIO, BUT1_PIO_ID, BUT1_PIO_IDX_MASK, PIO_IT_RISE_EDGE, order1);
	pio_enable_interrupt(BUT1_PIO, BUT1_PIO_IDX_MASK);

	NVIC_EnableIRQ(BUT1_PIO_ID);
	NVIC_SetPriority(BUT1_PIO_ID, 5); // Prioridade 5
	
	//interrupt da muscic2
	pio_handler_set(BUT2_PIO, BUT2_PIO_ID, BUT2_PIO_IDX_MASK, PIO_IT_RISE_EDGE, order2);
	pio_enable_interrupt(BUT2_PIO, BUT2_PIO_IDX_MASK);

	NVIC_EnableIRQ(BUT2_PIO_ID);
	NVIC_SetPriority(BUT2_PIO_ID, 5); // Prioridade 5

	//interrupt da muscic3
	pio_handler_set(BUT3_PIO, BUT3_PIO_ID, BUT3_PIO_IDX_MASK, PIO_IT_RISE_EDGE, order3);
	pio_enable_interrupt(BUT3_PIO, BUT3_PIO_IDX_MASK);

	NVIC_EnableIRQ(BUT3_PIO_ID);
	NVIC_SetPriority(BUT3_PIO_ID, 5); // Prioridade 5
	
	
	
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
	music1.name= &"Star Wars";

	music2.notes = &underworld_melody;
	music2.tempo = &underworld_tempo;
	music2.size = (sizeof(underworld_melody)/sizeof(underworld_melody[0]));
	music2.order = 2;
	music2.name= &"Underworld";

	music3.notes = &mario_melody;
	music3.tempo = &mario_tempo;
	music3.size = (sizeof(mario_melody)/sizeof(mario_melody[0]));
	music3.order = 3;
	music3.name= &"Mario Theme";

	PAUSE = 0;
	ORDER = 0;
	pio_set(LED_PIO,LED_PIO_IDX_MASK);
	pio_set(LED1_PIO,LED1_PIO_IDX_MASK);
	pio_set(LED2_PIO,LED2_PIO_IDX_MASK);
	pio_set(LED3_PIO,LED3_PIO_IDX_MASK);
	board_init();
	sysclk_init();

	delay_init();

	gfx_mono_ssd1306_init();


	// super loop
	// aplicacoes embarcadas n�o devem sair do while(1).


	while (1) {

		switch (ORDER){
			case 1:
				ORDER = 1;
				leds_song(music1);
				play_song(music1);
				gfx_mono_draw_string("            ", 10,10, &sysfont);

				break;
			case 2:
				ORDER = 2;
				leds_song(music2);
				play_song(music2);
				gfx_mono_draw_string("            ", 10,10, &sysfont);

				break;
			case 3:
				ORDER = 3;
				leds_song(music3);
				play_song(music3);
				gfx_mono_draw_string("            ", 10,10, &sysfont);

				break;
			default:
				break;
		}
	}
	
	return 0;
}