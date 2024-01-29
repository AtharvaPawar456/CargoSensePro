# CargoSensePro

- Automated Train Container Monitoring System

### CargoSensePro - Dashboard
<img src="https://github.com/AtharvaPawar456/CargoSensePro/blob/main/project%20output/dashboad.jpeg" alt="Image 1" height="280">

### CargoSensePro - Project Details
<img src="https://github.com/AtharvaPawar456/CargoSensePro/blob/main/project%20output/project%20details.jpeg" alt="Image 1" height="280">

### CargoSensePro - Contact
<img src="https://github.com/AtharvaPawar456/CargoSensePro/blob/main/project%20output/contact.jpeg" alt="Image 1" height="280">


## Abstract
This project aims to automatically detect and record train container parameters such as weight, content height, and container ID at different stations using an ESP-32 microcontroller, HC-SR04 ultrasonic sensor, load cells, RFID, servo motor, and OLED display. The collected data is uploaded to a ThingSpeak server and rendered on an HTML website for real-time monitoring.

## Problem Statement
Current train container monitoring systems lack automation, leading to manual errors and delays in identifying data loss during transit. This project addresses these issues by providing an automated solution for monitoring and recording container parameters.

## Description
The system comprises ESP-32 microcontroller, HC-SR04 ultrasonic sensor for height measurement, two 10kg load cells for weight measurement, RFID for container identification, a servo motor for control, and an OLED display for real-time information. The collected data is sent to a ThingSpeak server and visualized on an HTML website.

## Approach
- Station 1: RFID identifies the container, load cells measure weight, and ultrasonic sensor measures height. Data is sent to ThingSpeak.
Transit: Container moves to Station 2.
- Station 2: RFID identifies the container, load cells and ultrasonic sensor measure parameters. Data is compared with Station 1. Discrepancies indicate data loss.

## Advantage
- Automation reduces manual errors.
- Real-time monitoring of container parameters.
- Quick identification of data loss during transit.

## Limitation
- Dependency on RFID for container identification.
- Accuracy of measurements may be affected by external factors.

## Future Scope
- Integration with GPS for location tracking.
- Implementation of machine learning for predictive analysis.
- Enhanced security features for RFID.

## Block Diagram


## Getting Started
- Clone the repository.
- Install required libraries (list them in the document).
- Connect the components as per the provided circuit diagram.
- Upload the code to the ESP-32.
- Monitor the data on the ThingSpeak channel and access the HTML website for real-time visualization.

## Contributors
List the contributors and their roles in the project.

## License
Specify the project's license.

## Acknowledgements
Acknowledge any third-party tools, libraries, or resources used in the project.

## Api
https://api.thingspeak.com/update?api_key=K8CH7XH11OFPA1WG&field1=9&field2=8.2&field3=10.3
https://api.thingspeak.com/update?api_key=K8CH7XH11OFPA1WG&field1=9&field2=8.1&field3=10.1

https://api.thingspeak.com/update?api_key=K8CH7XH11OFPA1WG&field1=5&field2=8.4&field3=10.3
https://api.thingspeak.com/update?api_key=K8CH7XH11OFPA1WG&field1=5&field2=8.2&field3=10.5

https://api.thingspeak.com/update?api_key=K8CH7XH11OFPA1WG&field1=11&field2=8.9&field3=10.9
https://api.thingspeak.com/update?api_key=K8CH7XH11OFPA1WG&field1=11&field2=8.2&field3=10.5
