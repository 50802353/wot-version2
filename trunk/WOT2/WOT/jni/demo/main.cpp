#include "gametutor.h"
#include "CExample.h"

#if CONFIG_PLATFORM == PLATFORM_WIN32_VS
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

	ESContext esContext;
	char m_strTitle[] = "WOT";
	int m_iWidth = 800;
	int m_iHeight = 480;



	esInitContext ( &esContext );
	esCreateWindow ( &esContext, m_strTitle, m_iWidth, m_iHeight, ES_WINDOW_RGB );
	esRegisterDrawFunc ( &esContext, CVSView::onPaint);
	esRegisterKeyFunc( &esContext, CVSView::onKey);
	esRegisterTouchDownFunc(&esContext, CVSView::onTouchDown);
	esRegisterTouchUpFunc(&esContext, CVSView::onTouchUp);
	esRegisterTouchMoveFunc(&esContext, CVSView::onTouchMove);

	SGameConfig cnf = {
		m_iWidth,
		m_iHeight,
		false,
		m_strTitle,
		CGLES2Driver::GetInstance(),
		new CExample(),
		&esContext
	};
	GameTutor::StartApp(cnf);
	GameTutor::FinalizeApp();


	/*while (true)
	{
		CGame* a = CGame::GetInstance();
		if (!a->IsAlive())
			return 0;
	};*/
}

#elif CONFIG_PLATFORM == PLATFORM_ANDROID

extern "C" {
JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_step(JNIEnv * env, jobject obj);
JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_KeyDown(JNIEnv * env, jobject obj, jint keycode);
JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_KeyUp(JNIEnv * env, jobject obj, jint keycode);
JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_TouchDown(JNIEnv * env, jobject obj, jint x, jint y);
JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_TouchUp(JNIEnv * env, jobject obj, jint x, jint y);
JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_TouchMove(JNIEnv * env, jobject obj, jint x, jint y);
JNIEXPORT bool JNICALL Java_bkit_wot_GL2JNILib_IsListenEvent(JNIEnv * env, jobject obj);
JNIEXPORT bool JNICALL Java_bkit_wot_GL2JNILib_IsEndGame(JNIEnv * env, jobject obj);
};


JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	GameTutor::CGLES2Driver::GetInstance();
	GameTutor::SGameConfig cnf = {
		width,
		height,
		false,
		"Hello",
		GameTutor::CGLES2Driver::GetInstance(),
		new CExample(),
	};
	GameTutor::StartApp(cnf);
	Log("Start OK");
	//GameTutor::FinalizeApp();
	//Log("Final OK");
}

JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_step(JNIEnv * env, jobject obj)
{

    GameTutor::CAndroidView::GetInstance()->Update();
}

JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_KeyDown(JNIEnv * env, jobject obj, jint keycode)
{
	GameTutor::CAndroidView::GetInstance()->onKeyDown(keycode);
}

JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_KeyUp(JNIEnv * env, jobject obj, jint keycode)
{
	GameTutor::CAndroidView::GetInstance()->onKeyUp(keycode);
}

JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_TouchDown(JNIEnv * env, jobject obj, jint x, jint y)
{
	GameTutor::CAndroidView::GetInstance()->onTouchDown(x, y);
}

JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_TouchUp(JNIEnv * env, jobject obj, jint x, jint y)
{
	GameTutor::CAndroidView::GetInstance()->onTouchUp(x, y);
}

JNIEXPORT void JNICALL Java_bkit_wot_GL2JNILib_TouchMove(JNIEnv * env, jobject obj, jint x, jint y)
{
	GameTutor::CAndroidView::GetInstance()->onTouchMove(x, y);
}

JNIEXPORT bool JNICALL Java_bkit_wot_GL2JNILib_IsListenEvent(JNIEnv * env, jobject obj)
{
	return GameTutor::CGame::GetInstance()->isListenEvent;
}

JNIEXPORT bool JNICALL Java_bkit_wot_GL2JNILib_IsEndGame(JNIEnv * env, jobject obj)
{
	return GameTutor::CGame::GetInstance()->IsAlive();
}

#endif
