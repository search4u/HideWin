#pragma once
#include "msgmgr.h"
#include <string>
using namespace std;
class Downloader : public MsgPump
{
public:
	Downloader()
	{
	}
	void DoDownload()
	{
		Sleep(200);
		MsgData data;
		data.nMsgID = 1001;
		data.wParam = 1;
		data.lParam = 2;
		Post(&data);
	}
};


class MyUi : public MsgReceiver
{
public:
	MyUi()
	{
	}
	void OnMsg(MsgData *msgData)
	{
		if (msgData->nMsgID = 1001)
		{
			if (msgData->wParam ==1)
			{
				string aa;
			}
			if (msgData->lParam == 2)
			{
				string bb;
			}
		}
	}	
};