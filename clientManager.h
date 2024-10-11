#pragma once
#include "utils.h"

using namespace std;

typedef enum{
	chat_TextMSG,// mensajencon  nombre usuario y texto y metadatos
	chat_ExitMSG,//El cliente desconecta del sistema
	chat_AckMSG //respuesta entre mensajes enviados al server
	
}chatMSGTypes;

class ClientManager{
	
	public:
		static inline map< string , int> clients;
		static inline bool salir=false; 
		static void atiendeCliente(int clientId);
		static void broadcastMessages(string nombre,string msg);

};
