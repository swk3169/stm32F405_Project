/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "BlinkLed.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 led blink sample (trace via ITM).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// Then demonstrates how to blink a led with 1 Hz, using a
// continuous loop and SysTick delays.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the ITM output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- Timing definitions -------------------------------------------------

// Keep the LED on for 2/3 of a second.
#define BLINK_ON_TICKS  (TIMER_FREQUENCY_HZ * 3 / 4)
#define BLINK_OFF_TICKS (TIMER_FREQUENCY_HZ - BLINK_ON_TICKS)

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include "Timer.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"

GPIO_InitTypeDef gp;
UART_HandleTypeDef UartHandle;

#define countof(a)	(sizeof(a)/sizeof(*(a)))
#define TxBufferSize (countof(TxBuffer)-1)
#define RxBufferSize	(0xFF)

uint8_t TxBuffer[50] = "Booting_UART1\n\r";
//uint8_t TxBuffer[50]="";
uint8_t RxBuffer[RxBufferSize];

unsigned int data;

void my_ms_delay_int_count(volatile unsigned int n) {
	for (n *= 14000; n > 0; n--)
		;
}

void my_us_delay_int_count(volatile unsigned int n) {
	for (n *= 14; n > 0; n--)
		;
}

void UART_config(void) {  // PA9(UART1_Tx), PA10(UART1_Rx)
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;
	__HAL_RCC_USART1_CLK_ENABLE()
	;

	gp.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	gp.Mode = GPIO_MODE_AF_PP;
	gp.Pull = GPIO_NOPULL;
	gp.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gp.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOA, &gp);

	UartHandle.Instance = USART1;
	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UartHandle);

	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
}

void playNote(int note) {
	if (note == 0) {
		// do 1900us on 1900us off 200ȸ �ݺ�(0.8��)
		for (int t = 0; t < 200; t++) {
			GPIOB->ODR = 0x8000;
			my_us_delay_int_count(1900);
			GPIOB->ODR = 0x0000;
			my_us_delay_int_count(1900);
		}
		// off (0.2)
		GPIOB->ODR = 0x0000;
		my_ms_delay_int_count(200);
	} else if (note == 1) {
		for (int t = 0; t < 200; t++) {
			GPIOB->ODR = 0x8000;
			my_us_delay_int_count(1700);
			GPIOB->ODR = 0x0000;
			my_us_delay_int_count(1700);
		}
		// off (0.2)
		GPIOB->ODR = 0x0000;
		my_ms_delay_int_count(200);
	} else if (note == 2) {
		for (int t = 0; t < 200; t++) {
			GPIOB->ODR = 0x8000;
			my_us_delay_int_count(1515);
			GPIOB->ODR = 0x0000;
			my_us_delay_int_count(1515);
		}
		// off (0.2)
		GPIOB->ODR = 0x0000;
		my_ms_delay_int_count(200);
	} else if (note == 3) {
		for (int t = 0; t < 200; t++) {
			GPIOB->ODR = 0x8000;
			my_us_delay_int_count(1433);
			GPIOB->ODR = 0x0000;
			my_us_delay_int_count(1433);
		}
		// off (0.2)
		GPIOB->ODR = 0x0000;
		my_ms_delay_int_count(200);
	} else if (note == 4) {
		for (int t = 0; t < 200; t++) {
			GPIOB->ODR = 0x8000;
			my_us_delay_int_count(1276);
			GPIOB->ODR = 0x0000;
			my_us_delay_int_count(1276);
		}
		// off (0.2)
		GPIOB->ODR = 0x0000;
		my_ms_delay_int_count(200);
	} else if (note == 5) {
		for (int t = 0; t < 200; t++) {
			GPIOB->ODR = 0x8000;
			my_us_delay_int_count(1136);
			GPIOB->ODR = 0x0000;
			my_us_delay_int_count(1136);
		}
		// off (0.2)
		GPIOB->ODR = 0x0000;
		my_ms_delay_int_count(200);
	} else if (note == 6) {
		for (int t = 0; t < 200; t++) {
			GPIOB->ODR = 0x8000;
			my_us_delay_int_count(1012);
			GPIOB->ODR = 0x0000;
			my_us_delay_int_count(1012);
		}
		// off (0.2)
		GPIOB->ODR = 0x0000;
		my_ms_delay_int_count(200);
	} else if (note == 7) {
		for (int t = 0; t < 200; t++) {
			GPIOB->ODR = 0x8000;
			my_us_delay_int_count(956);
			GPIOB->ODR = 0x0000;
			my_us_delay_int_count(956);
		}
		// off (0.2)
		GPIOB->ODR = 0x0000;
		my_ms_delay_int_count(200);
	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef * huart) {
	//RxBuffer[0] += 1;  //a�� ������ b�� �ȴ�.
	HAL_UART_Transmit(&UartHandle, (uint8_t*) RxBuffer, 1, 5);

	if (strcmp((char*) RxBuffer, "1") == 0) {
		RCC->AHB1ENR = 0x00000002;
		GPIOB->MODER = 0x40000000;
		GPIOB->OTYPER = 0;
		GPIOB->PUPDR = 0;
		GPIOB->OSPEEDR = 0;

		unsigned int period, buf;
		for (period = 0x1000; period >= 1; period--) {
			GPIOB->ODR = 0x8000;
			buf = period;
			while (buf--)
				;

			GPIOB->ODR = 0x0000;
			buf = period;
			while (buf--)
				;
		}

	} else if (strcmp((char*) RxBuffer, "2") == 0) {
		RCC->AHB1ENR = 0x00000003;
		GPIOA->MODER |= 0x00000010;
		GPIOA->OTYPER = 0;
		GPIOA->PUPDR = 0;
		GPIOA->OSPEEDR = 0;

		GPIOB->MODER = 0x00000000;
		GPIOB->PUPDR = 0;
		GPIOB->OSPEEDR = 0;

//		unsigned int data;
//
//		data = GPIOB->IDR;
//		if (data & (0x01 << 2)) {
//			GPIOA->ODR = 0x0004;
//		} else {
//			GPIOA->ODR = 0x0000;
//		}

	} else if (strcmp((char*) RxBuffer, "3") == 0) {
		RCC->AHB1ENR = 0x00000002;
		GPIOB->MODER = 0x40000000;
		GPIOB->OTYPER = 0;
		GPIOB->PUPDR = 0;
		GPIOB->OSPEEDR = 0;

		unsigned int period, buf;

		playNote(0);
		playNote(1);
		playNote(2);
		playNote(3);
		playNote(4);
		playNote(5);
		playNote(6);
		playNote(7);
	}
}

void Buzzer(void) {

}

int main(int argc, char* argv[]) {
	// Infinite loop
	UART_config();

	HAL_UART_Transmit(&UartHandle, (uint8_t*) TxBuffer, TxBufferSize, 0xFFFF);

	while (1) {
		//HAL_UART_Transmit(&UartHandle, (uint8_t*) TxBuffer, TxBufferSize, 0xFFFF);
		HAL_UART_Receive_IT(&UartHandle, (uint8_t *) RxBuffer, 1);

		data = GPIOB->IDR;
		if (data & (0x01 << 2)) {
			GPIOA->ODR = 0x0004;
		} else {
			GPIOA->ODR = 0x0000;
		}

	}
	// Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------