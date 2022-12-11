#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include "message.h"

using namespace std;

namespace http_request {
	class Socket {
	public: 
		Socket();
		Socket(int socket_fd, struct sockaddr_in addr);
		Socket(int socket_fd, struct sockaddr_in addr, string host, int port);
		~Socket();
		void configure_addr(string host, int port);
		void socket_bind();
		void socket_connect();
		void socket_listen();
		int socket_send(string msg);
		int socket_write(string msg);
		Message* socket_read();
		Socket* socket_accept();
		const int get_socket_fd() const {
			return socket_fd_;
		}
		const string get_socket_host() const {
			return socket_host_;
		}
		const int get_socket_port() const {
			return socket_port_;
		}
	private:
		string socket_host_;
		int socket_port_;
		int socket_fd_;
		struct sockaddr_in addr_;
	};
}