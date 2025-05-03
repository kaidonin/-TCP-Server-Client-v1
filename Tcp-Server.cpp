#include <iostream>
#include <string>
#include <ws2tcpip.h>
#pragma comment(lib ,"ws2_32.lib")

using namespace std ;
string key="zakariafahmi";

int main () {
	WSADATA  data ;
	WORD ver = MAKEWORD(2,2);
	if(WSAStartup(ver,&data)!=0){
		cerr<<"can't initialize winsock ! "<< endl ;
		return 1 ;
	}
	
	SOCKET listening = socket(AF_INET , SOCK_STREAM , 0);
	if(listening == INVALID_SOCKET){
		cerr<<"can't create socket ! "<<endl;
		WSACleanup();
		return 2 ;
		
	}
	sockaddr_in hint ;
	hint.sin_family=AF_INET;
	hint.sin_port=htons(54000);
	hint.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(listening,(sockaddr*)&hint,sizeof(hint)) ;
	listen(listening ,SOMAXCONN);
	
	fd_set master ;
	FD_ZERO(&master);
	FD_SET(listening,&master);
	
	while(true){
		fd_set copy = master ;
		int sockcount = select(0,&copy,nullptr,nullptr,nullptr);
		
		for(int i = 0 ; i<sockcount; i++){
			
			SOCKET  sock = copy.fd_array[i];
			if(sock==listening)
			{
			SOCKET client = accept(listening,nullptr,nullptr);
			FD_SET(client,&master);
			string welmsg = "welcome to our chat server !" ;
				string output = welmsg ;
				int keylen = key.length();
				for(int i = 0 ; i < output.length();i++){
				output[i]= output[i] ^ key[i % key.length()];
	}
			send(client,output.c_str(),output.size()+1,0);	
			
			}
			else
			{
				char buf[4096];
				ZeroMemory(buf,4096);
				int byrecv=recv(sock,buf ,4096,0);
				if(byrecv<=0){
					closesocket(sock);
					FD_CLR(sock,&master);
				}	else	{
				
				for(int i = 0 ; i <master.fd_count;i++){
					SOCKET outsock = master.fd_array[i];
					if(outsock!=listening && outsock!=sock){
						send(outsock,buf,byrecv,0);
					}
			    }
		
				}
				
			}
		}
		
		
		
	}
	
	return 0 ;
	
}

