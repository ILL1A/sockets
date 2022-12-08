#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

namespace logger {
	void info(string msg) {
		cout << msg << '\n';
	}
	void error(string msg) {
		cout << msg << '\n';
		exit(0);
	}
}