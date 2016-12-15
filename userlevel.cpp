#include "userlevel.h"
UserLevel::UserLevel(QWidget *parent):QDialog (parent)
{
    this->setWindowTitle("自定义");
    this->setMaximumSize(180,150);
    this->setMinimumSize(180,150);
    IntValidator = new QIntValidator(this);
    mGL = new QGridLayout(this);

    mEnter = new QPushButton("Enter",this);
    connect(mEnter,&QPushButton::clicked,this,[=](){
        this->accept();
    });

    mCancel = new QPushButton("Cancel",this);
    connect(mCancel,&QPushButton::clicked,this,[=](){
        this->close();
    });
    Width = new QLabel("宽度:",this);
    mWidth = new QLineEdit("0",this);
    mWidth->setValidator(IntValidator);

    Height = new QLabel("高度:",this);
    mHeight = new QLineEdit("0",this);
    mHeight->setValidator(IntValidator);

    MineNum = new QLabel("数量:",this);
    mMineNum = new QLineEdit("0",this);
    mMineNum->setValidator(IntValidator);


    mGL->setColumnStretch(0,1);
    mGL->setRowStretch(0,1);

    mGL->addWidget(Width, 1, 1, Qt::AlignCenter);
    mGL->addWidget(mWidth, 1, 2, Qt::AlignCenter);

    mGL->addWidget(Height, 2, 1, Qt::AlignCenter);
    mGL->addWidget(mHeight, 2, 2, Qt::AlignCenter);

    mGL->addWidget(MineNum, 3, 1, Qt::AlignCenter);
    mGL->addWidget(mMineNum, 3, 2, Qt::AlignCenter);

    mGL->addWidget(mCancel, 4, 1, Qt::AlignCenter);
    mGL->addWidget(mEnter, 4, 2, Qt::AlignCenter);

    mGL->setColumnStretch(3,1);
    mGL->setRowStretch(5,1);
}

void UserLevel::SetWidth(int Width)
{
    mWidth->setText(QString("%1").arg(Width));
}

void UserLevel::SetHeight(int Height)
{
    mHeight->setText(QString("%1").arg(Height));
}

void UserLevel::SetMineNum(int MineNum)
{
    mHeight->setText(QString("%1").arg(MineNum));
}

int UserLevel::GetWidth()
{
    return mWidth->text().toInt();
}

int UserLevel::GetHeight()
{
    return mHeight->text().toInt();
}

int UserLevel::GetMineNum()
{
    return mMineNum->text().toInt();
}
