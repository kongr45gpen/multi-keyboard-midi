#pragma once
#include "../WinToast/src/wintoastlib.h"

class WinToastHandler : public WinToastLib::IWinToastHandler {
public:
	// Public interfaces
	void toastActivated() const override {}
	void toastActivated(int actionIndex) const override {}
	void toastDismissed(WinToastDismissalReason state) const override {}
	void toastFailed() const override {}
};