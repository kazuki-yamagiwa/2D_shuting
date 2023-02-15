//--------------------------------------------------------------//
//	"scene_game.h	"											//
//		�V�[�� : �Q�[��											//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#pragma once

#include "../object/object.h"

#define PLAYER_TAMA_NUM		10
#define MISSILE_NUM	4
#define ENEMY_TAMA_NUM	10
#define ENEMY_TAMA_NUM2	10
#define ENEMY1_NUM	3
#define SCORE_KETA			8

struct Vector2 {
	int x, y;
};
struct Enemy
{
	
};
class vnSceneGame
{
private:
	vnSprite	* pEnemy1[ENEMY1_NUM];
	vnSprite	* pPlayer;
	vnSprite	* pBG;
	vnSprite	* pPlayer_Tama[PLAYER_TAMA_NUM];
	vnSprite	* pPlayer_missile[MISSILE_NUM];
	vnSprite	* pPlayer_Bomb;
	Vector2		target[ENEMY1_NUM];

	Vector2		MissileShooting[MISSILE_NUM];
	vnSprite	* pEnemy_Tama[ENEMY_TAMA_NUM];
	vnSprite	* pEnemy_Tama2[ENEMY_TAMA_NUM2];
	vnSprite	* pBoss;
	vnSprite	* pScore[SCORE_KETA];
	vnSprite	* pHp;
	vnSprite	* pHpber;

	//�~�T�C���ԍ�
	int M_number[MISSILE_NUM];
	//M �������ꂽ���̎���
	int	t;
	//pEnemy1 �ԍ�
	int E1_number[ENEMY1_NUM];
	//pEnemy1���������ꂽ���̎���
	int	tE;
	


public:

	void SetScore(vnSprite* ptr, int);

	void GameInit(void);

	//������
	bool initialize();

	//�I��
	void terminate();

	//����
	void execute();

	//�`��
	void render();

	
};
