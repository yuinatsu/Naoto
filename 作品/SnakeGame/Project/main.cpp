//---------------------------------
// ゲーム制作：Project4
// 氏名　　　：2016010 梶原尚人
//---------------------------------

#include <DxLib.h>
#include "main.h"
#include "SceneCtl.h"
#include "_debug/_DebugDispOut.h"
#include "_debug/_DebugConOut.h"


// WinMain関数
//-----------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SceneCtl sceneCtl;
	sceneCtl.Run();

	return 0;
}