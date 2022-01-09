#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QWidget>

namespace Ui {
class Introduction;
}

class Introduction : public QWidget
{
    Q_OBJECT

public:
    explicit Introduction(QString num,QWidget *parent = nullptr);

    ~Introduction();

private slots:
    void on_backButton_clicked();

private:
    Ui::Introduction *ui;
};

#endif // INTRODUCTION_H
