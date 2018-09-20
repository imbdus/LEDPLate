#ifndef FORM_PRODUCT_H
#define FORM_PRODUCT_H

#include <QWidget>

namespace Ui {
class Form_product;
}

class Form_product : public QWidget
{
    Q_OBJECT

public:
    explicit Form_product(QWidget *parent = 0);
    ~Form_product();

private:
    Ui::Form_product *ui;
};

#endif // FORM_PRODUCT_H
