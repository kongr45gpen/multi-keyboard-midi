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
	keysToNotes1[VK_ESCAPE] = 0x00;
	keysToNotes1[VK_F1] = 0x01;
	keysToNotes1[VK_F2] = 0x02;
	keysToNotes1[VK_F3] = 0x03;
	keysToNotes1[VK_F4] = 0x04;
	keysToNotes1[VK_F5] = 0x05;
	keysToNotes1[VK_F6] = 0x06;
	keysToNotes1[VK_F7] = 0x07;
	keysToNotes1[VK_F8] = 0x08;
	keysToNotes1[VK_F9] = 0x09;
	keysToNotes1[VK_F10] = 0x0A;
	keysToNotes1[VK_F11] = 0x0B;
	keysToNotes1[VK_F12] = 0x0C;
	keysToNotes1[VK_SNAPSHOT] = 0x0D;
	keysToNotes1[VK_INSERT] = 0x0E;
	keysToNotes1[VK_DELETE] = 0x0F;
	keysToNotes1[VK_HOME] = 0x10;
	keysToNotes1[VK_END] = 0x11;
	keysToNotes1[VK_PRIOR] = 0x12;
	keysToNotes1[VK_NEXT] = 0x13;

	// Numbers row
	keysToNotes1[VK_OEM_3] = 0x14; // ` key
	keysToNotes1['1'] = 0x15;
	keysToNotes1['2'] = 0x16;
	keysToNotes1['3'] = 0x17;
	keysToNotes1['4'] = 0x18;
	keysToNotes1['5'] = 0x19;
	keysToNotes1['6'] = 0x1A;
	keysToNotes1['7'] = 0x1B;
	keysToNotes1['8'] = 0x1C;
	keysToNotes1['9'] = 0x1D;
	keysToNotes1['0'] = 0x1E;
	keysToNotes1[VK_OEM_MINUS] = 0x1F;
	keysToNotes1[VK_OEM_PLUS] = 0x20;
	keysToNotes1[VK_BACK] = 0x21;

	// Top row
	keysToNotes1[VK_TAB] = 0x22;
	keysToNotes1['Q'] = 0x23;
	keysToNotes1['W'] = 0x24;
	keysToNotes1['E'] = 0x25;
	keysToNotes1['R'] = 0x26;
	keysToNotes1['T'] = 0x27;
	keysToNotes1['Y'] = 0x28;
	keysToNotes1['U'] = 0x29;
	keysToNotes1['I'] = 0x2A;
	keysToNotes1['O'] = 0x2B;
	keysToNotes1['P'] = 0x2C;
	keysToNotes1[VK_OEM_4] = 0x2D; // left bracket
	keysToNotes1[VK_OEM_6] = 0x2E;
	keysToNotes1[VK_OEM_5] = 0x2F; // \ key

	// Middle row
	keysToNotes1['A'] = 0x30;
	keysToNotes1['S'] = 0x31;
	keysToNotes1['D'] = 0x32;
	keysToNotes1['F'] = 0x33;
	keysToNotes1['G'] = 0x34;
	keysToNotes1['H'] = 0x35;
	keysToNotes1['J'] = 0x36;
	keysToNotes1['K'] = 0x37;
	keysToNotes1['L'] = 0x38;
	keysToNotes1[VK_OEM_1] = 0x39; // ; key
	keysToNotes1[VK_OEM_7] = 0x3A; // ' key
	keysToNotes1[VK_RETURN] = 0x3B;

	// Bottom row
	keysToNotes1[VK_LSHIFT] = 0x3C;
	keysToNotes1['Z'] = 0x3D;
	keysToNotes1['X'] = 0x3E;
	keysToNotes1['C'] = 0x3F;
	keysToNotes1['V'] = 0x40;
	keysToNotes1['B'] = 0x41;
	keysToNotes1['N'] = 0x42;
	keysToNotes1['M'] = 0x43;
	keysToNotes1[VK_OEM_COMMA] = 0x44;
	keysToNotes1[VK_OEM_PERIOD] = 0x45;
	keysToNotes1[VK_OEM_2] = 0x46; // / key
	keysToNotes1[VK_RSHIFT] = 0x47;

	// Full-bottom row
	keysToNotes1[VK_LCONTROL] = 0x48;
	keysToNotes1[VK_SPACE] = 0x49;
	keysToNotes1[VK_APPS] = 0x4A;
	keysToNotes1[VK_RCONTROL] = 0x4B;

	// Numpad
	keysToNotes1[VK_NUMPAD0] = 0x4C;
	keysToNotes1[VK_NUMPAD1] = 0x4D;
	keysToNotes1[VK_NUMPAD2] = 0x4E;
	keysToNotes1[VK_NUMPAD3] = 0x4F;
	keysToNotes1[VK_NUMPAD4] = 0x50;
	keysToNotes1[VK_NUMPAD5] = 0x51;
	keysToNotes1[VK_NUMPAD6] = 0x52;
	keysToNotes1[VK_NUMPAD7] = 0x53;
	keysToNotes1[VK_NUMPAD8] = 0x54;
	keysToNotes1[VK_NUMPAD9] = 0x55;

	// Now, perform the calculations for the second keyboard
	// Copy all the keys in a transposed way
	for (int i = 0; i < 255; i++) {
		uint8_t note = keysToNotes1[i];
		if (note > 0x21) note--;
		if (note > 0x22) note--;
		if (note > 0x2F) note--;
		if (note > 0x3B) note--;
		if (note > 0x3C) note--;
		keysToNotes2[i] = keysToNotes1[i] + 0x55 - 0x14;
	}

	// Function row stays the same
	keysToNotes2[VK_ESCAPE] = keysToNotes1[VK_ESCAPE];
	keysToNotes2[VK_F1] = keysToNotes1[VK_F1];
	keysToNotes2[VK_F2] = keysToNotes1[VK_F2];
	keysToNotes2[VK_F3] = keysToNotes1[VK_F3];
	keysToNotes2[VK_F4] = keysToNotes1[VK_F4];
	keysToNotes2[VK_F5] = keysToNotes1[VK_F5];
	keysToNotes2[VK_F6] = keysToNotes1[VK_F6];
	keysToNotes2[VK_F7] = keysToNotes1[VK_F7];
	keysToNotes2[VK_F8] = keysToNotes1[VK_F8];
	keysToNotes2[VK_F9] = keysToNotes1[VK_F9];
	keysToNotes2[VK_F10] = keysToNotes1[VK_F10];
	keysToNotes2[VK_F11] = keysToNotes1[VK_F11];
	keysToNotes2[VK_F12] = keysToNotes1[VK_F12];
	keysToNotes2[VK_SNAPSHOT] = keysToNotes1[VK_SNAPSHOT];
	keysToNotes2[VK_INSERT] = keysToNotes1[VK_INSERT];
	keysToNotes2[VK_DELETE] = keysToNotes1[VK_DELETE];
	keysToNotes2[VK_HOME] = keysToNotes1[VK_HOME];
	keysToNotes2[VK_END] = keysToNotes1[VK_END];
	keysToNotes2[VK_PRIOR] = keysToNotes1[VK_PRIOR];
	keysToNotes2[VK_NEXT] = keysToNotes1[VK_NEXT];
	// Numpad stays the same (takes care of laptops without numpad)
	keysToNotes2[VK_NUMPAD0] = keysToNotes1[VK_NUMPAD0];
	keysToNotes2[VK_NUMPAD1] = keysToNotes1[VK_NUMPAD1];
	keysToNotes2[VK_NUMPAD2] = keysToNotes1[VK_NUMPAD2];
	keysToNotes2[VK_NUMPAD3] = keysToNotes1[VK_NUMPAD3];
	keysToNotes2[VK_NUMPAD4] = keysToNotes1[VK_NUMPAD4];
	keysToNotes2[VK_NUMPAD5] = keysToNotes1[VK_NUMPAD5];
	keysToNotes2[VK_NUMPAD6] = keysToNotes1[VK_NUMPAD6];
	keysToNotes2[VK_NUMPAD7] = keysToNotes1[VK_NUMPAD7];
	keysToNotes2[VK_NUMPAD8] = keysToNotes1[VK_NUMPAD8];
	keysToNotes2[VK_NUMPAD9] = keysToNotes1[VK_NUMPAD9];
	// Symbols from the bottom row stay the same
	keysToNotes2[VK_OEM_COMMA] = keysToNotes1[VK_OEM_COMMA];
	keysToNotes2[VK_OEM_PERIOD] = keysToNotes1[VK_OEM_PERIOD];
	keysToNotes2[VK_OEM_2] = keysToNotes1[VK_OEM_2];
	keysToNotes2[VK_RSHIFT] = keysToNotes1[VK_RSHIFT];
	keysToNotes2[VK_LCONTROL] = keysToNotes1[VK_LCONTROL];
	keysToNotes2[VK_SPACE] = keysToNotes1[VK_SPACE];
	keysToNotes2[VK_APPS] = keysToNotes1[VK_APPS];
	keysToNotes2[VK_RCONTROL] = keysToNotes1[VK_RCONTROL];
	// Some extra symbols stay the same
	keysToNotes2[VK_BACK] = 0x21;
	keysToNotes2[VK_TAB] = 0x22;
	keysToNotes2[VK_OEM_5] = 0x2F; // \ key
	keysToNotes2[VK_RETURN] = 0x3B;
	keysToNotes2[VK_LSHIFT] = 0x3C;
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



void Midi::key(USHORT key, uint64_t device, bool down, USHORT flags, USHORT makeCode) {
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

		// ???
		if (key == VK_SHIFT) {
			key = (makeCode == 0x36) ? VK_RSHIFT : VK_LSHIFT;
		}
		else if (key == VK_CONTROL) {
			key = ((flags & RI_KEY_E0) != 0) ? VK_LCONTROL : VK_RCONTROL;
		}
		else if (key == VK_MENU) {
			key = ((flags & RI_KEY_E0) != 0) ? VK_LMENU : VK_RMENU;
		}

		uint8_t note;
		if (key >= Midi::MAXKEYS) {
			note = 255;
		}
		else if (device == deviceOne) {
			note = keysToNotes1[key];
		}
		else {
			note = keysToNotes2[key];
		}

		/*
		std::cout << "rcvevt " << std::setw(5) << std::hex << ((int)key) << "->"
			<< std::setw(5) << ((int)note) << " is " << down
			<< std::endl << std::dec;
		*/

		if (note < 128 && pressed[note] != down) { // status has changed
			// Key was pressed, party!
			if (down) {
				keyDown(note);
			}
			else {
				keyUp(note);
			}
			std::cout << "key " << std::setw(5) << std::hex << ((int)key) << "->"
				<< std::setw(5) << ((int)note) << " is " << down << std::endl;
			pressed[note] = down;
		}

		if (note >= 128) {
			std::cout << "unknown press " << std::setw(5) << std::hex << ((int)key) << "->"
				<< std::setw(5) << ((int)note) << " is " << down << std::endl << std::dec;
		}
	}
}

Midi::~Midi()
{
	midiout->closePort();
	delete midiout;
}
