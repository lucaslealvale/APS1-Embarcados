/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include "asf.h"

/************************************************************************/
/* defines                                                              */
/************************************************************************/

#include "asf.h"

#define LED_PIO           PIOC                 // periferico que controla o LED
#define LED_PIO_ID        12                  // ID do periférico PIOC (controla LED)
#define LED_PIO_IDX       8                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1 << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED

// Configuracoes do botao
#define BUT_PIO PIOA
#define BUT_PIO_ID 10
#define BUT_PIO_IDX 11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)

/*  Default pin configuration (no attribute). */
#define _PIO_DEFAULT             (0u << 0)
/*  The internal pin pull-up is active. */
#define _PIO_PULLUP              (1u << 0)
/*  The internal glitch filter is active. */
#define _PIO_DEGLITCH            (1u << 1)
/*  The pin is open-drain. */
#define _PIO_OPENDRAIN           (1u << 2)
/*  The internal debouncing filter is active. */
#define _PIO_DEBOUNCE            (1u << 3)

/************************************************************************/
/* constants                                                            */
/************************************************************************/

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
void _pio_set(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_SODR = ul_mask;
}

void _pio_clear(Pio *p_pio, const uint32_t ul_mask)
{
	p_pio->PIO_CODR = ul_mask;
}

void _pio_pull_up(Pio *p_pio, const uint32_t ul_mask,
const uint32_t ul_pull_up_enable){
		
		if(p_pio->PIO_PUDR == 1){
			
		}
		p_pio->PIO_PUER = 1;
}

void _pio_set_input(Pio *p_pio, const uint32_t ul_mask,
        const uint32_t ul_attribute)
{
	p_pio->PIO_ODR = ul_mask;
	if(ul_attribute & _PIO_PULLUP){
		//_pio_se
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
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);

	// Inicializa PIO do botao
	pmc_enable_periph_clk(BUT_PIO_ID);
	//Inicializa PC8 como saída
	_pio_set_input(BUT_PIO, BUT_PIO_MASK, _PIO_PULLUP);
	pio_pull_up(BUT_PIO,BUT_PIO_IDX_MASK,1);
	
}

/************************************************************************/
/* Main                                                                 */
/************************************************************************/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
	// inicializa sistema e IOs
	init();
	
	char status;

	// super loop
	// aplicacoes embarcadas não devem sair do while(1).
	while (1)
	{
		_pio_set(PIOC, LED_PIO_IDX_MASK);      // Coloca 1 no pino LED
		delay_ms(500);                        // Delay por software de 200 ms
		_pio_clear(PIOC, LED_PIO_IDX_MASK);    // Coloca 0 no pino do LED
		delay_ms(500);                        // Delay por software de 200 ms
		status = pio_get(PIOA, PIO_INPUT, BUT_PIO_IDX_MASK);
	}
	return 0;
}
