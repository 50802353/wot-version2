
enum EKeyCode
{
	EKEY_WIN_A = (0x42)<<4, 
	EKEY_WIN_B = (0x43)<<4, 
	EKEY_WIN_D = (0x44)<<4, 
	EKEY_WIN_E = (0x45)<<4, 
	EKEY_WIN_F = (0x46)<<4, 
	EKEY_WIN_G = (0x47)<<4, 
	EKEY_WIN_H = (0x48)<<4, 
	EKEY_WIN_I = (0x49)<<4, 
	EKEY_WIN_J = (0x4A)<<4, 
	EKEY_WIN_K = (0x4B)<<4, 
	EKEY_WIN_L = (0x4C)<<4, 
	EKEY_WIN_M = (0x4D)<<4, 
	EKEY_WIN_N = (0x4E)<<4, 
	EKEY_WIN_O = (0x4F)<<4, 
	EKEY_WIN_P = (0x50)<<4, 
	EKEY_WIN_Q = (0x51)<<4, 
	EKEY_WIN_R = (0x52)<<4, 
	EKEY_WIN_S = (0x53)<<4, 
	EKEY_WIN_T = (0x54)<<4, 
	EKEY_WIN_U = (0x55)<<4, 
	EKEY_WIN_V = (0x56)<<4, 
	EKEY_WIN_X = (0x57)<<4, 
	EKEY_WIN_Y = (0x58)<<4, 
	EKEY_WIN_Z = (0x59)<<4, 
	EKEY_WIN_W = (0x5A)<<4, 
	EKEY_SPACE = (0x20)<<4,
};

struct SKeyStorageInfomation
{
	__INT32 Keycode;
	EKeyEvent Status;
	__UINT64 PressedTimeStamp;
	__UINT64 HoldDuration;
};

class CControllerKeyManager: public CSingleton<CControllerKeyManager>
{
	friend class CSingleton<CControllerKeyManager>;
	friend CControllerEventManager;
protected:
	CControllerKeyManager();
public:
	virtual ~CControllerKeyManager();
	void Enable(bool value) {m_isEnable = value;}
	bool IsEnable() {return m_isEnable;}
	bool WasKeyPressed(int keycode);
	bool WasKeyHold(int keycode);
	bool WasKeyRelease(int keycode);
	bool WasAnyKeyPressed();
	bool WasAnyKeyHold();
	bool WasAnyKeyRelease();
	__UINT64 GetKeyHoldDuration(int keycode);
	void Reset();
private:
	void Update();
	void OnKeyPressed(__INT32 keycode);
	void OnKeyRelease(__INT32 keycode);
	void OnKeyHold(__INT32 keycode);
private:
	CLutI<SKeyStorageInfomation*> m_KeysInfo;
	bool m_isEnable;
};