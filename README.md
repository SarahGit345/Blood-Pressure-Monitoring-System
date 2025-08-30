Blood Pressure & Health Monitoring System

An IoT-based Health Monitoring System that measures Blood Pressure, Body Temperature, and SpO₂ (Oxygen Saturation) using Arduino and sensors. The system displays results on an LCD screen and uploads data to the ThingSpeak IoT platform for real-time remote monitoring.

🚀 Abstract
Health monitoring plays a critical role in preventive healthcare, enabling early detection and management of various health conditions. This project presents an IoT-based system that measures:
Blood Pressure using the MPX5100DP pressure sensor
Body Temperature using the DS18B20 sensor
SpO₂ (Oxygen Saturation) using the MAX30100 sensor

The collected data is displayed on a 16x2 LCD and transmitted to the cloud via ESP-01 WiFi module. The device achieves high accuracy:
Systolic Pressure: ±2.96%
Diastolic Pressure: ±3.29%
Temperature: ±0.63%
SpO₂: <2% error
This makes it a reliable and cost-effective solution for continuous health monitoring.

🛠️ Components Used

MPX5100DP Pressure Sensor → Blood Pressure measurement
DS18B20 Temperature Sensor → Body Temperature measurement
MAX30100 Sensor → SpO₂ & Heart Rate
Arduino Uno → Main Controller
ESP-01 WiFi Module → IoT connectivity
Relay Module → Controls air pump & solenoid
Air Pump & Cuff → Inflates for BP measurement
Solenoid Valve → Releases cuff pressure
16x2 LCD Display → Shows real-time values
Push Button → Starts measurements
Power Supply (5V/9V DC)

⚡ Working Principle

User powers ON the device and presses the push button.
Arduino triggers the air pump via a relay to inflate the cuff.
MPX5100DP sensor measures cuff pressure → Arduino processes systolic & diastolic values.
DS18B20 sensor measures temperature.
MAX30100 sensor measures SpO₂ and heart rate.
Readings are displayed on the LCD screen.
Data is sent to ThingSpeak IoT platform through ESP-01 for remote access.
Arduino activates the solenoid valve to deflate cuff safely.

📊 Block Diagram

<img width="233" height="175" alt="image" src="https://github.com/user-attachments/assets/b8066d3a-30ee-4156-a66d-9b17847e6d78" />
<img width="253" height="190" alt="image" src="https://github.com/user-attachments/assets/4594779f-d24d-4f91-a46e-8ca4fc3f376e" />


🔧 Installation & Usage

Install Arduino IDE and required libraries:
OneWire.h (for DS18B20)
DallasTemperature.h (for DS18B20)
Wire.h & MAX30100_PulseOximeter.h (for MAX30100)
LiquidCrystal.h (for LCD)
Connect hardware as per circuit diagram.

Upload CODE/bp_monitoring.ino to Arduino.
Configure WiFi credentials in the code for ESP-01.
Open ThingSpeak channel and link device.
View real-time health data on LCD and cloud dashboard.

✅ Results

Accurate BP, Temperature, and SpO₂ measurements.
Remote monitoring via ThingSpeak IoT cloud.
Compact and cost-effective device suitable for hospitals and home healthcare.

📌 Future Enhancements

Integration with mobile health apps.
Adding ECG monitoring.
AI-based prediction for hypertension/fever risks.
Battery-powered wearable version.

👥 Contributors

Hemant Mukkamala (bl.en.u4eac23024@bl.students.amrita.edu
)

Sarah Thomas (bl.en.u4eac23049@bl.students.amrita.edu
)

Sai Charan (bl.en.u4eac23079@bl.students.amrita.edu
)

📜 References

IoT Based SPO2 and Temperature Monitoring Using Arduino Mega and GSM
IoT Based Health Monitoring System Using Arduino
Wireless Patient Monitoring System

