#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"

#include "esp_bt.h"
#include "bt_app_core.h"
#include "bt_app_av.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_a2dp_api.h"
#include "esp_avrc_api.h"
#include "phy_controller_stack.h"
#include "host_stack_bluedroid.h"
#include "esp_heap_caps.h"
#include "i2s_config_file.h"
#include "remote_devices.h"

void mem_calc() {
	printf("Free Heap: %lu bytes\n", (unsigned long)esp_get_free_heap_size());
    }
    
void playstatus_callback(esp_avrc_playback_stat_t playback) {
  switch (playback) {
    case ESP_AVRC_PLAYBACK_STOPPED:
      printf("Stopped.");
      break;
    case ESP_AVRC_PLAYBACK_PLAYING:
      printf("Playing.");
      break;
    default:
      printf("Got unknown playback status %d\n", playback);
  }
}


void my_avrc_callback(esp_avrc_ct_cb_event_t event, esp_avrc_ct_cb_param_t *param) {
    switch (event) {
        case ESP_AVRC_CT_METADATA_RSP_EVT:
            printf("Metadata received: %s\n", param->meta_rsp.attr_text);
            break;
        case ESP_AVRC_CT_CONNECTION_STATE_EVT:
            if (param->conn_stat.connected){
					printf("\nConnected");
					printf("\nRemote Device Connected to -- \n");
					printf("%s", remote_dev_i.remote_device_name);
					}
			printf("\nDisconnected");
            break;
		case ESP_AVRC_PLAYBACK_PLAYING:
			printf("Play status response event");
			break;
        default:
            break;
    }
}

void bluetooth_dinit(){
	//A function to disable the Blue Tooth and its connectivity
	 esp_err_t bluedroid_disable_stat = esp_bluedroid_disable();
	 printf("%s", esp_err_to_name( bluedroid_disable_stat));
	 esp_err_t blue_controller_disarm = esp_bt_controller_disable();
	 printf("%s", esp_err_to_name( blue_controller_disarm));
	 esp_err_t err_controller_init = esp_bt_controller_deinit();
	 printf("%s", esp_err_to_name( err_controller_init));
	 esp_err_t error_code_check_ble_disable= esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT);
	 printf("%s", esp_err_to_name( error_code_check_ble_disable));
}
void app_main(void)
{
	esp_log_level_set("*", ESP_LOG_NONE); 

	mem_calc();
	phy_controller_init();
	host_stack();
	bt_app_task_start_up();
	bt_app_work_dispatch(bt_av_hdl_stack_evt, BT_APP_EVT_STACK_UP, NULL, 0, NULL);
	esp_avrc_ct_init();
    esp_avrc_ct_register_callback(my_avrc_callback);
	//inter_ic_sound();
	// Register the audio state callback
    esp_a2d_sink_init();  // Initialize A2DP sink
   	mem_calc();
}
