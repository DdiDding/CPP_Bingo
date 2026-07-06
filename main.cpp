#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define SHUFFLE 100
#define BLUE 3
#define WHITE 7
#define RED 4
#define GRAY 8
#define YELLOW 14

#define MAP_WIDTH 55
#define MAP_HEIGHT 20
#define MAP_X 0
#define MAP_Y 0

void Title();
void Draw_map();
void Gotoxy(int x, int y);
void Draw_plate(int * p_plate, int * p_plate2,int * c_plate,int * c_plate2); //빙고판 그리는 함수
void Draw_interface();
void Swap(int * plate, int * plate2);//빙고판에 숫자를 넣고 랜덤으로 섞어주며 동시에 카피본까지 생성 함수
void Ingame(); // 인게임 함수
void Set_com_plate(int * c_plate, int * c_plate2);
void Color(unsigned short text); //텍스트 색상 변경
void Reset_text();//하단부분 텍스트 초기화
int Player_select(int * s_plate, int game_turn);//플레이어 숫자 입력 함수, 선택한숫자들의 배열을 주소로 받음
int Com_select(int * s_plate, int game_turn); //컴퓨터 인공지능 합해서 숫자 뽑기
void Check_num(int * p_plate, int * c_plate, int select_num);
bool Check_bingo(int * plate);
void Game_result(int result); //게임 결과 값 받아서 그에 맞는 인터페이스 출력
int kb(int kb_result); // 키보드 입력 받는 함수
bool Result_menu(); //결과 메뉴
void move_line_num();


int line_num = 4; // 가로세로 길이
int plate_width = (4 * line_num) + 1;//판의 가로 길이
int plate_heigt = (2 * line_num) + 1;//판의 가로 길이


bool who_turn = true;  // true면 플레이어 차례, false면 컴퓨터 차례
bool game_start = true;

int main() {

	while (1) {
		system("cls");
		Title();
		//타이틀 화면 - line_num 정하는 곳

		if (game_start) {
			do {
				Color(WHITE);
				Ingame();
			} while (Result_menu());
		}
		else {
			exit(0);
		}
	}
	
	return 0;
}

/*line ──────────────────────────────────────────────────────────*/
/*line ──────────────────────────────────────────────────────────*/

void Gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



void Color(unsigned short text) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}


void Draw_plate(int * plate , int * plate2 , int * c_plate , int * c_plate2) {

	system("cls");

	int cnt = 0; // plate의 index 카운터 

	//플레이어 플레이트 출력부분
	printf("┏");
	for (int i = 0; i < line_num - 1; i++) {
		printf("━━━┳");
	}
	printf("━━━┓\n");

	for (int i = 0; i < ((line_num - 1) * 2) + 1; i++) {

		if (i % 2 == 0) {

		
			//벽과 숫자부분
			for (int j = 0; j < line_num; j++) {

				printf("┃");

				//if문으로 색상만 지정
				if (plate[cnt] >= 1) Color(WHITE);
				else if (plate[cnt] == 0) Color(BLUE);
				else if (plate[cnt] == -100) Color(RED);
				
				//숫자가 10보다 작으면 
				if (plate2[cnt] < 10) {
					printf("  %d", plate2[cnt]);
				}
				//숫자가 10보다 크면
				else {
					printf(" %d", plate2[cnt]);
				}

				Color(WHITE);
				cnt++;
			}
			printf("┃\n");
		}
		else {
			printf("┣");
			//바닥 부분
			for (int k = 0; k < line_num - 1; k++) {
				printf("━━━╋");
			}
			printf("━━━┫\n");
		}
	}

	printf("┗");
	for (int i = 0; i < line_num - 1; i++) {
		printf("━━━┻");
	}
	printf("━━━┛\n");

	//컴퓨터 플레이트 출력 부분 (계산은 안해도됭!)
	//5면 8번 4면 6번  3면 4번  - > line_num-1 *2
	cnt = 0; // 카운트 초기화
	Gotoxy(plate_width + (2 * line_num) + 22, 0);

	//상단 부분-----
	printf("┏");
for (int i = 0; i < line_num - 1; i++) {
	printf("━━━┳");
}
printf("━━━┓");

//중단 부분-----
for (int i = 0; i < ((line_num - 1) * 2) + 1; i++) {

	Gotoxy(plate_width + (2 * line_num) + 22, 1 + i);
	//줄수가 짝수일 때 - 벽이랑 숫자 출력
	if (i % 2 == 0) {

		printf("┃");
		for (int j = 0; j < line_num; j++) {

			//if문으로 색상만 지정
			if (c_plate[cnt] >= 1) Color(WHITE);
			else if (c_plate[cnt] == 0) Color(BLUE);
			else if (c_plate[cnt] == -100) Color(RED);

			//숫자가 10보다 작으면 
			if (c_plate2[cnt] < 10) {
				printf("  %d", c_plate2[cnt]);
			}
			//숫자가 10보다 크면
			else {
				printf(" %d", c_plate2[cnt]);
			}
			Color(WHITE);
			printf("┃");
			cnt++;
		}
	}
	else {
		Gotoxy(plate_width + (2 * line_num) + 22, 1 + i);
		printf("┣");
		for (int k = 0; k < line_num - 1; k++) {
			printf("━━━╋");
		}
		printf("━━━┫\n");
	}
}
//밑 부분
Gotoxy(plate_width + (2 * line_num) + 22, line_num * 2);
printf("┗");
for (int i = 0; i < line_num - 1; i++) {
	printf("━━━┻");
}
printf("━━━┛\n");
}



void Swap(int * plate, int * plate2) {
	int a, b, temp;

	//받은 영역에 숫자 집어넣음
	for (int i = 0; i < (line_num*line_num); i++) {
		plate[i] = i + 1;
		plate2[i] = i + 1;
	}

	//랜덤 섞기
	for (int i = 0; i < SHUFFLE; i++) {

		do {
			a = rand() % (line_num*line_num);
			b = rand() % (line_num*line_num);
		} while (a == b);

		temp = plate[a];
		plate[a] = plate[b];
		plate[b] = temp;

		plate2[a] = plate[a];
		plate2[b] = plate[b];
	}
}


//4 * line_num + 1 이 판 크기
void Draw_interface() {

	if (line_num == 4) {
		Gotoxy(plate_width + 1, 1);
	}
	else if (line_num == 5) {
		Gotoxy(plate_width + 4, 1);
	}
	else if (line_num == 3) {
		Gotoxy(plate_width - 1, 1);
	}
	Color(BLUE);
	printf(" [플레이어]");
	Color(WHITE);
	printf("  VS  ");
	Color(RED);
	printf("[컴ㅡ퓨터]");
	Color(WHITE);
	

	if (line_num == 4) {
		Gotoxy(plate_width + line_num, (plate_heigt / 2) + 1);
	}
	else if (line_num == 5) {
		Gotoxy(plate_width + line_num + 3, (plate_heigt / 2) + 1);
	}
	else if (line_num == 3) {
		Gotoxy(plate_width + line_num -1, (plate_heigt / 2) + 1);
	}
	
	if (who_turn) printf("< 플레이어 턴 입니다 >"); //22칸 소모 
	else printf("< 컴퓨터의 턴 입니다.>");

	if (line_num == 4) {
		Gotoxy(plate_width + 1, (plate_heigt / 2) + 3);
	}
	else if (line_num == 5) {
		Gotoxy(plate_width + 4, (plate_heigt / 2) + 3);
	}
	else if (line_num == 3) {
		Gotoxy(plate_width - 1, (plate_heigt / 2) + 3);
	}
	

	printf("  ■");printf("=기본  ");
	Color(BLUE); printf("■"); Color(WHITE);printf("=체크  "); Color(RED);printf("■");Color(WHITE); printf("=봉쇄");
	Color(WHITE);

	

	
	for (int i = 0; i < (2 * plate_width) + 22 + (2 * line_num) ; i++){
		Gotoxy(0+i, plate_heigt + 2);
		printf("─");
		Gotoxy(0+i, plate_heigt + 7);
		printf("─");
	}
}


//1면 플레이어 승, -1면 컴퓨터 승! 2면 무승부!
void Game_result(int result) {

	if (line_num == 4) {
		Gotoxy(plate_width + 9, 1);
	}
	else if (line_num == 5) {
		Gotoxy(plate_width + 11, 1);
	}
	else if (line_num == 3) {
		Gotoxy(plate_width + 6, 1);
	}
		

	if (result == 1) {
		Color(BLUE);
		printf("  [ 플레이어 ]");
	}
	else if(result ==-1){
		Color(RED);
		printf("  [ 컴ㅡ퓨터 ]");
	}
	else {
		Color(WHITE);
		printf("                   ");
	}
	
	if (line_num == 4) {
		Gotoxy(plate_width + 11, 3);
	}
	else if (line_num == 5) {
		Gotoxy(plate_width + 14, 3);
	}
	else if (line_num == 3) {
		Gotoxy(plate_width + 10, 3);
	}

	Color(YELLOW);
	if (result == 1 || result == -1) printf("! 승리 !");
	else printf("!무승부!");
	

	Color(WHITE);
	if (line_num == 4) {
		Gotoxy(plate_width + 1, (plate_heigt / 2) + 3);
	}
	else if (line_num == 5) {
		Gotoxy(plate_width + 4, (plate_heigt / 2) + 3);
	}
	else if (line_num == 3) {
		Gotoxy(plate_width - 1, (plate_heigt / 2) + 3);
	}

	printf("  ■");printf("=기본  ");
	Color(BLUE); printf("■"); Color(WHITE);printf("=체크  "); Color(RED);printf("■");Color(WHITE); printf("=봉쇄");
		
	Gotoxy(plate_width + line_num + 4, plate_heigt + 1);
	if (result == 1) {
		Color(YELLOW);
		printf("승리 하셨습니다");
	}
	else if (result == -1) {
		Color(RED);
		printf("패배 하셨습니다");
	}
	else {
		Color(YELLOW);
		printf("무ㅡ승부 입니다");
	}
	Color(WHITE);

	for (int i = 0; i < (2 * plate_width) + 22 + (2 * line_num); i++) {
		Gotoxy(0 + i, plate_heigt + 2);
		printf("─");
		Gotoxy(0 + i, plate_heigt + 7);
		printf("─");
	}
}

//컴퓨터 겉영역 설정  0이면 '?', -1이면 '불능' -2이면 '체크' 체크는 숫자로 표현
void Set_com_plate(int * c_plate, int * c_plate2){

	
	for (int i = 0; i < (line_num * line_num); i++) {
		if (c_plate[i] == -1) {
			c_plate2[i] = -1;
		}
		else if (c_plate[i] == -2) {
			c_plate2[i] = -2;
		}
	}
}


void Reset_text() {

	Gotoxy(plate_width + 1, 1);
	printf("                           ");
	Gotoxy(plate_width + 1, (plate_heigt / 2) + 3);
	printf("                         ");
	Gotoxy(plate_width + line_num, (plate_heigt / 2) + 1);
	printf("                         ");
	Gotoxy(5, plate_heigt + 4);
	printf("                                                  ");
	Gotoxy(5, plate_heigt + 5);
	printf("                                                  ");
	Gotoxy(5, plate_heigt + 6);
	printf("                                                  ");
}


int Player_select(int * selected_num, int game_turn) {
	int input;

	do {

		bool check = true; // 예외상태일 때 false로 전환
		Gotoxy(51, plate_heigt + 4);
		printf("                   ");
		Gotoxy(51, plate_heigt + 4);
		scanf_s("%d", &input);

		if (1 <= input && input <= (line_num * line_num)) {
			if (getchar() == '\n') {

				for (int i = 0; i <= (game_turn-1); i++) {

					if (input == selected_num[i]) {
						check = false;
						break;
					}
				}
				//check이 true일때 
				if (check) {
					break;
				}
			}
		}
		else {
			while (getchar() != '\n');
		}

		Gotoxy(5, plate_heigt + 6);
		Color(RED);
		printf("선택 되지 않은 1 - %d까지의 정수만 입력 해 주세요.", (line_num * line_num));
		Color(WHITE);
	} while (1);
	Gotoxy(5, plate_heigt + 6);
	printf("                                                                  ");

	return input;
}


//플레이트 순서에 따라 체크 or 봉쇄가 되니까 주의하자
void Check_num(int * check_plate, int * block_plate, int select_num){

	for (int i = 0; i < (line_num * line_num); i++) {

		if (check_plate[i] == select_num) {
			check_plate[i] = 0;
		}
		if (block_plate[i] == select_num) {
			block_plate[i] = -100;
		}
	}
}


//true반환시 빙고가 있음, false반환시 빙고가 없음
bool Check_bingo(int * plate) {

	bool result = false;
	int temp = 0;

	//세로검사
	for (int i = 0; i < line_num; i++) {
		
		if (plate[i] == 0) {
			
			for (int j = (i + line_num); j <= i + (line_num * (line_num - 1)); j+= line_num) {
				temp += plate[j];
			}

			if (temp == 0) {
				result = true;
				return result;
			}
			else {
				temp = 0;
				result = false;
			}
		}
		else {
			result = false;
		}
	}
	//가로 검사
	temp = 0;
	for (int i = 0; i <= line_num * (line_num-1); i += line_num) {

		if (plate[i] == 0) {

			//i가 4면 ; 
			//j = 5; j < 7 ; ㅓ++
			for (int j = i + 1; j <= i + (line_num - 1); j++) {
				temp += plate[j];
			}

			if (temp == 0) {
				result = true;
				return result;
			}
			else {
				temp = 0;
				result = false;
			}
		}
		else {
			result = false;
		}
	}

	//대각선 검사
	temp = 0;

	if (plate[0] == 0) {

		for (int i = 0; i <= (line_num + 1) * (line_num - 1); i+= (line_num +1)) {
			temp += plate[i];
		}

		if (temp == 0) {
			result = true;
			return result;
		}
		else {
			temp = 0;
			result = false;
		}
	}
	else {
		result = false;
	}

	temp = 0;
	if (plate[line_num - 1] == 0) {

		//i = 3; i <= 5 * 3
		for (int i = (line_num - 1); i <= line_num * (line_num - 1); i += (line_num - 1)) {
			temp += plate[i];
		}

		if (temp == 0) {
			result = true;
			return result;
		}
		else {
			temp = 0;
			result = false;
		}
	}
	else {
		result = false;
	}

	return result;
}



int Com_select(int * selected_num, int game_turn) {
	
	bool end = false; //이미 선택했는지 확인
	int select = 0;
	
	do {

		bool check = true; // 예외상태일 때 false로 전환

		select = (rand() % (line_num * line_num)) + 1;

				for (int i = 0; i <= (game_turn - 1); i++) {

					if (select == selected_num[i]) {
						check = false;
						break;
					}
				}
				//check이 true일때 
				if (check) {
					break;
				}
	} while (1);

	return select;
}



int kb(int kb_result) { //1,2,3,4반환시 계속 입력 5반환시 게임시작 6반환시 게임종료

	int key;

	key = _getch(); //키보드의 아스키값은 224 후에 다음 x 로 확장문자임

	if (key == 224) {

		key = _getch();

		switch (key) {
		case 72:
			//printf("위방향키\n");
			kb_result = 1;
			return 1;
		case 75:
			//printf("왼쪽방향키\n");
			kb_result = 3;
			return 3;
		case 77:
			//printf("오른쪽방향키\n");
			kb_result = 4;
			return 4;
		case 80:
			//printf("아래방향키\n");
			kb_result = 2;
			return 2;
		}
		return 0;
	}
	else if (key == 13) { //엔터 입력시

		if (kb_result == 1) {

			return 5;
		}
		else if (kb_result == 2) {

			return 6;
		}
	}
	else return kb_result;
}


void Ingame() {

	//난수 초기화
	srand((unsigned int)time(NULL));

	int com_select = 0;//컴퓨터 선택 index
	int game_turn = -1;//게임 전체 턴 수 

	//선택한 숫자들 저장 영역
	int * selected_num;
	selected_num = (int *)calloc(sizeof(int), line_num*line_num);

	//플레이어 실영역 설정
	int * player_plate;
	player_plate = (int *)calloc(sizeof(int), line_num*line_num);
	//플레이어 겉영역 설정
	int * player_plate2;
	player_plate2 = (int *)calloc(sizeof(int), line_num*line_num);
	Swap(player_plate, player_plate2);

	//컴퓨터 실영역 설정
	int * com_plate;
	com_plate = (int *)calloc(sizeof(int), line_num*line_num);
	//컴퓨터 겉영역 설정  0이면 '?', -1이면 '불능' -2이면 '체크'
	int * com_plate2;
	com_plate2 = (int *)calloc(sizeof(int), line_num*line_num);
	Swap(com_plate, com_plate2);

	//인게임--
	//빙고판 그리는 부분
	Draw_plate(player_plate, player_plate2, com_plate, com_plate2);
	Draw_interface();

	//---------------------------------------------------------------------------------------------------------------------------------------
	//인게임 시작
	while (1) {
		//플레이어 턴 -----------------------------------------------------
		
		game_turn++;//턴수 증가

		if (game_turn == (line_num * line_num)) {
			Draw_plate(player_plate, player_plate2, com_plate, com_plate2);
			Game_result(2);
			break;
		}

		who_turn = true;
		Draw_interface();
		
		Gotoxy(5, plate_heigt + 4);
		printf("플레이어 턴 입니다.               숫자 입력 : ");

		selected_num[game_turn] = Player_select(selected_num, game_turn); //숫자 입력
		Check_num(player_plate, com_plate, selected_num[game_turn]); // 실영역에 계산하기 1번째 매개변수가 체크, 2번째가 봉쇄
		Draw_plate(player_plate, player_plate2, com_plate, com_plate2);//계산한거 출력
		Draw_interface();

		if (Check_bingo(player_plate)) {
			Color(YELLOW);
			Gotoxy(plate_width + line_num + 4, plate_heigt + 4);
			printf("!! B I N G O !!");
			Color(WHITE);
			Sleep(1000);

			Draw_plate(player_plate, player_plate2, com_plate, com_plate2);
			Game_result(1);
			break;

		} //빙고가 존재하는지 확인! TODO 게임 종료 만들기

		//컴퓨터 턴 -----------------------------------------------------
		game_turn++;//턴수 증가

		if (game_turn == (line_num * line_num)) {
			Draw_plate(player_plate, player_plate2, com_plate, com_plate2);
			Game_result(2);
			break;
		}


		who_turn = false;
		Draw_interface();
		Gotoxy(5, plate_heigt + 4);
		printf("컴ㅡ퓨터 턴 입니다.               숫자 선택중...");
		Sleep(1000);
		selected_num[game_turn] = Com_select(selected_num, game_turn); //컴퓨터 숫자 입력
		Check_num(com_plate, player_plate, selected_num[game_turn]); // 실영역에 계산하기 1번째 매개변수가 체크, 2번째가 봉쇄
		Draw_plate(player_plate, player_plate2, com_plate, com_plate2);//계산한거 출력
		Draw_interface();
		Gotoxy(5, plate_heigt + 4);
		printf("컴퓨터가 %d를 선택했습니다.", selected_num[game_turn]);
		Sleep(1000);

		if (Check_bingo(com_plate)) {
			
			Color(YELLOW);
			Gotoxy(0, plate_heigt + 4);
			printf("                                              ");
			Gotoxy(plate_width + line_num + 4, plate_heigt + 4);
			printf("!! B I N G O !!");
			Color(WHITE);
			Sleep(1000);
			Draw_plate(player_plate, player_plate2, com_plate, com_plate2);
			Game_result(-1);
			break;
		} //빙고가 존재하는지 확인! TODO 게임 종료 만들기
	}
	//---------------------------------------------------------------------------------------------------------------------------------------

	//동적할당 해제 ★★★ 중요하당 안한뻔햇음ㅋㅋ
	free(player_plate);
	free(player_plate2);
	free(com_plate);
	free(com_plate2);

	Color(7);
	Gotoxy(plate_width + line_num + 7, plate_heigt + 4);
	printf("다시 시작");

	Gotoxy(plate_width + line_num + 3, plate_heigt + 4);
	printf("▶");

	Color(8); //회색
	Gotoxy(plate_width + line_num + 7, plate_heigt + 6);
	printf("메인 메뉴");
}



bool Result_menu() {

	int kb_result = 1;

	while (kb_result == 1 || kb_result == 2) {
		kb_result = kb(kb_result);

		if (kb_result == 1) {

			Color(7);
			Gotoxy(plate_width + line_num + 7, plate_heigt + 4);
			printf("다시 시작");

			Gotoxy(plate_width + line_num + 3, plate_heigt + 4);
			printf("▶");

			Color(8); //회색
			Gotoxy(plate_width + line_num + 7, plate_heigt + 6);
			printf("메인 메뉴");

			Gotoxy(plate_width + line_num + 3, plate_heigt + 6);
			printf("   ");
		}
		else if (kb_result == 2) {

			Color(GRAY);
			Gotoxy(plate_width + line_num + 7, plate_heigt + 4);
			printf("다시 시작");

			Gotoxy(plate_width + line_num + 3, plate_heigt + 4);
			printf("   ");

			Color(WHITE); //회색
			Gotoxy(plate_width + line_num + 7, plate_heigt + 6);
			printf("메인 메뉴");

			Gotoxy(plate_width + line_num + 3, plate_heigt + 6);
			printf("▶");
		}
	}

	if (kb_result == 5) { //다시시작하기 
		return true;
	}
	else if (kb_result == 6) { //메인메뉴로
		return false;
	}
}


void Title() {

		Gotoxy(MAP_WIDTH / 2 - 10, 5);
		printf("〓〓〓〓〓〓〓〓〓〓〓〓");

		Gotoxy(24, 7);
		printf("B I N G O!");

		Gotoxy(MAP_WIDTH / 2 - 10, 9);
		printf("〓〓〓〓〓〓〓〓〓〓〓〓");

		move_line_num();
		
		Color(WHITE);
		Gotoxy(MAP_WIDTH / 2 - 3, 14);
		printf("게임 시작");

		Color(GRAY);
		Gotoxy(MAP_WIDTH / 2 - 3, 17);
		printf("게임 종료");


		int kb_result = 1;
		int kb_sub = 1; // 0이 3x3, 1이 4x4 ,2가 5x5

		while (kb_result == 1 || kb_result == 2 || kb_result == 3 || kb_result == 4 ) {
			kb_result = kb(kb_result);

			if (kb_result == 1) {
				Color(WHITE);
				Gotoxy(MAP_WIDTH / 2 - 3, 14);
				printf("게임 시작");

				Color(GRAY);
				Gotoxy(MAP_WIDTH / 2 - 3, 17);
				printf("게임 종료");
				
			}
			else if (kb_result == 2) {
				Color(GRAY);
				Gotoxy(MAP_WIDTH / 2 - 3, 14);
				printf("게임 시작");

				Color(WHITE);
				Gotoxy(MAP_WIDTH / 2 - 3, 17);
				printf("게임 종료");
				
			}
			else if (kb_result == 3) {
				if (line_num == 4 || line_num == 5) {
					line_num --;
					move_line_num();
				}
			}
			else if (kb_result == 4) {
				if (line_num == 3 || line_num == 4) {
					line_num ++;
					move_line_num();
				}
			}

		}

		if (kb_result == 5) { //r게임 시작
			game_start = true;
		}
		else if (kb_result == 6) { //종료
			game_start = false;
		}


		Draw_map();
}

void Draw_map(void) { //맵 테두리 그리는 함수  보니까 순서도 중요했다.. 바닥을 마지막에 깔아야함
	int i;

	Gotoxy(MAP_X, MAP_Y);

	printf("┌");
	for (i = MAP_X + 1;i < MAP_WIDTH - 1;i++) {
		printf("━");
	}
	printf("┐");


	for (i = MAP_Y + 1;i < MAP_HEIGHT;i++) {
		Gotoxy(MAP_X, i);
		printf("│");
		Gotoxy(MAP_WIDTH - 1, i);
		printf("│");

	}

	Gotoxy(MAP_X, MAP_HEIGHT);

	printf("└");
	for (i = MAP_X + 1;i < MAP_WIDTH - 1;i++) {
		printf("━");
	}
	printf("┘ ");
}



void move_line_num() {

	Gotoxy(MAP_WIDTH / 2 - 10, 12);
	printf("                              ");

	if (line_num == 4) {
		Gotoxy(MAP_WIDTH / 2 - 10, 12);
		Color(YELLOW);
		printf("◀");
		Color(GRAY);
		printf(" 3x3");
		Color(WHITE);
		printf("   4 x 4   ");
		Color(GRAY);
		printf("5x5 ");
		Color(YELLOW);
		printf("▶");
	}
	else if (line_num == 3) {
		Gotoxy(MAP_WIDTH / 2 - 10, 12);
		Color(GRAY);
		printf("◀");
		printf("    ");
		Color(WHITE);
		printf("   3 x 3   ");
		Color(GRAY);
		printf("4x4 ");
		Color(YELLOW);
		printf("▶");
	}
	else if (line_num == 5) {
		Gotoxy(MAP_WIDTH / 2 - 10, 12);
		Color(YELLOW);
		printf("◀");
		Color(GRAY);
		printf(" 4x4");
		Color(WHITE);
		printf("   5 x 5   ");
		Color(GRAY);
		printf("    ");
		printf("▶");
	}
}