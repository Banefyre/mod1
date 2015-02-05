#ifndef _TimeManager_HPP_
#define _TimeManager_HPP_

#include <chrono>													// Used for the C++ 11 time functionality
#include <thread>													// used for the C++ 11 sleep functionality


// This is our TimeManager singleton class to calculate our frame rate and give a time slice.
// We use the Singleton design pattern so that we don't need to pass in the time slice everywhere.
class TimeManager
{
public:

	// The function to get the instance of the manager, or initialize and return the instance.
	// By creating a static variable of the instance we ensure this only gets created once.
	// This is also thread-safe in C++ 11 according to the specifications.
	static TimeManager& Instance()
	{
		static TimeManager instance;
		return instance;
	}

	// This calculates our current scene's frames per second and displays it in the console
	double calculateFrameRate(bool writeToConsole);

	// This returns the current time in seconds (since 1/1/1970, call "epoch")
	double getTime();

	// This pauses the current thread for an amount of time in milliseconds
	void sleep(int milliseconds);

	// This is the time slice that stores the total time in seconds that has elapsed since the last frame
	double deltaTime = 0;

	// This is the current time in seconds
	double currentTime = 0;

private:
	TimeManager(){};								// Private so that it can  not be called
	TimeManager(TimeManager const&);				// copy constructor is private
	TimeManager& operator=(TimeManager const&);		// assignment operator is private
};

#endif


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// This file defines our TimeManager class for calculating frame rate and giving
// a time slice between frames.
//
// 
// � 2000-2014 GameTutorials