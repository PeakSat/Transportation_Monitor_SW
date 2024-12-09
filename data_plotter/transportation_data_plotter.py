import pandas as pd
import matplotlib.pyplot as plt

# File paths for data
env_data_file = "data/env_log.csv"
accel_data_file = "data/acc_log.csv"

# Load environmental data
def load_env_data(file_path):
    """Load temperature and humidity data."""
    env_data = pd.read_csv(file_path, header=None, names=["timestamp", "temp_C", "hum_rH"])
    env_data["timestamp"] = pd.to_datetime(env_data["timestamp"], unit='s')  # Assuming Unix timestamp
    return env_data

# Load acceleration data
def load_accel_data(file_path):
    """Load acceleration data."""
    accel_data = pd.read_csv(
        file_path,
        header=None,
        names=["timestamp", "rawAccX", "rawAccY", "rawAccZ", "GX", "GY", "GZ"]
    )
    accel_data["timestamp"] = pd.to_datetime(accel_data["timestamp"], unit='s')  # Assuming Unix timestamp
    return accel_data

# Plot environmental data
def plot_env_data(env_data):
    """Plot temperature and humidity."""
    plt.figure(figsize=(10, 5))
    plt.plot(env_data["timestamp"], env_data["temp_C"], label="Temperature (°C)", color="red")
    plt.plot(env_data["timestamp"], env_data["hum_rH"], label="Humidity (%)", color="blue")
    plt.xlabel("Time")
    plt.ylabel("Values")
    plt.title("Temperature and Humidity Over Time")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

# Plot acceleration data
def plot_accel_data(accel_data):
    """Plot raw acceleration (X, Y, Z) and G values."""
    # Raw acceleration plot
    plt.figure(figsize=(10, 5))
    plt.plot(accel_data["timestamp"], accel_data["rawAccX"], label="RawAcc X", color="green")
    plt.plot(accel_data["timestamp"], accel_data["rawAccY"], label="RawAcc Y", color="orange")
    plt.plot(accel_data["timestamp"], accel_data["rawAccZ"], label="RawAcc Z", color="purple")
    plt.xlabel("Time")
    plt.ylabel("Raw Acceleration")
    plt.title("Raw Acceleration (X, Y, Z) Over Time")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

    # G values plot
    plt.figure(figsize=(10, 5))
    plt.plot(accel_data["timestamp"], accel_data["GX"], label="G X", color="cyan")
    plt.plot(accel_data["timestamp"], accel_data["GY"], label="G Y", color="magenta")
    plt.plot(accel_data["timestamp"], accel_data["GZ"], label="G Z", color="yellow")
    plt.xlabel("Time")
    plt.ylabel("G Values")
    plt.title("G Values (X, Y, Z) Over Time")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

# Main function
def main():
    # Load data
    env_data = load_env_data(env_data_file)
    accel_data = load_accel_data(accel_data_file)
    
    # Plot data
    plot_env_data(env_data)
    plot_accel_data(accel_data)

if __name__ == "__main__":
    main()
