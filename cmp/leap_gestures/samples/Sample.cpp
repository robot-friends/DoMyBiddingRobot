/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.							 *
* Leap Motion proprietary and confidential. Not for distribution.							*
* Use subject to the terms of the Leap Motion SDK Agreement available at			 *
* https://developer.leapmotion.com/sdk_agreement, or another agreement				 *
* between Leap Motion and you, your company or other organization.						 *
\******************************************************************************/

#include <iostream>
#include <cstring>
#include "Leap.h"

#define STATE_END 3

using namespace Leap;

static const char *get_strongest_dir(Leap::Vector directions) {
	double
		x = directions[0],
		y = directions[1];
	if(fabs(x) > fabs(y))
		return x > 0 ? "right" : "left";
	return y > 0 ? "forward" : "back";
}

class SampleListener : public Listener {
	public:
		virtual void onInit(const Controller&);
		virtual void onConnect(const Controller&);
		virtual void onDisconnect(const Controller&);
		virtual void onExit(const Controller&);
		virtual void onFrame(const Controller&);
		virtual void onFocusGained(const Controller&);
		virtual void onFocusLost(const Controller&);
		virtual void onDeviceChange(const Controller&);
		virtual void onServiceConnect(const Controller&);
		virtual void onServiceDisconnect(const Controller&); };
void SampleListener::onInit(const Controller& controller) { /* printf("Initialized\n"); */ }
void SampleListener::onConnect(const Controller& controller) {
	/* printf("Connected\n"); */
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	controller.enableGesture(Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
	controller.enableGesture(Gesture::TYPE_SWIPE); }
void SampleListener::onDisconnect(const Controller& controller) { /* Note: not dispatched when running in a debugger. */ /* printf("Disconnected\n"); */ }
void SampleListener::onExit(const Controller& controller) { /* printf("Exited\n"); */ }

void SampleListener::onFrame(const Controller& controller) {
	// Get the most recent frame and report some basic information
	const Frame frame = controller.frame();
	// Get gestures
	const GestureList gestures = frame.gestures();
	for(auto &gesture : gestures) {
		switch(gesture.type()) {
			case Gesture::TYPE_SWIPE: {
				SwipeGesture swipe(gesture);
				if(gesture.state() != STATE_END)
					break;
				std::cout << get_strongest_dir(swipe.direction()) << std::endl;
				break;
			}
			/* case Gesture::TYPE_KEY_TAP: { */
			/* 	/1* KeyTapGesture tap(gesture); *1/ */
			/* 	printf("keytap\n"); */
			/* 	break; */
			/* } */
			/* case Gesture::TYPE_SCREEN_TAP: { */
			/* 	/1* ScreenTapGesture screentap(gesture); *1/ */
			/* 	printf("screentap\n"); */
			/* 	break; */
			/* } */
		}
	}
}

void SampleListener::onFocusGained(const Controller& controller) { /* printf("Focus Gained\n"); */ }
void SampleListener::onFocusLost(const Controller& controller) { /* printf("Focus Lost\n"); */ }
void SampleListener::onDeviceChange(const Controller& controller) {
	/* printf("Device Changed\n"); */
	/* const DeviceList devices = controller.devices(); */
	/* for(auto &d : devices) */
	/* 	printf("id: %d\tisStreaming: %s\n", d.toString().c_str(), (d.isStreaming() ? "true" : "false")); */ }
void SampleListener::onServiceConnect(const Controller& controller) { /* printf("Service Connected\n"); */ }
void SampleListener::onServiceDisconnect(const Controller& controller) { /* printf("Service Disconnected\n"); */ }

int main(int argc, char** argv) {
	// Create a sample listener and controller
	SampleListener listener;
	Controller controller;
	// Have the sample listener receive events from the controller
	controller.addListener(listener);
	if(argc > 1 && strcmp(argv[1], "--bg") == 0)
		controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
	getchar();
	// Remove the sample listener when done
	controller.removeListener(listener);
	return 0;
}
