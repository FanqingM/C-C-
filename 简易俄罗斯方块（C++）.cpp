
//�ο�windows������������CSDN��������C++��д����˹���飨��Ҫ�ǽ�����Ʋ��֣���Ϸ���������Լ���ɣ�


#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
using namespace std;
int map[21][12];
/*
����ԭ����������ά���������淽���������Ϣ
���Ƿ�����Ϣʹ�õĺ�����Ҫ����ת���ƶ�����
���ʹ����ά����Ļ�������ת����������Ҫ���ݷ���������������Ƿ������ת���ж�
�޷�ʵ�ֽϴ�ļ򻯣�����Ȼ���������ģʽ
*/
int block00[4][4] = { { 10,0,0,0 },{ 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 } };
int block01[4][4] = { { 11,0,1,0 },{ 0,0,1,0 },{ 0,0,1,0 },{ 0,0,1,0 } };
int block02[4][4] = { { 12,0,0,0 },{ 0,0,0,0 },{ 1,1,1,0 },{ 0,1,0,0 } };
int block03[4][4] = { { 13,0,0,0 },{ 0,1,0,0 },{ 1,1,0,0 },{ 0,1,0,0 } };
int block04[4][4] = { { 14,0,0,0 },{ 0,0,0,0 },{ 0,1,0,0 },{ 1,1,1,0 } };
int block05[4][4] = { { 15,0,0,0 },{ 0,1,0,0 },{ 0,1,1,0 },{ 0,1,0,0 } };
int block06[4][4] = { { 16,0,0,0 },{ 0,0,0,0 },{ 1,1,1,0 },{ 1,0,0,0 } };
int block07[4][4] = { { 17,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 } };
int block08[4][4] = { { 18,0,0,0 },{ 0,0,0,0 },{ 0,0,1,0 },{ 1,1,1,0 } };
int block09[4][4] = { { 19,0,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 0,1,1,0 } };
int block10[4][4] = { { 20,0,0,0 },{ 0,0,0,0 },{ 1,1,1,0 },{ 0,0,1,0 } };
int block11[4][4] = { { 21,0,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 1,1,0,0 } };
int block12[4][4] = { { 22,0,0,0 },{ 0,0,0,0 },{ 1,0,0,0 },{ 1,1,1,0 } };
int block13[4][4] = { { 23,0,0,0 },{ 0,1,1,0 },{ 0,1,0,0 },{ 0,1,0,0 } };
int block14[4][4] = { { 24,0,0,0 },{ 0,0,0,0 },{ 0,1,1,0 },{ 1,1,0,0 } };
int block15[4][4] = { { 25,0,0,0 },{ 1,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 } };
int block16[4][4] = { { 26,0,0,0 },{ 0,0,0,0 },{ 1,1,0,0 },{ 0,1,1,0 } };
int block17[4][4] = { { 27,0,0,0 },{ 0,0,1,0 },{ 0,1,1,0 },{ 0,1,0,0 } };
int block18[4][4] = { { 28,0,0,0 },{ 0,0,0,0 },{ 1,1,0,0 },{ 1,1,0,0 } };
void initialWindow(HANDLE hOut);//��ʼ������
void initialPrint(HANDLE hOut);//��ʼ������
void gotoXY(HANDLE hOut, int x, int y);//�ƶ����
void randBlock(HANDLE hOut, int block[4][4]);//������ɷ��鲢��ӡ����һ������λ��
bool collisionDetection(int block[4][4], int map[21][12], int x, int y);//�����ײ
void printBlock(HANDLE hOut, int block[4][4], int x, int y);//��ӡ����
void clearBlock(HANDLE hOut, int x, int y,int block[4][4]);//��������
void equal(int block1[4][4], int block2[4][4]);             //ִ�и�ֵ����
void myLeft(HANDLE hOut, int block[4][4], int map[21][12], int x, int& y);//����
void myRight(HANDLE hOut, int block[4][4], int map[21][12], int x, int& y);//����
void myDown(HANDLE hOut, int block[4][4], int map[21][12], int& x, int y);//
void myTurn(HANDLE hOut, int block[4][4], int map[21][12], int &x, int& y);//˳ʱ����ת90��
//int myDown(HANDLE hOut, int block[4][4], int map[21][12], int& x, int y);//��������

void gameOver(HANDLE hOut, int block[4][4], int map[21][12]);//��Ϸ����
void eliminateRow(HANDLE hOut, int map[21][12], int& fraction);
//�жϲ�ִ���Ƿ������в����·�ֵ

void initialWindow(HANDLE hOut)            //���Ʋ�������
{
    COORD size = { 80, 25 };
    SetConsoleScreenBufferSize(hOut, size);
    SMALL_RECT rc = { 0, 0, 79, 24 };
    SetConsoleWindowInfo(hOut, true, &rc);
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(hOut, &cursor_info);
}
void gotoXY(HANDLE hOut, int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}
void initialPrint(HANDLE hOut)
{
    SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    for (int i = 0; i < 20; ++i)
    {
        cout << "��                    ����                      ��" << endl;
    }
    gotoXY(hOut, 26, 0);     //���к���
    cout << "������������";
    gotoXY(hOut, 0, 20);
    cout << "��������������������������������������";    
    gotoXY(hOut, 26, 2);
    cout << "��   ����      ";
    gotoXY(hOut, 26, 4);
    cout << "��һ���飺";
    gotoXY(hOut, 26, 9);
    cout << "����������";
    gotoXY(hOut, 30, 11);
    cout << "W����ת S���ٽ�";
    gotoXY(hOut, 30, 12);
    cout << "D������ A������";
    gotoXY(hOut, 30, 13);
    cout << "P����ʼ/��ͣ";
    gotoXY(hOut, 30, 14);
    cout << "B �����˳�";
    gotoXY(hOut, 26, 16);
    cout << "��    �ڣ�";
    gotoXY(hOut, 30, 18);
    cout << "����˹����";
    gotoXY(hOut, 35, 19);
    cout << "���ߣ�mfq";
    for (int i = 0; i <= 20; i++)
        map[i][0] = map[i][11] = 1;
    for (int i = 0; i < 12; i++)
        map[20][i] = 1;
}
void printBlock(HANDLE hOut, int block[4][4], int x, int y)
{
    switch (block[0][0])
    {
    case 10:
    case 11:
        SetConsoleTextAttribute(hOut, FOREGROUND_RED);
        break;
    case 12:
    case 13:
    case 14:
    case 15:
        SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
        break;
    case 16:
    case 17:
    case 18:
    case 19:
        SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
        break;
    case 20:
    case 21:
    case 22:
    case 23:
        SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
    case 24:
    case 25:
        SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
    case 26:
    case 27:
        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
    case 28:
        SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;
    }
    //�����Ǹ���׼�������������ɫ
    //������ɵ����Ĵ�ӡ����
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (block[i][j] == 1)
            {
                gotoXY(hOut, 2 * (y + j), x + i);
                //����������������к��У����Ƕ���gotoXY�������ԣ������к���
                //��ӡ�������ξ�����һ������Ҫ*2������size��ԭ��
                cout << "��";
            }
}
void clearBlock(HANDLE hOut, int x, int y, int block[4][4])
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if (block[i][j] == 1)
            {
                gotoXY(hOut, 2 * (y + j), x + i);
                cout << "  ";
                    //һ���������ո�
            }
}
bool collisionDetection(int block[4][4], int map[21][12], int x, int y)    //�����ײ

//�˺�������Ӧ��ʱҪ����ƽ��������ת�ķ�����ȡ�������ִ���ƶ��������x��y
{
    for(int i=0;i<4;i++)
        for (int j = 0; j < 4; j++)
        
            if (x + i >= 0 && y + j >= 0 && block[i][j] == 1 && map[x + i][y + j] == 1)      //��block���ͼmap�еط��غ���
                return false;
        
    return true;
}


void myLeft(HANDLE hOut, int block[4][4], int map[21][12], int x, int& y)          //����
{
    if (collisionDetection(block, map, x, y-1))   //������ǵ���ײ��⺯��������һ����y-1
    {
        clearBlock(hOut, x, y, block);
        y--;
        printBlock(hOut, block, x, y);
    }
}

void myRight(HANDLE hOut, int block[4][4], int map[21][12], int x, int& y)
{
    if (collisionDetection(block, map, x, y+1))   //������ǵ���ײ��⺯��������һ����y+1
    {
        clearBlock(hOut, x, y, block);
        y++;
        printBlock(hOut, block, x, y);
    }
}
void equal(int block1[4][4], int block2[4][4])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            block1[i][j] = block2[i][j];
}

void myTurn(HANDLE hOut, int block[4][4], int map[21][12], int& x, int& y)
//Ҫע����ת�����Ͻ��Ƿ����仯���Ӷ�����ײ��⺯��ѡ��ͬ�Ĳ���
{
    switch (block[0][0])
    {
    case 10:
        if (collisionDetection(block01, map, x, y))
            clearBlock(hOut, x, y,block);
        equal(block, block01);
        break;
    case 11:
        if (collisionDetection(block00, map, x, y + 1))
            clearBlock(hOut, x, y,block);
        equal(block, block00);
        y++;
        break;
    case 12:
        if (collisionDetection(block03, map, x, y))
            clearBlock(hOut, x, y,block);
        equal(block, block03);
        break;
    case 13:
        if (collisionDetection(block04, map, x, y - 1))
            clearBlock(hOut,x, y,block);
        equal(block, block04);
        y--;
        break;
    case 14:
        if (collisionDetection(block05, map, x, y + 1))
            clearBlock(hOut,x, y,block);
        equal(block, block05);
        y++;
        break;
    case 15:
        if (collisionDetection(block02, map, x, y))
            clearBlock(hOut, x, y,block);
        equal(block, block02);
        break;
    case 16:
        if (collisionDetection(block07, map, x, y))
            clearBlock(hOut, x, y,block);
        equal(block, block07);
        break;
    case 17:
        if (collisionDetection(block08, map, x, y - 1))
            clearBlock(hOut, x, y,block);
        equal(block, block08);
        break;
    case 18:
        if (collisionDetection(block09, map, x, y + 1))
            clearBlock(hOut,x, y,block);
        equal(block, block09);
        y++;
        break;
    case 19:
        if (collisionDetection(block06, map, x, y))
            clearBlock(hOut, x, y,block);
        equal(block, block06);
        break;
    case 20:
        if (collisionDetection(block11, map, x, y))
            clearBlock(hOut, x, y,block);
        equal(block, block11);
        break;
    case 21:
        if (collisionDetection(block12, map, x, y - 1))
            clearBlock(hOut, x, y,block);
        equal(block, block12);
        y--;
        break;
    case 22:
        if (collisionDetection(block13, map, x, y + 1))
            clearBlock(hOut, x, y,block);
        equal(block, block13);
        y++;
        break;
    case 23:
        if (collisionDetection(block10, map, x, y))
            clearBlock(hOut, x, y,block);
        equal(block, block10);
        break;
    case 24:
        if (collisionDetection(block15, map, x, y))
            clearBlock(hOut, x, y,block);
        equal(block, block15);
        break;
    case 25:
        if (collisionDetection(block14, map, x, y - 1))
            clearBlock(hOut, x, y,block);
        equal(block, block14);
        y--;
        break;
    case 26:
        if (collisionDetection(block17, map, x, y))
            clearBlock(hOut, x, y,block);
        equal(block, block17);
        break;
    case 27:
        if (collisionDetection(block16, map, x, y))
            clearBlock(hOut, x, y,block);
        equal(block, block16);
        break;
    }
    clearBlock(hOut, x, y, block);
    printBlock(hOut, block, x, y);
}
    
void randBlock(HANDLE hOut, int block[4][4])   //������ɷ��鲢��ӡ����һ������λ
{
    int Block[19][4][4];
    equal(Block[0], block00);
    equal(Block[1], block01);
    equal(Block[2], block02);
    equal(Block[3], block03);
    equal(Block[4], block04);
    equal(Block[5], block05);
    equal(Block[6], block06);
    equal(Block[7], block07);
    equal(Block[8], block08);
    equal(Block[9], block09);
    equal(Block[10], block10);
    equal(Block[11], block11);
    equal(Block[12], block12);
    equal(Block[13], block13);
    equal(Block[14], block14);
    equal(Block[15], block15);
    equal(Block[16], block16);
    equal(Block[17], block17);
    equal(Block[18], block18);
    srand((unsigned)time(NULL));
    int n = rand() % 19;
    equal(block, Block[n]);
    clearBlock(hOut, 5, 15, block);
    printBlock(hOut, block, 5, 15);
}


void myDown(HANDLE hOut, int block[4][4], int map[21][12], int& x, int y)
{
    if (collisionDetection(block, map, x+1, y ))   //������ǵ���ײ��⺯��������һ����y+1
    {
        clearBlock(hOut, x, y, block);
        x++;
        printBlock(hOut, block, x, y);
    }

}

void eliminateRow(HANDLE hOut, int map[21][12], int& fraction)       //�����⣬�ؼ��������Ժ��ַ�ʽ�˳���ѭ��

//��������ֻ���һ�У���Ϊ�������������ѭ�����ڣ���һ�м��ײ���һ��
{
    int i = 19;
    int j;

    for (j = 1; j < 12; j++)
        if (map[i][j] == 0)            //���ȡ��������������ڴ�ѭ�����ڷ��õ�λ��
            return;
    
        if (j == 11)                           //˵����һ�б�����������
        {
            fraction += 100;

            //��ʱ���������ȫ1�У����˳��˴�ѭ���������ǵ�i+1��
            //����ִ�����в���
            SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
            for (int m = i ; m > 0; m--)
                for (int n = 1; n < 11; ++n)
                {
                    map[m][n] = map[m - 1][n];
                    gotoXY(hOut, 2 * n, m);
                    if (map[m][n] == 1)
                        cout << "��";
                    else
                        cout << "  ";
                }
        }
}


    


void gameOver(HANDLE hOut,int map[21][12])           //��Ϸ����
{
    for(int j=1;j<10;j++)
        if (map[2][j] == 1)
        {
            system("cls");
            gotoXY(hOut, 20, 10);
            cout << "Game Over";
            getchar();
        }
}

int main()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼����豸���
    initialWindow(hOut);
    gotoXY(hOut, 0, 0);
    initialPrint(hOut);
    int fraction = 0;
    int val = 200;             //�����ٶ�,valԽ���ٶ�Խ��
    int blockA[4][4];            //��ѡ������
    int blockB[4][4];            //��������ķ���
   
re:
    gotoXY(hOut, 26, 3);
    cout << fraction;
    static int z = 0;               //��zΪָ�꣬��Ϊ��һ����֮���ǲ�һ����
    int x = 1;
    int y = 1;
    gameOver(hOut, map);
    if (z == 0)                    //��һ��û����һ�������Ԥ�⣬���������������һ������㣬�������ѡ��07
    {
        equal(blockB, block18);
        printBlock(hOut, blockB, x, y);
    }
    else                           //֮��ģ�����Ҫ����Ԥ������������print����֮ǰrand������block
    {
        equal(blockB, blockA);
        printBlock(hOut, blockB, x, y);
        clearBlock(hOut, 5, 15, blockA);
    }
    randBlock(hOut, blockA);        //�������ߵĹ�ͬ����print�����ú�������rand���������һ���顣
    z++;
    while (1)
    {
        if (!collisionDetection(blockB, map, x + 1, y))//�������ǿ��ǵ����顰���ס�ʱ����map�������䣬�Ӷ�������һ�鷽��
        {    
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    if (blockB[i][j] == 1)
                        map[x + i][y + j] = 1;
            goto re;
        }
             
           
        if (GetAsyncKeyState('A') & 0x8000)
            myLeft(hOut, blockB, map, x, y);
        else if (GetAsyncKeyState('D') & 0x8000)
            myRight(hOut, blockB, map, x, y);
        else if (GetAsyncKeyState('W') & 0x8000)
            myTurn(hOut, blockB, map, x, y);
        else if (GetAsyncKeyState('B') & 0x8000)
        {
            system("cls");
            gotoXY(hOut, 20, 10);
            cout << "��Ϸ����";
            getchar();
        }
        myDown(hOut, blockB, map, x, y);
        Sleep(val);        
        eliminateRow(hOut, map, fraction);

    }
}
//�Ƚϳ����ķ�����ü��̵�ָ�
//char key;
//key=getchar();
//if(_kbhit)
//������������

/*

��Ҫ���������1��
���ʵ�������ٶȱ仯ʱ����Ӱ�찴����������
��Ҫ���������2��
���ʵ�ּ�������
��Ҫ���������3��
���ʹ����Ϸ�������ƴ���Ϸ���������ʹ��Qt����

*/