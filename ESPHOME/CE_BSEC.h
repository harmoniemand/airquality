#include "esphome.h"
#include "bsec.h"

class CE_BSEC : public PollingComponent, public Sensor
{
public:
  // constructor

  int Intervall = 500;
  int lastRun = 0;

  Bsec iaqSensor;

  Sensor *RawTemperatureSensor = new Sensor();
  Sensor *PressureSensor = new Sensor();
  Sensor *RawHumiditySensor = new Sensor();
  Sensor *GasResistanceSensor = new Sensor();
  Sensor *IaqSensor = new Sensor();
  Sensor *IaqAccuracySensor = new Sensor();
  Sensor *TemperatureSensor = new Sensor();
  Sensor *HumiditySensor = new Sensor();
  Sensor *StaticIaqSensor = new Sensor();
  Sensor *Co2EquivalentSensor = new Sensor();
  Sensor *BreathVocEquivalentSensor = new Sensor();

  String output;

  // Sensor *TSensor = new Sensor();
  // Sensor *PSensor = new Sensor();
  // Sensor *HSensor = new Sensor();
  // Sensor *AQSensor = new Sensor();
  int errorState = 0;
  Sensor *ErrorSensor = new Sensor();

  CE_BSEC() : PollingComponent(500) {}

  void setup() override
  {
    // This will be called by App.setup()
    // iaqSensor.begin(BME680_I2C_ADDR_PRIMARY, Wire);

    iaqSensor.begin(BME680_I2C_ADDR_SECONDARY, Wire);
    // output = "\nBSEC library version " + String(iaqSensor.version.major) + "." + String(iaqSensor.version.minor) + "." + String(iaqSensor.version.major_bugfix) + "." + String(iaqSensor.version.minor_bugfix);
    // Serial.println(output);
    checkIaqSensorStatus();

    bsec_virtual_sensor_t sensorList[10] = {
        BSEC_OUTPUT_RAW_TEMPERATURE,
        BSEC_OUTPUT_RAW_PRESSURE,
        BSEC_OUTPUT_RAW_HUMIDITY,
        BSEC_OUTPUT_RAW_GAS,
        BSEC_OUTPUT_IAQ,
        BSEC_OUTPUT_STATIC_IAQ,
        BSEC_OUTPUT_CO2_EQUIVALENT,
        BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    };

    iaqSensor.updateSubscription(sensorList, 10, BSEC_SAMPLE_RATE_LP);
    checkIaqSensorStatus();
  }

  void update() override
  {
    // Serial.println(lastRun);
    // Serial.println(Intervall);
    // Serial.println(millis());

    float rawTemperature;
    float pressure;
    float rawHumidity;
    float gasResistance;
    float iaq;
    float iaqAccuracy;
    float temperature;
    float humidity;
    float staticIaq;
    float co2Equivalent;
    float breathVocEquivalent;

    if (iaqSensor.run())
    { // If new data is available

      float rawTemperature = iaqSensor.rawTemperature;
      float pressure = iaqSensor.pressure;
      float rawHumidity = iaqSensor.rawHumidity;
      float gasResistance = iaqSensor.gasResistance;
      float iaq = iaqSensor.iaq;
      float iaqAccuracy = iaqSensor.iaqAccuracy;
      float temperature = iaqSensor.temperature;
      float humidity = iaqSensor.humidity;
      float staticIaq = iaqSensor.staticIaq;
      float co2Equivalent = iaqSensor.co2Equivalent;
      float breathVocEquivalent = iaqSensor.breathVocEquivalent;

      if (lastRun < millis() - Intervall)
      {
        lastRun = millis();
        unsigned long time_trigger = millis();

        RawTemperatureSensor->publish_state(rawTemperature);
        PressureSensor->publish_state(pressure);
        RawHumiditySensor->publish_state(rawHumidity);
        GasResistanceSensor->publish_state(gasResistance);
        IaqSensor->publish_state(iaq);
        IaqAccuracySensor->publish_state(iaqAccuracy);
        TemperatureSensor->publish_state(temperature);
        HumiditySensor->publish_state(humidity);
        StaticIaqSensor->publish_state(staticIaq);
        Co2EquivalentSensor->publish_state(co2Equivalent);
        BreathVocEquivalentSensor->publish_state(breathVocEquivalent);

        output = String(time_trigger);
        output += ", " + String(rawTemperature);
        output += ", " + String(pressure);
        output += ", " + String(rawHumidity);
        output += ", " + String(gasResistance);
        output += ", " + String(iaq);
        output += ", " + String(iaqAccuracy);
        output += ", " + String(temperature);
        output += ", " + String(humidity);
        output += ", " + String(staticIaq);
        output += ", " + String(co2Equivalent);
        output += ", " + String(breathVocEquivalent);
        Serial.println(output);
      }
    }
    else
    {
      checkIaqSensorStatus();
    }
  }

  void checkIaqSensorStatus(void)
  {
    if (iaqSensor.status != BSEC_OK)
    {
      if (iaqSensor.status < BSEC_OK)
      {
        // output = "BSEC error code : " + String(iaqSensor.status);
        // Serial.println(output);
        errorState = 1;
        ErrorSensor->publish_state(1);
      }
      else
      {
        // output = "BSEC warning code : " + String(iaqSensor.status);
        // Serial.println(output);
        errorState = 2;
        ErrorSensor->publish_state(2);
      }
    }
    else if (iaqSensor.bme680Status != BME680_OK)
    {
      if (iaqSensor.bme680Status < BME680_OK)
      {
        // output = "BME680 error code : " + String(iaqSensor.bme680Status);
        // Serial.println(output);
        errorState = 1;
        ErrorSensor->publish_state(1);
      }
      else
      {
        // output = "BME680 warning code : " + String(iaqSensor.bme680Status);
        // Serial.println(output);
        errorState = 2;
        ErrorSensor->publish_state(2);
      }
    }
    else
    {
      if (errorState != 0)
      {
        ErrorSensor->publish_state(0);
        errorState = 0;
      }
    }
  }
};