#ifndef MINEBUTTON_H
#define MINEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
enum STATUS
{
    NOMINE = 0,
    ISMINE = 1,
    UNKNOW = 2
};
class MineButton : public QPushButton
{
    Q_OBJECT
public:
    MineButton(QWidget *parent = 0);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    int GetState();
signals:
    void ChangeState(int state);
private:
     int state;
};

#endif // MINEBUTTON_H
