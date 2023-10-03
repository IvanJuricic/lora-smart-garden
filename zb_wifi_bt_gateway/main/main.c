#include <stdio.h>
#include <time.h>
#include "ble_custom.h"
#include "wifi_custom.h"

static const char *TAG = "Main: ESP32-C6";

void app_main() {

    /* Initialize NVS — it is used to store PHY calibration data */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    initCredentialsSemaphore();

    init_ble();
    int wifi_status = 0;

    if(xSemaphoreTake(wifiCredentialsSemaphore, portMAX_DELAY)) {
        ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
        wifi_status = wifi_init_sta();
        if(wifi_status) {
            printf("Wifi connected\n");
        }
    }
}