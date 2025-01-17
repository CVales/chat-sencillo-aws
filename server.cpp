#include "utils.h"
#include <iostream>
#include <string>
#include <thread>
#include <list>
#include "clientManager.h"
using namespace std;

int main(int argc, char** argv)
{
	//iniciar servidor
	vector<unsigned char> buffer;
	int serverSocket=initServer(5000);
	cout<<"Server iniciado\n";
	//loop
	while(1){
		//esperar conexion
		while(!checkClient()){usleep(100);}
		//conexion recibida
		//sacar clientId
		int clientId=getLastClientID();
		cout<<"Conexion establecida con cliente:"<<clientId<<"\n";

		//crear thread atiendeCliente
		thread *th=new thread(ClientManager::atiendeCliente,clientId);
	//till ctrl-C
	}
	//cerrar socket
	close(serverSocket);
	
	/*while(!checkClient()){usleep(100);}
	//atender conexion
	int clientId=getLastClientID();
	cout<<"Conexion establecida con cliente:"<<clientId<<"\n";
	
	//recibir mensaje
	recvMSG(clientId,buffer);
	//desempaquetar datos
	int msgSize=unpack<int>(buffer);
	string msg;
	msg.resize(msgSize);
	unpackv<char>(buffer,(char*)msg.data(),msgSize);

	//mostrar datos
	cout<<"Mensaje recibido de cliente " <<clientId<<" "<<msg<<endl;
	
	//devolver OK
	buffer.clear();
	pack(buffer,1);
	sendMSG(clientId,buffer);
	
	//cerrar conexion
	closeConnection(clientId);
	//cerrar servidor
	cout<<"Conexion cerrada con cliente:"<<clientId<<"\n";
	*/
	
 return 0;
}
