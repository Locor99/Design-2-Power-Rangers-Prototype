import threading
import time
import tkinter as tk
from tkinter import scrolledtext

from pc_arduino_serial_interface import PcArduinoSerialInterface


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
        self.thread = threading.Thread(target=self.read_serial_data, daemon=True)
        self.thread.start()

        # Assurer que le thread s'arrête lorsque l'interface est fermée
        self.master.protocol("WM_DELETE_WINDOW", self.on_closing)

    def read_serial_data(self):
        while self.running:
            data = self.serial_interface.read_data()
            if data:
                # Appeler display_data dans le thread principal
                self.text_area.after(0, self.display_data, data)
            time.sleep(0.001)

    def display_data(self, data):
        # Afficher les données dans le widget text_area
        self.text_area.insert(tk.END, data + "\n")
        # Auto-scroll
        self.text_area.see(tk.END)

    def on_closing(self):
        """Arrêter proprement le thread et fermer la connexion série avant de fermer la fenêtre."""
        self.running = False
        self.thread.join()
        self.serial_interface.close()
        self.master.destroy()
