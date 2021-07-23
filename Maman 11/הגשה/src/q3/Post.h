#pragma once

#include "Media.h"

#include <iostream>


class Post
{
private:
	std::string text;
	Media* media;
public:
	Post(std::string);
	Post(std::string, Media*);
	~Post();

	std::string getText();
	Media* getMedia();

	friend std::ostream& operator << (std::ostream& os, const Post& post)
	{
		os << "Post(\"" << post.text << "\"," << *post.media << ")";
		return os;
	};
};

