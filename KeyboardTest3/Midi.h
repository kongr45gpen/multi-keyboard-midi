#pragma once

#include "../rtmidi/RtMidi.h"
#include "windows.h"
#include <bitset>

class Midi
{
	RtMidiOut *midiout;

	int designatedPort;

	// There are 128 MIDI notes
	std::bitset<128> pressed = { false };
	
	// Scratch vector
	std::vector<unsigned char> message = std::vector<unsigned char>(3);
public:
	Midi();
	~Midi();

	void connect();

	void key(USHORT key, uint64_t device, bool down);
};

