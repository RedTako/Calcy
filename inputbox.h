#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QLineEdit>
#include <tokenizer.h>

class InputBox : public QLineEdit
{
    Q_OBJECT

public:
    InputBox(QWidget* parent = nullptr);

    double validate();



protected:
    void paintEvent(QPaintEvent* event) override;
    void timerEvent(QTimerEvent* event) override;
    Tokenizer tokenizer;

private slots:
    void onTextEdit(const QString& str);
};

#endif // INPUTBOX_H
