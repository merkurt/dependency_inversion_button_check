#include "gtest/gtest.h"
#include "button_check.cpp"

const char* testOutput = "NaN";

void testOutput_clear(void) {
	testOutput = "NaN";
}

struct digital_read : buttonCheck_input{
	bool buttonRead() override {
		return 1;
	}
};

struct digital_read_to_zero : buttonCheck_input{
	bool buttonRead() override {
		return 0;
	}
};

struct serial_output : buttonCheck_output{
	void printOutput(const char* output) override {
		testOutput = output;
	}

};

TEST(buttonCheck, structIsAlive) {
	buttonCheck bc;
	ASSERT_EQ(bc.buttonLastState, 0);
	ASSERT_EQ(bc.buttonCurrentState, 0);
};

TEST(buttonCheck, InputIsAlive) {
	buttonCheck bc;
	bc.input = new digital_read;
	bc.output = new serial_output;
	ASSERT_EQ(bc.buttonCurrentState, 0);
	ASSERT_EQ(bc.buttonLastState, 0);
	bc.run();
	ASSERT_EQ(bc.buttonCurrentState, 1);
	ASSERT_EQ(bc.buttonLastState, 0);
	bc.run();
	ASSERT_EQ(bc.buttonCurrentState, 1);
	ASSERT_EQ(bc.buttonLastState, 1);
}

TEST(buttonCheck, RunFuncitonIsAlive) {
	testOutput_clear();
	buttonCheck bc;
	bc.input = new digital_read;
	bc.output = new serial_output;
	bc.buttonLastState = 1;
	ASSERT_EQ(bc.buttonLastState, 1);
	ASSERT_EQ(bc.buttonCurrentState, 0);
	bc.run();
	ASSERT_EQ(bc.buttonLastState, 0);
	ASSERT_EQ(bc.buttonCurrentState, 1);
}

TEST(buttonCheck, outputFunctionIsAlive) {
	testOutput_clear();
	buttonCheck bc;
	bc.input = new digital_read;
	bc.output = new serial_output;
	ASSERT_EQ(bc.buttonCurrentState, 0);
	ASSERT_EQ(bc.buttonLastState, 0);
	ASSERT_EQ(bc.buttonLastState, bc.buttonCurrentState);
	ASSERT_STREQ(testOutput, "NaN");
	bc.run();
	ASSERT_EQ(testOutput, "RISING");
	ASSERT_EQ(bc.buttonCurrentState, 1);
}

TEST(buttonCheck, outputFunctionTest1) {
	testOutput_clear();
	buttonCheck bc;
	bc.input = new digital_read;
	bc.output = new serial_output;
	ASSERT_EQ(bc.buttonCurrentState, 0);
	bc.buttonCurrentState = 1;
	ASSERT_EQ(bc.buttonCurrentState, 1);
	bc.run();
	ASSERT_EQ(bc.buttonLastState, 1);
	ASSERT_EQ(bc.buttonCurrentState, 1);
	ASSERT_STREQ(testOutput, "NaN");
}

TEST(buttonCheck, outputFunctionTest2) {
	testOutput_clear();
	buttonCheck bc;
	bc.input = new digital_read_to_zero;
	bc.output = new serial_output;
	ASSERT_EQ(bc.buttonCurrentState, 0);
	bc.buttonCurrentState = 1;
	ASSERT_EQ(bc.buttonCurrentState, 1);
	bc.run();
	ASSERT_STREQ(testOutput, "FALLING");
	ASSERT_EQ(bc.buttonCurrentState, 0);
	ASSERT_EQ(bc.buttonLastState, 1);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}