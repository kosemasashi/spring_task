#include "DxLib.h"
#include <iostream>
#include <ctime>
#include <random>
#include <tuple>

/*色と対応する番号*/
#define BLUE 1
#define RED 2
#define YELLOW 3
#define PURPLE 4
#define GREEN 5


using namespace std;
random_device rnd;

/*プレイヤーの手札*/
class Player_card {
public:
	int card_number[18];/*1～5までの数字が入る*/
	int card_color[5] = {0};/*0番目が1の青*/
	void display(int turn);/*手札の表示*/
	void card_sort();/*手札を集計*/
};

class Field {
public:
	int field[8][8] = { 0 };
	int tate[8] = { 0 };/*行0～7*/
	int yoko[8] = { 0 };/*列0～7*/

	void display();
	void place_judg();
	int card_judg(int card,int place);
};

void Player_card::display(int turn) {
	int i=0;
	if (turn == 1) {
		i = 300;
	}
	int penb = LoadGraph("ペンパン青.png");
	int penr = LoadGraph("ペンパン赤.png");
	int peny = LoadGraph("ペンパン黄色.png");
	int penp = LoadGraph("ペンパン紫.png");
	int peng = LoadGraph("ペンパン緑.png");
		DrawExtendGraph(10 + 50+i, 100 + 250, 50 + 50+i, 150 + 250, penb, TRUE);
		DrawExtendGraph(10 + 100+i, 100 + 250, 50 + 100+i, 150 + 250, penr, TRUE);
		DrawExtendGraph(10 + 150+i, 100 + 250, 50 + 150+i, 150 + 250, peny, TRUE);
		DrawExtendGraph(10 + 200+i, 100 + 250, 50 + 200+i, 150 + 250, penp, TRUE);
		DrawExtendGraph(10 + 250+i, 100 + 250, 50 + 250+i, 150 + 250, peng, TRUE);
	
	DrawFormatString(150 + i, 330, GetColor(255, 255, 255), "%dのカード", turn);
		DrawFormatString(90+i, 350, GetColor(0, 0, 255), "%d", card_color[0]);
		DrawFormatString(140+i, 350, GetColor(255,0 , 0), "%d", card_color[1]);
		DrawFormatString(190+i, 350, GetColor(255, 255, 0), "%d", card_color[2]);
		DrawFormatString(240+i, 350, GetColor(255, 0, 255), "%d", card_color[3]);
		DrawFormatString(290+i, 350, GetColor(0, 255, 0), "%d", card_color[4]);
		//DrawString(220+i, 370, "番号：12345", GetColor(255, 255, 255));
		//DrawString(260+i, 400 , "残り枚数", GetColor(255, 255, 255));
	
}

void Player_card::card_sort() {
	for (int i = 0; i < 18; i++) {
		card_color[card_number[i] - 1]++;
	}
}

void Field::display() {/*フィールドの表示*/
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j <= i; j++) {
			printfDx("%d", field[i][j]);
		}
		printfDx("\n");
	}
}

void Field::place_judg() {
	int check = 0;/*選択しの数*/
	 if(field[7][7] == 0){/*最下段が埋まっているか否か*/
		 tate[check] = 0;
		 yoko[check] = 7;
		check++;
		printfDx("%d:8列1番\n",check);
		for (int i = 0; i < 8; i++) {
			if (field[7][i] == 0) {/*最下段の何番目が開いているか？*/
				tate[check] = i;
				yoko[check] = 7;
				check++;
				printfDx("%d:8列%d番\n",check,i+1);
				break;
			}
		}
	}

	/*最下段以外の判定*/
	for (int i = 0; i < 7; i++){
		for (int j = 0; j <= i; j++) {
			if (field[i][j] == 0&&field[i + 1][j] !=0 && field[i + 1][j + 1] !=0) {/*その場所が0で、下二つが数字が入っているかどうか*/
				tate[check] = j;
				yoko[check] = i;
				check++;
				printfDx("%d:%d列%d番\n", check, i+1, j+1);
			}
		}
	}
	if (check == 0) {
		printfDx("出せる場所がありませ\n");
	}
	
}

int Field::card_judg(int card,int place) {
	int a,b;
	if (yoko[place] == 7) {
		if (tate[place] == 0) {
			for (int i = 0; i < 8; i++) {
				for (int j = i; j >=0; j--) {
					if (j == 0) {/*0番目は0を入れる*/
						field[i][j] = 0;
					}
					else {
						if (field[i][j - 1] != 0) {/*左隣りに数字があれば入れる*/
							field[i][j] = field[i][j - 1];
						}
					}
				}
			}
		}
		field[yoko[place]][tate[place]] = card;
		return 1;/*出せたなら1をかえす*/
	}
	else {
		if (card == field[yoko[place] + 1][tate[place]] || card == field[yoko[place] + 1][tate[place] + 1]) {/*下と同じ色なら出せる*/
			field[yoko[place]][tate[place]] = card;
			return 1;
		}
		else {
			printfDx("その場所にその色は出せません\n");
			return 0;
		}
	}
};

int key_in() {
	while (1) {
		WaitKey();
		if (CheckHitKey(KEY_INPUT_NUMPAD1) || CheckHitKey(KEY_INPUT_1)) {
			return 1;
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD2) || CheckHitKey(KEY_INPUT_2)) {
			return 2;
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD3) || CheckHitKey(KEY_INPUT_3)) {
			return 3;
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD4) || CheckHitKey(KEY_INPUT_4)) {
			return 4;
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD5) || CheckHitKey(KEY_INPUT_5)) {
			return 5;
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD6) || CheckHitKey(KEY_INPUT_6)) {
			return 6;
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD7) || CheckHitKey(KEY_INPUT_7)) {
			return 7;
		}
		if (CheckHitKey(KEY_INPUT_NUMPAD8) || CheckHitKey(KEY_INPUT_8)) {
			return 8;
		}
		else {
			printfDx("不必要なキーを押さないでください\n");
		}
	}

}

/*手札の生成*/
void shuffle(struct Player_card* plr1,Player_card* plr2) {
	/*カード生成*/
	int all_card[36];
	int k = 0;
	for (int i = BLUE; i < GREEN+1; i++) {
		for (int j = 0; j < 7; j++) {
			all_card[k] = i;
			k++;
		}
	}
	all_card[35] = GREEN;/*最後の一枚*/
	

	/*シャッフル*/
	int rand,num;
	for (int i = 0; i < 36; i++) {
		rand = rnd() % 36;
		num = all_card[rand];
		all_card[rand] = all_card[i];
		all_card[i] = num;
	}

	/*各手札にセット*/
	int l=0;
	for (int i = 0; i < 18; i++) {
		plr1->card_number[i] = all_card[l];
		l++;
	}

	for (int i = 0; i < 18; i++) {
		plr2->card_number[i] = all_card[l];
		l++;
	}
	
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return -1;    // エラーが起きたら直ちに終了
	}

	 Player_card player[2];/*プレイヤーの手札*/
	 Field fild;/*フィールド*/

	 shuffle(&player[0],&player[1]);/*シャッフル*/
	 player[0].card_sort();
	 player[1].card_sort();

	
	 
	/*ゲーム開始*/
	 int turn=rnd()%2;/*0ならplayer[0]、1ならplayer[1]*/
	 int turn1=0;
	 int hand;
	 int place;

		 printfDx("%dのターン\n", turn % 2);
		 printfDx("最初に出すカードを入力してください\n");
		 fild.display();
		 player[turn % 2].display(turn%2);
		 player[(turn + 1) % 2].display((turn + 1) % 2);
		 printfDx("手札:");
		 while (1) {
			 hand = key_in();/*入力待ち*/
			 if (hand < 1 || hand > 5) {/*色以外の番号を押差ないように*/
				 printfDx("不必要なキーを押さないでください1\n");
			 }
			 else {
				 if (player[turn % 2].card_color[hand - 1] == 0) {/*0枚か確認*/
					 printfDx("その色は0枚です\n");
				 }
				 else {
					 break;
				 }
			 }
		 }
		 printfDx("%d\n", hand);
		 player[turn % 2].card_color[hand - 1]--; /*選んだ色を減らす*/
		 fild.field[7][0] = hand;/*選んだ色を入れる*/
		 clsDx();
		 ClearDrawScreen();/*画面クリア*/
		 turn++;
		 printfDx("%dのターン\n", turn % 2);
		 player[turn % 2].display(turn % 2);
		 player[(turn+1) % 2].display((turn+1) % 2);
		 fild.display();

		 /*最初の手以外のゲーム*/
		 while (1) {
			 fild.place_judg();/*出せる場所の提示*/

			 printfDx("色を指定してください\n");
			 printfDx("出せない場合、またはリタイアする場合6を押してください\n");
			 while (1) {
				 hand = key_in();
				 if (hand < 1 || hand > 6) {/*色以外の番号を押差ないように*/
					 printfDx("不必要なキーを押さないでください\n");
				 }
				 else {
					 if (hand == 6) {/*リタイアキー*/
						 break;
					 }
					 else {
						 if (player[turn % 2].card_color[hand - 1] == 0) {/*0枚か確認*/
							 printfDx("その色は0枚です\n");
						 }
						 else {
							 break;
						 }
					 }
				 }
			 }

			 if (hand == 6) {/*6をおしたときターンを飛ばす*/
				 turn1++;
				 turn--;
				 clsDx();
				 ClearDrawScreen();
			 }
			 else {
				 printfDx("場所を入力してください\n");
				 place = key_in();
				 if (fild.card_judg(hand, place - 1) == 0) {/*場所を選択してその色が出せるか判定*/
					 turn--;/*もう一度やり直す*/
					 if (turn1 == 1) {
						 turn++;
					 }
				 }
				 else {
					 player[turn % 2].card_color[hand - 1]--;
				 }
				 clsDx();
				 ClearDrawScreen();
				 player[turn % 2].display(turn % 2);
				 player[(turn + 1) % 2].display((turn + 1) % 2);
			 }
			 if (turn1 == 1) {/*リタイア*/
				 turn--;
			 }
			 else {
				 if (turn1 == 2) {/*ゲーム終了*/
					 break;
				 }
			 }
			 turn++;/*最後に足す*/
			 printfDx("%dのターン\n", turn % 2);
			 fild.display();
			 player[turn % 2].display(turn % 2);
			 player[(turn + 1) % 2].display((turn + 1) % 2);
		 }
		 clsDx();
		 ClearDrawScreen();

		 /*勝敗判定*/
		 int sum=0,sum2=0;
		 for (int i = 0; i < 5; i++) {
			 sum += player[0].card_color[i];
		 }
		 for (int i = 0; i < 5; i++) {
			 sum2 += player[1].card_color[i];
		 }

		 if (sum == sum2) {
			 DrawString(260, 250, "引き分け", GetColor(0, 0, 255));
		 }
		 else {
			 if (sum > sum2) {
				 DrawString(260, 250, "1の勝利", GetColor(255, 0, 0));
			 }
			 else {
				 DrawString(260, 250, "0の勝利", GetColor(255, 0, 0));
			 }
		 }

	WaitKey();        // キーの入力待ち(『WaitKey』を使用)

	DxLib_End();        // ＤＸライブラリ使用の終了処理

	return 0;        // ソフトの終了
}