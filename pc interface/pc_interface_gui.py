import threading
import time
import tkinter as tk

from pc_arduino_serial_interface import PcArduinoSerialInterface


class ArduinoDataGUI:
    def __init__(self, master, port):
        self.master = master
        self.port = port
        self.serial_interface = PcArduinoSerialInterface(self.port)
        self.master.title("Arduino Data Viewer")

        self.mass_string = tk.StringVar()
        self.isStable = tk.BooleanVar()

        self.mass_label = tk.Label(master, textvariable=self.mass_string)
        self.mass_label.pack(padx=10, pady=10)

        # Démarrer un thread pour lire les données en arrière-plan
        self.running = True
        self.thread = threading.Thread(target=self.read_serial_data, daemon=True)
        self.thread.start()

        # Assurer que le thread s'arrête lorsque l'interface est fermée
        self.master.protocol("WM_DELETE_WINDOW", self.on_closing)

    def read_serial_data(self):
        while self.running:
            data = self.serial_interface.read_data()
            if data:
                # Appeler display_data dans le thread principal
                self.mass_label.after(0, self.display_mass, data)
            time.sleep(0.001)

    def display_mass(self, mass):
        self.mass_string.set(f"{str(mass)} g")

    def on_closing(self):
        """Arrêter proprement le thread et fermer la connexion série avant de fermer la fenêtre."""
        self.running = False
        self.thread.join()
        self.serial_interface.close()
        self.master.destroy()
