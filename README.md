# CSGO-Scene-bomb

This repository contains a PlatformIO project designed for the Arduino Uno. It is set up to be used with Visual Studio Code and the PlatformIO IDE plugin. Follow the steps below to get started with loading this project onto your Arduino Uno.

## Prerequisites

Before you begin, ensure you have the following installed:
- [Visual Studio Code (VS Code)](https://code.visualstudio.com/)
- [PlatformIO IDE Extension for VS Code](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)

## Installation

1. **Clone the Repository**

   First, clone this repository to your local machine using VS Code. Open VS Code, press `Ctrl+Shift+P` to open the command palette, type `Git: Clone`, and enter the URL of this repository. Choose a directory to store the project.

2. **Open the Project**

   Open the cloned project folder in VS Code. If the PlatformIO Home page does not automatically open, you can access it by clicking on the PlatformIO icon on the activity bar on the far left side of VS Code.

3. **Install Dependencies**

   The PlatformIO project may depend on external libraries. These can be installed automatically by PlatformIO. Simply navigate to the `platformio.ini` file in the root of the project directory and make sure all dependencies listed under `lib_deps` are correct.

## Configuring the Project

The `platformio.ini` file is already configured for Arduino Uno. It should look something like this:

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
```

Ensure that this configuration matches your requirements. You can modify the `platform`, `board`, and `framework` values to fit other types of projects or Arduino boards as needed.

## Uploading to Arduino Uno

1. **Connect Your Arduino Uno**

   Connect your Arduino Uno to your PC using a USB cable. Ensure that it is powered on.

2. **Select the Correct Port**

   Click on the PlatformIO icon in VS Code, go to `PROJECT TASKS`, expand the `uno` environment, click on `Upload`, and select the appropriate serial port that your Arduino Uno is connected to. This can typically be done from the `Serial Monitor` icon in the PlatformIO toolbar at the bottom of VS Code.

3. **Build and Upload**

   Click the `Upload` button under the `uno` environment task. This will compile the code and upload it to your Arduino Uno. You will see the output in the Terminal at the bottom of VS Code.

4. **Monitor the Output**

   To see the serial output from your Arduino Uno, open the Serial Monitor from the PlatformIO toolbar. Set the baud rate to 9600 or whatever baud rate your program uses.

## Troubleshooting

If you encounter issues with uploading to the Arduino Uno, check the following:
- Ensure the Arduino is correctly connected via USB.
- Make sure the correct port is selected in the PlatformIO toolbar.
- Verify that the drivers for Arduino Uno are installed on your PC.

For more help, consult the [PlatformIO documentation](https://docs.platformio.org/en/latest/) or raise an issue in this repository.

## Contributing

Contributions to this project are welcome! Please fork the repository and submit a pull request with your changes.

---

This README template covers all basic steps needed to load and manage a PlatformIO project on Arduino Uno using VS Code, making it straightforward even for those new to the platform or hardware.

## STLs

Stl files can be found on MakerWorld or at this link: https://makerworld.com/en/models/432819
