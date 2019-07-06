#include "inputbox.h"
#include <QPaintEvent>
#include <stack>
#include <vector>
#include <QPainter>

InputBox::InputBox(QWidget *parent) : QLineEdit(parent)
{
    connect(this, &InputBox::textEdited, this, &InputBox::onTextEdit);
}

double InputBox::validate()
{
    auto string = this->text();
    const std::vector<Tokenizer::TokenPtr>& list = tokenizer.tokenize(text());

    auto test = (*(list[0])).getContent().toStdString().c_str();

    std::vector<TokenBase*> output;
    std::stack<TokenBase*> operatorStack;

    for(size_t i = 0; i < list.size(); i++)
    {
        TokenBase* t = list[i].get();
        if(t->isOperator())
        {
            if(operatorStack.size() == 0 || operatorStack.top()->getContent() == '(')
            {
                operatorStack.push(t);
            }
            else if(t->getContent() == "(") { operatorStack.push(t); }
            else if(t->getContent() == ")")
            {
                do
                {
                    output.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                while(operatorStack.top()->getContent() != "(");
                if(operatorStack.top()->getContent() == "(")
                    operatorStack.pop();
            }
            else if(operatorStack.top()->getPrecedence() > t->getPrecedence())
            {
                operatorStack.push(t);
            }
            else if(operatorStack.top()->getPrecedence() <= t->getPrecedence())
            {
                output.push_back(operatorStack.top());
                operatorStack.pop();

                operatorStack.push(t);
            }
            else
            {
                operatorStack.push(t);
            }
        }
        else
        {
            output.push_back(t);
        }

        if(i == list.size() - 1 && operatorStack.size() > 0)
        {
            size_t stackSize = operatorStack.size();
            for(size_t j = 0; j < stackSize; j++)
            {
                output.push_back(operatorStack.top());
                operatorStack.pop();
            }

        }
    }

    std::stack<double> operandStack;
    size_t stackSize = output.size();
    double result = 0;
    for(size_t i = 0; i < stackSize; i++)
    {
        TokenBase* t = output[i];
        if(t->isOperator())
        {
            OperatorToken* op = static_cast<OperatorToken*>(t);
            double& d1 = operandStack.top();
            operandStack.pop();

            double r = 0;
            if(operandStack.size() > 0)
            {
                double& d2 = operandStack.top();
                operandStack.pop();
                r = op->evaluate(d2, d1);
            }
            else
            {
                r = op->evaluate(0, d1);
            }


            operandStack.push(r);
        }
        else
        {
            operandStack.push(static_cast<ValueToken*>(t)->getValue());
        }
    }

    return operandStack.top();
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


