# Modbot Wireless Control System

## Overview

The Modbot Wireless Control System is a client-server setup designed to send controller inputs to a modular robot via sockets. On the client side, the system captures and sends controller inputs. On the server side, it receives and prints out these controller inputs with timestamps in milliseconds.

## Features

- **PS4 Controller Support**: The system has been successfully tested with a PS4 controller. Other controllers are expected to be compatible but have not been tested yet.
- **Modular Design**: The system is designed to be adaptable for different controllers and modular bots.
- **Real-time Feedback**: The server prints out controller inputs in real-time, measured in milliseconds.

## Setup

1. Ensure you have `pip` installed on your system. You can install `pip` by following the instructions [here](https://pip.pypa.io/en/stable/installation/).

2. Run the `install.py` script to install all necessary dependencies:
   ```bash
   python install.py
