#ifndef FORM_LAYOUT_H
#define FORM_LAYOUT_H

#include <QWidget>
#include "cqlabel.h"

namespace Ui {
class Form_layout;
}

class Form_layout : public QWidget
{
    Q_OBJECT

public:
    explicit Form_layout(QWidget *parent = 0);
    ~Form_layout();

private:
    Ui::Form_layout *ui;

    void initCQLabel();
};

#endif // FORM_LAYOUT_H
