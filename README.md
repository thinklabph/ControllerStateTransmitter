# ControllerStateTransmitter

## Installing the Board

1. In the Arduino IDE, click on **File** > **Preferences...**.
2. On **Additional boards manager URLs** enter the link below.
    ```
    https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
    ```
3. Click **Save**.


## How to use

1. Clone this repository by clicking on **Code** > **Download Zip**.
2. Unzip the downloaded Zip file.
3. Go inside the folder and locate `ControllerStateTransmitter.ino` and open it in Arduino IDE.
4. Modify the `R24_ADDRESS` to a custom 5-character string of your choice. This string is used to identify and pair the controller with the corresponding transceiver in your mobot. Ensure that the string is identical on both the [controller](https://github.com/thinklabph/ControllerStateTransmitter) and [mobot](https://github.com/thinklabph/ControllerStateReceiver) for successful pairing.
5. Set the Board by clicking on **Tools** > **Board** > **Seeed SAMD Boards** > **Seeeduino XIAO**.
6. Set the Port to the micronctoller of the controller.
7. Upload.
8. Open Serial Monitor and set to **115200 baud**


## Refrences

- https://wiki.seeedstudio.com/Seeeduino-XIAO/#getting-started