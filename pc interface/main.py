import tkinter as tk

from pc_interface_gui import ArduinoDataGUI


def main():
    # Créer la fenêtre principale de Tkinter
    root = tk.Tk()

    # Ajustez le port COM selon votre configuration
    port = "COM3"  # Sur Windows
    # port = "/dev/ttyUSB0"  # Sur Linux
    # port = "/dev/tty.SLAB_USBtoUART"  # Sur MacOS

    app = ArduinoDataGUI(root, port)

    # Lancer la boucle principale de Tkinter
    root.mainloop()


if __name__ == "__main__":
    main()
