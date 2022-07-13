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
	SetWindowText("2016010_�������l");
	SetGraphMode(1024, 768, 32);// (X���W, Y���W, �𑜓x)
	ChangeWindowMode(true);// (true : Window, false : �t���X�N���[��)
	if (DxLib_Init() == -1)
	{
		return false;// �ُ�I��
	}
	return true;// ����I��
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	if (!SysInit())
	{
		return -1;// �ُ�I��
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

	// �ÓI�ɖ���	:	{} ... ���������X�g
	//Square shape1{ 100, 100, 100, 100 };
	//Shape shape2{ 200, 200, 100, 50 };
	//Square shape3{ 300, 300, 100, 50 };
	// ���I�ɖ���

	//C++14�ȍ~�ł���΁Amake_unique�֐����g����
	//std::unique_ptr<Shape> shape1 = std::make_unique<Square>(Vector2Flt{ 100, 100 }, Vector2Flt{ 100, 100 });
	//std::unique_ptr<Shape> shape2 = std::make_unique<Circle>(Vector2Flt{ 300, 300 }, Vector2Flt{ 50, 50 });
	//std::unique_ptr<Shape> shape3 = std::make_unique<Circle>(Vector2Flt{ 100, 300 }, Vector2Flt{ 10, 10 });
	//�R���X�g���N�^�̈����Ƃ��āA���I�m�ۂ����������̃A�h���X���w��
	//std::unique_ptr<Shape> shape1(new Square(Vector2Flt{ 100, 100 }, Vector2Flt{ 100, 100 }));
	// reset�֐����g���Čォ����
	//std::unique_ptr<Shape> shape1;
	//shape1.reset(new Square(Vector2Flt{ 100, 100 }, Vector2Flt{ 100, 100 }));

	/*shape1.get()->Draw();
	shape2.get()->Draw();*/

	//Shape* shape1 = new Square(Vector2Flt{ 100, 100 }, Vector2Flt{ 100, 100 });
	//Shape* shape2 = new Shape(200, 200, 100, 100);
	//Square* shape3 = new Square(300, 300, 100, 100);

	std::chrono::system_clock::time_point nowTime, oldTime;
	nowTime = std::chrono::system_clock::now();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)// window�����, ESC�L�[�̓���
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

		// �ÓI�ɖ���
		//shape1.Draw();// Square��Draw()�ŕ`��
		//shape1.Draw(2.0f);// Square��Draw()�ŕ`��
		//shape1.Draw(2.0f, { 100,100 });// Square��Draw()�ŕ`��
		//shape2.Draw();// Shape��Draw()�ŕ`��
		//shape3.Shape::Draw();// Shape��Draw()�ŕ`��			// ���O��Ԃ𖾎��I�ɋL�q����A�N���X�̊K�w���オ��͉̂\
		// ���I�ɖ���
		//shape1->Draw(2.0f, { 50,50 });
		//shape1->Draw();
		//shape2->Draw();
		for (auto& shape : shapeVec)
		{
			shape->Draw();
		}
		// �ʉ�
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
	return 0;// ����I��
}
