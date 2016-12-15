#ifndef USERLEVEL_H
#define USERLEVEL_H
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
class UserLevel:public QDialog
{
public:
    UserLevel(QWidget *parent = 0);
private:
    QGridLayout *mGL;
    QPushButton *mEnter;
    QPushButton *mCancel;
    QLabel *Width;
    QLabel *Height;
    QLabel *MineNum;
    QLineEdit *mWidth;
    QLineEdit *mHeight;
    QLineEdit *mMineNum;
    QIntValidator *IntValidator;
public:
    void SetWidth(int Width);
    void SetHeight(int Height);
    void SetMineNum(int MineNum);
    int GetWidth();
    int GetHeight();
    int GetMineNum();
};

#endif // USERLEVEL_H
