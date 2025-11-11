#pragma once
#include "gameObject/IGameObject.h"
#include <vector>

class Game;

class Totalscore : public IGameObject
{
public:
    Totalscore();
    ~Totalscore();

    bool Start() override;
    void Update() override;
    void Render(nsK2EngineLow::RenderContext& rc) override;

    void AddScore(int points);          // スコア加算
    void RegisterGameScore();           // ゲームごとにスコア登録
    int m_score = 0;                    // 現在のスコア
    int m_gamescore = 0;                // 今回ゲームのスコア
    int m_totalScore = 0;               // 全体の合計スコア
    int GetTotalScore() const
    {
        return m_totalScore;
    }
private:
    int m_gameScores[10] = {};          // 各ゲームのスコア配列
    bool m_isVisible = true;            // 表示状態フラグ
private:
	Game* m_game = nullptr;             // ゲームオブジェクトへのポインタ
	FontRender m_fontRender;            //スコア表示用
    FontRender m_mainScoreFont;         // 合計スコア表示用
    std::vector<std::unique_ptr<FontRender>> m_scoreFonts;

};
