# Airquality Sensor

![image of a sensor](https://github.com/harmoniemand/airquality/blob/main/assets/20201111-_K0A0501.jpg?raw=true)


## Hardware

This hardwarelist is a recommendation. You may use other suppliers for cheaper prices. The printable cases are designed for this hardware.


| Name              | Price | Link
| ----------------- | ----- | ---
| Adafruit BME680   | ~ 27€ | https://eckstein-shop.de/Adafruit-BME680-Temperature-Humidity-Pressure-and-Gas-Sensor-STEMMA-QT
| ESP32             | ~ 10€ | https://www.conrad.de/de/p/joy-it-entwickler-platine-node-mcu-esp32-modul-1656367.html
| WS2812 LED Strip  | ~ 54€ | https://www.conrad.de/de/p/rgb-led-stripe-mit-ws2812b-leds-144-leds-m-2m-rolle-802076536.html
| USB Cable         | ~  2€ |
| USB Power Supply  | ~ 10€ |


## Printable cases

Could be found in 3D Models. Hardware could easily mounted to a wall or just stand on a table.


![rendering of casings](https://github.com/harmoniemand/airquality/blob/main/assets/RenderingEnv_2020-Nov-12_05-47-15AM-000_CustomizedView1602486251_png.png)


## Pins
    
    ESP32           BME680           LED Stripe
     Pin 21 -------> SDA
     Pin 22 -------> SCL
     5V -----------> Vin
     GND ----------> GND
     PIN  5 -------------------------> LED DATA
     5V -----------------------------> LED +
     GND ----------------------------> GND


## QuickStart (maybe not complete)


    # install plattformio -> https://docs.platformio.org/en/latest//core/installation.html
    pip3 install esphome
    
    cd makerspace_digitalwerkstatt_bme680
    pio lib install "me-no-dev/AsyncTCP"
    pio lib install "ottowinter/ESPAsyncWebServer-esphome"
    pio lib install "boschsensortec/BSEC Software Library"
    cd ..
    
    esphome run bme680.yml
    
    

    
