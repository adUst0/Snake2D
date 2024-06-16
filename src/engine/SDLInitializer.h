#pragma once

// Local includes

// SDL includes

// std includes

// Have this class as a first member variable in the top level game class because SDL initialization has to be the first code to execute
// while destruction should be the last code to execute
class SDLInitializer
{
public:
	SDLInitializer();
	~SDLInitializer();
};

