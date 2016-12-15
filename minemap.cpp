#include "minemap.h"

static int Height = 0;
static int Width = 0;
static int MineNum = 0;
MineMap::MineMap(int level, QWidget *parent) : QWidget(parent), mMineNum(0), mWidth(0), mHeight(0)
{
    SetLevel(level);
    mLife = true;
    mStart = false;
    mTimer = new QTimer(this);
    connect(mTimer,&QTimer::timeout,this,[=](){
        mTimeCur->display(mTimeCur->intValue() + 1);

    });
    mMineNow = 0;
}

MineMap::~MineMap()
{
    for(int i = 0; i < mHeight; ++i)
    {
        if(mMine[i] != NULL)
        {
            delete[] mMine[i];
            mMine[i]=NULL;
        }
        if(mMineButton[i] != NULL)
        {
            delete[] mMineButton[i];
            mMineButton[i]=NULL;
        }
    }
    delete[] mMine;
    mMine = NULL;
    delete[] mMineButton;
    mMineButton = NULL;
}

void MineMap::SetLevel(int level)
{
    mVBoxLayout = new QVBoxLayout(this);
    switch(level)
    {
    case EASY:
        mHeight = 9;
        mWidth = 9;
        mMineNum = 10;
        break;
    case NORMAL:
        mHeight = 16;
        mWidth = 16;
        mMineNum = 40;
        break;
    case HARD:
        mHeight = 16;
        mWidth = 30;
        mMineNum = 99;
        break;
    case USER:
        mUser = new UserLevel(this);
        mUser->SetWidth(Width);
        mUser->SetHeight(Height);
        mUser->SetMineNum(MineNum);
        if(mUser->exec() == QDialog::Accepted)
        {
            mHeight = mUser->GetHeight();
            mWidth = mUser->GetWidth();
            mMineNum = mUser->GetMineNum();

        }
        if(!mHeight || !mWidth || !mMineNum)
        {
            mHeight = Height;
            mWidth = Width;
            mMineNum = MineNum;
        }
        break;
    }
    Height =mHeight;
    Width = mWidth;
    MineNum = mMineNum;
    DrawMap();
}
struct MINEPOS
{
    int row;
    int col;
}const minepos[8] = {{ 0, 1 }, { 0, -1 },{ 1, 0 },{ -1, 0 },{ 1, 1 },{ 1, -1 },{ -1, 1 },{ -1, -1 }};

void MineMap::DrawMap()
{
    mNumCur = new QLCDNumber;
    mNumCur->display(mMineNum);
    mTimeCur = new QLCDNumber;
    mRePlay = new QPushButton("RE");
    mRePlay->setMinimumSize(50,40);
    mRePlay->setMaximumSize(50,40);
    QFont Font;
    Font.setBold(true);
    Font.setPointSize(15);
    mRePlay->setFont(Font);
    connect(mRePlay,&QPushButton::clicked,this,[=](){
        mRePlay->setText("RE");
        mLife = true;
        mStart = false;
        mTimeCur->display(0);
        mNumCur->display(mMineNum);
        mTimer->stop();
        mMineNow = 0;
        for(int i = 0; i < mHeight; ++i)
        {
            for(int j = 0; j < mWidth; ++j)
            {
                mMine[i][j] = '0';
                mMineButton[i][j].setText("");
                mMineButton[i][j].setEnabled(true);
            }
        }
        CreateMine();
    });

    mVBoxLayout->setSpacing(0);
    mMineButton = new MineButton*[mHeight];
    mMine = new char*[mHeight];
    HBoxLayout = new QHBoxLayout;
    HBoxLayout->addWidget(mNumCur);
    HBoxLayout->addStretch(1);
    HBoxLayout->addWidget(mRePlay);
    HBoxLayout->addStretch(1);
    HBoxLayout->addWidget(mTimeCur);
    mVBoxLayout->addLayout(HBoxLayout);

    setMine();
}

const MINEPOS diapos[4] = { { 1, 1 },{ 1, -1 },{ -1, 1 },{ -1, -1 } };


void MineMap::clearclick(int row, int col)
{
    mMineButton[row][col].setEnabled(false);

    mMineButton[row][col].setText(QString("%1").arg(mMine[row][col] == '0' ? '\0' : mMine[row][col]));

    IsWin();
    if(mMine[row][col] == 'B')
    {
        mRePlay->setText("LOST");
        for(int i = 0; i < mHeight; ++i)
        {
            for(int j = 0; j < mWidth; ++j)
            {
                if(mMine[i][j] == 'B')
                {
                    mMineButton[i][j].setText(QString("%1").arg(mMine[i][j]));
                    mMineButton[i][j].setEnabled(false);
                }
            }
        }
        mLife = false;
        mTimer->stop();
        return;
    }

    if(mMine[row][col] != '0')
    {
        return;
    }
    if(row > 0 && mMineButton[row - 1][col].isEnabled())
        clearclick(row - 1, col);
    if(row < mHeight - 1 && mMineButton[row + 1][col].isEnabled())
        clearclick(row + 1, col);
    if(col > 0 && mMineButton[row][col - 1].isEnabled())
        clearclick(row, col - 1);
    if(col < mWidth -1 && mMineButton[row][col + 1].isEnabled())
        clearclick(row, col + 1);

    for(int i = 0; i < 4; ++i)
    {
        int rtemp = row + diapos[i].row;
        int ctemp = col + diapos[i].col;
        if(-1 == rtemp || -1 == ctemp || mHeight == rtemp || mWidth == ctemp)
            continue;
        if(mMine[rtemp][ctemp] != 'B' && mMine[rtemp][ctemp] != '0' && mMineButton[rtemp][ctemp].isEnabled())
        {
            IsWin();
            mMineButton[rtemp][ctemp].setEnabled(false);
            mMineButton[rtemp][ctemp].setText(QString("%1").arg(mMine[rtemp][ctemp] == '0' ? '\0' : mMine[rtemp][ctemp]));
        }
    }
}

void MineMap::IsWin()
{
    if(++mMineNow == (mHeight * mWidth - mMineNum))
    {
        mRePlay->setText("WIN");
        mTimer->stop();
    }
}
void MineMap::setMine()
{
    for(int i = 0; i < mHeight; ++i)
    {
        HBoxLayout = new QHBoxLayout;
        HBoxLayout->setSpacing(0);
        mMineButton[i] = new MineButton[mWidth];
        mMine[i] = new char[mWidth]{ 0 };
        for(int j = 0; j < mWidth; ++j)
        {
            mMine[i][j] = '0';
            HBoxLayout->addWidget(&mMineButton[i][j]);
            connect(&mMineButton[i][j],&MineButton::ChangeState,this,[=](int state){
                switch(state)
                {
                case ISMINE:
                    mNumCur->display(mNumCur->intValue() - 1);
                    break;
                case UNKNOW:
                    mNumCur->display(mNumCur->intValue() + 1);
                    break;
                }
            });
            connect(&mMineButton[i][j],&MineButton::clicked,this,[=](){
                if(!mStart)
                {
                    mStart = !mStart;
                    mTimer->start(1000);
                }
                if(mLife)
                {
                    clearclick(i, j);
                }
            });
        }
        HBoxLayout->addStretch(1);
        mVBoxLayout->addLayout(HBoxLayout);
    }
    mVBoxLayout->addStretch(1);
    mVBoxLayout->setSpacing(0);

    CreateMine();

    this->setMinimumWidth(mWidth * mMineButton[0][0].width());
    this->setMinimumHeight(mHeight * mMineButton[0][0].height() + 60);
}

void MineMap::CreateMine()
{
    for(int i = 0; i < mMineNum; ++i)
    {
        int row = rand() % mHeight;
        int col = rand() % mWidth;
        if(mMine[row][col] != 'B')
        {
            mMine[row][col] = 'B';
            for(int j = 0; j < 8; ++j)
            {
                int rtemp = row + minepos[j].row;
                int ctemp = col + minepos[j].col;
                if(-1 == rtemp || -1 == ctemp || mHeight == rtemp || mWidth == ctemp)
                    continue;
                if(mMine[rtemp][ctemp] != 'B')
                    mMine[rtemp][ctemp]++;
            }
        }
    }
}

