struct SPointerStorageInfomation
{
	__INT32 ID;
	EPointerEvent Status;
	__INT32 PressedX;
	__INT32 PressedY;
	__INT32 DraggedX;
	__INT32 DraggedY;
	__INT32 LastDraggedX;
	__INT32 LastDraggedY;
	__INT32 DraggedDiffX;
	__INT32 DraggedDiffY;
};

struct SPointerUserInfo //for user
{
	__INT32 ID;
	SPosition2D<__INT32> OriginalPosition;
	SPosition2D<__INT32> CurrentPosition;
	__INT32 DragDistanceX;
	__INT32 DragDistanceY;
	__INT32 DragDiffDistanceX;
	__INT32 DragDiffDistanceY;
};

class CControllerPointerManager: public CSingleton<CControllerPointerManager>
{
	friend class CSingleton<CControllerPointerManager>;
	friend CControllerEventManager;
protected:
	CControllerPointerManager();
public:
	virtual ~CControllerPointerManager();
	void Reset();
	void SleepUntilPress(); // reset state, and wait until next press action
	void Enable(bool value) {m_isEnable = value;}
	bool IsEnable() {return m_isEnable;}

	bool WasTouchedInside(__INT32 x, __INT32 y, __INT32 w, __INT32 h);
	bool WasReleaseInside(__INT32 x, __INT32 y, __INT32 w, __INT32 h);

	__INT32 GetNumberOfActivePointers();
	void GetActivePointer(__INT32 maxPointer, __INT32 &num, SPointerUserInfo* info);
private:
	void PointerPressed(__INT32 ID, __INT32 x, __INT32 y);
	void PointerReleased(__INT32 ID, __INT32 x, __INT32 y);
	void PointerDragged(__INT32 ID, __INT32 x, __INT32 y);
	void Update();
private:
	CLutI<SPointerStorageInfomation*> m_PointersInfo;
	bool m_isEnable;
	bool m_isSleeping;
};