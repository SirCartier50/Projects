# Modbot Wireless Control System

## Overview

The Modbot Wireless Control System is a client-server setup designed to send controller inputs to a modular robot via sockets. On the client side, the system captures and sends controller inputs. On the server side, it receives and prints out these controller inputs with timestamps in milliseconds.

## Features

- **PS4 Controller Support**: The system has been successfully tested with a PS4 controller. Other controllers are expected to be compatible but have not been tested yet.
- **Modular Design**: The system is designed to be adaptable for different controllers and modular bots.
- **Real-time Feedback**: The server prints out controller inputs in real-time, measured in milliseconds.

## Setup

1. Ensure you have `pip` installed on your system. You can install `pip` by following the instructions [here](https://pip.pypa.io/en/stable/installation/).

2. Run the `install.py` script to install all necessary dependencies: `python install.py`

3. Update the IP addresses in the server and client files to match your network setup.

## Files

### `install.py`

This script reads through the `requirements.txt` file and installs the necessary Python packages using `pip`.

### `requirements.txt`

Contains a list of Python packages required for the system to run. The `install.py` script uses this file to install dependencies.

### `client.py`

The client-side script that captures controller inputs and sends them to the server. Make sure to change the IP address in this file to match the server's IP address.

### `server.py`

The server-side script that receives and prints out controller inputs with timestamps in milliseconds. The server prints out its IP address on startup, which should be used in the `client.py` file.

### `Controller.py`

Contains the source code of the Controller class to help manage all controllers.

### `procon.py`

Contains the source code of the procon Class to include joycon capabilites.

## Usage

1. Start the server:
   python server.py

2. Start the client:
   python client.py

3. Use the PS4 controller to send inputs. The server will print out the inputs with timestamps in milliseconds.
