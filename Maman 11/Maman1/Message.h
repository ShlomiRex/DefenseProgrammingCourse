#pragma once

#include <string>
#include <iostream>

class Message
{
private:
	std::string text;
public:
	Message(std::string);
	~Message();
	std::string getText() const;

	//My own functions
	friend std::ostream& operator << (std::ostream& os, const Message& msg)
	{
		os << "Message(\"" << msg.getText() << "\")";
		return os;
	};
};

