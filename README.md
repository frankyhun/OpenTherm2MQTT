# OpenTherm Boiler Control via MQTT

This project enables the control of an OpenTherm-compatible boiler using MQTT.

## Hardware Requirements

- [OpenTherm Shield](https://diyless.com/product/master-opentherm-shield)
- WeMos D1 Mini ESP32

## Prerequisites

- OpenTherm-compatible boiler
- MQTT server

## Setup and Installation

1. Update WiFi credentials and MQTT settings in `config.h`. Modify the fields marked with `TODO`.
2. Compile the code using your preferred IDE.
3. Upload the compiled firmware to the D1 Mini ESP32.

## MQTT Topics

### Published Topics

The device publishes boiler status updates and logs to the following MQTT topics:

- `boiler/status`\
  Example payload:
  ```json
  {"heating": "ON", "hotwater": "OFF", "flame": "ON", "modulation": 25, "pressure": 1.5, "temperature": 45.0, "return_temperature": 38.0}
  ```
- `boiler/target`
- `boiler/wifi`
- `boiler/log/info`
- `boiler/log/error`

### Subscribed Topics

The device listens for control commands on the following topics:

- `boiler/control/heating`
  Example payload:
  ```json
  "ON"
  ```
- `boiler/control/hotwater`
  Example payload:
  ```json
  "ON"
  ```
- `boiler/control/heating_setpoint`
  Example payload:
  ```json
  45.0
  ```

## License

This project is open-source and provided under the MIT License.

## Contributing

Contributions and improvements are welcome. Please submit issues or pull requests via the repository.

## Contact

For support or inquiries, please open an issue in the repository.

