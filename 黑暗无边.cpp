#include <iostream>
#include <Windows.h>
#include <time.h>
#include <iomanip>
#include <ctime>
#include <string>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 
using namespace std;

char map[16][31];//15*30
bool maplist[10];//һ���ؿ�һ���Ÿ����� 
int level=1;//�ؿ��ȼ� 
int x = 2, y = 4;//��ɫλ�� 
int clocktime = clock(), ct_m = clock();//��ˢ���� 
int press = 0;//�������Ƽ��̰����жϹ��� 
bool press_bool = false;//�����ж��Ƿ�Ҫ���Ƽ��̰��� 
int ag = 10, hp = 300;//������ֵ 
int fight = false;
int m_xy[4][3], m_hp[4];
bool alive = true;
int att_m = clock(), att = clock() - 1000;//������� 
int dir = 0;//����, 0^ 1< 2v 3> 
int att_xy[7];
string state;//״̬ 

void make(){//���ɹؿ���ͼ
	
	//���õ�ͼ
	x = 2, y = 4;
	for(int i=0; i<9; i++){
		maplist[i] = false;
	} 
	
	srand(std::time(0));//�������������
	maplist[0] = maplist[1] = maplist[3] = true;
	maplist[2] = rand()%2;
	maplist[4] = rand()%2;
	maplist[6] = rand()%2;
	if (maplist[2]){maplist[5] = rand()%2;}
	if (maplist[6] || maplist[4]){maplist[7] = rand()%2;}
	if (maplist[5] || maplist[7]){maplist[8] = rand()%2;}
	
	for (int i=0; i<15; i++){
		for (int j=0; j<30; j++){
			map[i][j]='/';//ȫ����䡮/��
		}
	}
	
	for (int i=0; i<=2; i++){
		for (int j=0; j<=2; j++) {
			if (maplist[i*3+j]){
				if (i != 0 || j != 0){//��һ�����䲻��̽�� 
					for (int p=0; p<=4; p++){
						if (p == 0 || p == 4){
							for (int o=0; o<=9; o++){
								map[i*5+p][j*10+o]='#';
							}
						} else {
							map[i*5+p][j*10]='#';
							for (int o=1; o<=8; o++){
								map[i*5+p][j*10+o]='?';
							}map[i*5+p][j*10+9]='#';
						}
				 	}/* ������������ڣ���ô 
					    "##########",
						"#????????#",
						"#????????#",
						"#????????#",
						"##########",������ôһ��
						*/
				} else {
					for (int p=0; p<=4; p++){
						if (p == 0 || p == 4){
							for (int o=0; o<=9; o++){
								map[i*5+p][j*10+o]='#';
							}
						} else {
							map[i*5+p][j*10]='#';
							for (int o=1; o<=8; o++){
								map[i*5+p][j*10+o]='.';
							}map[i*5+p][j*10+9]='#';
						}
				 	}
				}
			}
		}
	}
	for (int i=0; i<=2; i++){//����ͨ�� 
		for (int j=0; j<=2; j++) {
			if(maplist[i*3+j-3] && maplist[i*3+j]){
				map[i*5-1][j*10+4] = '.';
				map[i*5-1][j*10+5] = '.';
				map[i*5][j*10+4] = '.';
				map[i*5][j*10+5] = '.';
			} if (maplist[i*3+j-1] && maplist[i*3+j] && i*3+j != 0 && i*3+j != 3 && i*3+j != 6){
				map[i*5+2][j*10] = '.';
				map[i*5+2][j*10-1] = '.';
			}
		}
	}
} 
void box(){
	srand(std::time(0));//�������������
	int num = rand()%2;
	if (num == 0){
		int ag_ = level * 20 + rand()%35;
		if (ag_ < ag){
			state = "������һ�ѱ����ϵ��������õĽ�������㶪����";
		} else {
			state = "������һ�Ѹ��õ�������";
			ag = ag_;
		}
	} else if (num == 1){
		state = "������һƿ����ҩˮ���㽫��������ȥ";
		hp += 80 + level * 20 + rand()%50;
	}
}


int main(){
	
	make();
	
	while (alive){
		
		//���㴦���ĸ�����
		int x_room = x / 5, y_room = y / 10; 
		
		//�жϼ��̰���
		if (KEY_DOWN('A') && (map[x][y-1] == 46 || map[x][y-1] == 63) && clock() - press >= 150){//���� 
			y -= 1;
			press_bool = true;
			dir = 1;
		} if (KEY_DOWN('D') && (map[x][y+1] == 46 || map[x][y+1] == 63) && clock() - press >= 150){//���� 
			y += 1;
			press_bool = true; 
			dir = 3;
		} if (KEY_DOWN('W') && (map[x-1][y] == 46 || map[x-1][y] == 63) && clock() - press >= 150){//���� 
			x -= 1;
			press_bool = true; 
			dir = 0;
		} if (KEY_DOWN('S') && (map[x+1][y] == 46 || map[x+1][y] == 63) && clock() - press >= 150){//���� 
			x += 1;
			press_bool = true; 
			dir = 2;
		} if (press_bool){
			press = clock();
			press_bool = false; 
		} if (clock() - att >= 1000 && KEY_DOWN('Q')){
			att = clock();
		} if (clock() - att <= 500) {
			if (dir == 0){
				att_xy[0] = x-1;
				att_xy[1] = y-1;
				att_xy[2] = x-1;
				att_xy[3] = y;
				att_xy[4] = x-1;
				att_xy[5] = y+1;
			}else if (dir == 1){
				att_xy[0] = x-1;
				att_xy[1] = y-1;
				att_xy[2] = x;
				att_xy[3] = y-1;
				att_xy[4] = x+1;
				att_xy[5] = y-1;
			}else if (dir == 2){
				att_xy[0] = x+1;
				att_xy[1] = y-1;
				att_xy[2] = x+1;
				att_xy[3] = y;
				att_xy[4] = x+1;
				att_xy[5] = y+1;
			}else if (dir == 3){
				att_xy[0] = x-1;
				att_xy[1] = y+1;
				att_xy[2] = x;
				att_xy[3] = y+1;
				att_xy[4] = x+1;
				att_xy[5] = y+1;
			}
		}if (KEY_DOWN('E')){
			if (dir == 0){
				if (map[x-1][y] == '$'){
					map[x-1][y] = '*';
					box(); 
				} else if (map[x-1][y] == '0'){
					make();
					level++;
				} 
			} else if (dir == 1){
				if (map[x][y-1] == '$'){
					map[x][y-1] = '*';
					box(); 
				} else if (map[x][y-1] == '0'){
					make();
					level++;
				}  
			} else if (dir == 2){
				if (map[x+1][y] == '$'){
					map[x+1][y] = '*';
					box(); 
				} else if (map[x+1][y] == '0'){
					make();
					level++;
				} 
			} else if (dir == 3){
				if (map[x][y+1] == '$'){
					map[x][y+1] = '*';
					box(); 
				} else if (map[x][y+1] == '0'){
					make();
					level++;
				} 
			}
		}
		
		//̽������
		if (map[x][y] == '?'){
			for (int i=1; i<=3; i++){
				for (int j=1; j<=8; j++){
					map[x_room*5+i][y_room*10+j] = '.';
				}
			} //���ɷ����еĶ���
			if (map[1][1] == '?' || map[1][11] == '?' || map[1][21] == '?' || map[6][1] == '?' || map[6][11] == '?' || map[6][21] == '?' || map[11][1] == '?' || map[11][11] == '?' || map[11][21] == '?' ){
				srand(std::time(0));//�������������
				int num = rand()%3;
				cout <<num; 
				if (num){//����
					map[x_room*5][y_room*10+4] = '#';//���� 
					map[x_room*5][y_room*10+5] = '#';
					map[x_room*5+4][y_room*10+4] = '#';
					map[x_room*5+4][y_room*10+5] = '#';
					map[x_room*5+2][y_room*10] = '#';
					map[x_room*5+2][y_room*10+9] = '#';
					for (int i=0; i<3; i++){
						m_xy[i][0] = x_room*5+2;
						m_xy[i][1] = y_room*10+3+i*2;
						srand(std::time(0));//�������������
						m_hp[i] = 25 * level + rand()%40;
					} fight = true;
				} else {//���� 
					map[x_room*5+2][y_room*10+5] = '$';
				}
			} else {
				map[x_room*5+2][y_room*10+5] = '0';
			}
		}
		if (clock() - ct_m >= 1000){//��1֡
			ct_m = clock(); 
			//���ƹ����ƶ������� 
			if (fight){
				for (int i=0; i<3; i++){
					if (m_xy[i][0] > x){
						m_xy[i][0] -= 1;
					} else if (m_xy[i][0] < x){
						m_xy[i][0] += 1;
					} else if (m_xy[i][1] > y){
						m_xy[i][1] -= 1;
					} else if (m_xy[i][1] < y){
						m_xy[i][1] += 1;
					}	
				}for (int i=0; i<3; i++){
					if (m_xy[i][0] == x && m_xy[i][1] == y){
						if (clock() - att_m >= 2000){
							hp -= 5*level + rand()%30;
							state = "���յ��˹�����";
							att_m = clock();
						}
					}
				}for (int i=0; i<3; i++){
					if ((m_xy[i][0] == att_xy[0] && m_xy[i][1] == att_xy[1]) || (m_xy[i][0] == att_xy[2] && m_xy[i][1] == att_xy[3]) || (m_xy[i][0] == att_xy[4] && m_xy[i][1] == att_xy[5]) || ((m_xy[i][0] == x && m_xy[i][1] == y) && clock() - att <= 500)){
						m_hp[i] -= ag + rand()%20;
					}if (m_hp[i] <= 0){
						m_xy[i][0] = 114514;
						m_xy[i][1] = 114514;
						state = "�й�����ˣ�";
					}
				}if (m_hp[0] <= 0 && m_hp[1] <= 0 && m_hp[2] <= 0){
					if(maplist[(x_room*3+y_room)-3]) {//���� 
						map[x_room*5][y_room*10+4] = '.';
						map[x_room*5][y_room*10+5] = '.';
					}if(maplist[(x_room*3+y_room)+3]) {
						map[x_room*5+4][y_room*10+4] = '.';
						map[x_room*5+4][y_room*10+5] = '.';
					}if(maplist[(x_room*3+y_room)-1] && y_room != 0) {
						map[x_room*5+2][y_room*10] = '.';
					}if(maplist[(x_room*3+y_room)+1] && y_room != 2) {
						map[x_room*5+2][y_room*10+9] = '.';
					}
					state = "���������й��";
					fight = false;
				}
			} 
		}
		if (clock() - clocktime >= 50){//��Ȼ����20ˢ����
		
			int fps = 1000 / (clock() - clocktime); 
			clocktime = clock();
			system("cls");
			for(int i=0; i<=15; i++){
				for(int j=0; j<=30; j++){
					if (i == x && j == y){
						cout << '@';
					} else if ((i == m_xy[0][0] || i == m_xy[1][0] || i == m_xy[2][0]) && (j == m_xy[0][1] || j == m_xy[1][1] || j == m_xy[2][1]) && fight){
						cout << '!';
					} else if(clock() - att <= 500 && ((i == att_xy[0] && j == att_xy[1]) || (i == att_xy[2] && j == att_xy[3]) || (i == att_xy[4] && j == att_xy[5]))) {
						cout << '<';
					} else {
						cout << map[i][j];
					}
				}cout << endl;
			}cout << "hp:" << hp << endl;
			cout << "level:" << level <<endl;
			cout << "fps:" << fps << endl;
			cout << "������:" << ag << endl;
			cout << state << endl;
		}
		if (hp <= 0){
			alive = false;
			cout << "GAME OVER";
			Sleep(1000);
		}
	}
}

