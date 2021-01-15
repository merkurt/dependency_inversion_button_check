
struct buttonCheck_input {
	virtual bool buttonRead(void) {
		return 0;
	}
};

struct buttonCheck_output {
	virtual void printOutput(const char* output) {
		;
	}
};

struct buttonCheck {
	bool buttonLastState{ 0 };
	bool buttonCurrentState{ 0 };
	void run() {
		buttonLastState = buttonCurrentState;
		buttonCurrentState = input->buttonRead();
		if (buttonCurrentState != buttonLastState) {
			if (buttonCurrentState > buttonLastState) {
				output->printOutput("RISING");
			}
			else {
				output->printOutput("FALLING");
			}
		}
	}
	struct buttonCheck_input* input;
	struct buttonCheck_output* output;
};

