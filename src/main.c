///**
//  ******************************************************************************
//  * @file    main.c
//  * @author  Ac6
//  * @version V1.0
//  * @date    01-December-2013
//  * @brief   Default main function.
//  ******************************************************************************
//*/

#include "stm32f4xx.h"        //inclus�o das defini��es do microcontrolador
#include <stdio.h>            //necess�rio para usar as fun��es printf e scanf
#include "Utility.h"
//#include "arm_math.h"


//Prot�tipo de fun��es
void Configure_GPIO(void);        //configura��o dos pinos de GPIO
void Configure_Timer3(void);    //configura��o da base de tempo
void Configure_ADC(void);        //configura��o do conversor AD
void Configure_DAC(void);        //configura��o do conversor DA

//Defini��es
#define OFFSET      2048    //offset do conversor DAC
#define MAX_SAMPLE	256		//n�mero m�ximo de amostras

//Declara��o de vari�veis globais
int16_t stored_sample[256];    //array de armazenamento de amostras
int16_t sample;                //amostra digitalizada
uint16_t pointer=0;            //ponteiro para o array de armazenamento


int main(void)
{
	Utility_Init();			//configura o sistema de clock
	Configure_GPIO();       //configura os pinos de entrada e sa�da
	Configure_Timer3();     //configura a base de tempo
	Configure_ADC();        //configura o conversor AD
	Configure_DAC();        //configura o conversor DA
    USART1_Init();          //inicializa a USART1

    //Liga o Timer3 para iniciar as convers�es
    TIM3->CR1 |= TIM_CR1_CEN;    //habilita o Timer3 para gera��o dos gatilhos de convers�o

    while(1)
    {
    	//printf("Entrou While\n");
        if(ADC1->SR & ADC_SR_EOC)    //aguarda a amostra estar dispon�vel
        {
        	//printf("Entrou if");
            int16_t sample = (ADC1->DR) - OFFSET;        //faz a leitura do valor convertido;
            stored_sample[pointer] = sample;
            ++pointer;	//atualiza o ponteiro

            if(pointer == MAX_SAMPLE)
            {
            	pointer = 0;

            	//printf("RODANDO A FFT\n");
            	//printf("Amostras:\n");
//            	printf("start"); // Sincronizar com a leitura em python
            	for(int contador=0; contador <256; ++contador)
            	{
            		printf("%d\n", stored_sample[contador]);
            	}
            	printf("end\n"); // Sincronizar com a leitura em python
//            	Delay_ms(500); //Delay para ficar mais f�cil de ler, apagar no futuro

//            	while(1);
            	//RODAR A FFT E ATUALIZAR A TELA
            }
        }
    }
}

//Configura��o dos pinos de GPIO
void Configure_GPIO(void)
{
    //Configura��o dos pinos de GPIO
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;    //habilita o clock do GPIOA
    GPIOA->OSPEEDR = 0;                    //pino PA0 como entrada anal�gica do ADC
    GPIOA->MODER |= 0b11;                    //pino PA0 como entrada anal�gica do ADC
    GPIOA->MODER |= 0b11 << 8;                //pino PA4 como sa�da anal�gica do DAC
}

//O Timer3 � usado como base de tempo (taxa de amostragem de 48 kHz)
void Configure_Timer3(void)
{
    //Configura��o do Timer3 para gera��o de gatilhos
    //Timer3 gera pulsos de gatilho (TRGO) em cada overflow
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;        //liga o clock do Timer3
    TIM3->PSC = 0;                            //prescaler /1
    TIM3->EGR = TIM_EGR_UG;                    //update event para escrever o valor de PSC
    TIM3->CR2 = TIM_CR2_MMS_1;                //master mode 010: update
    TIM3->ARR = 1749;                        //overflow do contador a cada 20,83 us
    TIM3->CR1 |= TIM_CR1_URS;                //overflow gera um gatilho em TRGO
}

//Configura��o do conversor ADC
void Configure_ADC(void)
{
    //Configura��o do ADC1
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;        //liga o clock da interface digital do ADC1
    ADC->CCR |= 0b01 << 16;                    //prescaler /4
    ADC1->SQR1 &= ~(0xF << 20);                //convers�o de apenas um canal
    ADC1->SQR3 &= ~(0x1F);                    //sele��o do canal a ser convertido (IN_0)
    ADC1->SMPR2 = 0b001;                    //sampling time de cada canal do ADC1= (15)cycles*(1/ADCCLK) = 714,29 ns. Conversion time de cada canal = (15+12)cycles*(1/ADCCLK) = 1,28 us
    ADC1->CR2 |= 0b1000 << 24;                //seleciona TIM3_TRGO como fonte de gatilho do ADC1
    ADC1->CR2 |= ADC_CR2_EXTEN_0;            //habilita disparo externo em rising edge no ADC1
    ADC1->CR2 |= ADC_CR2_ADON;                //liga o conversor ADC1
}

//Configura��o do conversor DAC
void Configure_DAC(void)
{
    //Configura��o do DAC1
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;        //habilita o clock da interface digital do DAC
    DAC->CR |= DAC_CR_BOFF1;                //habilita o buffer anal�gico do DAC1
    DAC->CR |= DAC_CR_EN1;                    //habilita o canal 1 do DAC1
}
