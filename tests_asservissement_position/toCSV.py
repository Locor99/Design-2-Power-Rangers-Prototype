import serial
import time

# Configuration du port série : remplacez 'COM3' par le bon port de votre Arduino
port = 'COM4'
baud_rate = 115200

# Création de la connexion série
ser = serial.Serial(port, baud_rate, timeout=1)
time.sleep(2)  # Attendre que la connexion soit établie

# Ouvrir le fichier CSV pour l'écriture
with open('../../../OneDrive - Université Laval/Sessions/H-24/Design 2/pythonProject/donnees_arduino.csv', 'w') as fichier_csv:
    # Écrire l'en-tête du fichier CSV
    fichier_csv.write("temps (ms), setpoint,sortieRegulateur,courantLu\n")

    try:
        while True:
            # Lire une ligne depuis le port série
            ligne = ser.readline()

            # Si la ligne n'est pas vide, la décoder et l'écrire dans le fichier CSV
            if ligne:
                ligne_decodee = ligne.decode('utf-8', errors='ignore').strip()  # Ignorer les erreurs de décodage
                print(ligne_decodee)  # Afficher la ligne pour vérification
                fichier_csv.write(ligne_decodee + "\n")
    except KeyboardInterrupt:
        print("Arrêté par l'utilisateur")

# Fermer la connexion série
ser.close()
