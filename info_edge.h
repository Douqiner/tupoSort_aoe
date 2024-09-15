#ifndef INFO_EDGE_H
#define INFO_EDGE_H

#include <QWidget>

namespace Ui {
class InfoEdge;
}

class InfoEdge : public QWidget
{
    Q_OBJECT

public:
    explicit InfoEdge(QWidget *parent = nullptr);
    ~InfoEdge();
    void setInfo(int id, int weight, int style, int from, int to, int l, int e, int le);
    void setModeEdit();
    void setModeUse();

    int id;

private slots:
    //发出更改信息
    void setEdgeWeight();
    void setEdgeStyle();
    void deleteEdge();

signals:
    //更改信息
    void sendSetEdgeWeight(int id, int weight);
    void sendSetEdgeStyle(int id, int style);
    void sendDeleteEdge(int id);

private:
    Ui::InfoEdge *ui;
};

#endif // INFO_EDGE_H
