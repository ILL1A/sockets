#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "socket.h"
#include "logger.h"
#include "message.h"

using namespace std;

namespace http_request {
	const int BUFFER_SIZE = 256;
	Socket::Socket() {
		socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_fd_ < 0) {
			logger::error("cannot create a socket");
		}
	}
	Socket::Socket(int socket_fd, struct sockaddr_in addr) : socket_fd_(socket_fd), addr_(addr) {}
	Socket::Socket(int socket_fd, struct sockaddr_in addr, string host, int port) : 
		socket_fd_(socket_fd), addr_(addr), socket_host_(host), socket_port_(port) {}
	Socket::~Socket() {
		close(socket_fd_);
	}
	void Socket::configure_addr(string host, int port) {
		socket_port_ = port; socket_host_ = host;
		addr_.sin_family = AF_INET;
		addr_.sin_port = htons(port);
		addr_.sin_addr.s_addr = inet_addr(host.c_str());
	}
	void Socket::socket_bind() {
		int resp = bind(socket_fd_, (struct sockaddr*) &addr_, sizeof(addr_));
		if (resp < 0) {
			logger::error("bind error");
		}
	}
	void Socket::socket_connect() {
		int resp = connect(socket_fd_, (struct sockaddr*) &addr_, sizeof(addr_));
		if (resp < 0) {
			logger::error("connect error");
		}
	}
	void Socket::socket_listen() {
		int resp = listen(socket_fd_, 100);
		if (resp < 0) {
			logger::error("listen error");
		}
	}
	int Socket::socket_send(string message) {
		const char* data = message.c_str();
		int resp = send(socket_fd_, data, strlen(data), 0);
		if (resp < 0) {
			logger::error("send error");
		}
		return resp;
	}
	int Socket::socket_write(string message) {
		const char* data = message.c_str();
		int resp = write(socket_fd_, data, strlen(data));
		if (resp < 0) {
			logger::error("write error");
		}
		return resp;
	}
	Message* Socket::socket_read() {
		char buffer[BUFFER_SIZE];
		bzero(buffer, BUFFER_SIZE);
		int resp = read(socket_fd_, buffer, BUFFER_SIZE - 1);
		if (resp < 0) {
			logger::error("read error");
		}
		Message* message = new Message(resp, socket_host_, socket_port_, (string)buffer);
		return message;
	}
	Socket* Socket::socket_accept() {
		struct sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);
		int client_fd;
		client_fd = accept(socket_fd_, (struct sockaddr*) &client_addr, &client_len);
		if (client_fd < 0) {
			logger::error("accept error");
		}
		Socket* new_client = new Socket(client_fd, client_addr, inet_ntoa(addr_.sin_addr), ntohs(addr_.sin_port));
		return new_client;
	}
}