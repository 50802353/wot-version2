#include "gametutor.h"
#include "CExample.h"

int main()
{
	CWriterStream<CFileWin32Driver> *Fo = new CWriterStream<CFileWin32Driver> ("test.bin");
	Fo->WriteInt32(-100);
	Fo->Close();
	SAFE_DEL(Fo);

	CReaderStream<CFileWin32Driver> *F = new CReaderStream<CFileWin32Driver>("test.bin");
	int re;
	F->ReadInt32(re);
	printf("%d\n", re);
	F->Close();
	SAFE_DEL(F);

	SGameConfig cnf = {
		400,
		200,
		false,
		"Hello",
		CGLPipelineDriver::GetInstance(),
		new CExample(),
	};
	GameTutor::StartApp(cnf);
	GameTutor::FinalizeApp();

	while(true);
}