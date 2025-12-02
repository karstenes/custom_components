import esphome.codegen as cg
from esphome.components import i2c, output
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@keschnier"]
DEPENDENCIES = ["i2c"]

i2c_relay_ns = cg.esphome_ns.namespace("i2c_relay")
I2CRelay = i2c_relay_ns.class_(
    "I2CRelay", output.BinaryOutput, cg.Component, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(I2CRelay),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(0x18))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
    await output.register_output(var, config)
