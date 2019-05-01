#include "Midi.h"

#include "Windows.h"
#include "../rtmidi/RtMidi.h"
#include <iostream>
#include <iomanip>

void Midi::keyDown(uint8_t key, uint8_t velocity)
{
	message[0] = 144;
	message[1] = key;
	message[2] = velocity;

	try {
		midiout->sendMessage(&message);
	}
	catch (RtMidiError &error) {
		error.printMessage();
		//exit(EXIT_FAILURE);
	}
}

void Midi::keyUp(uint8_t key, uint8_t velocity)
{
	message[0] = 128;
	message[1] = key;
	message[2] = velocity;

	try {
		midiout->sendMessage(&message);
	}
	catch (RtMidiError &error) {
		error.printMessage();
		//exit(EXIT_FAILURE);
	}
}

Midi::Midi()
{
	// Initialize everything to 255
	keysToNotes1.fill(255);
	keysToNotes2.fill(255);

	// Function row
	keysToNotes1[VK_ESCAPE] = 0x01;
	keysToNotes1[VK_F1] = 0x54;
	keysToNotes1[VK_F2] = 0x55;
	keysToNotes1[VK_F3] = 0x56;
	keysToNotes1[VK_F4] = 0x57;
	keysToNotes1[VK_F5] = 0x58;
	keysToNotes1[VK_F6] = 0x59;
	keysToNotes1[VK_F7] = 0x5A;
	keysToNotes1[VK_F8] = 0x5B;
	keysToNotes1[VK_F9] = 0x5C;
	keysToNotes1[VK_F10] = 0x5D;
	keysToNotes1[VK_F11] = 0x5E;
	keysToNotes1[VK_F12] = 0x5F;
	keysToNotes1[VK_SNAPSHOT] = 0x37;
	keysToNotes1[VK_INSERT] = 0x6B;
	keysToNotes1[VK_DELETE] = 0x6C;
	keysToNotes1[VK_HOME] = 0x60;
	keysToNotes1[VK_END] = 0x68;
	keysToNotes1[VK_PRIOR] = 0x62;
	keysToNotes1[VK_NEXT] = 0x6A;

	// Numbers row
	keysToNotes1[VK_OEM_3] = 0x29; // ` key
	keysToNotes1['1'] = 0x02;
	keysToNotes1['2'] = 0x03;
	keysToNotes1['3'] = 0x04;
	keysToNotes1['4'] = 0x05;
	keysToNotes1['5'] = 0x06;
	keysToNotes1['6'] = 0x07;
	keysToNotes1['7'] = 0x08;
	keysToNotes1['8'] = 0x09;
	keysToNotes1['9'] = 0x0A;
	keysToNotes1['0'] = 0x0B;
	keysToNotes1[VK_OEM_MINUS] = 0x0C;
	keysToNotes1['='] = 0x0D;
	keysToNotes1[VK_BACK] = 0x0E;

	// Top row
	keysToNotes1[VK_TAB] = 0x0F;
	keysToNotes1['Q'] = 0x10;
	keysToNotes1['W'] = 0x11;
	keysToNotes1['E'] = 0x12;
	keysToNotes1['R'] = 0x13;
	keysToNotes1['T'] = 0x14;
	keysToNotes1['Y'] = 0x15;
	keysToNotes1['U'] = 0x16;
	keysToNotes1['I'] = 0x17;
	keysToNotes1['O'] = 0x18;
	keysToNotes1['P'] = 0x19;
	keysToNotes1[VK_OEM_4] = 0x1A; // left bracket
	keysToNotes1[VK_OEM_6] = 0x1B;
	keysToNotes1[VK_OEM_5] = 0x2B; // \ key

	// Middle row
	keysToNotes1['A'] = 0x1E;
	keysToNotes1['S'] = 0x1F;
	keysToNotes1['D'] = 0x20;
	keysToNotes1['F'] = 0x21;
	keysToNotes1['G'] = 0x22;
	keysToNotes1['H'] = 0x23;
	keysToNotes1['J'] = 0x24;
	keysToNotes1['K'] = 0x25;
	keysToNotes1['L'] = 0x26;
	keysToNotes1[VK_OEM_1] = 0x27; // ; key
	keysToNotes1[VK_OEM_7] = 0x28; // ' key
	keysToNotes1[VK_RETURN] = 0x1C;

	// Bottom row
	keysToNotes1[VK_LSHIFT] = 0x2A;
	keysToNotes1['Z'] = 0x2C;
	keysToNotes1['X'] = 0x2D;
	keysToNotes1['C'] = 0x2E;
	keysToNotes1['V'] = 0x2F;
	keysToNotes1['B'] = 0x30;
	keysToNotes1['N'] = 0x31;
	keysToNotes1['M'] = 0x32;
	keysToNotes1[VK_OEM_COMMA] = 0x33;
	keysToNotes1[VK_OEM_PERIOD] = 0x34;
	keysToNotes1[VK_OEM_2] = 0x35; // / key
	keysToNotes1[VK_RSHIFT] = 0x36;

	// Full-bottom row
	keysToNotes1[VK_LCONTROL] = 0x1D;
	keysToNotes1[VK_SPACE] = 0x39;
	keysToNotes1[VK_APPS] = 0x76;
	keysToNotes1[VK_RCONTROL] = 0x1D;

	// Numpad
	keysToNotes1[VK_NUMPAD0] = 0x40;
	keysToNotes1[VK_NUMPAD1] = 0x41;
	keysToNotes1[VK_NUMPAD2] = 0x42;
	keysToNotes1[VK_NUMPAD3] = 0x43;
	keysToNotes1[VK_NUMPAD4] = 0x44;
	keysToNotes1[VK_NUMPAD5] = 0x45;
	keysToNotes1[VK_NUMPAD6] = 0x46;
	keysToNotes1[VK_NUMPAD7] = 0x47;
	keysToNotes1[VK_NUMPAD8] = 0x48;
	keysToNotes1[VK_NUMPAD9] = 0x49;

	keysToNotes2['A'] = 0x70;
	keysToNotes2['S'] = 0x71;
	keysToNotes2['D'] = 0x72;
	keysToNotes2['F'] = 0x73;
	keysToNotes2['G'] = 0x74;
	keysToNotes2['H'] = 0x75;
	keysToNotes2['J'] = 0x76;
	keysToNotes2['K'] = 0x77;
	keysToNotes2['L'] = 0x78;
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

			if (portName == "LoopBe Internal MIDI 1" || portName == "loopMIDI Port 1") {
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
		//message[0] = 144;
		//message[1] = 64;
		//message[2] = 90;
		//midiout->sendMessage(&message);
	}
	catch (RtMidiError &error) {
		error.printMessage();
		//exit(EXIT_FAILURE);
	}
}



void Midi::key(USHORT key, uint64_t device, bool down) {
	// First of all, check if CAPS LOCK was pressed
	if (key == VK_CAPITAL) {
		if (!down) {
			if ((GetKeyState(VK_CAPITAL) & 0x0001) == 0) {
				std::cout << "DISABLING" << std::endl;
				toastExists = true;
				toastText = L"Disabled keyboard-to-MIDI";

				// Caps Lock is OFF
				enabled = false;
				for (size_t i = 0; i < pressed.size(); i++) {
					// Call off all the buttons
					if (pressed[i]) {
						keyUp(i);
						pressed[i] = false;
					}
					// ???
					// Don't call off all the buttons, since we might want
					// to leave some open???
				}
			}
			else {
				// Caps Lock is ON
				enabled = true;
				std::cout << "ENABLING" << std::endl;
				toastExists = true;
				toastText = L"!! Enabling keyboard-to-MIDI";
			}
		}

		return;
	}
	if (enabled) {
		// Get the first device
		if (!hasDevice) {
			deviceOne = device;
			hasDevice = true;
			std::cout << "Associated device " << device << " as keyboard #1. Proceed with your other devices!" << std::endl;
		}

		uint8_t note;
		if (key >= Midi::MAXKEYS) {
			note = 255;
		} else if (device == deviceOne) {
			note = keysToNotes1[key];
		} else {
			note = keysToNotes2[key];
		}

		if (note < 128 && pressed[note] != down) { // status has changed
			// Key was pressed, party!
			if (down) {
				keyDown(note);
			}
			else {
				keyUp(note);
			}
			std::cout << "key " << std::setw(5) << note << " is " << down << std::endl;
			pressed[note] = down;
		}
	}
}

Midi::~Midi()
{
	midiout->closePort();
	delete midiout;
}
