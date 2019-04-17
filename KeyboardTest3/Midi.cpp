#include "Midi.h"

#include "Windows.h"
#include "../rtmidi/RtMidi.h"
#include <iostream>

Midi::Midi()
{
	
}

void Midi::connect()
{
	std::cout << "Number of midi devices: " << midiOutGetNumDevs() << std::endl;



	// RtMidiOut constructor
	try {
		midiout = new RtMidiOut();
	}
	catch (RtMidiError &error) {
		error.printMessage();
		exit(EXIT_FAILURE);
	}
	// Check outputs.
	unsigned int nPorts = midiout->getPortCount();
	std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
	std::string portName;
	for (unsigned int i = 0; i < nPorts; i++) {
		try {
			portName = midiout->getPortName(i);

			if (portName == "LoopBe Internal MIDI 1") {
				designatedPort = i;
				std::cout << "Found designated port " << i << std::endl;
			}
		}
		catch (RtMidiError &error) {
			error.printMessage();
			delete midiout;
		}
		std::cout << "  Output Port #" << i + 1 << ": " << portName << '\n';
	}
	std::cout << '\n';
	// Clean up

	try {
		midiout->openPort(designatedPort);
		message[0] = 144;
		message[1] = 64;
		message[2] = 90;
		midiout->sendMessage(&message);
	}
	catch (RtMidiError &error) {
		error.printMessage();
		//exit(EXIT_FAILURE);
	}
}

void Midi::key(USHORT key, uint64_t device, bool down) {
	uint8_t note;
	// Convert key to note
	note = key;

	// Sanity check
	if (note >= 128) note = 0;

	// Old value
	bool old = pressed[note];
	if (old != down) {
		old = down;
		if (down) {
			message[0] = 144;
		}
		else {
			message[0] = 128;
		}
		pressed[note] = down;

		message[1] = note;
		message[2] = 90;
		try {
			midiout->sendMessage(&message);
		}
		catch (RtMidiError &error) {
			error.printMessage();
			//exit(EXIT_FAILURE);
		}
	}
}

Midi::~Midi()
{
	midiout->closePort();
	delete midiout;
}
