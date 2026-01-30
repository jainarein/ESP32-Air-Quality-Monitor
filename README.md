# ESP32 Air Quality Monitoring System 🌍

A web-based air quality monitoring system built using **ESP32** and MQ-series gas sensors.  
The system reads sensor data, estimates Air Quality Index (AQI) levels, and displays the results on a **real-time web dashboard hosted directly on the ESP32**.

This project focuses on embedded sensing, on-device data processing, and lightweight web visualization.

---

## 🚀 Features
- ESP32-based embedded web server (no external backend)
- Real-time AQI estimation from gas sensor readings
- Dark-themed, responsive web dashboard
- Automatic page refresh every 5 seconds
- Simple and efficient firmware design

---

## 🛠️ Hardware Components
- ESP32 Dev Module  
- MQ2 Gas Sensor  
- MQ135 Gas Sensor *(planned / optional)*  
- Wi-Fi network

---

## 📊 AQI Classification
The estimated AQI is categorized into standard air quality levels:

| AQI Range | Air Quality Level |
|----------|------------------|
| 0–50     | Good |
| 51–100   | Moderate |
| 101–150  | Unhealthy (Sensitive Groups) |
| 151–200  | Unhealthy |
| 201–300  | Very Unhealthy |
| 301–500  | Hazardous |

---

## 🌐 Web Dashboard
- Displays current AQI value
- Shows corresponding air quality status
- Hosted directly on the ESP32 using an embedded HTTP server
- Accessible via ESP32 local IP address

**Note:** UI screenshots may show simulated AQI values for demonstration purposes when physical sensors are unavailable.

---

## ⚙️ System Workflow
1. ESP32 reads analog data from the MQ2 gas sensor  
2. Raw ADC values are scaled to estimate AQI  
3. AQI value is mapped to a standard air quality category  
4. Results are served as a web page through the ESP32 web server  
5. The dashboard auto-refreshes to display updated values  

---

## 🧪 Calibration Method
A simple linear scaling approach is used for AQI estimation:

AQI = Raw_ADC × Calibration_Factor

The calibration factor was derived experimentally and can be adjusted to improve accuracy based on the environment and sensor behavior.

---

## 📂 Project Structure
ESP32-Air-Quality-Monitor/  
├── esp32_aqi_dashboard.ino  
├── README.md  
└── ui_dashboard.jpg

---

## ▶️ How to Run
1. Open the `.ino` file in Arduino IDE  
2. Select **ESP32 Dev Module** as the board  
3. Enter your Wi-Fi credentials in the code  
4. Upload the sketch to ESP32  
5. Open Serial Monitor to note the ESP32 IP address  
6. Visit the IP address in a web browser to view the dashboard  

---

## 🔒 Security Note
Wi-Fi credentials are intentionally kept as placeholders in the repository.  
Update them locally before uploading the code to the ESP32.

---

## 📌 Limitations
- AQI values are approximate and not reference-grade  
- MQ135 sensor integration requires proper voltage scaling  
- Environmental factors affect gas sensor accuracy  

---

## 🚧 Future Improvements
- Proper MQ135 integration with ADC voltage scaling  
- Sensor data smoothing and filtering  
- Historical AQI visualization  
- TinyML-based AQI trend prediction  
- Cloud integration (Grafana / ThingSpeak)  

---

## 📷 Screenshots

![ESP32 AQI Dashboard](/ui_dashboard.jpg)

---

## 📄 License
This project is open-source and intended for educational and learning purposes.
