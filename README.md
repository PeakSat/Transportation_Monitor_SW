<h1 align="center">🚀 PeakSat Transportation Monitor Software 🚀</h1>

<p align="center">
    <img src="https://github.com/PeakSat/OBC_Software/blob/main/media/peaksat_logo.png?raw=true" alt="PeakSat Logo" width="200"/>
</p>

---

## 🌟 Overview

The **PeakSat Transportation Monitor** software is designed to accompany various satellite components during transportation. Its purpose is to log critical variables to ensure safe handling and detect any mishandling during transit.

### 🔍 Logged Variables
- **Temperature**  
- **Relative Humidity**  
- **Acceleration (X, Y, Z axes)**  
- **Shock Events**

---

## 🛠️ Build Instructions

This project uses **PlatformIO**, so to build and upload the software, you’ll need:
1. **VS Code IDE** with the **PlatformIO extension** installed.  
2. Alternatively, you can use `esptool.py` to upload the precompiled binary located at:  
   ```plaintext
   .pio/build/pico32/firmware.bin
   ```

---

## 📊 Data Plotter
To visualize the logged data, follow these steps:

1. Copy the .csv file from the SD card to the **data** folder inside the **data_plotter** directory.
2. Open a command line and navigate to the **data_plotter** directory.
3. Run the following command to see the plotted results:
```shell
python transportation_data_plotter.py
```
> Note: Do not rename the .csv files, as the parser relies on specific filenames.
