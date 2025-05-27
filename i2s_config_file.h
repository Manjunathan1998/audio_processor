#include "driver/i2s_std.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "driver/i2s_std.h"
#include "driver/gpio.h"
static i2s_chan_handle_t tx_chan;  // Global declaration

void inter_ic_sound(){
i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
chan_cfg.auto_clear = true;
i2s_std_config_t std_cfg = {
	.clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(44100),
    .slot_cfg = I2S_STD_MSB_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO),
    .gpio_cfg = {
    .mclk = I2S_GPIO_UNUSED,
    .bclk = GPIO_NUM_27,
    .ws = GPIO_NUM_14,
    .dout = GPIO_NUM_26,
    .din = I2S_GPIO_UNUSED,
    .invert_flags = {
    .mclk_inv = false,
    .bclk_inv = false,
    .ws_inv = false,
 },
    },
       };
        /* enable I2S */
        ESP_ERROR_CHECK(i2s_new_channel(&chan_cfg, &tx_chan, NULL));
        ESP_ERROR_CHECK(i2s_channel_init_std_mode(tx_chan, &std_cfg));
        ESP_ERROR_CHECK(i2s_channel_enable(tx_chan));
}

void stop_i2s(void) {
    printf("Stopping i2s");
    if (tx_chan) {
        i2s_channel_disable(tx_chan);
        i2s_del_channel(tx_chan);
        tx_chan = NULL;
    }
}
        