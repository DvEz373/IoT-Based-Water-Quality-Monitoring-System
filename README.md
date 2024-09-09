# IoT-Based Water Quality Monitoring System

## Overview
This project was developed as part of the Technology for Indonesia (TFI) 2024 initiative, supported by the KSE scholarship program. The goal is to create a real-time water quality monitoring system using IoT technology. The system measures key water quality parameters and provides real-time data for analysis and decision-making.

## Key Features
- **IoT Integration**: Uses ESP32 to connect the system to the internet, enabling real-time monitoring via a cloud platform.
- **Water Quality Parameters**: Monitors temperature, pH levels, turbidity, and Total Dissolved Solids (TDS) in real-time.
- **Data Display**: Includes an LCD 20x4 I2C display for local real-time data viewing.
- **Data Visualization**: Displays data on a web dashboard for easy analysis.
- **Mobile Access**: Remote monitoring through a mobile app or web interface.

## Hardware Components
- **ESP32**: Microcontroller with Wi-Fi capability for IoT integration.
- **pH Sensor**: Measures the acidity or alkalinity of the water.
- **Temperature Sensor**: Tracks the water temperature.
- **Turbidity Sensor**: Measures water clarity.
- **TDS Sensor**: Measures the total dissolved solids (salts, minerals, etc.) in the water.
- **LCD 20x4 I2C**: Displays real-time water quality data locally.
- **Power Supply**: Battery-powered or solar-powered for remote deployments.

## Software Components
- **Firmware**: Custom-developed code for ESP32 to control sensors and display data on the LCD.
- **Cloud Platform**: System uses a cloud IoT platform for data storage and processing.
- **Mobile App/Web Dashboard**: Real-time data visualization and monitoring through an easy-to-use interface.

## How It Works
1. **Data Collection**: Sensors measure water quality parameters (pH, temperature, turbidity, TDS).
2. **Local Display**: Real-time sensor data is displayed on the LCD 20x4 I2C screen.
3. **Data Transmission**: The ESP32 sends the collected data to the cloud via Wi-Fi.
4. **Data Visualization**: Data is displayed on a web dashboard and mobile app for remote monitoring.
5. **Alerts**: Threshold-based alerts are triggered if any parameter exceeds the acceptable range.

## Installation & Setup
1. Install the firmware on the ESP32 using Arduino IDE or PlatformIO.
2. Connect the sensors and LCD 20x4 I2C to the ESP32 as per the schematic.
3. Set up your cloud IoT platform and configure the data streams.
4. Deploy the system in your water source and monitor the data locally and remotely.

## Applications
- **Environmental Monitoring**: Track water bodies, lakes, and rivers for pollution levels.
- **Agriculture**: Monitor water quality for irrigation and aquaculture.
- **Industrial**: Ensure compliance by tracking water quality in industrial discharge.

## Future Enhancements
- **Machine Learning Integration**: Implement predictive analytics for water quality trends.
- **Extended Parameters**: Add sensors for dissolved oxygen, electrical conductivity, etc.
- **Long-Term Monitoring**: Enhance for long-term deployments with solar power.

## Acknowledgments
This project was made possible through the KSE scholarship and the Technology for Indonesia (TFI) 2024 initiative. Special thanks to mentors and collaborators for their guidance and support.

## Contact
For more information, reach out via email: ezekiel.devin@gmail.com