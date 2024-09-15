#ifndef MYGRAPH_VIEW_H
#define MYGRAPH_VIEW_H

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QPainter>
#include <QColor>

#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>

#include <QDebug>
#include <QSet>
#include <QFile>
#include <QStack>
#include <QTimer>

class MySationItem;
class MyEdgeItem;
class MyGraphicsView;
const QColor nullColor = QColor(172, 172, 172);
const QColor showColor = QColor(200, 0, 0);
const QColor edgeColor = QColor(0, 0, 150);

// 边型
enum myShape {
    straight,
    cross_down,
    down_cross
};

//点信息
struct vNode {
    bool isExist = false;
    //拓扑信息
    int posFirst = -1;  // 正邻接表第一条边编号
    int invFirst = -1;  // 逆邻接表第一条边编号 // 删除时上一个被删除的编号
    int inDegree = 0;  // 入度
    int outDegree = 0; // 出度
    //算法信息
    int fackInDegree = 0;
    int fackOutDegree = 0;
    int Ve = 0;
    int Vl = 0;
    //其它信息
    MySationItem* sationAt;
};

struct eNode{
    bool isExist = false;
    //拓扑信息
    int from = -1;   // 来自点 // 删除时上一个被删除的编号
    int to = -1;     // 到达点
    int weight;
    //算法信息
    int e = 0;
    int l = 0;
    //其它信息
    MyEdgeItem* edgeAt;
};

class AbstractGraph
{
public:
    MyGraphicsView* view;

    //图
    int vMaxId = -1;
    int vNum = 0;
    int vLastDelete = -1;

    int eMaxId = -1;
    int eNum = 0;
    int eLastDelete = -1;

    QVector<vNode> vInfo;  // 下标为点id
    QVector<eNode> eInfo;  // 下标为边id

    QVector<int> posList;  // 正邻接表 下标为边id 内容为指向下一条边
    QVector<int> invList;  // 逆邻接表 下标为边id 内容为指向下一条边

    AbstractGraph(MyGraphicsView* view);
    //图操作
    MySationItem* addVex(QPointF center, QString name);

    MyEdgeItem* addEdge(int from, int to, enum myShape style, int weight);
    bool checkExist(int from, int to);
    bool checkNoLoop(int from, int to);
    bool checkNoRepetition(int from, int to);

    void setEdgeWeidght(int id, int weight);

    void deleteVex(int id);
    void deleteEdge(int id);
    //保存和读取
    int save(QString filePath);
    int read(QString filePath);//只能在初始化后使用
    //算法
    QString printList();
    bool checkOneFromTo(int &from, int &to);
    QVector<int> AOE(int from, int to);
};


//MyGraphicsView（滚轮缩放/右键拖动移动）
class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    //场景
    QGraphicsScene* myGraphicsScene;
    //拓扑结构
    AbstractGraph tupo = AbstractGraph(this);
    //模式
    enum MODE {
        Edit,
        Use
    };
    int mode = Edit;
    //事件相关变量
    QPointF lastPos;
    bool onRightPress = false;//是否正在移动
    bool onLeftPress = false;//是否正在拖动点

    bool SELECTED;//是否有图元在选中
    QGraphicsItem *selectItem = nullptr;//选中的图元
    void setNewSelected(QGraphicsItem *newSelectItem);

    explicit MyGraphicsView(QWidget *parent = nullptr);
    //模式切换
    enum Qt::CursorShape backModeCurser();
    void changeToUse();
    void changeToEdit();

    //图操作
    MySationItem* addSation(QPointF center);
    MyEdgeItem* addEdge(int from, int to, enum myShape style, int weight);

    //当前展示
    bool SHOWING = false;
    QVector<int> showPath;
    //编辑状态
    bool EDITED = false;
    void setEdited(bool edited);

    ~MyGraphicsView();

protected:
    //鼠标事件重写
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

signals:
    //信息栏
    void showSationInfo(int id, QString name, QPointF center, int Vl, int Ve);
    void showEdgeInfo(int id, int weight, int style, int from, int to, int l, int e, int le);
    void unshow();
    //主界面信号
    void sendSetTitleEdited(bool edited);
    //发送指示文字
    void sendText(QString text);
    //解除拓扑禁断
    void sendUnSorting();

public slots:
    void checkAddEdge(int from, int to, int style, qreal weight);
    //接受信息修改
    void setSationName(int id, QString name);
    void setSationCenter(int id, QPointF center);
    void setEdgeWeight(int id, qreal weight);
    void setEdgeStyle(int id, int style);

    void deleteSation(int id) {
        setNewSelected(nullptr);
        tupo.deleteVex(id);
        // 更改信号
        setEdited(true);
    }
    void deleteEdge(int id) {
        setNewSelected(nullptr);
        tupo.deleteEdge(id);
        // 更改信号
        setEdited(true);
    }
    //接受文件请求
    void replySave(QString filePath);
    void replyOther(QString otherPath);
    void replyRead(QString filePath);
    //接受查询请求
    void replyPrintList();
    void replyTupoSort();
    void oneTupoSort();
    void replyAOE();

private:
    void endTupoSort();
    //拓扑排序信息
    QTimer timer;
    QVector<int> ansList;
    QStack<int> s;

};

enum myType {
    mySationItem = QGraphicsItem::UserType + 1,
    myEdgeItem = QGraphicsItem::UserType + 2
};


class MySationItem : public QGraphicsEllipseItem
{
public:
    explicit MySationItem(int id, QPointF center, QString name, MyGraphicsView* view);
    ~MySationItem();
    void rePaint(QPointF center);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    int type() const override {return myType::mySationItem;};
    QPointF getCenter();
    void setTextName(bool isName);
    void setShowing(bool showing);

    //信息
    int id;
    QString name;
    QGraphicsTextItem* text = nullptr;

    MyGraphicsView* view;
    //状态
    bool SELECTED = false;
    bool SHOWING = false;

private:
    //设置
    int fontSize = 10;
    int size = 10;
    QPen myPen = QPen(QColor(0, 0, 0), 2);
    QFont myFont = QFont("Microsoft YaHei UI", 15);
};


class MyEdgeItem : public QGraphicsPathItem
{
public:
    explicit MyEdgeItem(int id, enum myShape style, MyGraphicsView* view);
    ~MyEdgeItem();
    int type() const override {return myType::myEdgeItem;};
    void reSetStyle();
    void reSetPath();
    void setShowing(bool showing);

    //信息
    int id;
    enum myShape style;
    MyGraphicsView* view;
    //状态
    bool SELECTED = false;//点击选中
    bool SHOWING = false; //展示

private:
    //图形
    QGraphicsPathItem* secondLine = nullptr;
    QGraphicsTextItem* text = nullptr;
    //设置
    int edgeSpace = 3;
    int myPenWidth = 6;
    int arrowWidth = 2;
    int arrowLength = 6;
    qreal arrowAngle = M_PI / 6;
    QFont myFont = QFont("Microsoft YaHei UI", 15);
};

#endif // MYGRAPH_VIEW_H
