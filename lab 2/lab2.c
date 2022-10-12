#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"

#define LED_GPIO 23
#define BTN_GPIO 18

void taskOne(void* parameter1)
{
    while(1)
    {
        printf("TASK 1 - Nhom 3 L01 - HCMUT K19 \n");	// Ghi them TASK 1 de cho thay de quan sat

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void taskTwo(void* parameter2)
{
    gpio_pad_select_gpio(18);
    gpio_set_direction(18, GPIO_MODE_INPUT);

    while(1)
    {
        if (gpio_get_level(18) == 0)
        {
            printf("TASK 2 - ESP32\n"); 	// Ghi them TASK 2 de cho thay de quan sat

            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
    vTaskDelete(NULL);
}

void app_main(void)
{

    xTaskCreate(
        taskOne,          /* Task function. */
        "TaskOne",        /* String with name of task. */
        10000,            /* Stack size in bytes. */
        NULL,             /* Parameter passed as input of the task */
        0,                /* Priority of the task. */
        NULL                /* Task handle. */
    );            
    
    xTaskCreate(
        taskTwo,          /* Task function. */
        "TaskTwo",        /* String with name of task. */
        10000,            /* Stack size in bytes. */
        NULL,             /* Parameter passed as input of the task */
        1,                /* Priority of the task. */
        NULL                /* Task handle. */
    );            
}