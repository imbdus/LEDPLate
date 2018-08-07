#ifndef FORMONE_H
#define FORMONE_H

#include <QWidget>

//class FormTwo;

namespace Ui {
class FormOne;
}

class FormOne : public QWidget
{
    Q_OBJECT

public:
    explicit FormOne(QWidget *parent = 0);
    //FormOne();
    ~FormOne();

private:
    Ui::FormOne *ui;
};

#endif // FORMONE_H
