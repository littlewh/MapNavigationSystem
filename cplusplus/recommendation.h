#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include <QWidget>

namespace Ui {
class Recommendation;
}

class Recommendation : public QWidget
{
    Q_OBJECT

public:
    explicit Recommendation(QWidget *parent = nullptr);

    ~Recommendation();

private slots://槽声明
    void on_pushButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_backButton_clicked();

private:
    Ui::Recommendation *ui;
};


#endif // RECOMMENDATION_H
