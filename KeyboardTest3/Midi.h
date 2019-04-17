#pragma once

#include "../rtmidi/RtMidi.h"
#include "windows.h"
#include <array>
#include <bitset>

class Midi
{
	RtMidiOut *midiout;

	int designatedPort;

	// There are 128 MIDI notes
	std::bitset<128> pressed = { false };
	
	// Scratch vector
	std::vector<unsigned char> message = std::vector<unsigned char>(3);

	bool enabled = false;

	void keyDown(uint8_t key, uint8_t velocity = 90);
	void keyUp(uint8_t key, uint8_t velocity = 90);

	const static uint16_t MAXKEYS = 512;
	std::array<uint8_t, Midi::MAXKEYS> keysToNotes1;
	std::array<uint8_t, Midi::MAXKEYS> keysToNotes2;

	uint64_t deviceOne;
	bool hasDevice = false;
public:
	Midi();
	~Midi();

	void connect();

	void key(USHORT key, uint64_t device, bool down);
};

