//--------------------------------------------------------------//
//	"scene_game.cpp"											//
//		シーン : ゲーム											//
//													2021/06/01	//
//														Ichii	//
//--------------------------------------------------------------//
#include "../../framework.h"
#include "../../framework/vn_environment.h"
#include<stdlib.h>

//プロトタイプ宣言
bool	HitCheck(float, float, float, float, float, float);
float	CalcLength(float, float, float, float);
int	GetRandom(int, int);
float	AngToRad(float);
int TargetC(int, int);

#define	PI	3.14159265359

#define TAMA_SPD		20
#define TAMA_KANKAKU	10
#define	MISSILE_V0	2
#define MISSILE_KANKAKU	1
#define	BOMB_MOVE_LEG

int Pl_Tama_Kankaku;
int Missile_Kankaku;


enum {
	PLAY_START,
	PLAY_MAIN,
	PLAY_RESTART,
};

int	Play_seq = PLAY_START;
int	Player_start_add = 6;
int	player_start_cnt = 0;

int	Player_Hp_Max = 100;
int Player_Hp = Player_Hp_Max;

//時間
int Time;
int Target_count;




//敵関連
#define ENEMY_KANKAKU	300
#define ENEMY_KANKAKU2	300
#define ENEMY_ADD_DMG	10

int		Em_Kankaku;
int		Em_Kankaku2;
float	Em_Vec[ENEMY_TAMA_NUM];
float	Em_Vec2[ENEMY_TAMA_NUM2];
float	Mm_Vec[MISSILE_NUM];
float	Tg_Vec[MISSILE_NUM];
float	Target_Rad[ENEMY1_NUM];
float	r[ENEMY1_NUM];

// UI 関連
#define	SCORE_X_POS		40.0f
#define	SCORE_Y_POS		50.0f
#define SCORE_SIZE		50.0f
#define SCORE_X_ADD		55.0f

#define SCORE_ADD		100

int		game_score = 0;

#define HPBER_VSIZE		50.0f

#define HPWAKU_HSIZE	400.0f
#define	HPBER_HSIZE		376.0f

#define	HPBER_X_POS		1050.0f
#define HPBER_Y_POS		SCORE_Y_POS


//初期化(
bool vnSceneGame::initialize()
{
	//スプライトの作成
	for (int i = 0; i <ENEMY1_NUM; i++)
	{
		pEnemy1[i] = new vnSprite(0.0f, 0.0f, 128.0f, 128.0f, L"data/image/sample_texture.png", 0.5f, 1.0f, 0.5f, 1.0f);
		pEnemy1[i]->setExecuteEnable(false);
		pEnemy1[i]->setRenderEnable(false);
	}

	pBG = new vnSprite((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, CLIENT_WIDTH, CLIENT_HEIGHT, L"data/image/BG.jpg");
	pPlayer = new vnSprite((float)500, (float)500, 128.0f, 64.0f, L"data/image/Player.png", 0.0f, 0.72f, 0.0f, 1.0f);

	for (int i = 0; i < PLAYER_TAMA_NUM; i++)
	{
		pPlayer_Tama[i] = new vnSprite(0.0f, 0.0f, 64.0f, 16.0f, L"data/image/Player.png", 0.72f, 1.0f, 0.8f, 0.9f);
		pPlayer_Tama[i]->setExecuteEnable(false);
		pPlayer_Tama[i]->setRenderEnable(false);
	}
	Pl_Tama_Kankaku = 0;
//MISSILE
	for (int i = 0; i < MISSILE_NUM; i++)
	{
		pPlayer_missile[i] = new vnSprite(0.0f, 0.0f, 64.0f, 16.0f, L"data/image/Player.png", 0.72f, 1.0f, 0.8f, 0.9f);
		pPlayer_missile[i]->setExecuteEnable(false);
		pPlayer_missile[i]->setRenderEnable(false);
	}
	Missile_Kankaku = 0;



	for (int i = 0; i < ENEMY_TAMA_NUM; i++)
	{
		pEnemy_Tama[i] = new vnSprite(50.0f, 50.0f, 32.0f, 32.0f, L"data/image/number_icon.png", 0.0f, 0.25f, 0.0f, 0.25f );
		pEnemy_Tama[i]->setExecuteEnable(false);
		pEnemy_Tama[i]->setRenderEnable(false);
	}
	Em_Kankaku = 0;

	for (int i = 0; i < ENEMY_TAMA_NUM2; i++)
	{
		pEnemy_Tama2[i] = new vnSprite(50.0f, 50.0f, 32.0f, 32.0f, L"data/image/number_icon.png", 0.0f, 0.25f, 0.75f, 1.00f);
		pEnemy_Tama2[i]->setExecuteEnable(false);
		pEnemy_Tama2[i]->setRenderEnable(false);
	}
	Em_Kankaku2 = 0;

	for (int i = 0; i < SCORE_KETA; i++)
	{
		pScore[i] = new vnSprite(SCORE_X_POS + i * SCORE_X_ADD, SCORE_Y_POS+ 15, SCORE_SIZE, SCORE_SIZE, L"data/image/number_icon.png", 0.0f, 0.25f, 0.0f, 0.25f);
	}

	pHp = new vnSprite(HPBER_X_POS, HPBER_Y_POS, HPWAKU_HSIZE, HPBER_VSIZE, L"data/image/HPgauge_frame.png");
	pHpber = new vnSprite(HPBER_X_POS, HPBER_Y_POS, HPWAKU_HSIZE, HPBER_VSIZE, L"data/image/HPgauge.png");


	return true;
}

//終了
void vnSceneGame::terminate()
{
	//スプライトの削除
	for (int i = 0; i < ENEMY1_NUM; i++) delete pEnemy1 [i];
	delete pPlayer;
	delete pBG;
	for (int i = 0; i < PLAYER_TAMA_NUM; i++) delete pPlayer_Tama[i];
	for (int i = 0; i <MISSILE_NUM; i++) delete pPlayer_missile[i];
	for (int i = 0; i < ENEMY_TAMA_NUM; i++) delete pEnemy_Tama[i];
	for (int i = 0; i < ENEMY_TAMA_NUM2; i++) delete pEnemy_Tama2[i];
	for (int i = 0; i < SCORE_KETA; i++)delete pScore[i];
	delete pHp;
	delete pHpber;

}

//処理関数
void vnSceneGame::execute()
{
	/*pSprite->rot = kaiten;
	pSprite->scaleX = kaiten / 10;
	pSprite->scaleY = (20 - kaiten) / 10;

	pSprite2->posX += addX;
	if (pSprite2->posX < 0) {
		pSprite2->posX = 0;
		addX *= -1.0f;
	}
	if (pSprite2->posX > CLIENT_WIDTH) {
		pSprite2->posX = CLIENT_WIDTH;
		addX *= -1.0f;
	}

	pSprite2->posY += addY;
	if (pSprite2->posY < 0) {
		pSprite2->posY = 0;
		addY *= -1.0f;
	}
	if (pSprite2->posY > CLIENT_HEIGHT) {
		pSprite2->posY = CLIENT_HEIGHT;
		addY *= -1.0f;
	}



	pSprite4->posX += addX;
	if (pSprite4->posX < 0) {
		pSprite4->posX = 0;
		addX *= 1.0f;
	}
	if (pSprite4->posX > CLIENT_WIDTH) {
		pSprite4->posX = CLIENT_WIDTH;
		addX *= 1.0f;
	}

	pSprite4->posY += addY;
	if (pSprite4->posY < 0) {
		pSprite4->posY = 0;
		addY *= 1.0f;
	}
	if (pSprite4->posY > CLIENT_HEIGHT) {
		pSprite4->posY = CLIENT_HEIGHT;
		addY *= 1.0f;
	}



	pSprite3->posX = 200.0f + sinf(kaiten) * 200;
	pSprite3->posY = 200.0f + cosf(kaiten) * 200;
	kaiten += kaiten_add;
	if (kaiten > 20) kaiten_add *= -1;
	if (kaiten < 0) kaiten_add *= -1;*/


  switch (Play_seq)
  {
	case PLAY_START:
		pPlayer->posX += Player_start_add;
		if (Player_start_add == 0) player_start_cnt++;
		if (pPlayer->posX > 1000 && Player_start_add > 0)Player_start_add = 0;
		if (Player_start_add == 0 && player_start_cnt > 30)
			Player_start_add = -3;
		if (pPlayer->posX < 200 && Player_start_add < 0)Play_seq = PLAY_MAIN;
		if (vnKeyboard::on(DIK_Z))
		{
			pPlayer->posX = 200;
			Play_seq = PLAY_MAIN;
		}

		break;
	
	case PLAY_MAIN:
	if (vnKeyboard::on(DIK_A) || vnKeyboard::on(DIK_LEFT))
	{//左移動
		pPlayer->posX -= 5;
		if (pPlayer->posX < (pPlayer->sizeX / 2)) pPlayer->posX = pPlayer->sizeX / 2;
	}
	if (vnKeyboard::on(DIK_D) || vnKeyboard::on(DIK_RIGHT))
	{//右移動
		pPlayer->posX += 5;
		if (pPlayer->posX > (CLIENT_WIDTH - pPlayer->sizeX / 2)) pPlayer->posX = CLIENT_WIDTH - pPlayer->sizeX / 2;
	}
	if (vnKeyboard::on(DIK_W) || vnKeyboard::on(DIK_UP))
	{//上移動
		pPlayer->posY -= 5;
		if (pPlayer->posY < (pPlayer->sizeY / 2)) pPlayer->posY = pPlayer->sizeY / 2;
	}
	if (vnKeyboard::on(DIK_S) || vnKeyboard::on(DIK_DOWN))
	{//下移動
		pPlayer->posY += 5;
		if (pPlayer->posY > (CLIENT_HEIGHT - pPlayer->sizeY / 2)) pPlayer->posY = CLIENT_HEIGHT - pPlayer->sizeY / 2;
	}

	if (vnKeyboard::on(DIK_SPACE))
	{//スペースキー	弾の生成
		
		if (Pl_Tama_Kankaku <= 0)
		{
			for (int i = 0; i < PLAYER_TAMA_NUM; i++)
			{
				if (!pPlayer_Tama[i]->isExecuteEnable())
				{
					pPlayer_Tama[i]->setExecuteEnable(true);
					pPlayer_Tama[i]->setRenderEnable(true);
					pPlayer_Tama[i]->posX = pPlayer->posX;
					pPlayer_Tama[i]->posY = pPlayer->posY;
					Pl_Tama_Kankaku = TAMA_KANKAKU;
					break;
				}
			}
		}
		else
		{
			Pl_Tama_Kankaku--;
		}
	}
	int a;
	if (vnKeyboard::trg(DIK_M))
	{//M キー	弾の生成
		
		t = Time;
		Target_count = 0;
		if (Missile_Kankaku <= 0)
		{
			
			for (int i = 0; i < ENEMY1_NUM; i++)
			{
				r[i] = atan2((pEnemy1[i]->posY - pPlayer->posY), (pEnemy1[i]->posX - pPlayer->posX));
				Target_Rad[i] = fabsf(r[i]);
				if (Target_Rad[i] >= 0 && Target_Rad[i] <= 0.26) //|| (Target_Rad[i] >= 5.75 && Target_Rad[i] <= 6.283))
				{

					target[Target_count].x = pEnemy1[i]->posX;
					target[Target_count].y = pEnemy1[i]->posY;
					//Tg_Vec[i] = Mm_Vec[i];//atan2((target[i].y - pPlayer_missile[i]->posY), (target[i].x - pPlayer_missile[i]->posX));
					Target_count += 1;
				}
				/*if (Target_count == ENEMY1_NUM)
					target[Target_count].x = pEnemy1[Target_count]->posX;
					target[Target_count].y = pEnemy1[Target_count]->posY;*/
			}
			if (Target_count > 0)
			{
				a = 0;
				for (int i = 0; i < MISSILE_NUM; i++)
				{

					if (!pPlayer_missile[i]->isExecuteEnable())
					{
						pPlayer_missile[i]->setExecuteEnable(true);
						pPlayer_missile[i]->setRenderEnable(true);
						pPlayer_missile[i]->posX = pPlayer->posX;
						pPlayer_missile[i]->posY = pPlayer->posY;
						MissileShooting[i].x = pPlayer->posX;
						MissileShooting[i].y = pPlayer->posY;
						Missile_Kankaku = MISSILE_KANKAKU;
						M_number[i] = a;
						a += 1;
					}
					if (a >= 4)
						break;
				}
			}
			else
			{
				Missile_Kankaku--;
			}
		}
		else
		{
			Missile_Kankaku--;
		}
	}


	//pEnemy1 の生成

	int b;
	b = 0;
	//Target_count = 0;
	for (int i = 0; i < ENEMY1_NUM; i++)
	{
		if (!pEnemy1[i]->isExecuteEnable())
		{
			tE = Time;
			pEnemy1[i]->posX = 2000;
			pEnemy1[i]->posY = 2000;
			pEnemy1[i]->setExecuteEnable(true);
			pEnemy1[i]->setRenderEnable(true);
			E1_number[i] = b;
			b += 1;
		}
		if (b >= 3)
			break;
		//r[i] = atan2((pEnemy1[i]->posY - pPlayer->posY), (pEnemy1[i]->posX - pPlayer->posX));
		//Target_Rad[i] = fabsf(r[i]);
		//if (Target_Rad[i] >= 0 && Target_Rad[i] <= 0.52) //|| (Target_Rad[i] >= 5.75 && Target_Rad[i] <= 6.283))
		//{
		//	Target_count += 1;
		//	target[i].x = pEnemy1[i]->posX;
		//	target[i].y = pEnemy1[i]->posY;
		//	//Tg_Vec[i] = Mm_Vec[i];//atan2((target[i].y - pPlayer_missile[i]->posY), (target[i].x - pPlayer_missile[i]->posX));
		//}
		
	}

//プレイヤーの弾（真っ直ぐ）の動き
	for (int i = 0; i < PLAYER_TAMA_NUM; i++)
	{
		if (pPlayer_Tama[i]->isExecuteEnable())
		{
			pPlayer_Tama[i]->posX += TAMA_SPD;

			if (pPlayer_Tama[i]->posX > CLIENT_WIDTH)
			{
				pPlayer_Tama[i]->setExecuteEnable(false);
				pPlayer_Tama[i]->setRenderEnable(false);
			}
		}
	}

//Mの動き
	for (int j = 0;j < MISSILE_NUM; j++)
	{
			if (pPlayer_missile[j]->isExecuteEnable())
			{
				if (Time < t + 60)
				{
					
					if (M_number[j] == 0)
					{
						
						pPlayer_missile[j]->posY += MISSILE_V0;
					}
					if (M_number[j] == 1)
					{
						pPlayer_missile[j]->posY += MISSILE_V0 + 0.6;
					}
					if (M_number[j] == 2)
					{
						pPlayer_missile[j]->posY -= MISSILE_V0;
					}
					if (M_number[j] == 3)
					{
						pPlayer_missile[j]->posY -= MISSILE_V0 + 0.6;
					}
				}
				if (Time > t + 60)
				{						
					Mm_Vec[j] = atan2((target[j % Target_count].y - pPlayer_missile[j]->posY), (target[j % Target_count].x - pPlayer_missile[j]->posX));
					pPlayer_missile[j]->posX += cosf(Mm_Vec[j]) * 50.0f;
					pPlayer_missile[j]->posY += sinf(Mm_Vec[j]) * 50.0f;
				}
				if (pPlayer_missile[j]->posX < 0 || pPlayer_missile[j]->posX > CLIENT_WIDTH || pPlayer_missile[j]->posY > CLIENT_HEIGHT || pPlayer_missile[j]->posY < 0)
				{
					pPlayer_missile[j]->setExecuteEnable(false);
					pPlayer_missile[j]->setRenderEnable(false);
				}
			}
			
	}
	//pEnemy1 の動き
	for (int i = 0; i < ENEMY1_NUM; i++)
	{
		if (pEnemy1[i]->isExecuteEnable())
		{
			if (E1_number[i] == 0)
			{
				if (Time == tE )
				{
					pEnemy1[i]->posX = 1200;
					pEnemy1[i]->posY = -30;
				}
				if ( tE < Time && Time < tE + 60)
				{
					pEnemy1[i]->posX = 1200;
					pEnemy1[i]->posY += 2;
				}
				if (Time > tE + 60)
				{
					pEnemy1[i]->posX = 1200;
					pEnemy1[i]->posY += 0;
				}
			}
			if (E1_number[i] == 1)
			{
				if (Time == tE)
				{
					pEnemy1[i]->posX = 1200;
					pEnemy1[i]->posY = CLIENT_HEIGHT + 30;
				}
				if (tE < Time && Time < tE + 60)
				{
					pEnemy1[i]->posX = 1200;
					pEnemy1[i]->posY -= 2;
				}
				if (Time > tE + 60)
				{
					pEnemy1[i]->posX = 1200;
					pEnemy1[i]->posY += 0;
				}
			}
			if (E1_number[i] == 2)
			{
				if (Time == tE)
				{
					pEnemy1[i]->posX = CLIENT_WIDTH + 30;
					pEnemy1[i]->posY = CLIENT_HEIGHT / 2;
				}
				if (tE < Time && Time < tE + 60)
				{
					pEnemy1[i]->posX -= 2;
					pEnemy1[i]->posY = CLIENT_HEIGHT / 2;
				}
				if (Time > tE + 60)
				{
					pEnemy1[i]->posX += 0;
					pEnemy1[i]->posY = CLIENT_HEIGHT / 2;
				}
			}
		}
	}

//pEnemy_Tamaのランダム生成
	for (int i = 0; i < ENEMY_TAMA_NUM; i++)
	{
		if (Em_Kankaku <= 0)
		{
			if (!pEnemy_Tama[i]->isExecuteEnable())
			{
				pEnemy_Tama[i]->setExecuteEnable(true);
				pEnemy_Tama[i]->setRenderEnable(true);
				pEnemy_Tama[i]->posX = 2100.0f;
				pEnemy_Tama[i]->posY = (float)(rand() % 500 + 100);
				Em_Vec[i] = atan2((pPlayer->posY - pEnemy_Tama[i]->posY), (pPlayer->posX - pEnemy_Tama[i]->posX));
				Em_Kankaku = ENEMY_KANKAKU;
			}
		}
		else
		{
			Em_Kankaku--;
		}
	}
	//pEnemy_Tama（プレイヤーの方向に打ち出される）の動き
	for (int i = 0; i < ENEMY_TAMA_NUM; i++)
	{
		if (pEnemy_Tama[i]->isExecuteEnable())
		{
			pEnemy_Tama[i]->posX += cosf(Em_Vec[i]) * 10.0f;
			pEnemy_Tama[i]->posY += sinf(Em_Vec[i]) * 10.0f;
			if (pEnemy_Tama[i]->posX < 0)
			{
				pEnemy_Tama[i]->setExecuteEnable(false);
				pEnemy_Tama[i]->setRenderEnable(false);
			}
		}
	}
	//pEnemy_Tama2のランダム生成
	for (int i = 0; i < ENEMY_TAMA_NUM2; i++)
	{
		if (Em_Kankaku2 <= 0)
		{
			if (!pEnemy_Tama2[i]->isExecuteEnable())
			{
				pEnemy_Tama2[i]->setExecuteEnable(true);
				pEnemy_Tama2[i]->setRenderEnable(true);
				pEnemy_Tama2[i]->posX = 2100.0f;
				pEnemy_Tama2[i]->posY = (float)(rand() % 500 + 100);
				Em_Vec2[i] = 3.14f;
				Em_Kankaku2 = ENEMY_KANKAKU2;
			}
		}
		else
		{
			Em_Kankaku2--;
		}
	}
	//pEnemy_Tama2（直進）の動き
	for (int i = 0; i < ENEMY_TAMA_NUM2; i++)
	{
		if (pEnemy_Tama2[i]->isExecuteEnable())
		{
			pEnemy_Tama2[i]->posX += cosf(Em_Vec2[i]) * 10.0f;
			pEnemy_Tama2[i]->posY += sinf(Em_Vec2[i]) * 10.0f;
			if (pEnemy_Tama2[i]->posX < 0)
			{
				pEnemy_Tama2[i]->setExecuteEnable(false);
				pEnemy_Tama2[i]->setRenderEnable(false);
			}
		}
	}

//弾が当たったpEnemy_Tamaを消す
	for (int i = 0; i < PLAYER_TAMA_NUM; i++)
	{
		if (pPlayer_Tama[i]->isExecuteEnable())
		{
			for (int j = 0; j < ENEMY_TAMA_NUM; j++)
			{
				if (pEnemy_Tama[j]->isExecuteEnable())
				{
					if (HitCheck(pPlayer_Tama[i]->posX,
								 pPlayer_Tama[i]->posY,
								 pEnemy_Tama[j]->posX,
								 pEnemy_Tama[j]->posY,
								 16.0f,
								 16.0f))
					{
						pPlayer_Tama[i]->setExecuteEnable(false);
						pPlayer_Tama[i]->setRenderEnable(false);
						pEnemy_Tama[j]->setExecuteEnable(false);
						pEnemy_Tama[j]->setRenderEnable(false);
						game_score += SCORE_ADD;
						// ボス戦へのフラグを入れる
					}
				}
			}

			for (int j = 0; j < ENEMY_TAMA_NUM2; j++)
			{
				if (pEnemy_Tama2[j]->isExecuteEnable())
				{
					if (HitCheck(pPlayer_Tama[i]->posX,
						pPlayer_Tama[i]->posY,
						pEnemy_Tama2[j]->posX,
						pEnemy_Tama2[j]->posY,
						16.0f,
						16.0f))
					{
						pPlayer_Tama[i]->setExecuteEnable(false);
						pPlayer_Tama[i]->setRenderEnable(false);
						pEnemy_Tama2[j]->setExecuteEnable(false);
						pEnemy_Tama2[j]->setRenderEnable(false);
						game_score += SCORE_ADD;
						// ボス戦へのフラグを入れる
					}
				}
			}
		}
	}
	
	/// <summary>
	/// //////
	/// </summary>
	for (int i = 0; i < MISSILE_NUM; i++)
	{
		if (pPlayer_missile[i]->isExecuteEnable())
		{
			for (int j = 0; j < ENEMY_TAMA_NUM; j++)
			{
				if (pEnemy_Tama[j]->isExecuteEnable())
				{
					if (HitCheck(pPlayer_missile[i]->posX,
						pPlayer_missile[i]->posY,
						pEnemy_Tama[j]->posX,
						pEnemy_Tama[j]->posY,
						16.0f,
						16.0f))
					{
						//pPlayer_missile[i]->setExecuteEnable(false);
						//pPlayer_missile[i]->setRenderEnable(false);
						pEnemy_Tama[j]->setExecuteEnable(false);
						pEnemy_Tama[j]->setRenderEnable(false);
						game_score += SCORE_ADD;
						// ボス戦へのフラグを入れる
					}
				}
			}

			for (int j = 0; j < ENEMY_TAMA_NUM2; j++)
			{
				if (pEnemy_Tama2[j]->isExecuteEnable())
				{
					if (HitCheck(pPlayer_missile[i]->posX,
						pPlayer_missile[i]->posY,
						pEnemy_Tama2[j]->posX,
						pEnemy_Tama2[j]->posY,
						16.0f,
						16.0f))
					{
						//pPlayer_missile[i]->setExecuteEnable(false);
						//pPlayer_missile[i]->setRenderEnable(false);
						pEnemy_Tama2[j]->setExecuteEnable(false);
						pEnemy_Tama2[j]->setRenderEnable(false);
						//game_score += SCORE_ADD;
						// ボス戦へのフラグを入れる
					}
				}
			}
			int c;
			c = 0;
			for (int j = 0; j < ENEMY1_NUM; j++)
			{
				if (pEnemy1[j]->isExecuteEnable())
				{
					if (HitCheck(pPlayer_missile[i]->posX,
						pPlayer_missile[i]->posY,
						pEnemy1[j]->posX,
						pEnemy1[j /* % (Target_count + 1)*/ ]->posY,
						16.0f,
						48.0f))
					{
						pPlayer_missile[i]->setExecuteEnable(false);
						pPlayer_missile[i]->setRenderEnable(false);
						game_score += SCORE_ADD;
						// ボス戦へのフラグを入れる
						//pEnemy1[j]->setExecuteEnable(false);
						//pEnemy1[j]->setRenderEnable(false);//(target[3 % (Target_count+1)].y - pPlayer_missile[3]->posY
					}
				}c += 1;
				if (c >= 4)
				break;
			}
			
		}
	}
	


	for (int i = 0; i < ENEMY_TAMA_NUM; i++)
	{
		if (pEnemy_Tama[i]->isExecuteEnable())
		{
			if (HitCheck(pPlayer->posX,
				pPlayer->posY,
				pEnemy_Tama[i]->posX,
				pEnemy_Tama[i]->posY,
				16.0f,
				16.0f))
			{
				Player_Hp -= ENEMY_ADD_DMG;
				if (Player_Hp <= 0) GameInit();
				pEnemy_Tama[i]->setExecuteEnable(false);
				pEnemy_Tama[i]->setRenderEnable(false);
			}
		}
	}
	for (int i = 0; i < ENEMY_TAMA_NUM2; i++)
	{
		if (pEnemy_Tama2[i]->isExecuteEnable())
		{
			if (HitCheck(pPlayer->posX,
				pPlayer->posY,
				pEnemy_Tama2[i]->posX,
				pEnemy_Tama2[i]->posY,
				16.0f,
				16.0f))
			{
				Player_Hp -= ENEMY_ADD_DMG;
				if (Player_Hp <= 0) GameInit();
				pEnemy_Tama2[i]->setExecuteEnable(false);
				pEnemy_Tama2[i]->setRenderEnable(false);
			}
		}
	}
	//スコアの設定
	{
		int	score_tmp = game_score;
		for (int i = SCORE_KETA - 1; i > 0; i--)
		{
			SetScore(pScore[i], score_tmp % 10);
			score_tmp /= 10;
		}
	}

	pHpber->scaleX = (float)Player_Hp / (float)Player_Hp_Max;
	pHpber->posX = HPBER_X_POS + HPBER_HSIZE * ((float)Player_Hp / (float)Player_Hp_Max / 2.0f) - HPBER_HSIZE / 2;
	break;

	case PLAY_RESTART:
		if (pPlayer->posX > 200)
		{
			pPlayer->posX = 200;
			Play_seq = PLAY_MAIN;
		}
		pPlayer->posX += 3;
		break;
  }
  //デバッグ表示(画面に文字を出す)
  vnFont::print(10, 10, L"WASDキーで移動");

  vnFont::print(10, 70, L"Position(%.3f, %.3f)", pPlayer->posX, pPlayer->posY);
  vnFont::print(10, 90, L"Scale(%.3f, %.3f)", pPlayer->scaleX, pPlayer->scaleY);
  vnFont::print(100, 500, L"マウスの座標 : %d, %d", vnMouse::getX(), vnMouse::getY());

  
  
  Time += 1;
}

//描画関数
void vnSceneGame::render()
{
	//スプライトの描画
	switch(Play_seq)
	{
		case PLAY_START:
		case PLAY_RESTART:
		pBG->render();
		pPlayer->render();
		break;
		case PLAY_MAIN:
			pBG->render();
			pPlayer->render();

		for (int i = 0; i < ENEMY1_NUM; i++)
		{
			if (pEnemy1[i]->isRenderEnable())
			{
				pEnemy1[i]->render();
			}
		}

		for (int i = 0; i < PLAYER_TAMA_NUM; i++)
		{
			if (pPlayer_Tama[i]->isRenderEnable())
			{
				pPlayer_Tama[i]->render();
			}
		}

		for (int i = 0; i < MISSILE_NUM; i++)
		{
			if (pPlayer_missile[i]->isRenderEnable())
			{
				pPlayer_missile[i]->render();
			}
		}


		for (int i = 0; i < ENEMY_TAMA_NUM; i++)
		{
			if (pEnemy_Tama[i]->isRenderEnable())
			{
				pEnemy_Tama[i]->render();
			}
		}

		for (int i = 0; i < ENEMY_TAMA_NUM2; i++)
		{
			if (pEnemy_Tama2[i]->isRenderEnable())
			{
				pEnemy_Tama2[i]->render();
			}
		}

		for (int i = 0; i < SCORE_KETA; i++)
		{
			pScore[i]->render();
		}

		pHp->render();
		pHpber->render();

		break;
	}
}

void vnSceneGame::GameInit()
{
	Play_seq = PLAY_RESTART;
	pPlayer->posX = -100;
	pPlayer->posY = SCREEN_CENTER_Y;

	for (int i = 0; i < PLAYER_TAMA_NUM; i++)
	{
		pPlayer_Tama[i]->setExecuteEnable(false);
		pPlayer_Tama[i]->setRenderEnable(false);
	}
	Pl_Tama_Kankaku = 0;
	
	for (int i = 0; i < MISSILE_NUM; i++)
	{
		pPlayer_missile[i]->setExecuteEnable(false);
		pPlayer_missile[i]->setRenderEnable(false);
	}
	Missile_Kankaku = 0;

	for (int i = 0; i < ENEMY_TAMA_NUM; i++)
	{
		pEnemy_Tama[i]->setExecuteEnable(false);
		pEnemy_Tama[i]->setRenderEnable(false);
	}
	Em_Kankaku = 0;

	for (int i = 0; i < ENEMY_TAMA_NUM2; i++)
	{
		pEnemy_Tama2[i]->setExecuteEnable(false);
		pEnemy_Tama2[i]->setRenderEnable(false);
	}
	Em_Kankaku2 = 0;

	for (int i = 0; i < ENEMY1_NUM; i++)
	{
		pEnemy1[i]->setExecuteEnable(false);
		pEnemy1[i]->setRenderEnable(false);
	}
}


void vnSceneGame::SetScore(vnSprite* ptr, int no)
{
	ptr->vtx[0].u = (float)(no % 4) * 0.25f;
	ptr->vtx[0].v = (float)(no / 4) * 0.25f;
	ptr->vtx[1].u = (float)(no % 4 + 1) * 0.25f;
	ptr->vtx[1].v = (float)(no / 4) * 0.25f;
	ptr->vtx[2].u = (float)(no % 4) * 0.25f;
	ptr->vtx[2].v = (float)(no / 4 + 1) * 0.25f;
	ptr->vtx[3].u = (float)(no % 4 + 1) * 0.25f;
	ptr->vtx[3].v = (float)(no / 4 + 1) * 0.25f;
}

//円同士の当たり判定
bool HitCheck(float x1, float y1, float x2, float y2, float r1, float r2 )
{
	float len = CalcLength(x1, y1, x2, y2);
	return (len <= (r1 + r2)) ? true : false;
}

//2点間の距離
float CalcLength(float x1, float y1, float x2, float y2)
{
	return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

//乱数の取得
int GetRandom(int min, int max)
{
	return (rand() % (max - min + 1) + min);
}

// ラジアン角→360度変換
float	AngToRad(float ang) 
{
	return ang / 180.0f * PI;
}

int TargetC(int	a, int b)
{
	return a & b;
}
