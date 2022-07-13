#include <algorithm>
#include <memory>
#include <vector>
#include <chrono>
#include <dxlib.h>
#include "Graph/Square.h"
#include "Graph/Circle.h"
#include "Graph/Triangle.h"
#include "Graph/Star.h"
#include "Graph/Tree.h"
#include "Graph/Micky.h"
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"


bool SysInit(void)
{
	SetWindowText("2016010_梶原尚人");
	SetGraphMode(1024, 768, 32);// (X座標, Y座標, 解像度)
	ChangeWindowMode(true);// (true : Window, false : フルスクリーン)
	if (DxLib_Init() == -1)
	{
		return false;// 異常終了
	}
	return true;// 正常終了
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	if (!SysInit())
	{
		return -1;// 異常終了
	}

	srand((unsigned int)time(NULL));
	//_dbgSetup(1024, 768, 255);

	ShapeVec shapeVec;
	shapeVec.reserve(10);
	//shape[0].reset(new Square(Vector2Flt{ 100, 100 }, Vector2Flt{ 100, 100 }));
	shapeVec.emplace_back(std::make_unique<Square>(Vector2Flt{ 100, 100 }, Vector2Flt{ 200, 200 }));
	shapeVec.emplace_back(std::make_unique<Circle>(Vector2Flt{ 300, 100 }, Vector2Flt{ 50, 50 }));
	shapeVec.emplace_back(std::make_unique<Triangle>(Vector2Flt{ 100, 350 }, Vector2Flt{ 50, 50 }));
	shapeVec.emplace_back(std::make_unique<Star>(Vector2Flt{ 400, 200 }, Vector2Flt{ 50, 50 }));
	shapeVec.emplace_back(std::make_unique<Tree>(Vector2Flt{ 300, 300 }, Vector2Flt{ 50, 50 }));
	shapeVec.emplace_back(std::make_unique<Micky>(Vector2Flt{ 200, 200 }, Vector2Flt{ 30, 30 }));
	

	//std::unique_ptr<Shape> shape1;
	//shape.emplace_back(std::move(shape1));

	/*std::vector<int> intVec = { 0, 1, 2, 3, 4 };
	TRACE("%d, %d, %d, %d, %d", intVec[0], intVec[1], intVec[2], intVec[3], intVec[4]);
	for (auto num : intVec)
	{
		TRACE("%d", num);
	}

	auto itr = std::remove_if(intVec.begin(), intVec.end(), [&](int num) {return num % 2 == 0; });
	intVec.erase(itr, intVec.end());

	for (auto itr = intVec.begin(); itr != intVec.end(); itr++)
	{
		itr = intVec.erase(itr);
	}*/

	/*auto itr = std::remove_if(shapeVec.begin(), shapeVec.end(), [&](std::unique_ptr<Shape>& shape_) {
		return !(shape_->isAlive());
		});
	shapeVec.erase(itr, shapeVec.end());*/

	// 静的に明言	:	{} ... 初期化リスト
	//Square shape1{ 100, 100, 100, 100 };
	//Shape shape2{ 200, 200, 100, 50 };
	//Square shape3{ 300, 300, 100, 50 };
	// 動的に明言

	//C++14以降であれば、make_unique関数を使える
	//std::unique_ptr<Shape> shape1 = std::make_unique<Square>(Vector2Flt{ 100, 100 }, Vector2Flt{ 100, 100 });
	//std::unique_ptr<Shape> shape2 = std::make_unique<Circle>(Vector2Flt{ 300, 300 }, Vector2Flt{ 50, 50 });
	//std::unique_ptr<Shape> shape3 = std::make_unique<Circle>(Vector2Flt{ 100, 300 }, Vector2Flt{ 10, 10 });
	//コンストラクタの引数として、動的確保したメモリのアドレスを指定
	//std::unique_ptr<Shape> shape1(new Square(Vector2Flt{ 100, 100 }, Vector2Flt{ 100, 100 }));
	// reset関数を使って後から代入
	//std::unique_ptr<Shape> shape1;
	//shape1.reset(new Square(Vector2Flt{ 100, 100 }, Vector2Flt{ 100, 100 }));

	/*shape1.get()->Draw();
	shape2.get()->Draw();*/

	//Shape* shape1 = new Square(Vector2Flt{ 100, 100 }, Vector2Flt{ 100, 100 });
	//Shape* shape2 = new Shape(200, 200, 100, 100);
	//Square* shape3 = new Square(300, 300, 100, 100);

	std::chrono::system_clock::time_point nowTime, oldTime;
	nowTime = std::chrono::system_clock::now();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)// windowを閉じる, ESCキーの入力
	{
		_dbgStartDraw();
		oldTime = nowTime;
		nowTime = std::chrono::system_clock::now();
		auto elTime = nowTime - oldTime;

		auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(elTime).count();
		auto delta = msec / 1000.0f;

		for (auto& shape : shapeVec)
		{
			shape->Update(delta, shapeVec);
		}

		ClsDrawScreen();

		// 静的に明言
		//shape1.Draw();// SquareのDraw()で描画
		//shape1.Draw(2.0f);// SquareのDraw()で描画
		//shape1.Draw(2.0f, { 100,100 });// SquareのDraw()で描画
		//shape2.Draw();// ShapeのDraw()で描画
		//shape3.Shape::Draw();// ShapeのDraw()で描画			// 名前空間を明示的に記述する、クラスの階層を上がるのは可能
		// 動的に明言
		//shape1->Draw(2.0f, { 50,50 });
		//shape1->Draw();
		//shape2->Draw();
		for (auto& shape : shapeVec)
		{
			shape->Draw();
		}
		// 別解
		/*for (int n = 0; n < shapeVec.size(); n++)
		{
			shapeVec[num]->Draw();
		}*/

		//(*shape1).Draw();
		//shape2->Draw();
		//shape3->Shape::Draw();
		//_dbgDraw();
		ScreenFlip();
	}
	return 0;// 正常終了
}
