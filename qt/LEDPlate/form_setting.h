#ifndef FORM_SETTING_H
#define FORM_SETTING_H

#include <QWidget>

namespace Ui {
class Form_Setting;
}

class Form_Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Setting(QWidget *parent = 0);
    ~Form_Setting();


private:
    Ui::Form_Setting *ui;
};

#endif // FORM_SETTING_H
