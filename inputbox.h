#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QLineEdit>

class InputBox : public QLineEdit
{
    Q_OBJECT

public:
    InputBox(QWidget* parent = nullptr);

    double validate();



protected:
    void paintEvent(QPaintEvent* event) override;
    void timerEvent(QTimerEvent* event) override;


private slots:
    void onTextEdit(const QString& str);
};

#endif // INPUTBOX_H
