# -*-coding:Utf-8 -*
import socket
import os 
import random
from entity.utils import Console
from entity.utils import Vector2f
from entity import missile
from entity import vaisseau

def main(clients_connectes, infos_connexions):
	entity_tab = list()
	
	entity_tab.append(vaisseau(len(entity_tab), 0, Vector2f(10, 10), 0xff0000, Vector2f(50, 0), Vector2f(3, 0)))

	serveur_lance = True
	clients_a_lire = []
	
	while serveur_lance:
		random.seed(404)
		rand = random.randint(0, 1000)
		if (rand < 10):
			entity_tab.append(vaisseau(len(entity_tab), 0, Vector2f(10, 10), 0xff0000, Vector2f(50, 0), Vector2f(3, 0), 1, -1))
		elif (rand < 50 and rand > 48):
			entity_tab.append(vaisseau(len(entity_tab), 0, Vector2f(10, 10), 0xff0000, Vector2f(50, 0), Vector2f(3, 0), 1, 0.5))
		elif (rand < 55 and rand > 50):
			entity_tab.append(vaisseau(len(entity_tab), 0, Vector2f(10, 10), 0xff0000, Vector2f(50, 0), Vector2f(3, 0), 1, 0.5))
		
		try:
			clients_a_lire, wlist, xlist = select.select(clients_connectes, [], [], 0.05)
		except select.error:
			pass
		else:
			# On parcourt la liste des clients à lire
			for client in clients_a_lire:
				# Client est de type socket
				header_packet = client.recv(4)
				if(header_packet == b'000e'):
					id_packet = client.recv(4)
		
		#Traiter les données
		
		#Envoyer les packets
		
