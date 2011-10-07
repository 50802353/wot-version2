enum EControllerEvent
{
	ECE_POINTER,
	ECE_KEY,
};

enum EPointerEvent
{
	EPE_NONE,
	EPE_PRESSED,
	EPE_RELEASED,
	EPE_DRAGGED,
};

enum EKeyEvent
{
	EKE_NONE,
	EKE_PRESSED,
	EKE_HOLD,
	EKE_RELEASED,
};

struct SControllerEventPointerData
{
	__INT32 ID;
	EPointerEvent Event;
	__INT32 X;
	__INT32 Y;
};

struct SControllerEventKeyData
{
	__INT32 KeyCode;
	EKeyEvent Event;
};

struct SControllerEvent
{
	EControllerEvent Type;
	union 
	{
		SControllerEventPointerData PointerData;
		SControllerEventKeyData KeyData;
	};
};