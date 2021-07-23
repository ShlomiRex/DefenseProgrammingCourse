#pragma once

#include <iostream>
#include <map>
#include <list>
#include <sstream>

#include "Post.h"
#include "Message.h"

class USocial;

class User {
	friend class USocial;
protected:
	USocial* us;
	unsigned long id;
	std::string name;
	std::list<unsigned long> friends;
	std::list<Post*> posts;
	std::list<Message*> receivedMsgs;
public:
	User();
	~User();

	unsigned long getId() const;
	std::string getName() const;
	void addFriend(User*);
	void removeFriend(User*);
	void post(std::string);
	void post(std::string, Media*);
	std::list<Post*> getPosts() const;
	void viewFriendsPosts() const;
	void receiveMessage(Message*);
	virtual void sendMessage(User*, Message*) const;
	void viewReceivedMessages() const;

	//My own functions
	friend std::ostream& operator << (std::ostream& os, const User& user)
	{
		os << "User(" << user.id << "," << user.name << ")";
		return os;
	};
protected:
	/**
	* My own function
	* Generic function to send message (for User and BuisnessUser)
	* Note: Only used internally, inside 'public sendMessage' function.
	*/
	void sendMessageGeneric(User* to, Message* msg, bool buisnessUser) const;
};

class BuisnessUser : public User
{
public:
	void sendMessage(User*, Message*) const;
};



class USocial {
	friend class User;
private:
	std::map<unsigned long, User*> users;
public:
	USocial();
	~USocial();

	User* registerUser(std::string name, bool buisnessUser = false);
	void removeUser(User*);
	User* getUserById(unsigned long);
};

