///**
//  ******************************************************************************
//  * @file    main.c
//  * @author  Ac6
//  * @version V1.0
//  * @date    01-December-2013
//  * @brief   Default main function.
//  ******************************************************************************
//*/

#include "stm32f4xx.h"        //inclusão das definições do microcontrolador
#include <stdio.h>            //necessário para usar as funções printf e scanf
#include "Utility.h"
//#include "arm_math.h"


//Protótipo de funções
void Configure_GPIO(void);        //configuração dos pinos de GPIO
void Configure_Timer3(void);    //configuração da base de tempo
void Configure_ADC(void);        //configuração do conversor AD
void Configure_DAC(void);        //configuração do conversor DA

//Definições
#define OFFSET      2048    //offset do conversor DAC
#define MAX_SAMPLE	256		//número máximo de amostras

//Declaração de variáveis globais
int16_t stored_sample[256];    //array de armazenamento de amostras
int16_t sample;                //amostra digitalizada
uint16_t pointer=0;            //ponteiro para o array de armazenamento


int main(void)
{
	Utility_Init();			//configura o sistema de clock
	Configure_GPIO();       //configura os pinos de entrada e saída
	Configure_Timer3();     //configura a base de tempo
	Configure_ADC();        //configura o conversor AD
	Configure_DAC();        //configura o conversor DA
    USART1_Init();          //inicializa a USART1

    //Liga o Timer3 para iniciar as conversões
    TIM3->CR1 |= TIM_CR1_CEN;    //habilita o Timer3 para geração dos gatilhos de conversão

    while(1)
    {
    	//printf("Entrou While\n");
        if(ADC1->SR & ADC_SR_EOC)    //aguarda a amostra estar disponível
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
//            	Delay_ms(500); //Delay para ficar mais fácil de ler, apagar no futuro

//            	while(1);
            	//RODAR A FFT E ATUALIZAR A TELA
            }
        }
    }
}

//Configuração dos pinos de GPIO
void Configure_GPIO(void)
{
    //Configuração dos pinos de GPIO
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;    //habilita o clock do GPIOA
    GPIOA->OSPEEDR = 0;                    //pino PA0 como entrada analógica do ADC
    GPIOA->MODER |= 0b11;                    //pino PA0 como entrada analógica do ADC
    GPIOA->MODER |= 0b11 << 8;                //pino PA4 como saída analógica do DAC
}

//O Timer3 é usado como base de tempo (taxa de amostragem de 48 kHz)
void Configure_Timer3(void)
{
    //Configuração do Timer3 para geração de gatilhos
    //Timer3 gera pulsos de gatilho (TRGO) em cada overflow
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;        //liga o clock do Timer3
    TIM3->PSC = 0;                            //prescaler /1
    TIM3->EGR = TIM_EGR_UG;                    //update event para escrever o valor de PSC
    TIM3->CR2 = TIM_CR2_MMS_1;                //master mode 010: update
    TIM3->ARR = 1749;                        //overflow do contador a cada 20,83 us
    TIM3->CR1 |= TIM_CR1_URS;                //overflow gera um gatilho em TRGO
}

//Configuração do conversor ADC
void Configure_ADC(void)
{
    //Configuração do ADC1
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;        //liga o clock da interface digital do ADC1
    ADC->CCR |= 0b01 << 16;                    //prescaler /4
    ADC1->SQR1 &= ~(0xF << 20);                //conversão de apenas um canal
    ADC1->SQR3 &= ~(0x1F);                    //seleção do canal a ser convertido (IN_0)
    ADC1->SMPR2 = 0b001;                    //sampling time de cada canal do ADC1= (15)cycles*(1/ADCCLK) = 714,29 ns. Conversion time de cada canal = (15+12)cycles*(1/ADCCLK) = 1,28 us
    ADC1->CR2 |= 0b1000 << 24;                //seleciona TIM3_TRGO como fonte de gatilho do ADC1
    ADC1->CR2 |= ADC_CR2_EXTEN_0;            //habilita disparo externo em rising edge no ADC1
    ADC1->CR2 |= ADC_CR2_ADON;                //liga o conversor ADC1
}

//Configuração do conversor DAC
void Configure_DAC(void)
{
    //Configuração do DAC1
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;        //habilita o clock da interface digital do DAC
    DAC->CR |= DAC_CR_BOFF1;                //habilita o buffer analógico do DAC1
    DAC->CR |= DAC_CR_EN1;                    //habilita o canal 1 do DAC1
}
