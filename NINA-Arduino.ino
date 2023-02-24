#include <WiFi.h>

#include "SPIS.h"
#include "CommandHandler.h"

#define SPI_BUFFER_LEN SPI_MAX_DMA_LEN

uint8_t* commandBuffer;
uint8_t* responseBuffer;

void setupWiFi();

int debug = 0;

void setDebug(int d) {
    debug = d;

    if (debug) {
        Serial.begin(115200);
        Serial.println("Start");
    } else {
        Serial.end();
    }
}

void setup() {
    setDebug(debug);

    setupWiFi();
}


// unsigned long getTime() {
//   int ret = 0;
//   do {
//     ret = WiFi.getTime();
//   } while (ret == 0);
//   return ret;
// }

void setupWiFi() {
  SPIS.begin();

  // TODO: Not implemented. Used for OTA update, but I have disabled it as it caused compiler issues.
//   esp_vfs_spiffs_conf_t conf = {
//     .base_path = "/fs",
//     .partition_label = "storage",
//     .max_files = 20,
//     .format_if_mount_failed = true
//   };

//   esp_err_t ret = esp_vfs_spiffs_register(&conf);

  commandBuffer = (uint8_t*)heap_caps_malloc(SPI_BUFFER_LEN, MALLOC_CAP_DMA);
  responseBuffer = (uint8_t*)heap_caps_malloc(SPI_BUFFER_LEN, MALLOC_CAP_DMA);

  CommandHandler.begin();
}

void loop() {
    // wait for a command
    memset(commandBuffer, 0x00, SPI_BUFFER_LEN);
    int commandLength = SPIS.transfer(NULL, commandBuffer, SPI_BUFFER_LEN);

    if (debug)
        Serial.println(commandLength);

    if (commandLength == 0) {
        return;
    }

    if (debug) {
        Serial.println("COMMAND");

        for (int i=0; i<commandLength; i++) {
            Serial.printf("0x%x ", commandBuffer[i]);
        }
        Serial.println();
    }

    // process
    memset(responseBuffer, 0x00, SPI_BUFFER_LEN);
    int responseLength = CommandHandler.handle(commandBuffer, responseBuffer);

    SPIS.transfer(responseBuffer, NULL, responseLength);

    if (debug) {
        Serial.println("RESPONSE");

        for (int i=0; i<responseLength; i++) {
            Serial.printf("0x%x ", responseBuffer[i]);
        }
        Serial.println();
    }
}