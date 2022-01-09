#ifndef NEARBY_H
#define NEARBY_H

#include <QWidget>
#include "ask.h"

namespace Ui {
class NearBy;
}

class NearBy : public QWidget
{
    Q_OBJECT

public:
    explicit NearBy(QWidget *parent = nullptr);
    ~NearBy();

private slots:
    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_3_clicked();

    void on_backButton_clicked();

private:
    Ui::NearBy *ui;
    DriveCarmap *dmap;
};

#endif // NEARBY_H
