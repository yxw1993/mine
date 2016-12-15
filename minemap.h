#ifndef MINEMAP_H
#define MINEMAP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLCDNumber>
#include "minebutton.h"
#include "userlevel.h"
#include <QTimer>
enum _LEVEL
{
    EASY = 0,
    NORMAL = 1,
    HARD = 2,
    USER = 4
};

class MineMap : public QWidget
{
   // Q_OBJECT
public:
    explicit MineMap(int level = HARD, QWidget *parent = 0);
    ~MineMap();
    void SetLevel(int level);
    void DrawMap();
signals:
    void GameStart();
public slots:
private:
    int mMineNum;
    int mWidth;
    int mHeight;
    UserLevel *mUser;
    MineButton **mMineButton;
    char **mMine;
    QVBoxLayout *mVBoxLayout;
    QLCDNumber *mNumCur;
    QLCDNumber *mTimeCur;
    QPushButton *mRePlay;
    QHBoxLayout *HBoxLayout;
    bool mLife;
    int mMineNow;
private:
    void clearclick(int i, int j);
    void setMine();
    void CreateMine();
    void IsWin();
public:
    QTimer *mTimer;
    bool mStart;
};

#endif // MINEMAP_H
