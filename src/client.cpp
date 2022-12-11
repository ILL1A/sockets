#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include "include/socket.h"
#include "include/message.h"
#include "include/validator.h"

using namespace std;
using namespace http_request;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "provide 'host:port' as argument\n";
		return 0;
	}
	Address* address = get_address((string)argv[1]);
	Socket* socket = new Socket();
	socket -> configure_addr(address -> host_.c_str(), address -> port_);
	socket -> socket_connect();
	printf("client: connected to %s:%d server\n", address -> host_.c_str(), address -> port_);
	while (true) {
		cout << "type some message: \n";
		string message;
		getline(cin, message);
		int bytes_count = socket -> socket_write(message);
		printf("client: write %d bytes\n", bytes_count);
		Message* resp = socket -> socket_read();
		printf("client: got message: %s\n", resp -> get_sender_message().c_str());
	}
}