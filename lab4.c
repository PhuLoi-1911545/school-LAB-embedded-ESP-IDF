#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "esp_log.h"
#include "esp_timer.h"
#include "esp_sleep.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#define TIMER_1_MAX 10
#define TIMER_2_MAX 5

TimerHandle_t xTimer1;
TimerHandle_t xTimer2;


void periodic_timer_callback(TimerHandle_t arg) {
    const char *name = pcTimerGetTimerName(arg);
    uint32_t count = (uint32_t)pvTimerGetTimerID(arg);
    count ++;

    if(strcmp(name,"Timer 1")) {
        if(count > TIMER_1_MAX) {
            printf("STOP Timer 1\n");
            xTimerStop(arg,0);
        }
        else {
            printf("Timer 1 - Nhom 3 L01 - HCMUT K19\n");
            vTimerSetTimerID(arg,(void*)count);
        }
    }
    else if (strcmp(name,"Timer 2")) {
        if(count > TIMER_2_MAX) {
            printf("STOP Timer 2\n");
            xTimerStop(arg,0);
        }
        else {
            printf("Timer 2 - Nhom 3 L01 - HCMUT K19\n");
            vTimerSetTimerID(arg,(void*)count);
        }
    }
}


void app_main(void)
{

    xTimer1 = xTimerCreate(
        // NULL,          /* Task function. */
        "Timer 1",        /* String with name of task. */
        pdMS_TO_TICKS(2000),            /* Stack size in bytes. */
        pdTRUE,             /* Parameter passed as input of the task */
        0,                /* Priority of the task. */
        periodic_timer_callback                /* Task handle. */
    );            
    
    xTimer2 = xTimerCreate(
        // NULL,          /* Task function. */
        "Timer 2",        /* String with name of task. */
        pdMS_TO_TICKS(3000),            /* Stack size in bytes. */
        pdTRUE,             /* Parameter passed as input of the task */
        0,                /* Priority of the task. */
        periodic_timer_callback                /* Task handle. */
    ); 

    xTimerStart(xTimer1, 0);
    xTimerStart(xTimer2,0);         
}
