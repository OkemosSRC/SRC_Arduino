# SRC Arduino

The Solar Car side of the SRC Telemetry System.

This code is written for the Arduino Uno and is used to relay data from the solar car to the chase car.

Platform IO is used to compile and upload the code to the Arduino.

## Quick Start

1. Install [Platform IO Core](https://platformio.org/)
2. Install Platform IO CLion Plugin
3. Clone this repository
4. Open the project in CLion
6. Connect the Arduino to your computer
7. Upload the code to the Arduino

## Monitoring

To monitor the serial output of the Arduino, use the `pio device monitor` command in the terminal.

## Parsing

### Hash

The hash of a serial communication can be retrieved by the following Regex:

```regexp
\<\^\|BEGIN_HASH\|#\>(\w+)\<#\|END_HASH\|\$\>
```

### Data

The data of a serial communication can be retrieved by the following Regex:

```regexp
\<\^\|BEGIN_DATA\|\>([^]*)\<\|END_DATA\|\$\>
```

### OP Code

The OP Code of a serial communication can be retrieved by the following Regex:

```regexp
\<\^\|BEGIN_OPCODE\|\>(\d+)\<\|END_OPCODE\|\$\>
```

### INFO

The INFO of a serial communication can be retrieved by the following Regex:

```regexp
\<\^\|BEGIN_INFO\|\>(\w+)\<\|END_INFO\|\$\>
```

### Example Data Packet

```
<^|BEGIN_HASH|#>18444d4cb7eccbfa08e0cd03083696d9<#|END_HASH|$><^|BEGIN_OPCODE|>0<|END_OPCODE|$><^|BEGIN_DATA|>ANALOG_PIN_A0:9<->ANALOG_PIN_A1:86<|END_DATA|$>
```

### Example Info Packet

```
<^|BEGIN_HASH|#>7e6e7f46984472572a0369b4763251de<#|END_HASH|$><^|BEGIN_OPCODE|>1<|END_OPCODE|$><^|BEGIN_INFO|>STARTING<|END_INFO|$>
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details
