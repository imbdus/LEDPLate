#ifndef FORMTHREE_H
#define FORMTHREE_H

#include <QWidget>

namespace Ui {
class FormThree;
}

class FormThree : public QWidget
{
    Q_OBJECT

public:
    explicit FormThree(QWidget *parent = 0);
    ~FormThree();

private:
    Ui::FormThree *ui;
};

#endif // FORMTHREE_H
