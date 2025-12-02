#pragma once

#include "esphome/core/component.h"
#include "esphome/components/output/binary_output.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace i2c_relay {

class I2CRelay : public Component, public output::BinaryOutput, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  void write_state(bool state) override;
};


}  // namespace i2c_relay
}  // namespace esphome
