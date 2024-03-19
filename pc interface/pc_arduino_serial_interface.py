import time

import serial


class PcArduinoSerialInterface:
    def __init__(self, port, baudrate=9600):
        self.ser = serial.Serial(port, baudrate)
        time.sleep(2)

    def send_command(self, command):
        self.ser.write((command + "\n").encode())

    def read_data(self):
        if self.ser.in_waiting > 0:
            return self.ser.readline().decode().strip()
        return None

    def close(self):
        self.ser.close()
