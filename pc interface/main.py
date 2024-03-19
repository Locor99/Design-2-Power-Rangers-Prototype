import time

import serial


class PcArduinoSerialInterface:
    def __init__(self, port, baudrate=9600):
        self.ser = serial.Serial(port, baudrate)
        time.sleep(2)  # Attendre que la connexion soit établie

    def send_command(self, command):
        self.ser.write((command + "\n").encode())

    def read_data(self):
        if self.ser.in_waiting > 0:
            return self.ser.readline().decode().strip()
        return None

    def close(self):
        self.ser.close()


# Exemple d'utilisation
if __name__ == "__main__":
    interface = PcArduinoSerialInterface('COM3')  # Ajustez le port COM
    try:
        while True:
            data = interface.read_data()
            if data:
                print("Received from Arduino:", data)
            # Pour envoyer des commandes, utilisez :
            # interface.send_command("votre_commande")
            time.sleep(0.001)
    except KeyboardInterrupt:
        interface.close()
        print("Programme terminé.")
