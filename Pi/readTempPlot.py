import datetime
import matplotlib.pyplot as plt


def parse_data(data):
    # """Parses the data in the format `2023-07-13 15:54;25.85°C`."""
    date, temperature = data.split(";")
    date = datetime.datetime.strptime(date, "%Y-%m-%d %H:%M")
    temperature = temperature.strip("°C\n")
    temperature = float(temperature)
    return date, temperature


def main():

    # import data from file
    with open("/run/user/1000/gvfs/sftp:host=houdeda2.cz/home/hikari/temperature-plot.txt", "r") as f:
        data = f.readlines()

    dates = []
    temperatures = []
    for d in data:
        date, temperature = parse_data(d)
        dates.append(date)
        temperatures.append(temperature)

    plt.plot(dates, temperatures)
    plt.xlabel("Date")
    plt.ylabel("Temperature (°C)")
    plt.show()


if __name__ == "__main__":
    main()

