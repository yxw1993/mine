#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include "minemap.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    MineMap *mMine;
    QMenuBar *mMenuBar;
    QMenu *NewGame;
    QMenu *mHelp;
    void ReSet(int level);
private:
    void Action_Set();
};

#endif // MAINWINDOW_H
