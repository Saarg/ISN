# -*-coding:Utf-8 -*
import socket
import os 
from entity.utils import Console

port = 25565

os.system('clear')
Console.Info("Initialisation du serveur")

connexion_principale = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
connexion_principale.bind(('', port))
connexion_principale.listen(5)
Console.Info("Serveur en attente de connexion sur le port " + str(port))
while 1 :
	connexion_avec_client = list()
	infos_connexion = list()
	connexion_avec_client1, infos_connexion1 = connexion_principale.accept()
	connexion_avec_client.append(connexion_avec_client1)
	infos_connexion.append(infos_connexion1)
	Console.Info("Client1 en ligne, en attente du second client")
	connexion_avec_client1.send("Attente du second player...")
	
	connexion_avec_client2, infos_connexion2 = connexion_principale.accept()
	Console.Info("Client2 en ligne")
	connexion_avec_client.append(connexion_avec_client1)
	infos_connexion.append(infos_connexion1)

	connexion_avec_client1.send("Lancement de la partie")
	connexion_avec_client2.send("Lancement de la partie")
	
	Console.Info("Debut de la partie")

	
	
