#ifndef INFO_SATION_H
#define INFO_SATION_H

#include <QWidget>

namespace Ui {
class InfoSation;
}

class InfoSation : public QWidget
{
    Q_OBJECT

public:
    explicit InfoSation(QWidget *parent = nullptr);
    ~InfoSation();
    void setInfo(int id, QString name, QPointF center, int Vl, int Ve);
    void setModeEdit();
    void setModeUse();

    int id;

private slots:
    //发出更改信息
    void setVexName();
    void setVexCenter();
    void deleteVex();

signals:
    //更改信息
    void sendSetVexName(int id, QString name);
    void sendSetVexCenter(int id, QPointF center);
    void sendDeleteVex(int id);

private:
    Ui::InfoSation *ui;
};

#endif // INFO_SATION_H
