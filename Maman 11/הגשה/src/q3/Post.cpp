#include "Post.h"

Post::Post(std::string what) {
	this->text = what;
	this->media = nullptr;
}

Post::Post(std::string what, Media* media) {
	this->text = what;
	this->media = media;
}

Post::~Post() {
	delete this->media;
}

std::string Post::getText()
{
	return this->text;
}

Media* Post::getMedia()
{
	return this->media;
}
