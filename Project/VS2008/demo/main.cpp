#include "gametutor.h"
#include "CDemo.h"

int main()
{
	SGameConfig cnf = {
		800,
		600,
		false,
		"Hello",
		CGLPipelineDriver::GetInstance(),
		CALAudioDriver::GetInstance(),
		new CDemo(),
	};
	GameTutor::StartApp(cnf);
	GameTutor::FinalizeApp();
}