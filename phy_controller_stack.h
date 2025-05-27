#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_bt.h"

void phy_controller_init(){
	//Initialize NVS(Non Volatile Storage) to store calibration of BlueTooth Physical Layer Stacks
    esp_err_t error_code_check_nvs_init = nvs_flash_init();
    //const char *err_nvs_variable = esp_err_to_name(error_code_check_nvs_init);
    //printf("%s", err_nvs_variable);
    if (error_code_check_nvs_init == ESP_OK){
		printf("NVS Storage initialize success for BLUETOOTH INIT\n");
	}
	esp_err_t error_code_check_ble_disable= esp_bt_controller_mem_release(ESP_BT_MODE_BLE);
	//const char *err_ble_variable = esp_err_to_name(error_code_check_ble_disable);
	//printf("%s", err_ble_variable);
	if (error_code_check_ble_disable == ESP_OK){
		printf("BLE Controller memory has been released\n");	
	}
	//Controller default options are set up
	esp_bt_controller_config_t bth_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT(); 
	//Initiate the Controller
	esp_err_t err_controller_init = esp_bt_controller_init(&bth_cfg);
	//printf("%s", esp_err_to_name(err_controller_init));
	if (err_controller_init == ESP_OK){
		printf("BlueTooth Controller has been initiated\n");
	}
	//Enable the controller
	esp_err_t blue_controller_enable = esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT); 
	//const char *err_blue_controller_enable = esp_err_to_name(blue_controller_enable);
	if (blue_controller_enable == ESP_OK){
		printf("BlueTooth Controller has been enabled\n");
	}
}