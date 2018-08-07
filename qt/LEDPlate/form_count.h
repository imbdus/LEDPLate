#ifndef FORM_COUNT_H
#define FORM_COUNT_H

#include <QWidget>

namespace Ui {
class Form_count;
}

class Form_count : public QWidget
{
    Q_OBJECT

public:
    explicit Form_count(QWidget *parent = 0);
    ~Form_count();

private:
    Ui::Form_count *ui;
};

#endif // FORM_COUNT_H
