#ifndef FORM_LAYOUT_H
#define FORM_LAYOUT_H

#include <QWidget>
#include "cqlabel.h"
#include "myapp.h"
#include <QFileDialog>
#include <QFile>

namespace Ui {
class Form_layout;
}

class Form_layout : public QWidget
{
    Q_OBJECT

public:
    explicit Form_layout(QWidget *parent = 0);
    ~Form_layout();
    CQLabel * clabel;


private slots:

    void on_btn_save_clicked();

    void on_pushButton_clicked();

private:
    Ui::Form_layout *ui;
    void initCQLabel();
};

#endif // FORM_LAYOUT_H
