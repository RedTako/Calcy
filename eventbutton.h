#ifndef EVENTBUTTON_H
#define EVENTBUTTON_H

#include <QPushButton>

class EventButton : public QPushButton
{
    Q_OBJECT

public:
    EventButton(QWidget* parent = nullptr);
    EventButton(const EventButton&) = delete;


signals:
    void clickedSender(EventButton* sender);

public slots:
    void emitClicked();
};

#endif // EVENTBUTTON_H
