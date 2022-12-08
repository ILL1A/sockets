#ifndef _MESSAGE_H_
#define _MESSAGE_H_ 1
#include <iostream>
#include <string>

using namespace std;

namespace http_request {
	class Message {
	public:
		Message(int message_length, string sender_host, int sender_port, string message);
		const int get_message_length() const {
			return message_length_;
		}
		const string get_sender_host() const {
			return sender_host_;
		}
		const int get_sender_port() const {
			return sender_port_;
		}
		const string get_sender_message() const {
			return message_;
		}
	private:
		int message_length_;
		string sender_host_;
		int sender_port_;
		string message_;
	};
}

#endif // _MESSAGE_H_