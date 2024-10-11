#include "utils.h"
#include <string>
#include <iostream>
#include <string>
#include "clientManager.h"

using namespace std;

#define OK 1

void recibeMensajes(int serverId)
{
	vector<unsigned char> buffer;
	//loop
	do{
		//recibir mensaje
		recvMSG(serverId,buffer);

		//desempaquetar tipo
		auto tipo=unpack<chatMSGTypes>(buffer);
		switch(tipo){
				case chat_TextMSG:{
					//TextMSG
					//desempaquetar nombre/texto
					string nombre, msg;
					nombre.resize(unpack<int>(buffer));
					unpackv<char>(buffer,(char*)nombre.data(),(int)nombre.size());
					
					msg.resize(unpack<int>(buffer));
					unpackv<char>(buffer,(char*)msg.data(),(int)msg.size());
					
					//mostrar
					cout<<"Mensaje recibido:"<<nombre<<":"<<msg<<endl;
				}break;
				case chat_ExitMSG:{
					//exitMSG
					//salir=true
					ClientManager::salir=true;
				}break;
				
				case chat_AckMSG:
				default:
				{
					
				}break;
		};
				
	}while(!ClientManager::salir);
	//till exit
	
	
}





int main(int argc,char** argv)
{
	//conectar al servidor 127.0.0.1:5000
	auto serverConnection=initClient("127.0.0.1",5000);
	//pedir nombre usuario
	string nombre,msg;
	vector<unsigned char> buffer;
	thread *th=new thread(recibeMensajes,serverConnection.serverId);
	
	cout<<"Introduzca nombre de usuario\n";
	getline(cin,nombre);
	//loop
	do{
		//pedir texto
		getline(cin, msg);
		//empaquetar chat_TextMSG
		pack(buffer, chat_TextMSG);
		//empaquetar nombre y texto
		pack(buffer, (int)nombre.size());
		packv(buffer, (char*)nombre.data(), (int)nombre.size());
		
		pack(buffer, (int)msg.size());
		packv(buffer, (char*)msg.data(), (int)msg.size());
		
		//enviar 
		sendMSG(serverConnection.serverId,buffer);
		//recibir confirmacion
		buffer.clear();
		//recibir mensajes de usuarios
	//till "exit()"
	}while(msg!="exit()");
	
	
	//empaquetar chat_ExitMSG
	//enviar
	buffer.clear();
	pack(buffer,chat_ExitMSG);
	sendMSG(serverConnection.serverId,buffer);
	//cerrar conexion
	ClientManager::salir=true;
	closeConnection(serverConnection.serverId);
	cout<<"Cliente desconectado\n";
	
	return 0;
}





