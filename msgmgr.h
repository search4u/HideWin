#pragma once
#include <list>
class MsgPump;
class MsgReceiver;
class HidenWin;
class MsgData
{
public:
	MsgData()
	{
		nMsgID = 0;
		wParam = 0;
		lParam = 0;
		sender = NULL;
		receiver = NULL;
	}

	MsgData(MsgData *p)
	{
		if (p)
		{
			nMsgID = p->nMsgID;
			wParam = p->wParam;
			lParam = p->lParam;
			sender = p->sender;
			receiver = p->receiver;
		}
	}

	unsigned int nMsgID;
	unsigned int wParam;
	unsigned int lParam;
	MsgPump *sender;
	MsgReceiver *receiver;
};


class HidenWin
{
public:
	HidenWin()
	{
		CreateHideWindow();
	}
	HidenWin(MsgPump *p)
	{
		pp = p;
		CreateHideWindow();
	}
	HWND m_hWnd;
	MsgPump *pp;

	enum{WM_USER_DATA = WM_USER+1000};
	void DoCallBack(MsgData *msg);

	static LRESULT CALLBACK MyWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == HidenWin::WM_USER_DATA)
		{
			HidenWin *hd = (HidenWin*)GetWindowLong(hWnd, GWL_USERDATA);
			hd->DoCallBack((MsgData*)wParam);
			return true;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	void CreateHideWindow()
	{
		//create hiden window
		WNDCLASS wndClass;
		wndClass.style          = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc    = MyWndProc;
		wndClass.cbClsExtra     = 0;
		wndClass.cbWndExtra     = 0;
		//wndClass.hInstance      = hInstance;
		//wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
		//wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndClass.lpszMenuName   = NULL;
		wndClass.lpszClassName  = TEXT("RedirectHidenWindow");

		RegisterClass(&wndClass);
		m_hWnd = CreateWindow(
			TEXT("RedirectHidenWindow"), // window class name
			NULL,          // window caption
			WS_OVERLAPPED, // window style
			CW_USEDEFAULT, // initial x position
			CW_USEDEFAULT, // initial y position
			CW_USEDEFAULT, // initial x size
			CW_USEDEFAULT, // initial y size
			NULL,          // parent window handle
			NULL,          // window menu handle
			NULL,          //hInstance, // program instance handle
			NULL);         // creation parameters

		SetWindowLong(m_hWnd, GWL_USERDATA, (long)this);
	}
};

class MsgReceiver
{	
public:
	virtual void OnMsg(MsgData *msgData) = 0;
};

class MsgPump
{
public:
	MsgPump()
	{
		m_hideWin = new HidenWin(this);
	}

	void NewHidenWin()
	{
		//m_hideWin = new HidenWin(this);
	}
	void AddObserver(MsgReceiver *rec)
	{
		if (find(receiverList.begin(),receiverList.end(),rec)==receiverList.end())
		{
			receiverList.push_back(rec);
		}
	}
	void RemoveObserVer(MsgReceiver *rec)
	{
		if (find(receiverList.begin(),receiverList.end(),rec)!=receiverList.end())
		{
			receiverList.push_back(rec);
		}
	}
	void Post(MsgData *msg)
	{
		MsgData *p = new MsgData(msg);
		::SendMessage(m_hideWin->m_hWnd,HidenWin::WM_USER_DATA,(WPARAM)p,0);
		delete p;
	}

	void CallBack(MsgData *msg)
	{
		if (!receiverList.empty())
		{
			std::list<MsgReceiver*>::iterator it = receiverList.begin();
			for (;it != receiverList.end(); it++)
			{
				(*it)->OnMsg(msg);
			}
		}
	};
private:
	std::list<MsgReceiver*> receiverList;
	HidenWin *m_hideWin;
};
void HidenWin::DoCallBack(MsgData *msg)
{
	if (pp)
	{
		pp->CallBack(msg);
	}
}




