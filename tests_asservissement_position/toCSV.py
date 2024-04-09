import serial
import time
import os  # Importer le module os

# Configuration du port série : remplacez 'COM4' par le bon port de votre Arduino
port = '/dev/cu.usbmodem14201'
baud_rate = 115200

# Création de la connexion série
ser = serial.Serial(port, baud_rate, timeout=1)
time.sleep(2)  # Attendre que la connexion soit établie

# Déterminer le chemin du dossier d'exécution
chemin_dossier_execution = os.getcwd()  # Obtenir le chemin du dossier d'exécution

# Construire le chemin complet du fichier CSV
chemin_fichier_csv = os.path.join(chemin_dossier_execution, 'donnees_arduino.csv')

# Ouvrir le fichier CSV pour l'écriture
with open(chemin_fichier_csv, 'w') as fichier_csv:
    # Écrire l'en-tête du fichier CSV
    fichier_csv.write("temps (ms), S1_capteur, S2_ampli_instr, S3_filtre_capt,"
                      "S4_ampli_puissance_in, S5_ampli_puissance_out, S6_filtre_ampli_puissance\n")

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
