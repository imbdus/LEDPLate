#ifndef FORM_CAM_H
#define FORM_CAM_H

#include <QWidget>

namespace Ui {
class Form_cam;
}

class Form_cam : public QWidget
{
    Q_OBJECT

public:
    explicit Form_cam(QWidget *parent = 0);
    ~Form_cam();

private:
    Ui::Form_cam *ui;
};

#endif // FORM_CAM_H
