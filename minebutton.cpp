#include "minebutton.h"
#include <QPoint>
#include <QFont>
#include <QString>
#include <QPalette>
MineButton::MineButton(QWidget *parent):QPushButton(parent), state(NOMINE)
{
    this->setMaximumSize(30,30);
    this->setMinimumSize(30,30);
    QFont Font;
    Font.setPointSize(18);
    Font.setBold(true);
    setFont(Font);
}

void MineButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        bool flag =  event->pos().rx() > 0
                && event->pos().ry() > 0
                && event->pos().rx() < width()
                && event->pos().ry() < height();

        if(state != ISMINE && flag)
            click();
    }

}

void MineButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::RightButton)
    {
        switch(++state %= 3)
        {
        case NOMINE:
            this->setText("");
            break;
        case ISMINE:
            this->setText("F");
            break;
        case UNKNOW:
            this->setText("?");
            break;
        }
        emit ChangeState(state);
    }
}

int MineButton::GetState()
{
    return state;
}

