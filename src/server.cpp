#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <thread>
#include "socket.h"
#include "message.h"
#include "validator.h"

using namespace std;
using namespace http_request;

void connection_handler(Socket* client_socket) {
	string message = "successfully responded";
	Message* resp = new Message(0, "", -1, "");
	while ((resp = client_socket -> socket_read()) -> get_message_length() > 0) {
		printf("server: got message from %s:%d: %s\n", resp -> get_sender_host().c_str(), resp -> get_sender_port(), resp -> get_sender_message().c_str());
		int bytes_count = client_socket -> socket_send(message);
		printf("server: send %d bytes to %s:%d\n", bytes_count, resp -> get_sender_host().c_str(), resp -> get_sender_port());
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "provide 'host:port' as argument\n";
		return 0;
	}
	Address* address = get_address((string)argv[1]);
	Socket* socket = new Socket();
	socket -> configure_addr(address -> host_.c_str(), address -> port_);
	socket -> socket_bind();
	printf("server: listening on port %d\n", address -> port_);
	socket -> socket_listen();
	while (true) {
		Socket* client_socket = socket -> socket_accept();
		printf("server: connection from %s:%d accepted\n", client_socket -> get_socket_host().c_str(), client_socket -> get_socket_port());
		thread handler_thread(connection_handler, client_socket);
		handler_thread.detach();
	}
	socket -> ~Socket();
}