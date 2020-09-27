
//参考windows编程相关文章与CSDN————C++编写俄罗斯方块（主要是界面设计部分，游戏的主体由自己完成）


#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
using namespace std;
int map[21][12];
/*
这里原本是想用三维数组来储存方块的数据信息
但是方块信息使用的函数主要是旋转与移动函数
如果使用三维数组的话，在旋转函数内仍需要根据方块的类型来进行是否可以旋转的判断
无法实现较大的简化，故仍然采用下面的模式
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
void initialWindow(HANDLE hOut);//初始化窗口
void initialPrint(HANDLE hOut);//初始化界面
void gotoXY(HANDLE hOut, int x, int y);//移动光标
void randBlock(HANDLE hOut, int block[4][4]);//随机生成方块并打印到下一个方块位置
bool collisionDetection(int block[4][4], int map[21][12], int x, int y);//检测碰撞
void printBlock(HANDLE hOut, int block[4][4], int x, int y);//打印方块
void clearBlock(HANDLE hOut, int x, int y,int block[4][4]);//消除方块
void equal(int block1[4][4], int block2[4][4]);             //执行赋值操作
void myLeft(HANDLE hOut, int block[4][4], int map[21][12], int x, int& y);//左移
void myRight(HANDLE hOut, int block[4][4], int map[21][12], int x, int& y);//右移
void myDown(HANDLE hOut, int block[4][4], int map[21][12], int& x, int y);//
void myTurn(HANDLE hOut, int block[4][4], int map[21][12], int &x, int& y);//顺时针旋转90度
//int myDown(HANDLE hOut, int block[4][4], int map[21][12], int& x, int y);//加速下落

void gameOver(HANDLE hOut, int block[4][4], int map[21][12]);//游戏结束
void eliminateRow(HANDLE hOut, int map[21][12], int& fraction);
//判断并执行是否能消行并更新分值

void initialWindow(HANDLE hOut)            //控制产生窗口
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
        cout << "■                    ■☆                      ☆" << endl;
    }
    gotoXY(hOut, 26, 0);     //先列后行
    cout << "☆☆☆☆☆☆☆☆☆☆☆";
    gotoXY(hOut, 0, 20);
    cout << "■■■■■■■■■■■■☆☆☆☆☆☆☆☆☆☆☆☆☆";    
    gotoXY(hOut, 26, 2);
    cout << "分   数：      ";
    gotoXY(hOut, 26, 4);
    cout << "下一方块：";
    gotoXY(hOut, 26, 9);
    cout << "操作方法：";
    gotoXY(hOut, 30, 11);
    cout << "W：旋转 S：速降";
    gotoXY(hOut, 30, 12);
    cout << "D：右移 A：左移";
    gotoXY(hOut, 30, 13);
    cout << "P：开始/暂停";
    gotoXY(hOut, 30, 14);
    cout << "B 键：退出";
    gotoXY(hOut, 26, 16);
    cout << "关    于：";
    gotoXY(hOut, 30, 18);
    cout << "俄罗斯方块";
    gotoXY(hOut, 35, 19);
    cout << "作者：mfq";
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
    //以上是给标准输入输出配上颜色
    //以下完成单纯的打印操作
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (block[i][j] == 1)
            {
                gotoXY(hOut, 2 * (y + j), x + i);
                //对于数组而言是先行后列，但是对于gotoXY函数而言，是先列后行
                //打印的正方形决定第一个坐标要*2，是其size的原因
                cout << "■";
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
                    //一定是两个空格
            }
}
bool collisionDetection(int block[4][4], int map[21][12], int x, int y)    //检测碰撞

//此函数具体应用时要根据平动或者旋转的方向来取假设可以执行移动操作后的x与y
{
    for(int i=0;i<4;i++)
        for (int j = 0; j < 4; j++)
        
            if (x + i >= 0 && y + j >= 0 && block[i][j] == 1 && map[x + i][y + j] == 1)      //即block与地图map有地方重合了
                return false;
        
    return true;
}


void myLeft(HANDLE hOut, int block[4][4], int map[21][12], int x, int& y)          //左移
{
    if (collisionDetection(block, map, x, y-1))   //结合我们的碰撞检测函数，这里一定是y-1
    {
        clearBlock(hOut, x, y, block);
        y--;
        printBlock(hOut, block, x, y);
    }
}

void myRight(HANDLE hOut, int block[4][4], int map[21][12], int x, int& y)
{
    if (collisionDetection(block, map, x, y+1))   //结合我们的碰撞检测函数，这里一定是y+1
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
//要注意旋转后，左上角是否发生变化，从而对碰撞检测函数选择不同的参数
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
    
void randBlock(HANDLE hOut, int block[4][4])   //随机生成方块并打印到下一个方块位
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
    if (collisionDetection(block, map, x+1, y ))   //结合我们的碰撞检测函数，这里一定是y+1
    {
        clearBlock(hOut, x, y, block);
        x++;
        printBlock(hOut, block, x, y);
    }

}

void eliminateRow(HANDLE hOut, int map[21][12], int& fraction)       //有问题，关键在于是以何种方式退出的循环

//我们这里只检测一行，因为其放在主函数大循环体内，这一行即底部这一行
{
    int i = 19;
    int j;

    for (j = 1; j < 12; j++)
        if (map[i][j] == 0)            //这个取决我们这个函数在大循环体内放置的位置
            return;
    
        if (j == 11)                           //说明这一行被方块填满了
        {
            fraction += 100;

            //此时如果出现了全1行，则退出了大循环，并且是第i+1行
            //下面执行消行操作
            SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
            for (int m = i ; m > 0; m--)
                for (int n = 1; n < 11; ++n)
                {
                    map[m][n] = map[m - 1][n];
                    gotoXY(hOut, 2 * n, m);
                    if (map[m][n] == 1)
                        cout << "■";
                    else
                        cout << "  ";
                }
        }
}


    


void gameOver(HANDLE hOut,int map[21][12])           //游戏结束
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
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出设备句柄
    initialWindow(hOut);
    gotoXY(hOut, 0, 0);
    initialPrint(hOut);
    int fraction = 0;
    int val = 200;             //下落速度,val越大速度越慢
    int blockA[4][4];            //候选区方块
    int blockB[4][4];            //正在下落的方块
   
re:
    gotoXY(hOut, 26, 3);
    cout << fraction;
    static int z = 0;               //以z为指标，因为第一次与之后是不一样的
    int x = 1;
    int y = 1;
    gameOver(hOut, map);
    if (z == 0)                    //第一次没有下一个方块的预测，我们随便让他产生一个，简便，这里随便选了07
    {
        equal(blockB, block18);
        printBlock(hOut, blockB, x, y);
    }
    else                           //之后的，我们要满足预测条件，所以print产生之前rand产生的block
    {
        equal(blockB, blockA);
        printBlock(hOut, blockB, x, y);
        clearBlock(hOut, 5, 15, blockA);
    }
    randBlock(hOut, blockA);        //以上两者的共同点是print起到作用后，立刻在rand区域产生下一方块。
    z++;
    while (1)
    {
        if (!collisionDetection(blockB, map, x + 1, y))//这里我们考虑当方块“触底”时，将map进行扩充，从而操纵下一组方块
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
            cout << "游戏结束";
            getchar();
        }
        myDown(hOut, blockB, map, x, y);
        Sleep(val);        
        eliminateRow(hOut, map, fraction);

    }
}
//比较初级的方法获得键盘的指令：
//char key;
//key=getchar();
//if(_kbhit)
//。。。。。。

/*

需要解决的问题1：
如何实现下落速度变化时，不影响按键的灵敏度
需要解决的问题2：
如何实现加速下落
需要解决的问题3：
如何使用游戏引擎完善此游戏，或者如何使用Qt界面

*/