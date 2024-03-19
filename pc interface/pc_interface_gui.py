import threading
import time
import tkinter as tk
from tkinter import scrolledtext

from pc_arduino_serial_interface import \
    PcArduinoSerialInterface  # Assurez-vous que cette classe est bien définie ou intégrez son code ici


class ArduinoDataGUI:
    def __init__(self, master, port):
        self.master = master
        self.port = port
        self.serial_interface = PcArduinoSerialInterface(self.port)
        self.master.title("Arduino Data Viewer")

        # Création d'un widget Text pour afficher les données
        self.text_area = scrolledtext.ScrolledText(master, wrap=tk.WORD, width=40, height=10)
        self.text_area.pack(padx=10, pady=10)
        self.text_area.insert(tk.INSERT, "Waiting for data...\n")

        # Démarrer un thread pour lire les données en arrière-plan
        self.running = True
        self.thread = threading.Thread(target=self.read_serial_data)
        self.thread.start()

        # Assurer que le thread s'arrête lorsque l'interface est fermée
        self.master.protocol("WM_DELETE_WINDOW", self.on_closing)

    def read_serial_data(self):
        while self.running:
            data = self.serial_interface.read_data()
            if data:
                self.display_data(data)
            time.sleep(0.1)

    def display_data(self, data):
        pass
        # Utiliser la méthode after pour effectuer
