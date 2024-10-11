#include "clientManager.h"

void ClientManager::atiendeCliente(int clientId){
	bool salir=false;
	vector<unsigned char> buffer;
 
	while(!salir)
	{
		//recibir mensaje
		recvMSG(clientId,buffer);
		//tratar mensaje
			//desempaquetar tipo
			auto tipo=unpack<chatMSGTypes>(buffer);
				//swith tipo
			string nombre, msg;

			switch(tipo){
				case chat_TextMSG:{
					//TextMSG
					//desempaquetar nombre/texto
					nombre.resize(unpack<int>(buffer));
					unpackv<char>(buffer,(char*)nombre.data(),(int)nombre.size());
					
					msg.resize(unpack<int>(buffer));
					unpackv<char>(buffer,(char*)msg.data(),(int)msg.size());
					
					//mostrar
					cout<<"Mensaje recibido:"<<nombre<<":"<<msg<<endl;
					//reenviar a clientes
						//buscar el cliente en mapa
						if(clients.find(nombre)==clients.end())
							//si no está, se añade
							clients[nombre]=clientId;
								
								
						//reenviar al resto (broadcastMessages)
						broadcastMessages(nombre,msg);
				}break;
				case chat_ExitMSG:{
					//exitMSG
					//salir=true
					salir=true;
					clients.erase(nombre);
				}break;
				
				case chat_AckMSG:
				default:
				{
					
				//default
					//mensaje error
					//recuperacion exit
					cout<<"ERROR: "<<__FILE__<<":"<<__LINE__<<
							"Tipo de mensaje inválido"<<endl; 		
				}break;			
			};
	//devolver resultado AckMSG
		buffer.clear();
		pack(buffer,chat_AckMSG);
		sendMSG(clientId,buffer);
	}
	//cerrar conexion
	closeConnection(clientId);	
}
void ClientManager::broadcastMessages(string nombre,string msg){
	vector<unsigned char> buffer;
	//empaquetar nombre/msg
	pack(buffer, chat_TextMSG);
		//empaquetar nombre y texto
	pack(buffer, (int)nombre.size());
	packv(buffer, (char*)nombre.data(), (int)nombre.size());
	
	pack(buffer, (int)msg.size());
	packv(buffer, (char*)msg.data(), (int)msg.size());

	//por cada cliente
	for( auto &client: clients){
		//enviar paquete
		if(client.first!=nombre)
			sendMSG(client.second, buffer);
	}
}







