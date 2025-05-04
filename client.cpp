#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib ,"ws2_32.lib")
#include <thread>

  
    
using namespace std;
string name ;
string key="zakariafahmi";
void receiveMessages(SOCKET sock) {
    char buf[4096];
    
    while (true) {
        ZeroMemory(buf, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        	string output = buf;
		int keylen = key.length();
		for(int i = 0 ; i < output.length();i++){
		output[i]= output[i] ^ key[i % key.length()];
	}
        if (bytesReceived > 0) {
            cout << endl <<string(output, 0, bytesReceived) << endl;
        }
    }
}

void sendMessages(SOCKET sock) {
    string userInput;
  	
	
    while (true) {
    
        getline(cin, userInput);
        	string output =name+userInput ;
		int keylen = key.length();
		for(int i = 0 ; i < output.length();i++){
		output[i]= output[i] ^ key[i % key.length()];
	}
        
        send(sock, output.c_str(), output.size() + 1, 0);
    }
}




int main()
{
    cout << "\n CORTANA : [ Enter your username pls ] : " ;
	getline(cin, name);
	name = name + ">" ;

	
	string ipAddress = "127.0.0.1";
	int port = 54000;              

	// Initialize Winsock
	WSADATA data;
	WORD ver = MAKEWORD(2, 2);
	int wsOk = WSAStartup(ver, &data);
	if (wsOk != 0) {
		cerr << "Can't initialize Winsock! Quitting" << endl;
		return 1;
	}

	// Create socket
	SOCKET out = socket(AF_INET, SOCK_STREAM, 0);
	if (out == INVALID_SOCKET) {
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		return 2;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.s_addr = inet_addr(ipAddress.c_str());


	// Connect to server
	int connectResult = connect(out, (sockaddr*)&hint, sizeof(hint));
	if (connectResult == SOCKET_ERROR) {
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(out);
		WSACleanup();
		return 3;
	} 

	

  	thread recvThread(receiveMessages, out);
  	thread sendThread(sendMessages, out);

    recvThread.join();
    sendThread.join();
	// Gracefully close down everything
	closesocket(out);
	WSACleanup();
}
