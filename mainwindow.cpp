#include "mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Action_Set();

    mMine = new MineMap(HARD,this);
    this->setCentralWidget(mMine);
    this->setMaximumSize(mMine->minimumWidth(),mMine->height());
}

MainWindow::~MainWindow()
{

}

void MainWindow::ReSet(int level)
{
    mMine->close();
    delete mMine;
    mMine = NULL;
    mMine = new MineMap(level);
    this->setCentralWidget(mMine);
    this->resize(mMine->minimumWidth(),mMine->height());
    this->setMaximumSize(mMine->minimumWidth(),mMine->minimumHeight());
}

void MainWindow::Action_Set()
{
    mMenuBar = new QMenuBar(this);
    this->setMenuBar(mMenuBar);
    NewGame = new QMenu("NewGame",this);
    mMenuBar->addMenu(NewGame);
    mHelp = new QMenu("Help",this);
    mMenuBar->addMenu(mHelp);

    QAction *mEasy = new QAction("Easy",this);
    NewGame->addAction(mEasy);
    connect(mEasy,&QAction::triggered,this,[=](){
        ReSet(EASY);
    });
    QAction *mNormal = new QAction("Normal",this);
    NewGame->addAction(mNormal);
    connect(mNormal,&QAction::triggered,this,[=](){
        ReSet(NORMAL);
    });
    QAction *mHard = new QAction("Hard",this);
    NewGame->addAction(mHard);
    connect(mHard,&QAction::triggered,this,[=](){
        ReSet(HARD);
    });
    QAction *mUser = new QAction("User Custom",this);
    NewGame->addAction(mUser);
    connect(mUser,&QAction::triggered,this,[=](){
        ReSet(USER);
    });

    QAction *mAbout = new QAction("About",this);
    mHelp->addAction(mAbout);
    connect(mAbout,&QAction::triggered,this,[=](){
        mMine->mTimer->stop();
        QMessageBox::about(this,"About","作者:叶修伟");
        if(mMine->mStart)
            mMine->mTimer->start(1000);
    });
}
