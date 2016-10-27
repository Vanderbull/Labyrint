#include <windows.h>

#pragma comment ( lib, "dxguid.lib" ) /* guiid definitions */
//#if DIRECTINPUT_VERSION == 0x0800 
//#pragma comment ( lib, "dinput8.lib" )
//#else
#pragma comment ( lib, "dinput8.lib" )
#pragma comment ( lib, "dsound.lib" )
#pragma comment ( lib, "winmm.lib" )

#include <dinput.h>
#include <string>
#include <vector>
using namespace std;

// Used for mouse input
#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80)
// Used for Keyboard input
#define KEYDOWN(name, key) (name[key] & 0x80)

class diManager
{
public:
	~diManager(void);

	// singleton stuff
	static diManager& getInstance() { static diManager pInstance; return pInstance;}

	// initiating a input device for usage
	bool InitDirectInput(HINSTANCE hInst, HWND wndHandle, DWORD DeviceToUse);

	//Keyboard related functions
	bool isKeyDown(int which);

	//Mouse related functions
	bool isButtonDown(int which);
	inline int getCurMouseX(void) { return mouseState.lX; }
	inline int getCurMouseY(void) { return mouseState.lY; }
	inline int getCurMouseZ(void) { return mouseState.lZ; }

	//Overridable Input Processing Methods
	virtual HRESULT ProcessMouseInput();
	virtual HRESULT ProcessKeyboardInput();
	virtual HRESULT ProcessJoystickInput();

	void shutdown(void);

	void getInput(void);

private:
	diManager(void);

	LPDIRECTINPUT8        m_lpDI_Object;	// Direct input object
	
	LPDIRECTINPUTDEVICE8  m_lpDIDevice;		// Direct input device non specific
	LPDIRECTINPUTDEVICE8  m_lpDIKeyboard;	// Direct input device Keyboard
	LPDIRECTINPUTDEVICE8  m_lpDIMouse;		// Direct input device Mouse
	LPDIRECTINPUTDEVICE8  m_lpDIJoystick;   // Direct input device Joystick

	LPDIRECTINPUT8        g_lpDI;			// the direct input object old
	LPDIRECTINPUTDEVICE8  g_lpDIDevice;		// the direct input device old

	LPDIRECTINPUTDEVICE8  g_lpDIMouse;		// the direct input object old
	LPDIRECTINPUTDEVICE8  g_lpDIKeyboard;	// the direct input object old

	// char buffer for holding current state of Keyboard
	char buffer[256];

	DIDEVICEOBJECTDATA didod[256];
	DWORD dwElements;
	// the current state of the mouse device
	DIMOUSESTATE mouseState;
};