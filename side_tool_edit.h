#ifndef SIDE_TOOL_EDIT_H
#define SIDE_TOOL_EDIT_H

#include <QWidget>
#include <QPushButton>
#include <QColorDialog>
#include <QStackedWidget>
#include <QMessageBox>

#include "info_sation.h"
#include "info_edge.h"

namespace Ui {
class SideToolEdit;
}

class SideToolEdit : public QWidget
{
    Q_OBJECT

public:
    explicit SideToolEdit(QWidget *parent = nullptr);
    ~SideToolEdit();
    //切换模式
    void setModeEdit();
    void setModeUse();

    InfoSation* infoSation;
    InfoEdge* infoEdge;
private:
    Ui::SideToolEdit *ui;
    QStackedWidget* information;

private slots:
    //自用
    //发出添加边信息
    void addEdge();

public slots:
    //接受信息
    void setInfoSation(int id, QString name, QPointF center, int Vl, int Ve);
    void setInfoEdge(int id, int weight, int style, int from, int to, int l, int e, int le);
    void setInfoClose();
    //拓扑禁断
    void setSorting();
    void setUnSorting();
    //接受文本信息
    void setText(QString text);
    //提示
    void showTips();

signals:
    //添加边
    void sendAddEdge(int from, int to, int style, int weight);
    //功能信号
    void sendPrintList();
    void sendTupoSort();
    void sendAOE();
};

#endif // SIDE_TOOL_EDIT_H
