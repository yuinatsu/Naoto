#include<DxLib.h>
#include "GameScene.h"
#include "ResultScene.h"
#include "PauseScene.h"
#include "../common/ImageMng.h"
#include "../common/GmkEvent.h"
#include "../Object/ObjManager.h"
#include "../common/Debug.h"
#include "../Component/Collider/CircleCollider.h"
#include "../Object/UI/ItemUi.h"
#include "../Object/DefeatItem/LaundMine.h"
#include "Transition/CircleScene.h"
GameScene::GameScene()
{
	Init();
	CreateMaskScreen();
	DrawOwnScreen(0.0);
}

GameScene::~GameScene()
{
}

bool GameScene::Init(void)
{
	tmxObj_ = std::make_shared<TmxObj>();
	map_ = "tileset x1.png";

	// �}�b�v�̓ǂݍ���
	tmxObj_->LoadTMX("./Resource/tmx/map" + std::to_string(mapNum_) + ".tmx");

	// �J�����̏�����
	Cammng_.Init(map_, tmxObj_);

	// �\���T�C�Y���擾
	ViewSize_ = Cammng_.GetViewSize();

	// �X�N���[�����쐬
	viewID_ = MakeScreen(ViewSize_.x, ViewSize_.y, 255);

	gEvent_ = std::make_shared<GmkEvent>();
	auto itemUI = uiList_.emplace_back(std::make_shared<ItemUi>(Vector2{ 256,256 }, screenSize_));
	objMng_ = std::make_unique<ObjManager>(*itemUI,gEvent_, tmxObj_);
	//laundMineList_.emplace_back(std::make_unique<LaundMine>());

	

	elTime_ = 0.0f;

	isFirst_ = true;
	SceneFlag_ = false;
	return true;
}

uniqueScene GameScene::Update(float delta, uniqueScene ownScene)
{
	if (controller_->Released(InputID::btn1))
	{
		controller_->Update(delta);
		return std::make_unique<PauseScene>(std::move(ownScene));
	}

	defeats_ = objMng_->GetDefeats();

	for (const auto& ui : uiList_)
	{
		// UI�X�V
		ui->Update(delta);
		// ����̂ݏ����A�C�e���Z�b�g
		if (isFirst_ && objMng_->GetItemID().size() > 0)
		{
			for (auto& id : objMng_->GetItemID())
			{
				ui->SetItemID(id);
			}
			isFirst_ = false;
		}
		// �펞UI�ɃA�C�e���A�C�R���Z�b�g
		if (ui->GetItemID().size() > 0)
		{
			ui->ItemUpdate(delta);
		}
		if (CheckHitKey(KEY_INPUT_Q))
		{
			ui->SetItemID(std::make_pair(10,"Decoy"));
		}
		// �g�p���ꂽ�A�C�e���̏����Z�b�g
		objMng_->SetUseItem(ui->GetUseItem());
	}

	Cammng_.Update(objMng_->GetPlayer().GetPos());

	controller_->Update(delta);
	DrawOwnScreen(delta);

	elTime_ += delta;
	
	if (!objMng_->Update(delta))
	{
		//controller_->Update(delta);
		//return std::make_unique<CircleScene>(
		//	2.0,
		//	std::move(ownScene),
		//	std::make_unique<ResultScene>(defeats_, elTime_)
		//	);
		return std::make_unique<ResultScene>(defeats_, elTime_);
	}

	gEvent_->Update(delta);
	return ownScene;
}

void GameScene::DrawOwnScreen(float delta)
{
	// �`��p�I�t�Z�b�g���擾
	const auto drawOffset = Cammng_.GetOffset();

	// �������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(viewID_);
	ClsDrawScreen();

	SetFontSize(20);

	// �}�b�v�̕\��
	const auto& WorldArea = tmxObj_->GetWorldArea();
	const auto& TileSize = tmxObj_->GetTileSize();
	gEvent_->Draw();
	for (const auto& layer : tmxObj_->GetMapData())
	{
		for (int y = 0; y < WorldArea.y; y++)
		{
			for (int x = 0; x < WorldArea.x; x++)
			{
				auto image = y * WorldArea.x + x;
				if (image < layer.second.size())
				{
					// �O���t�B�b�Nid�̎擾
					int gid = layer.second[static_cast<__int64>(y) * WorldArea.x + x] - tmxObj_->GetFirstGID();
					if (gid >= 0)
					{
						// x,y�̂Ƃ�������W�ɖ߂�
						DrawGraph(static_cast<int>(x * TileSize.x + drawOffset.x), static_cast<int>(y * TileSize.y + drawOffset.y), lpImageMng.GetID(map_)[gid], true);
					}
				}
			}
		}
	}
	objMng_->Draw(drawOffset);
	auto mains = objMng_->GetMines();
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(50, 60, viewID_, true);
	for (const auto& ui : uiList_)
	{
		ui->UIDraw(delta);
	}
	//DrawFormatString(10, 10, 0xffffff, "GameScene");
	//DrawFormatString(10, 25, 0xffffff, "pos_.x = %f", objMng_->GetPlayer().GetPos().x);
	//DrawFormatString(10, 40, 0xffffff, "pos_.y = %f", objMng_->GetPlayer().GetPos().y);
	//DrawFormatString(10, 60, 0xffffff, "cam=%f:%f", Cammng_.GetOffset().x, Cammng_.GetOffset().y);

	//for (auto& laund : laundMineList_)
	//{
	//	laund->Draw(Vector2{ 10,10 });
	//}
}
