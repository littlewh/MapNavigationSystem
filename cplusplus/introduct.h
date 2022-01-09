#ifndef INTRODUCT_H
#define INTRODUCT_H

#include <QWidget>

namespace Ui {
class Introduct;
}

class Introduct : public QWidget
{
    Q_OBJECT

public:
    explicit Introduct(QWidget *parent = nullptr);
    ~Introduct();

private slots:
    void on_backButton_clicked();//槽声明

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

private:
    Ui::Introduct *ui;
};

#endif // INTRODUCT_H
