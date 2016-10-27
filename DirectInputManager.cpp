#include ".\DirectInputManager.h"

extern HINSTANCE hInst;				// holds the instance for this app

diManager::diManager(void)
{
	g_lpDI = NULL;
	g_lpDIMouse = NULL;
}

diManager::~diManager(void)
{
	shutdown();
}

/*******************************************************************
* initDirectInput
* Initializes DirectInput for use with a device
*******************************************************************/
bool diManager::InitDirectInput(HINSTANCE hInst, HWND wndHandle, DWORD DeviceToUse)
{
	HRESULT hr;

	// Create the DirectInput object. 
    hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, 
                            IID_IDirectInput8, (void**)&g_lpDI, NULL); 

	if FAILED(hr) 
		return false; 

//-------------------------------------------------------------------------

	if(DeviceToUse & 0x00000001L)
	{
		// Retrieve a pointer to an IDirectInputDevice8 interface 
		hr = g_lpDI->CreateDevice(GUID_SysMouse, &g_lpDIMouse, NULL); 
		if FAILED(hr)
			return false; 
	
		hr = g_lpDIMouse->SetDataFormat(&c_dfDIMouse); 
		if FAILED(hr)
			return false; 
	
		// Set the cooperative level 
		hr = g_lpDIMouse->SetCooperativeLevel(wndHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE); 
		if FAILED(hr) 
			return false; 

		// Get access to the input device. 
		hr = g_lpDIMouse->Acquire(); 
		if FAILED(hr) 
	        return false;
	}
	
	// Keyboard device initiating

	if(DeviceToUse & 0x00000002L)
	{
		// Retrieve a pointer to an IDirectInputDevice8 interface 
		hr = g_lpDI->CreateDevice(GUID_SysKeyboard, &g_lpDIKeyboard, NULL); 
		if FAILED(hr)
			return false; 
	
		hr = g_lpDIKeyboard->SetDataFormat(&c_dfDIKeyboard); 
		if FAILED(hr)
			return false; 
	
		// Set the cooperative level 
		hr = g_lpDIKeyboard->SetCooperativeLevel(wndHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE); 
		if FAILED(hr) 
			return false; 

		// Get access to the input device. 
		hr = g_lpDIKeyboard->Acquire(); 
		if FAILED(hr) 
	        return false;
	}

	return true;
}

/*******************************************************************
* shutdown
* Shuts down and releases DirectInput
*******************************************************************/
void diManager::shutdown(void)
{
	if (g_lpDI) 
    {
		if (g_lpDIKeyboard) 
        { 
			// Always unacquire device before calling Release(). 
            g_lpDIKeyboard->Unacquire(); 
            g_lpDIKeyboard->Release();
            g_lpDIKeyboard = NULL; 
        } 
        if (g_lpDIMouse) 
        { 
			// Always unacquire device before calling Release(). 
            g_lpDIMouse->Unacquire(); 
            g_lpDIMouse->Release();
            g_lpDIMouse = NULL; 
        } 
        g_lpDI->Release();
        g_lpDI = NULL; 
    } 
}

/*******************************************************************
* getInput
* Retrieves the current user input
*******************************************************************/
void diManager::getInput(void)
{
	HRESULT hr;

	//DIDEVICEOBJECTDATA didod[256];
	DWORD dwElements;
	hr = g_lpDIMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), 
                                    didod, &dwElements, 0 ); 

	//hr = g_lpDIMouse->GetDeviceState(sizeof(mouseState),(LPVOID)&mouseState); 


	// check the return state to see if the device is still accessible
	if (FAILED ( hr ))
	{
		// try and reacquire the input device
		hr = g_lpDIMouse->Acquire();
		// do a continuous loop until the device is reacquired
	       while( hr == DIERR_INPUTLOST ) 
			hr = g_lpDIMouse->Acquire();
	}			
}


/*******************************************************************
* isButtonDown
*******************************************************************/
bool diManager::isButtonDown(int which)
{
	return (bool)BUTTONDOWN(mouseState, which);
}

/*******************************************************************
* isKeyDown
*******************************************************************/
bool diManager::isKeyDown(int which)
{
	//return didod[DIK_LEFT].dwOfs;
	if(!didod[which].dwOfs)
		return (bool)KEYDOWN(buffer, which);
	return false;
}

/************************************************************************/
//Method:	ProcessKB()
//Purpose:	Capture Keyboard Input
/************************************************************************/
HRESULT diManager::ProcessKeyboardInput()
{
	HRESULT hr;

	hr = g_lpDIKeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), 
                                    didod, &dwElements, 0 ); 

	//Check for keyboard input and fill buffer
	hr = g_lpDIKeyboard->GetDeviceState(sizeof(buffer),(LPVOID)&buffer); 
    if FAILED(hr) 
    {
         g_lpDIKeyboard->Acquire();
         return E_FAIL; 
    }

	return S_OK;       
}

/************************************************************************/
//Method:	ProcessMouse
//Purpose:	Capture Mouse Input
/************************************************************************/
HRESULT diManager::ProcessMouseInput()
{
	HRESULT hr;
	//Check for mouse input and fill buffer
	hr = g_lpDIMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	if(hr == DIERR_INPUTLOST)
	{
		g_lpDIMouse->Acquire();
		return E_FAIL;
	}

	return S_OK;
}

/************************************************************************/
//Method:	ProcessJoy
//Purpose:	Capture Joystick Input
/************************************************************************/
HRESULT diManager::ProcessJoystickInput()
{
	//Get joystick state and fill buffer
//    if(FAILED(m_pDIJoy->Poll()))  
//    {
//        while( m_pDIJoy->Acquire() == DIERR_INPUTLOST ) 
//        {}

//        return E_FAIL; 
//    }

//    if( FAILED(m_pDIJoy->GetDeviceState( sizeof(DIJOYSTATE2), &m_js ) ) )
//        return E_FAIL;

	return S_OK;
}