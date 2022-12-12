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

// #include "bootloader_random.h"



typedef struct
{
    uint8_t ID;
    bool flag;
} Data;

xQueueHandle aQueue;

void aReceptionTask();
// void aRequest();
void aProcess();
void aOtherProcess();

void app_main() {
    aQueue = xQueueCreate(3, sizeof(Data));

    xTaskCreate(
        aReceptionTask,          /* Task function. */
        "Queue Gateway",        /* String with name of task. */
        10000,            /* Stack size in bytes. */
        NULL,             /* Parameter passed as input of the task */
        1,                /* Priority of the task. */
        NULL                /* Task handle. */
    );    

    xTaskCreate(
        aProcess,          /* Task function. */
        "Inportant Process",        /* String with name of task. */
        10000,            /* Stack size in bytes. */
        NULL,             /* Parameter passed as input of the task */
        0,                /* Priority of the task. */
        NULL                /* Task handle. */
    );    

    xTaskCreate(
        aOtherProcess,          /* Task function. */
        "Other Process",        /* String with name of task. */
        10000,            /* Stack size in bytes. */
        NULL,             /* Parameter passed as input of the task */
        0,                /* Priority of the task. */
        NULL                /* Task handle. */
    );    



}

void aReceptionTask() {
    uint8_t count = 0;
    const TickType_t aTicksToWait = pdMS_TO_TICKS(100);


    while (1)
    {
        BaseType_t aStatus;
        Data nData;
        nData .ID = count;

        if (count % 3 == 0) {
            nData.flag = 1;
        }
        else {
            nData.flag = 0;
        }

        if (count % 5 == 0) {
            aStatus = xQueueSendToFront(aQueue, &nData, aTicksToWait);
        }
        else {
            aStatus = xQueueSendToBack(aQueue, &nData, aTicksToWait);
        }

        if (aStatus == pdPASS)
        {
            ;
        }
        else if (aStatus ==errQUEUE_FULL)
        {
            printf("Request with ID %d meet FULL queue\n", count);
        }

        ++count;
        vTaskDelay(900/ portTICK_RATE_MS );
    }
    vTaskDelete(NULL);
    
}

void aProcess() {
    BaseType_t aStatus;
    const TickType_t aTicksToWait = pdMS_TO_TICKS(100);
    Data nData;

    while(1) {
        aStatus = xQueuePeek(aQueue, &nData, aTicksToWait);

        if (aStatus == pdPASS) {
            if (nData.flag == 1) {
                aStatus = xQueueReceive(aQueue, &nData, aTicksToWait);
                if (aStatus == pdPASS)
                {
                    printf("Process Data with ID: %d and FLAG = 1\n", nData.ID);
                }
                else
                {
                    printf("Response: Cound not recieve data\n");
                }
            }
        }
        vTaskDelay(1500/ portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
    
}


void aOtherProcess() {
    BaseType_t aStatus;
    const TickType_t aTicksToWait = pdMS_TO_TICKS(100);
    Data nData;

    while(1) {
        aStatus = xQueuePeek(aQueue, &nData, aTicksToWait);

        if (aStatus == pdPASS) {
            if (nData.flag == 0) {
                aStatus = xQueueReceive(aQueue, &nData, aTicksToWait);
                if (aStatus == pdPASS)
                {
                    printf("Process Data with ID: %d and FLAG = 0\n", nData.ID);
                }
                else
                {
                    printf("Response: Cound not recieve data\n");
                }
            }
        }
        vTaskDelay(1500/ portTICK_RATE_MS);
    }
    vTaskDelete(NULL);
    
}