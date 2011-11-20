#include "CAudioDriver.h"

namespace GameTutor
{
	CAudioDriver::CAudioDriver(EAudioDriver driver): m_AudioDriver(driver)
	{}

	bool CAudioDriver::IsAudioDriver(EAudioDriver driver)
	{
		return (m_AudioDriver==driver);
	}
}