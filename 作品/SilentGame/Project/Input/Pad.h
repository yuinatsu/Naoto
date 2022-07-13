#pragma once
#include <DxLib.h>
#include "Controller.h"

constexpr int motionRange = 30000;                                  // スティックの反応可動域

class Pad :
    public Controller
{
public:
    Pad();
    ~Pad();
    bool Init(void) override;										// 初期化
    void Update(double delta) override;								// 更新 Update(deltaTime)
    void StickUpdate(void);											// スティックの更新
    CntType GetCntType(void) override { return CntType::Pad; };		// コントローラータイプの取得
private:
    XINPUT_STATE input_;											// コントローラーの情報
    int padCnt_;												    // 今現在のpadの数
    int padID_;														// 自分のpadID
};

