#include "i2c_relay.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace i2c_relay {

static const char *TAG = "i2c_relay.component";

void I2CRelay::setup() {
  uint8_t rev_cmd = 0x04;
  if (this->write(&initialize_cmd, 1) != i2c::ERROR_OK) {
    this->mark_failed(); // Mark the component as failed if communication fails
    return;
  }
  uint8_t rev_major;
  if (this->read(&rev_major, 1) != i2c::ERROR_OK) {
    this->mark_failed(); // Mark the component as failed if communication fails
    return;
  }
  if (rev_major != 0) { // Example check for a specific response
    ESP_LOGE(TAG, "Initialization failed; revision: %d", rev_major);
    this->mark_failed(); // Mark the component as failed if the response is not
                         // as expected
    return;
  } else {
      uint8_t rev_minor;
      this->read(&rev_minor, 1);
      ESP_LOG(TAG, "Initialization complete; revision: %d, %d", rev_major, rev_minor)
  }
}

void I2CRelay::write_state(bool state) {
    if(state){
        this->write_byte(1, 0xff);
    } else {
        this->write_byte(0, 0xff);
    }
}

void I2CRelay::dump_config() {
  ESP_LOGCONFIG(TAG, "I2C Relay");
  LOG_I2C_DEVICE(this);
}

} // namespace empty_i2c_component
} // namespace esphome
