#define _CRT_SECURE_NO_WARNINGS    
#include <stdio.h>
#include <string.h>    // strcpy 함수 (양쪽의 문자열을 같아지게 하는 함수)
#include <stdlib.h>    // rand 함수 (랜덤 수 생성 함수)
#include <time.h>      // time 함수 (시간을 사용)
#include <Windows.h>   // Sleep, system 함수 (편의성을 위해 사용)

int stagelevel = 0;     //스테이지 레벨
int motion = 0;         //플레이어 행동
int monsterrand = 0;    //몬스터 행동 랜덤값
int talkrand = 0;       //대화 랜덤값
int chat_Monster = 0;   //몬스터 대사 랜덤값
int chat_Player = 0;    //몬스터 대사 랜덤값

int gameStart = 1;      //게임 시작값


void f_PrintPlayer(struct Player* player);                                      //플레이어 정보 출력
void f_PrintMonster(struct Monster* monster);                                   //몬스터 정보 출력
void f_PlayerInput(struct Player* player, struct Monster* monster);             //플레이어 모션
void f_MonsterInput(struct Player* player, struct Monster* monster);            //몬스터 모션
void f_present(struct Player* player);                      //스테이지 클리어 시 보상
void f_GameStart();                                         //게임 시작
void f_GameOver();                                          //게임 오버
void f_GameClear();                                         //게임 클리어
void f_StageStart(struct Player* player, struct Monster* monster);      //스테이지 시작
void f_GameInform();                                        //게임 정보 출력
void f_GameInformp();                                       //게임 제작한 사람 정보 출력


struct Player           //플레이어 구조체 선언
{

    char name[21];              //이름
    int health;                 //체력
    int hit;                    //공격력
    int playercritical;         //강화공격
    int playerheal;             //플레이어 힐량
    char print_Player[3][157];   //플레이어 대사

};

struct Monster          //적 구조체 선언
{

    char name[31];                  //적 이름
    int health;                     //적 체력
    int hit;                        //적 공격력
    char print_Monster_info[100];    //적 정보
    char print_Monster[3][123];      //적 대사

};

int main()
{
    struct Player player_s;
    struct Player* player = &player_s;          // 포인터로 할당

    struct Monster monster_s[10];
    struct Monster* monster[10];                // 포인터로 할당

    int size_Monster = sizeof(monster) / sizeof(monster[0]);

    for (int i = 0; i < size_Monster; i++)         //사이즈 오프로 크기 구하기
    {
        monster[i] = &monster_s[i];
    }

    /* 정보 초기화 */
    strcpy(player->name, "플레이어");
    player->health = 30;
    player->hit = 7;
    player->playercritical = 3;
    player->playerheal = 3;
    strcpy(player->print_Player[0], "각오해라!");
    strcpy(player->print_Player[1], "내 갈길을 막지마라!");
    strcpy(player->print_Player[2], "죽여주마!");

    strcpy(monster[0]->name, "슬라임");
    monster[0]->health = 10;
    monster[0]->hit = 3;
    strcpy(monster[0]->print_Monster_info, "슬라임이 통통거리며 나타났다!\n...뭔가 맛있어 보인다.");
    strcpy(monster[0]->print_Monster_info, "슬라임이 통통거리며 나타났다!\n...뭔가 맛있어 보인다.");
    strcpy(monster[0]->print_Monster[0], "...(뭐라는지 모르겠다.)");
    strcpy(monster[0]->print_Monster[1], "...(입이 없어 말을 못하는듯 하다.)");
    strcpy(monster[0]->print_Monster[2], "...(하고싶은 말이 있는 것 같다.)");

    strcpy(monster[1]->name, "습지 고블린");
    monster[1]->health = 14;
    monster[1]->hit = 7;
    strcpy(monster[1]->print_Monster_info, "나무 뒤에서 습지 고블린이 나타났다!\n기분나쁘게 웃고있다.");
    strcpy(monster[1]->print_Monster[0], "키키킼!(역시나 기분나쁘게 웃는다.)");
    strcpy(monster[1]->print_Monster[1], "캬아앜!(위협하고 있는것 같다.)");
    strcpy(monster[1]->print_Monster[2], "히히힣!(쯧... 더럽다.)");

    strcpy(monster[2]->name, "킹슬라임");
    monster[2]->health = 20;
    monster[2]->hit = 7;
    strcpy(monster[2]->print_Monster_info, "킹슬라임이 스멀스멀 나타났다!\n왕관은 어디서 난거지?");
    strcpy(monster[2]->print_Monster[0], "...(역시나 말을 못한다.)");
    strcpy(monster[2]->print_Monster[1], "...(몸을... 부풀린다?)");
    strcpy(monster[2]->print_Monster[2], "..(빠르게 처치하자.)");

    strcpy(monster[3]->name, "리저드맨");
    monster[3]->health = 23;
    monster[3]->hit = 10;
    strcpy(monster[3]->print_Monster_info, "늪지에서 리저드맨이 나타났다!\n얼굴이 도마뱀인게 굉장히 못생겼다.");
    strcpy(monster[3]->print_Monster[0], "여기서...나가라..!(아무래도 영역을 침범한듯 하다.)");
    strcpy(monster[3]->print_Monster[1], "키아아아아!(위협하고 있다.)");
    strcpy(monster[3]->print_Monster[2], "...(조용히 창을 들고 자세를 잡고있다.)");

    strcpy(monster[4]->name, "크로커다일");
    monster[4]->health = 28;
    monster[4]->hit = 12;
    strcpy(monster[4]->print_Monster_info, "앞의 호수에서 크로커다일이 나타났다!\n저 가죽... 비쌀것 같다.");
    strcpy(monster[4]->print_Monster[0], "크르르르...(입을 벌리고 싸울준비를 하고있다.)");
    strcpy(monster[4]->print_Monster[1], "크아아아아!(소리를 지르며 위협하고 있다.)");
    strcpy(monster[4]->print_Monster[2], "크르르르...(조심해야겠다...)");

    strcpy(monster[5]->name, "물의 정령");
    monster[5]->health = 31;
    monster[5]->hit = 15;
    strcpy(monster[5]->print_Monster_info, "반짝이는 원형의 물의 정령이 나타났다!\n사실 정령인지는 모르겠다.");
    strcpy(monster[5]->print_Monster[0], "...(어... 말을 못하는건가?)");
    strcpy(monster[5]->print_Monster[1], "...(반짝거리고 있다.아무래도 나가라는 듯.)");
    strcpy(monster[5]->print_Monster[2], "...(주위에 마법진이 생기고 있다.)");

    strcpy(monster[6]->name, "드레이크");
    monster[6]->health = 39;
    monster[6]->hit = 17;
    strcpy(monster[6]->print_Monster_info, "멍청해 보이는 드레이크가 나타났다!\n저래봬도 용족이니 방심하지 말자.");
    strcpy(monster[6]->print_Monster[0], "크르르릉!(뒤에 식탁이 있다. 식사시간을 방해한것 같다.)");
    strcpy(monster[6]->print_Monster[1], "크르르르...(안맞도록 조심하자.)");
    strcpy(monster[6]->print_Monster[2], "크르르르...(입에 피가 있다. 식사시간을 방해한것 같다.)");

    strcpy(monster[7]->name, "캇파");
    monster[7]->health = 50;
    monster[7]->hit = 18;
    strcpy(monster[7]->print_Monster_info, "오이를 들고있는 캇파가 나타났다.!\n...저걸로 후려치진 않겠지?");
    strcpy(monster[7]->print_Monster[0], "뭐야 너는!(나를 보고 놀란듯 하다.)");
    strcpy(monster[7]->print_Monster[1], "...퉷(굉장히 화가 난것 같다.)");
    strcpy(monster[7]->print_Monster[2], "저리 꺼져!(오이를 들고 위협하고있다. ...진짜 저게 무기인가?)");

    strcpy(monster[8]->name, "이끼 골렘");
    monster[8]->health = 300;
    monster[8]->hit = 10;
    strcpy(monster[8]->print_Monster_info, "쿵쿵거리는 소리와 함께 땅이 울린다...\n이끼 골렘이 나타났다!");
    strcpy(monster[8]->print_Monster[0], "...쿵(움직일때마다 땅이 울리고 있다.)");
    strcpy(monster[8]->print_Monster[1], "..쿵..쿵(점점 다가오고 있다.)");
    strcpy(monster[8]->print_Monster[2], "..쿵..쿵..쿵(중심을 잡기 힘들다.)");

    strcpy(monster[9]->name, "서펜트");
    monster[9]->health = 75;
    monster[9]->hit = 25;
    strcpy(monster[9]->print_Monster_info, "엄청난 크기의 수룡이 나타났다!\n던전의 끝이 보이는듯 하다.");
    strcpy(monster[9]->print_Monster[0], "감히 인간이 발을 들일 곳이 아니다!(저 놈만 잡으면 끝난다.)");
    strcpy(monster[9]->print_Monster[1], "썩 꺼져라!(반드시 죽이겠다.)");
    strcpy(monster[9]->print_Monster[2], "크아아아아!!(울음소리만 들어도 몸이 떨리고 있다. 긴장하도록 하자.)");
    /* 정보 초기화 */

    do
    {
        f_GameStart();

    } while (gameStart);

    for (stagelevel = 0; stagelevel < size_Monster; stagelevel)
    {
        f_StageStart(player, monster[stagelevel]);       //플레이어와 몬스터의 정보로 게임 시작
    }

    f_GameClear();

    return 0;
}

void f_PrintPlayer(struct Player* player)               //플레이어 정보 출력
{
    printf("=========================================\n");
    printf("==                                     ==\n");
    printf("        이름 : %s, 체력: %d\n", player->name, player->health);
    printf("==                                     ==\n");
    printf("=========================================\n\n");
}

void f_PrintMonster(struct Monster* monster)            //몬스터 정보 출력
{
    printf("=========================================\n");
    printf("==                                     ==\n");
    printf("  이름 : %s, 체력 : %d, 공격력 : %d\n", monster->name, monster->health, monster->hit);
    printf("==                                     ==\n");
    printf("=========================================\n\n");
}

void f_PlayerInput(struct Player* player, struct Monster* monster)      //플레이어 모션
{
    printf("\n어떤 행동을 할까?\n\n1[기본공격] 2[강화공격] 3[힐] 4[대화를 시도한다] : ");
    scanf("%d", &motion);

    if (motion != 1 && motion != 2 && motion != 3 && motion != 4)
    {
        printf("\n그런 행동은 없다!\n\n");
        f_PlayerInput(player, monster);
    }
    else
    {
        switch (motion)
        {
        case 1:

            printf("\n=========================================\n");
            printf("==                                     ==\n");
            printf("     기본 공격을 사용하였다!\n");
            printf("==                                     ==\n");
            printf("=========================================\n");
            Sleep(1000);

            printf("==                                     ==\n");
            printf("     %d의 데미지를 주었다!\n", player->hit);
            printf("==                                     ==\n");
            printf("=========================================\n\n");
            Sleep(1500);

            monster->health -= player->hit;

            break;

        case 2:

            printf("\n=========================================\n");
            printf("==                                     ==\n");
            printf("    강화 공격을 사용하였다!\n");
            printf("==                                     ==\n");
            printf("=========================================\n");
            Sleep(1000);

            printf("==                                     ==\n");
            printf("    %d의 데미지를 주었다\n", player->playercritical);
            printf("==                                     ==\n");
            printf("=========================================\n");
            Sleep(1500);


            monster->health -= player->playercritical;
            player->playercritical++;
            printf("==                                     ==\n");
            printf("  강화공격의 공격력이 1 상승했다. 현재 %d\n", player->playercritical);
            printf("==                                     ==\n");
            printf("=========================================\n\n");
            Sleep(1500);

            break;

        case 3:

            printf("\n===================================\n");
            printf("==                               ==\n");
            printf("    체력을 회복한다.\n");
            printf("==                               ==\n");
            printf("===================================\n");
            Sleep(1000);

            printf("==                               ==\n");
            printf("    %d의 체력을 회복했다.\n", player->playerheal);
            printf("==                               ==\n");
            printf("===================================\n\n");
            Sleep(1500);

            player->health += player->playerheal;

            break;

        case 4:

            printf("==============================\n");
            printf("==                          ==\n");
            printf("   당신은 대화를 시도한다.\n");
            printf("   실패했다.\n");
            printf("==                          ==\n");
            printf("==============================\n\n");

            break;
        }
    }
}

void f_MonsterInput(struct Player* player, struct Monster* monster)      //몬스터 모션
{
    printf("\n몬스터 동작\n\n");

    srand((unsigned int)time(NULL));
    monsterrand = rand() % 10;

    if (monsterrand >= 3)
    {

        printf("===========================================\n");
        printf("==                                       ==\n");
        printf("   %s의 공격!\n", monster->name);
        printf("==                                       ==\n");
        printf("===========================================\n");
        Sleep(1000);
        printf("==                                       ==\n");
        printf("   %s에 의해 %d의 데미지를 입었다\n", monster->name, monster->hit);
        printf("==                                       ==\n");
        printf("===========================================\n\n");
        Sleep(2000);

        system("cls");

        player->health -= monster->hit;
    }
    else if (monsterrand >= 0)
    {

        printf("=======================================\n");
        printf("==                                   ==\n");
        printf("  %s은(는) 아무것도 하지 않았다.\n", monster->name);
        printf("==                                   ==\n");
        printf("=======================================\n\n");
        Sleep(2000);

        system("cls");
    }
}

void f_present(struct Player* player)       //스테이지 클리어 시 보상
{
    int upStat = 0;

    Sleep(1000);

    printf("선택보상\n");
    Sleep(1000);

    printf("\n증가시킬 능력치를 선택하세요.\n");
    printf("이외의 선택 시 아무런 능력치도 오르지 않습니다.\n\n");
    printf("[1]기본공격[2]체력[3]회복량 : ");
    scanf("%d", &upStat);

    switch (upStat)
    {
    case 1:

        printf("\n======================================\n");
        printf("==                                  ==\n");
        printf("      공격력이 3 올랐습니다.\n");
        printf("==                                  ==\n");
        printf("======================================\n");

        player->hit += 3;

        break;

    case 2:

        printf("\n======================================\n");
        printf("==                                  ==\n");
        printf("      체력이 7 올랐습니다.\n");
        printf("==                                  ==\n");
        printf("======================================\n");

        player->health += 7;

        break;

    case 3:

        printf("\n======================================\n");
        printf("==                                  ==\n");
        printf("     체력 회복량이 3 올랐습니다.\n");
        printf("==                                  ==\n");
        printf("======================================\n");

        player->playerheal += 3;

        break;

    default:

        printf("\n======================================\n");
        printf("==                                  ==\n");
        printf("   아무 변화도 없습니다.\n");
        printf("==                                  ==\n");
        printf("======================================\n");

        break;
    }
}

void f_GameStart()      //게임 시작
{
    int select = 0;

    printf("        ========================================================\n");
    printf("        ===                                                  ===\n");
    printf("        ===                                                  ===\n");
    printf("        ===             로그라이크 텍스트 rpg                ===\n");
    printf("        ===                                                  ===\n");
    printf("        ===                                                  ===\n");
    printf("        ========================================================\n\n");


    printf("선택지 1.게임 시작\n");
    printf("       2.게임 정보\n ");
    printf("      3.만든 사람들\n");
    scanf("%d", &select);

    switch (select)
    {
    case 1:

        printf("        ==========================\n");
        printf("        ==                      ==\n");
        printf("        ==  게임을 시작합니다!  ==\n");
        printf("        ==                      ==\n");
        printf("        ==========================\n");
        Sleep(1000);

        gameStart = 0;

        system("cls");

        break;

    case 2:
        f_GameInform();            //게임 정보 출력

        break;

    case 3:
        f_GameInformp();           //게임 제작한 사람 정보 출력

        break;

    default:
        printf("다시 입력해주세요.\n\n");

        break;
    }
}


void f_GameOver()       //게임 오버
{
    system("cls");
    printf("\n===================================================\n");
    printf("==                                               ==\n");
    printf("       플레이어의 체력이 0이 되어버렸습니다.\n");
    printf("     당신은 던전의 끝에 도달하지 못하였습니다...\n");
    printf("==                                               ==\n");
    printf("===================================================\n");


    exit(0);
}

void f_GameClear()      //게임 클리어
{
    system("cls");
    printf("\n===============================================\n");
    printf("==                                           ==\n");
    printf("              축하드립니다!\n");
    printf("   소원을 이룰 수 있다는 소문은 진짜일까요?\n");
    printf("==                                           ==\n");
    printf("===============================================\n");

    exit(0);
}

void f_StageStart(struct Player* player, struct Monster* monster)       //스테이지 시작
{
    printf("\n제%d 구역에 도착하였다.\n\n", stagelevel + 1);
    Sleep(1000);

    printf("\n%s\n", monster->print_Monster_info);
    Sleep(2000);

    while (monster->health > 0)
    {
        srand((unsigned int)time(NULL));                  // 랜덤 함수 초기화

        chat_Player = rand() % 3;           //0부터 2까지의 값 중 랜덤으로 한 숫자를 변수에 저장
        chat_Monster = rand() % 3;

        printf("\n플레이어 : ");
        printf("%s\n\n", player->print_Player[chat_Player]);

        f_PrintPlayer(player);              //플레이어 정보 출력

        printf("%s : ", monster->name);
        printf("%s\n\n", monster->print_Monster[chat_Monster]);
        f_PrintMonster(monster);            //몬스터 정보 출력

        f_PlayerInput(player, monster);     //플레이어 행동

        if (monster->health > 0)
        {
            f_MonsterInput(player, monster);
        }

        if (player->health <= 0)
        {
            f_GameOver();
        }
    }

    printf("\n적을 쓰러뜨렸습니다.\n\n");
    Sleep(1000);

    printf("보상 지급\n");
    Sleep(1000);

    printf("\n======================================\n");
    printf("==                                  ==\n");
    printf("        체력이 3 올랐습니다.\n");
    printf("==                                  ==\n");
    printf("======================================\n\n");
    player->health += 3;

    f_present(player);
    Sleep(1000);

    printf("==                                  ==\n");
    printf("   다음 스테이지로 이동합니다.\n");
    printf("==                                  ==\n");
    printf("======================================\n");
    Sleep(1500);

    system("cls");

    stagelevel++;
}

void f_GameInform()     //게임 정보 출력
{
    system("cls");
    printf("        =====================================================================\n");
    printf("        ===                                                               ===\n");
    printf("        ===               이 던전 안에는 몬스터가 많습니다.               ===\n");
    printf("        ===  던전의 끝에 도달하면 소원을 이룰 수 있다는 소문이 있습니다.  ===\n");
    printf("        ===             과연 당신은 끝까지 도달할 수 있을까요?            ===\n");
    printf("        ===                                                               ===\n");
    printf("        =====================================================================\n");

}

void f_GameInformp()    //게임 제작한 사람 정보 출력
{
    system("cls");
    //개인정보
}