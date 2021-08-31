#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id, thread2_id, thread3_id, thread4_id;

void thread1(void *arg){
  uint8_t state = 0;
  
  while(1){
    state ^= LED1;
    LEDWrite(LED1, state);
    osDelay(200);
  } // while
} // thread1

void thread2(void *arg) {
  uint8_t state = 0;
  
  while (1){
    state ^= LED2;
    LEDWrite (LED2, state);  
    osDelay(300);
  }//while
}//thread2

void thread3(void *arg) {
  uint8_t state = 0;
  
  while (1){
    state ^= LED3;
    LEDWrite (LED3, state);
    osDelay(500);
  }//while
}//thread3

void thread4(void *arg) {
  uint8_t state = 0;
  uint32_t tick;
  
  while (1){
    tick = osKernelGetTickCount();
    state ^= LED4;
    LEDWrite (LED4, state);
    
    osDelayUntil(tick + 100);
  }//while
}//thread4

    void main(void){
  LEDInit(LED4 | LED2 | LED3 | LED1); //Inicializa os leds

  osKernelInitialize(); //Inicializa o kernel do RTOS

  //osThreadNew adiciona uma tarefa as tarefas ativas
  
    thread1_id = osThreadNew(thread1, NULL, NULL);
    thread2_id = osThreadNew(thread2, NULL, NULL);
    thread3_id = osThreadNew(thread3, NULL, NULL);
    thread4_id = osThreadNew(thread4, NULL, NULL);
 
  if(osKernelGetState() == osKernelReady)
    osKernelStart(); //Inicio da execução de tarefas

  while(1);
} // main
