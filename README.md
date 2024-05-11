# Window Wrapper Class

<p>By using this FREE library, you agree to the terms of use. Only term of use is that if you use it, you give me credit for it. Other then that, enjoy using it and you can change it as you see fit. If you do make changes, please let me know because I might update this to incorporate your changes (with credit of course). Thank you for taking the time to look at it and I hope you enjoy it.</p>

<p>This is a basic window wrapper class so that you can create a window in as little as 4 lines of code.</p>

>cWIN myWindow;
>myWindow.RegisterWindow();
>myWindow.Create();
>myWindow.HandleMessages();

<p>This is all you need to create a basic window using this wrapper. I will go over all the functions and how they are used in this readme file.</p>

>cWIN()
>cWIN(string)
>cWIN(WNDCLASSEX)

<p>These are your constructors. All of them will work but two of them have added functionability. The second allows you to change the Window Title / Window Class during construction while the last allows you to just input your own WNDCLASSEX to override the built in one that is in the class itself.</p>

>bool RegisterWindow();

<p>This funtion registers your class. This is separate from the Create function and the constructor so that the programmer has time to edit the WNDCLASSEX as they see fit before registering and you can call create as many times as you like later. This is useful if you have multiple windows that you want to create and run.</p>

>bool Create();
>bool Create(int, int, int, int);
>bool Create()

<p>These are the functions you use to create the window. The default for the window size is position is USEDEFAULT but you can either used the other two methods to specify the window size and position if you want more control over it.</p>

>void HandleMessages();

<p>This function is your message handler. It is set up for handling both accelorators and dialog messages. Dialog messages is setup by default by passing DLGWINDOWEXTRA in the cbWndExtra variable of WNDCLASSEX. This allows you to use WS_TABSTOP when you create windows to tab between. You can remove this default by using the function described later and setting it to 0.</p>

>void SetWindowTitle(string);

<p>This function will set your window title and class to the string you pass in.</p>

>void SetAccel(HACCEL);

<p>This is for setting up accelorators. Default setting is NULL for not having any.</p>

>void SetMenu(WORD);

<p>This is for setting up a menu from a resource. I don't use this myself, I rather create my menu when WM_CREATE is called but I still added this in case others would like to use it.</p>

>void SetIcon(HICON);
>void SetIcon(WORD);

<p>This allows you to set up an Icon either as a resource or from LoadImage / LoadCursor. If you use it from a resource, you do not need to use the MAKEINTRESOURCE macro as it is already used in the function. Just do SetIcon(ID_ICON); If you use LoadImage, then put (HICON) in from to cast it to HICON.</p>

>void SetCursor(HCURSOR);
>void SetCursor(WORD);

<p>This works exactly the same as the icon except this is for setting up a cursor. The only difference is that you won't use HICON to cast it, but rather use HCURSOR.</p>

>void SetBackground(COLORREF);
>void SetBackground(HBRUSH);

<p>This is for setting up the initial background color. I do have a repository for colors if you are interested in passing one of them into here.</p>

>void SetWndExtra(int);
>void SetClsExtra(int)

<p>This is to set the cbWndExtra and cbClsExtra variables. Most people don't use these and set tne to 0, but the default for WndExtra is DLGWINDOWEXTRA to allow TABSTOP to work. Setting this to 0 will remove that and allow you control TABBING yourself.</p>

>void SetWindowTimer(unsigned int);
>void SetFrameRate(unsigned int);

<p>These two do the same thing, except that the first one allows you finer control on how often the WM_TIMER is called. 1000 is equal to 1 second, so if you call it every 500, it will call WM_TIMER every half a second if other priority calls are not being made at the time. This is a lower priority Message so it isn't guaranteed at the time, keep that in mind. FrameRate does the math of computing how many times you want it to load in a second. So 30 would be 30 times in a second which is standard, 60 being high quality if you are talking about loading graphics for a game. Though I would caution you on using this for a game, it would be better to create your own thread and handle it outside of the window messages instead for better quality.</p>

>void SetStyle(DWORD);

<p>The default style for any window created is WS_OVERLAPPEDWINDOW. You can use this to change the style of the window to anything you wish.</p>

>void SetParentWindow(HWND);

<p>This allows you to set a parent window for the class. The reason you may want to use a wrapper and still use this as a child window is that you can control the window inside the other window as you see fit.</p>

>void SetWndProc;

<p>This is where you can pass the WndProc that you want to run instead of the built in one for the class. Just create the function and pass it in with this function to use it.</p>

>void AddProc(UINT, LRESULT *(HWND, WPARAM, LPARAM));
>void RemoveProc(UINT);
>void ClearProc();

<p>This is to use the built in WndProc. To use it, create functions for each message and then pass it in. For this, I will give an example on how it is used since this could be more complicated. For this example, I have created an icon resource that I named IDI_ICON that is 256x256. You will also need to define TRAY_ICONUID, ID_EXIT and WM_TRAYMESSAGE for this example to work which is why I put it at the top. You create functions that return LRESULT and you pass in HWND, WPARAM, LPARAM as the variables which you can see down below. Usually in a Proc you would also have UINT msg, but that will already be used as I will go into shortly.</p>

>#define WM_TRAYMESSAGE (WM_USER + 1)<br>
>#define TRAYICONUID 60000<br>
>#define ID_EXIT 1501<br>
><br>
>LRESULT Create(HWND hWnd, WPARAM wParam, LPARAM lParam)<br>
{<br>
	NOTIFYICONDATA nid;<br>
	nid.cbSize = sizeof(NOTIFYICONDATA);<br>
	nid.hWnd = hWnd;<br>
	nid.uID = TRAY_ICONUID;<br>
	nid.uVersion = NOTIFYICON_VERSION;<br>
	nid.uCallbackMessage = WM_TRAYMESSAGE;<br>
	nid.hIcon = (HICON)LoadImage((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDI_ICON), IMAGE_ICON, 256, 256, LR_CREATEDIBSECTION);<br>
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;<br>
	StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), "William's Test Program!");<br>
	Shell_NotifyIcon(NIM_ADD, &nid);<br>
	return 0;<br>
}<br>
>
>LRESULT Command(HWND hWnd, WPARAM wParam, LPARAM lParam)<br>
{<br>
	RECT rc;<br>
	const HWND hDesktop = GetDesktopWindow();<br>
	GetWindowRect(hDesktop, &rc);<br>
	switch (LOWORD(wParam))<br>
	{<br>
	case ID_EXIT:<br>
	{<br>
		NOTIFYICONDATA nid;<br>
		nid.cbSize = sizeof(NOTIFYICONDATA);<br>
		nid.hWnd = hWnd;<br>
		nid.uID = TRAY_ICONUID;<br>
		Shell_NotifyIcon(NIM_DELETE, &nid);<br>
		PostQuitMessage(0);<br>
		break;<br>
	}<br>
	}<br>
	return 0;<br>
}<br>
>
>WNDProc TrayMessage(HWND hWnd, WPARAM wParam, LPARAM lParam)<br>
{<br>
	switch (lParam)<br>
	{<br>
	case WM_LBUTTONDBLCLK:<br>
	{<br>
		ShowWindow(hWnd, SW_NORMAL);<br>
		break;<br>
	}<br>
	case WM_RBUTTONUP:<br>
	{<br>
		POINT cursor;<br>
		GetCursorPos(&cursor);<br>
		HMENU hMenu = CreatePopupMenu();<br>
		InsertMenu(hMenu, 0, MF_BYPOSITION | MF_STRING, ID_EXIT, "Exit");<br>
		TrackPopupMenu(hMenu, TPM_LEFTALIGN, cursor.x, cursor.y, 0, hWnd, NULL);<br>
	}<br>
	default:<br>
		return (WNDProc)DefWindowProc(hWnd, WM_TRAYMESSAGE, wParam, lParam);<br>
	}<br>
	return 0;<br>
}<br>
>
>WNDProc Close(HWND hWnd, WPARAM wParam, LPARAM lParam)<br>
{<br>
	ShowWindow(hWnd, SW_HIDE);<br>
	return 0;<br>
}<br>
>
>WNDProc Quit(HWND hWnd, WPARAM wParam, LPARAM lParam)<br>
{<br>
	NOTIFYICONDATA nid;<br>
	nid.cbSize = sizeof(NOTIFYICONDATA);<br>
	nid.hWnd = hWnd;<br>
	nid.uID = TRAY_ICONUID;<br>
	Shell_NotifyIcon(NIM_DELETE, &nid);<br>
	PostQuitMessage(0);<br>
	return (WNDProc)DefWindowProc(hWnd, WM_QUIT, wParam, lParam);<br>
}<br>



<p>So here we used 5 functions. Now to add them, you would just do this ...</p>

>	cWIN Win("Will's Example!");<br>
	Win.SetIcon(IDI_ICON);<br>
	Win.SetBackground(RGB(255, 255, 255));<br>
	Win.AddProc(WM_CREATE, Create);<br>
	Win.AddProc(WM_COMMAND, Command);<br>
	Win.AddProc(WM_TRAYMESSAGE, TrayMessage);<br>
	Win.AddProc(WM_CLOSE, Close);<br>
	Win.AddProc(WM_QUIT, Quit);<br>
	if (!Win.RegisterWindow()) return -1;<br>
	if (!Win.Create()) return -2;<br>
	Win.HandleMessages();<br>

<p>Now that you see the code, you can see where the msg is added. WM_CREATE is called, so it will run the Create function to handle that message. The message wrapper will automatically run DefWindowProc if it doesn't find the messages. All messages are added to a map which is searched when a message is detected. This small example will create window and put the icon in the system tray. If you click the close button, it will minimize it to the system tray. To close the program, right click on the icon you used to create the program and then click close. Use double left click to reopen the window. A very simple program to demonstrate how to use the wrapper. The reason I used LoadImage here is that I like my ICONS to use transparancy so I wanted to pass in the LR_CREATEDIBSECTION in LoadImage. This isn't the default but it really should be for decent icons in todays world. You can create your own icons using a free problem called GIMP (it is what I use). Load an image into it, remove the background, and export it as an icon. Then you won't get that box around your icon in the system tray or anywhere it is used.</p>

>const HWND GetHWND();

<p>This is just to access the HWND of the class.</p>

>cWIN &operator=(const cWIN &right);
>bool operator==(const cWIN &right);
>bool operator!=(const cWIN &right);

<p>I don't even know why I bothered to add these, but they are operators that you can use. Not sure what use they will be, only added them just in case one day I did find a use for them.</p>
<p>If you have any questions or concerns, please feel free to let me know. I threw this together in a few days based on an older version I wrote 15 to 20 years ago that needed updating. There is a lot more I wish to add later like Automatica Window Skinning, but for now I stuck with the basics.</p>
<p>William Glenn Ward<br>Computer Programmer / Graphic Designer<br>WilliamW1979@netscape.net<br>GamerTag: WillWolf76<br><br>Programming C/C++ since 1998</p>
