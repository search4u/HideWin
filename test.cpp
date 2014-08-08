#include "windows.h"
#include <process.h> 
#include <regex>
//#include <string>
#include "download.h"

using namespace std;

unsigned __stdcall DownLoadPro( void* pArguments )
{
	Downloader *d = (Downloader*)pArguments;
	d->DoDownload();
	return 0;
} 

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == 10086)
	{
		HidenWin *hd = (HidenWin*)GetWindowLong(hWnd, GWL_USERDATA);
		hd->DoCallBack((MsgData*)wParam);
		return true;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

unsigned __stdcall MyProc( void* pArguments )
{
	HWND w = (HWND)pArguments;
	::SendMessage(w,10086,0,0);
	return 0;
} 
int main()
{
	MyUi ui;
	Downloader downloader;
	downloader.AddObserver(&ui);
	_beginthreadex(NULL,0,DownLoadPro,&downloader,NULL,NULL);


	//HidenWin wnd;
	//_beginthreadex(NULL,0,MyProc,wnd.m_hWnd,NULL,NULL);
	//::PostMessage(wnd.m_hWnd,10086,0,0);


	MSG msg;
	while (::GetMessage(&msg,NULL,0,0))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	//WNDCLASS wndClass;
	//wndClass.style          = CS_HREDRAW | CS_VREDRAW;
	//wndClass.lpfnWndProc    = WndProc;
	//wndClass.cbClsExtra     = 0;
	//wndClass.cbWndExtra     = 0;
	////wndClass.hInstance      = hInstance;
	////wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
	////wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
	//wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//wndClass.lpszMenuName   = NULL;
	//wndClass.lpszClassName  = TEXT("RedirectHidenWindow");

	//RegisterClass(&wndClass);
	//HWND m_hWnd = CreateWindow(
	//	TEXT("RedirectHidenWindow"), // window class name
	//	NULL,          // window caption
	//	WS_OVERLAPPED, // window style
	//	CW_USEDEFAULT, // initial x position
	//	CW_USEDEFAULT, // initial y position
	//	CW_USEDEFAULT, // initial x size
	//	CW_USEDEFAULT, // initial y size
	//	NULL,          // parent window handle
	//	NULL,          // window menu handle
	//	NULL,          //hInstance, // program instance handle
	//	NULL);         // creation parameters

	//::SendMessage(m_hWnd,10086,0,0);
	getchar();

	//std::tr1::regex pattern;
	//std::tr1::cmatch res;
	//pattern = "^abcd$";
	//
	//char *pReadBuf = NULL;
	//
	//FILE *f = fopen("E:\\text.txt","r");
	//if (f)
	//{
	//	fseek(f,0,SEEK_END); //定位到文件末 
	//	int nFileLen = ftell(f); //文件长度
	//	if (nFileLen>0)
	//	{
	//		pReadBuf = new char[nFileLen+1];
	//		memset(pReadBuf,0,nFileLen+1);
	//		fseek(f,0,SEEK_SET);
	//		fread(pReadBuf,sizeof(char),nFileLen,f);
	//		fclose(f);
	//	}
	//}
	//if (pReadBuf)
	//{
	//	bool bSuc = regex_search(pReadBuf,res,pattern);

	//	int nLen = res.length();
	//	int nSize = res.size();

	//	
	//	pattern = "[a]";
	//	string replacement = "HE";
	//	string text(pReadBuf);
	//	string str = regex_replace(text,pattern,replacement);
	//	int i = 2;
	//	delete pReadBuf;
	//}
	return 1;
}


