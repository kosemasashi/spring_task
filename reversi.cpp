#include "DxLib.h"
#include <iostream>
#include <ctime>
#include <random>
#include <tuple>

/*�F�ƑΉ�����ԍ�*/
#define BLUE 1
#define RED 2
#define YELLOW 3
#define PURPLE 4
#define GREEN 5


using namespace std;
random_device rnd;

/*�v���C���[�̎�D*/
class Player_card {
public:
	int card_number[18];/*1�`5�܂ł̐���������*/
	int card_color[5] = {0};/*0�Ԗڂ�1�̐�*/
	void display(int turn);/*��D�̕\��*/
	void card_sort();/*��D���W�v*/
};

class Field {
public:
	int field[8][8] = { 0 };
	int tate[8] = { 0 };/*�s0�`7*/
	int yoko[8] = { 0 };/*��0�`7*/

	void display();
	void place_judg();
	int card_judg(int card,int place);
};

void Player_card::display(int turn) {
	int i=0;
	if (turn == 1) {
		i = 300;
	}
	int penb = LoadGraph("�y���p����.png");
	int penr = LoadGraph("�y���p����.png");
	int peny = LoadGraph("�y���p�����F.png");
	int penp = LoadGraph("�y���p����.png");
	int peng = LoadGraph("�y���p����.png");
		DrawExtendGraph(10 + 50+i, 100 + 250, 50 + 50+i, 150 + 250, penb, TRUE);
		DrawExtendGraph(10 + 100+i, 100 + 250, 50 + 100+i, 150 + 250, penr, TRUE);
		DrawExtendGraph(10 + 150+i, 100 + 250, 50 + 150+i, 150 + 250, peny, TRUE);
		DrawExtendGraph(10 + 200+i, 100 + 250, 50 + 200+i, 150 + 250, penp, TRUE);
		DrawExtendGraph(10 + 250+i, 100 + 250, 50 + 250+i, 150 + 250, peng, TRUE);
	
	DrawFormatString(150 + i, 330, GetColor(255, 255, 255), "%d�̃J�[�h", turn);
		DrawFormatString(90+i, 350, GetColor(0, 0, 255), "%d", card_color[0]);
		DrawFormatString(140+i, 350, GetColor(255,0 , 0), "%d", card_color[1]);
		DrawFormatString(190+i, 350, GetColor(255, 255, 0), "%d", card_color[2]);
		DrawFormatString(240+i, 350, GetColor(255, 0, 255), "%d", card_color[3]);
		DrawFormatString(290+i, 350, GetColor(0, 255, 0), "%d", card_color[4]);
		//DrawString(220+i, 370, "�ԍ��F12345", GetColor(255, 255, 255));
		//DrawString(260+i, 400 , "�c�薇��", GetColor(255, 255, 255));
	
}

void Player_card::card_sort() {
	for (int i = 0; i < 18; i++) {
		card_color[card_number[i] - 1]++;
	}
}

void Field::display() {/*�t�B�[���h�̕\��*/
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j <= i; j++) {
			printfDx("%d", field[i][j]);
		}
		printfDx("\n");
	}
}

void Field::place_judg() {
	int check = 0;/*�I�����̐�*/
	 if(field[7][7] == 0){/*�ŉ��i�����܂��Ă��邩�ۂ�*/
		 tate[check] = 0;
		 yoko[check] = 7;
		check++;
		printfDx("%d:8��1��\n",check);
		for (int i = 0; i < 8; i++) {
			if (field[7][i] == 0) {/*�ŉ��i�̉��Ԗڂ��J���Ă��邩�H*/
				tate[check] = i;
				yoko[check] = 7;
				check++;
				printfDx("%d:8��%d��\n",check,i+1);
				break;
			}
		}
	}

	/*�ŉ��i�ȊO�̔���*/
	for (int i = 0; i < 7; i++){
		for (int j = 0; j <= i; j++) {
			if (field[i][j] == 0&&field[i + 1][j] !=0 && field[i + 1][j + 1] !=0) {/*���̏ꏊ��0�ŁA����������������Ă��邩�ǂ���*/
				tate[check] = j;
				yoko[check] = i;
				check++;
				printfDx("%d:%d��%d��\n", check, i+1, j+1);
			}
		}
	}
	if (check == 0) {
		printfDx("�o����ꏊ������܂�\n");
	}
	
}

int Field::card_judg(int card,int place) {
	int a,b;
	if (yoko[place] == 7) {
		if (tate[place] == 0) {
			for (int i = 0; i < 8; i++) {
				for (int j = i; j >=0; j--) {
					if (j == 0) {/*0�Ԗڂ�0������*/
						field[i][j] = 0;
					}
					else {
						if (field[i][j - 1] != 0) {/*���ׂ�ɐ���������Γ����*/
							field[i][j] = field[i][j - 1];
						}
					}
				}
			}
		}
		field[yoko[place]][tate[place]] = card;
		return 1;/*�o�����Ȃ�1��������*/
	}
	else {
		if (card == field[yoko[place] + 1][tate[place]] || card == field[yoko[place] + 1][tate[place] + 1]) {/*���Ɠ����F�Ȃ�o����*/
			field[yoko[place]][tate[place]] = card;
			return 1;
		}
		else {
			printfDx("���̏ꏊ�ɂ��̐F�͏o���܂���\n");
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
			printfDx("�s�K�v�ȃL�[�������Ȃ��ł�������\n");
		}
	}

}

/*��D�̐���*/
void shuffle(struct Player_card* plr1,Player_card* plr2) {
	/*�J�[�h����*/
	int all_card[36];
	int k = 0;
	for (int i = BLUE; i < GREEN+1; i++) {
		for (int j = 0; j < 7; j++) {
			all_card[k] = i;
			k++;
		}
	}
	all_card[35] = GREEN;/*�Ō�̈ꖇ*/
	

	/*�V���b�t��*/
	int rand,num;
	for (int i = 0; i < 36; i++) {
		rand = rnd() % 36;
		num = all_card[rand];
		all_card[rand] = all_card[i];
		all_card[i] = num;
	}

	/*�e��D�ɃZ�b�g*/
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

	if (DxLib_Init() == -1)    // �c�w���C�u��������������
	{
		return -1;    // �G���[���N�����璼���ɏI��
	}

	 Player_card player[2];/*�v���C���[�̎�D*/
	 Field fild;/*�t�B�[���h*/

	 shuffle(&player[0],&player[1]);/*�V���b�t��*/
	 player[0].card_sort();
	 player[1].card_sort();

	
	 
	/*�Q�[���J�n*/
	 int turn=rnd()%2;/*0�Ȃ�player[0]�A1�Ȃ�player[1]*/
	 int turn1=0;
	 int hand;
	 int place;

		 printfDx("%d�̃^�[��\n", turn % 2);
		 printfDx("�ŏ��ɏo���J�[�h����͂��Ă�������\n");
		 fild.display();
		 player[turn % 2].display(turn%2);
		 player[(turn + 1) % 2].display((turn + 1) % 2);
		 printfDx("��D:");
		 while (1) {
			 hand = key_in();/*���͑҂�*/
			 if (hand < 1 || hand > 5) {/*�F�ȊO�̔ԍ��������Ȃ��悤��*/
				 printfDx("�s�K�v�ȃL�[�������Ȃ��ł�������1\n");
			 }
			 else {
				 if (player[turn % 2].card_color[hand - 1] == 0) {/*0�����m�F*/
					 printfDx("���̐F��0���ł�\n");
				 }
				 else {
					 break;
				 }
			 }
		 }
		 printfDx("%d\n", hand);
		 player[turn % 2].card_color[hand - 1]--; /*�I�񂾐F�����炷*/
		 fild.field[7][0] = hand;/*�I�񂾐F������*/
		 clsDx();
		 ClearDrawScreen();/*��ʃN���A*/
		 turn++;
		 printfDx("%d�̃^�[��\n", turn % 2);
		 player[turn % 2].display(turn % 2);
		 player[(turn+1) % 2].display((turn+1) % 2);
		 fild.display();

		 /*�ŏ��̎�ȊO�̃Q�[��*/
		 while (1) {
			 fild.place_judg();/*�o����ꏊ�̒�*/

			 printfDx("�F���w�肵�Ă�������\n");
			 printfDx("�o���Ȃ��ꍇ�A�܂��̓��^�C�A����ꍇ6�������Ă�������\n");
			 while (1) {
				 hand = key_in();
				 if (hand < 1 || hand > 6) {/*�F�ȊO�̔ԍ��������Ȃ��悤��*/
					 printfDx("�s�K�v�ȃL�[�������Ȃ��ł�������\n");
				 }
				 else {
					 if (hand == 6) {/*���^�C�A�L�[*/
						 break;
					 }
					 else {
						 if (player[turn % 2].card_color[hand - 1] == 0) {/*0�����m�F*/
							 printfDx("���̐F��0���ł�\n");
						 }
						 else {
							 break;
						 }
					 }
				 }
			 }

			 if (hand == 6) {/*6���������Ƃ��^�[�����΂�*/
				 turn1++;
				 turn--;
				 clsDx();
				 ClearDrawScreen();
			 }
			 else {
				 printfDx("�ꏊ����͂��Ă�������\n");
				 place = key_in();
				 if (fild.card_judg(hand, place - 1) == 0) {/*�ꏊ��I�����Ă��̐F���o���邩����*/
					 turn--;/*������x��蒼��*/
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
			 if (turn1 == 1) {/*���^�C�A*/
				 turn--;
			 }
			 else {
				 if (turn1 == 2) {/*�Q�[���I��*/
					 break;
				 }
			 }
			 turn++;/*�Ō�ɑ���*/
			 printfDx("%d�̃^�[��\n", turn % 2);
			 fild.display();
			 player[turn % 2].display(turn % 2);
			 player[(turn + 1) % 2].display((turn + 1) % 2);
		 }
		 clsDx();
		 ClearDrawScreen();

		 /*���s����*/
		 int sum=0,sum2=0;
		 for (int i = 0; i < 5; i++) {
			 sum += player[0].card_color[i];
		 }
		 for (int i = 0; i < 5; i++) {
			 sum2 += player[1].card_color[i];
		 }

		 if (sum == sum2) {
			 DrawString(260, 250, "��������", GetColor(0, 0, 255));
		 }
		 else {
			 if (sum > sum2) {
				 DrawString(260, 250, "1�̏���", GetColor(255, 0, 0));
			 }
			 else {
				 DrawString(260, 250, "0�̏���", GetColor(255, 0, 0));
			 }
		 }

	WaitKey();        // �L�[�̓��͑҂�(�wWaitKey�x���g�p)

	DxLib_End();        // �c�w���C�u�����g�p�̏I������

	return 0;        // �\�t�g�̏I��
}