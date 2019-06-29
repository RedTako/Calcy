#include "inputbox.h"
#include <QPaintEvent>

#include <QPainter>

InputBox::InputBox(QWidget *parent) : QLineEdit(parent)
{
    connect(this, &InputBox::textEdited, this, &InputBox::onTextEdit);
}

double InputBox::validate()
{

    return 0;
}

void InputBox::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

//    QPainter p(this);
//    int fontSize = 20;

//    p.setPen(Qt::darkGray);
//    p.setBrush(Qt::white);
//    p.setFont(QFont("Arial", fontSize));
//    QRect area = rect();
//    area.setRect(area.x(), area.y(), area.width() - 1, area.height() - 1);


//    p.drawRoundedRect(area, 10, 10);

//    area.setWidth(area.width() - 4);
//    QTextOption options(Qt::AlignVCenter | Qt::AlignRight);


//    QRect textArea;

//    p.setPen(Qt::black);
//    p.drawText(area, text(), options);


}

void InputBox::timerEvent(QTimerEvent *event)
{

}

void InputBox::onTextEdit(const QString& str)
{
    QString inputStr = this->text();
    bool replace = false;

    for(int i = 0; i < inputStr.size(); i++)
    {
        if(inputStr[i] == '*')
        {
            inputStr[i] = 'x';
            replace = true;
        }
        else if(inputStr[i] == '/')
        {
            char32_t ch =  static_cast<char32_t>(0x00f7); //weird workaround because divide is two characters for some reason :)
            inputStr[i] = ch;
            replace = true;
        }
    }

    if(replace)
        setText(inputStr);
}


