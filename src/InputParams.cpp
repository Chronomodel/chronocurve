#include "InputParams.h"


InputParams::InputParams()
{

}

InputParams::~InputParams()
{
    
}

void InputParams::init()
{
	mFile = InputFile(mFilepath, mTmin, mTmax);
}

void InputParams::display() const
{
	// Also display other params (not only file) ?
    mFile.display();
}
