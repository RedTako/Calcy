#include "eventbutton.h"

EventButton::EventButton(QWidget *parent) : QPushButton(parent)
{
    connect(this, &QPushButton::clicked, this, &EventButton::emitClicked);

}

void EventButton::emitClicked()
{
    emit clickedSender(this);
}

//void EventButton::clickedSender(EventButton *sender)
//{

//}
