#include "mygraph_view.h"

AbstractGraph::AbstractGraph(MyGraphicsView* view) {
    this->view = view;
}

MySationItem* AbstractGraph::addVex(QPointF center, QString name) {
    // 确定id
    int id;
    if (vMaxId + 1 == vNum) {
        id = vNum;
        vMaxId += 1;
        vInfo.append(vNode());
    } else {
        id = vLastDelete;
        vLastDelete = vInfo[id].invFirst;
    }
    ++vNum;
    name += QString::number(id);
    // 设置信息
    vInfo[id].isExist = true;
    vInfo[id].inDegree = 0;
    vInfo[id].outDegree = 0;
    vInfo[id].posFirst = -1;
    vInfo[id].invFirst = -1;
    vInfo[id].Ve = 0;
    vInfo[id].Vl = 0;
    // 新建item
    vInfo[id].sationAt = new MySationItem(id, center, name, view);
    return vInfo[id].sationAt;
}

MyEdgeItem* AbstractGraph::addEdge(int from,
                                   int to,
                                   enum myShape style,
                                   int weight) {
    // 默认已经检查好
    // 确定id
    int id;
    if (eMaxId + 1 == eNum) {
        id = eNum;
        eMaxId += 1;
        eInfo.append(eNode());
        posList.append(-1);
        invList.append(-1);
    } else {
        id = eLastDelete;
        eLastDelete = eInfo[id].from;
    }
    ++eNum;
    // 设置信息
    eInfo[id].isExist = true;
    eInfo[id].from = from;
    eInfo[id].to = to;
    eInfo[id].weight = weight;
    eInfo[id].e = 0;
    eInfo[id].l = 0;
    // 修改正逆邻接表(头插法)
    posList[id] = vInfo[from].posFirst;
    vInfo[from].posFirst = id;
    ++vInfo[from].outDegree;

    invList[id] = vInfo[to].invFirst;
    vInfo[to].invFirst = id;
    ++vInfo[to].inDegree;

    // 新建item
    eInfo[id].edgeAt = new MyEdgeItem(id, style, view);
    return eInfo[id].edgeAt;
}

bool AbstractGraph::checkExist(int from, int to) {
    if (from > vMaxId || to > vMaxId)
        return false;
    if (!vInfo[from].isExist || !vInfo[to].isExist)
        return false;
    return true;
}

bool AbstractGraph::checkNoLoop(int from, int to) {
    if (from == to)
        return false;
    else
        return true;
}

bool AbstractGraph::checkNoRepetition(int from, int to) {
    for (int e = vInfo[from].posFirst; e != -1; e = posList[e]) {
        if (eInfo[e].to == to)
            return false;
    }
    return true;
}

void AbstractGraph::setEdgeWeidght(int id, int weight) {
    eInfo[id].weight = weight;
}

void AbstractGraph::deleteVex(int id) {
    // 删除出边、入边
    for (int e = vInfo[id].posFirst; e != -1; e = posList[e]) {
        deleteEdge(e);
    }
    for (int e = vInfo[id].invFirst; e != -1; e = invList[e]) {
        deleteEdge(e);
    }
    // 删除点
    --vNum;
    vInfo[id].isExist = false;
    vInfo[id].invFirst = vLastDelete;
    vLastDelete = id;
    // 移除图元
    view->myGraphicsScene->removeItem(vInfo[id].sationAt);
    delete vInfo[id].sationAt;
}

void AbstractGraph::deleteEdge(int id) {
    // 邻接表中删除边
    // 正邻接表
    int e;
    e = vInfo[eInfo[id].from].posFirst;
    if (e == id) {
        // 第一条边
        vInfo[eInfo[id].from].posFirst = posList[e];
        --vInfo[eInfo[id].from].outDegree;
    } else {
        for (; posList[e] != id; e = posList[e])
            ;
        posList[e] = posList[id];
        --vInfo[eInfo[id].from].outDegree;
    }
    // 逆邻接表
    e = vInfo[eInfo[id].to].invFirst;
    if (e == id) {
        // 第一条边
        vInfo[eInfo[id].to].invFirst = invList[e];
        --vInfo[eInfo[id].to].inDegree;
    } else {
        for (; invList[e] != id; e = invList[e])
            ;
        invList[e] = invList[id];
        --vInfo[eInfo[id].to].inDegree;
    }
    // 移除图元
    view->myGraphicsScene->removeItem(eInfo[id].edgeAt);
    delete eInfo[id].edgeAt;
    // 维护信息
    --eNum;
    eInfo[id].isExist = false;
    eInfo[id].from = eLastDelete;
    eLastDelete = id;
}


int AbstractGraph::save(QString filePath)
{
    QFile out(filePath);
    if (out.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream ts(&out);
        //点
        ts << vMaxId << " " << vLastDelete << Qt::endl;
        for (vNode v : vInfo) {
            ts << v.isExist << " " ;
            if (v.isExist){
                ts << v.sationAt->name << " ";
                QPointF center = v.sationAt->getCenter();
                ts << center.x() << " " << center.y() << Qt::endl;
            }
            else
                ts << v.invFirst << Qt::endl;
        }
        //边
        ts << eMaxId << " " << eLastDelete <<Qt::endl;
        for (eNode e : eInfo) {
            ts << e.isExist << " " ;
            if (e.isExist){
                ts << e.from << " " << e.to << " " << e.weight << " ";
                ts << (int)e.edgeAt->style << Qt::endl;
            }
            else
                ts << e.from << Qt::endl;
        }

        out.close();
        return 0;
    }
    else {
        return -1;
    }
}

int AbstractGraph::read(QString filePath)
{
    QFile in(filePath);
    if (in.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ts(&in);
        int isExist;
        //点
        ts >> vMaxId >> vLastDelete;
        vInfo.resize(vMaxId + 1);
        for (int i = 0; i <= vMaxId; ++i) {
            ts >> isExist;
            vNode v;
            v.isExist = isExist;
            if (isExist){
                QString name;
                qreal x, y;

                ts >> name >> x >> y;
                // 新建item
                v.sationAt = new MySationItem(i, QPointF(x, y), name, view);
                view->myGraphicsScene->addItem(v.sationAt);
                vInfo[i] = v;

                ++vNum;
            }
            else {
                ts >> v.invFirst;
                vInfo[i] = v;
            }
        }
        //边
        ts >> eMaxId >> eLastDelete;
        eInfo.resize(eMaxId + 1);
        posList.resize(eMaxId + 1);
        invList.resize(eMaxId + 1);
        for (int i = 0; i <= eMaxId; ++i) {
            ts >> isExist;
            eNode e;
            e.isExist = isExist;
            if (isExist){
                int style;
                ts >> e.from >> e.to >> e.weight >> style;

                // 修改正逆邻接表(头插法)
                posList[i] = vInfo[e.from].posFirst;
                vInfo[e.from].posFirst = i;
                ++vInfo[e.from].outDegree;

                invList[i] = vInfo[e.to].invFirst;
                vInfo[e.to].invFirst = i;
                ++vInfo[e.to].inDegree;

                eInfo[i] = e;

                // 新建item
                eInfo[i].edgeAt = new MyEdgeItem(i, (enum myShape)style, view);
                eInfo[i].edgeAt->setZValue(-1);
                view->myGraphicsScene->addItem(eInfo[i].edgeAt);

                ++eNum;
            }
            else {
                ts >> e.from;
                eInfo[i] = e;
            }
        }

        in.close();
        return 0;
    }
    else {
        return -1;
    }
}

QString AbstractGraph::printList()
{
    QString ans;
    for (vNode v : vInfo) {
        if (v.isExist) {
            ans += v.sationAt->name;
            ans += ": ";
            bool first = true;
            for (int e = v.posFirst; e != -1; e = posList[e]) {
                if (first)
                    first = false;
                else
                    ans += "->";
                ans += QString::number(e);
            }
            ans += "\n";
        }
    }

    return ans;
}

bool AbstractGraph::checkOneFromTo(int &from, int &to)
{
    from = -1, to = -1;
    // 初始化伪入度出度
    for (vNode &v : vInfo) {
        if (v.isExist) {
            v.fackInDegree = v.inDegree;
            v.fackOutDegree = v.outDegree;
            v.Ve = 0;
            v.Vl = 1000000;
            if (v.inDegree == 0) {
                if (from == -1)
                    from = v.sationAt->id;
                else
                    return false;
            }
            if (v.outDegree == 0) {
                if (to == -1)
                    to = v.sationAt->id;
                else
                    return false;
            }
        }
    }
    if (from == -1 || to == -1)
        return false;
    else
        return true;
}

QVector<int> AbstractGraph::AOE(int from, int to)
{
    QVector<int> ans;
    QStack<int> s;
    int carry, carryTime;
    int cnt = 0;
    // 正向递推
    s.push(from);
    while (!s.isEmpty()) {
        carry = s.top();
        s.pop();
        ++cnt;
        //处理递推关系 使用逆邻接表
        for (int e = vInfo[carry].invFirst; e != -1; e = invList[e]) {
            carryTime = vInfo[eInfo[e].from].Ve + eInfo[e].weight;
            if (carryTime > vInfo[carry].Ve)
                vInfo[carry].Ve = carryTime;
        }

        //接着排序 使用正邻接表
        for (int e = vInfo[carry].posFirst; e != -1; e = posList[e]) {
            --vInfo[eInfo[e].to].fackInDegree;
            if (vInfo[eInfo[e].to].fackInDegree == 0)
                s.push(eInfo[e].to);
        }
    }
    if (cnt != vNum) {
        ans.append(-1);
        return ans;
    }

    vInfo[to].Vl = vInfo[to].Ve;
    // 逆向递推
    s.push(to);
    while (!s.isEmpty()) {
        carry = s.top();
        s.pop();
        //处理递推关系 使用正邻接表
        for (int e = vInfo[carry].posFirst; e != -1; e = posList[e]) {
            carryTime = vInfo[eInfo[e].to].Vl - eInfo[e].weight;
            if (carryTime < vInfo[carry].Vl)
                vInfo[carry].Vl = carryTime;
        }

        //接着排序 使用逆邻接表
        for (int e = vInfo[carry].invFirst; e != -1; e = invList[e]) {
            --vInfo[eInfo[e].from].fackOutDegree;
            if (vInfo[eInfo[e].from].fackOutDegree == 0)
                s.push(eInfo[e].from);
        }
    }

    // 计算完点，计算边
    for (eNode &e : eInfo) {
        if (e.isExist) {
            e.e = vInfo[e.from].Ve;
            e.l = vInfo[e.to].Vl - e.weight;
            if (e.l == e.e)
                ans.append(e.edgeAt->id);
        }
    }

    return ans;
}


void MyGraphicsView::setNewSelected(QGraphicsItem* newSelectItem) {
    if (newSelectItem) {
        newSelectItem->setSelected(true);

        // 发出更新信息
        if (newSelectItem->type() == myType::mySationItem) {
            MySationItem* sation = (MySationItem*)newSelectItem;
            emit showSationInfo(sation->id, sation->name, sation->getCenter(), tupo.vInfo[sation->id].Vl, tupo.vInfo[sation->id].Ve);
        } else if (newSelectItem->type() == myType::myEdgeItem) {
            MyEdgeItem* edge = (MyEdgeItem*)newSelectItem;
            int id = edge->id;

            emit showEdgeInfo(id, tupo.eInfo[id].weight, edge->style,
                              tupo.eInfo[id].from, tupo.eInfo[id].to,
                              tupo.eInfo[id].l, tupo.eInfo[id].e, tupo.eInfo[id].l - tupo.eInfo[id].e);;
        }

        SELECTED = true;
        if (selectItem && newSelectItem != selectItem) {
            selectItem->setSelected(false);
        }
        selectItem = newSelectItem;
    } else {
        SELECTED = false;

        // 发出无需显示信息
        emit unshow();

        if (selectItem) {
            selectItem->setSelected(false);
        }
        selectItem = newSelectItem;
    }
}

MyGraphicsView::MyGraphicsView(QWidget* parent) : QGraphicsView{parent} {
    myGraphicsScene = new QGraphicsScene(parent);

    this->setScene(myGraphicsScene);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");
    this->setSceneRect(this->rect());
    this->centerOn(0, 0);

    // this->setMouseTracking(true);

    // 无滑轮
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 抗锯齿
    this->setRenderHint(QPainter::Antialiasing);

    // 指针
    this->setCursor(backModeCurser());

    //拓扑计时器
    timer.setInterval(1000);
    timer.stop();
    connect(&timer, &QTimer::timeout, this, &MyGraphicsView::oneTupoSort);
}

enum Qt::CursorShape MyGraphicsView::backModeCurser() {
    if (mode == Edit)
        return Qt::CrossCursor;
    else
        return Qt::ArrowCursor;
}

void MyGraphicsView::changeToUse()
{
    for (vNode v : tupo.vInfo) {
        if (v.isExist)
            v.sationAt->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
    mode = MODE::Use;

}

void MyGraphicsView::changeToEdit()
{
    if (SHOWING) {
        for (int e : showPath) {
            tupo.eInfo[e].edgeAt->setShowing(false);
        }
        showPath.clear();
        SHOWING = false;
    }
    for (vNode v : tupo.vInfo) {
        if (v.isExist)
            v.sationAt->setFlag(QGraphicsItem::ItemIsMovable);
    }
    mode = MODE::Edit;
}

MySationItem* MyGraphicsView::addSation(QPointF center) {
    MySationItem* newStation = tupo.addVex(center, "v");
    myGraphicsScene->addItem(newStation);
    // 更改信号
    setEdited(true);
    return newStation;
}

MyEdgeItem* MyGraphicsView::addEdge(int from,
                                    int to,
                                    enum myShape style,
                                    int weight) {
    MyEdgeItem* newEdge = tupo.addEdge(from, to, style, weight);
    newEdge->setZValue(-1);
    myGraphicsScene->addItem(newEdge);
    // 更改信号
    setEdited(true);
    return newEdge;
}

void MyGraphicsView::setEdited(bool edited)
{
    if (edited ^ EDITED){
        EDITED = edited;
        emit sendSetTitleEdited(EDITED);
    }
}


MyGraphicsView::~MyGraphicsView() {
    myGraphicsScene->clear();
}

void MyGraphicsView::wheelEvent(QWheelEvent* event) {
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QPointF cursorPoint = event->position();
#else
    QPointF cursorPoint = event->posF();
#endif
    QPointF scenePos =
        this->mapToScene(QPoint(cursorPoint.x(), cursorPoint.y()));

    qreal scaleFactor = this->transform().m11();
    int wheelDeltaValue = event->angleDelta().y();
    if (wheelDeltaValue > 0) {
        if (scaleFactor > 2)
            return;
        this->scale(1.1, 1.1);
    } else {
        if (scaleFactor < 0.5)
            return;
        this->scale(1.0 / 1.1, 1.0 / 1.1);
    }
    this->centerOn(scenePos);
}

void MyGraphicsView::mousePressEvent(QMouseEvent* event) {
    setNewSelected(nullptr);
    if (event->button() == Qt::RightButton) {
        onRightPress = true;
        lastPos = mapToScene(event->pos());
        setCursor(Qt::ClosedHandCursor);
    } else if (!onRightPress && event->button() == Qt::LeftButton) {
        QGraphicsItem* find = nullptr;
        QList<QGraphicsItem*> finds = this->items(event->pos());
        foreach (QGraphicsItem* i, finds) {
            if (i && (i->type() == myType::mySationItem ||
                      i->type() == myType::myEdgeItem)) {
                find = i;
                break;
            }
        }

        if (find) {
            // 正在点击图元设置选中
            onLeftPress = true;
            setCursor(Qt::ClosedHandCursor);
            setNewSelected(find);

        } else {
            if (mode == MODE::Edit) {
                // 去除选中，产生新点
                MySationItem* newStation = addSation(mapToScene(event->pos()));
                setNewSelected(newStation);
            }
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent* event) {
    if (onRightPress && !(event->buttons() & Qt::RightButton)) {
        onRightPress = false;
        setCursor(backModeCurser());
    }
    if (onLeftPress && !(event->buttons() & Qt::LeftButton)) {
        onLeftPress = false;
        setCursor(backModeCurser());
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent* event) {
    if (mode == MODE::Edit && SELECTED && onLeftPress && selectItem->type() == myType::mySationItem) {
        // 发出更新信息
        MySationItem* sation = (MySationItem*)selectItem;
        emit showSationInfo(sation->id, sation->name, sation->getCenter(), tupo.vInfo[sation->id].Vl, tupo.vInfo[sation->id].Ve);
    }
    if (onRightPress) {
        QPointF dp = mapToScene(event->pos()) - lastPos;
        setSceneRect(sceneRect().x() - dp.x(), sceneRect().y() - dp.y(),
                     sceneRect().width(), sceneRect().height());
        lastPos = mapToScene(event->pos());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void MyGraphicsView::checkAddEdge(int from, int to, int style, qreal weight) {
    QMessageBox message(this);
    message.setWindowTitle("警告");
    message.setIconPixmap(QPixmap(":/icon/img/warn.png"));

    if (!tupo.checkExist(from, to)) {
        message.setText("指定的点不存在");
        message.exec();
        return;
    }

    if (!tupo.checkNoLoop(from, to)) {
        message.setText("点到点不能有环");
        message.exec();
        return;
    }

    if (!tupo.checkNoRepetition(from, to)) {
        message.setText("刚刚添加了一条重边！确认是否必要");
        message.exec();
    }

    MyEdgeItem* newEdge = tupo.addEdge(from, to, (enum myShape)style, weight);
    newEdge->setZValue(-1);
    myGraphicsScene->addItem(newEdge);
}

void MyGraphicsView::setSationName(int id, QString name) {
    tupo.vInfo[id].sationAt->name = name;
    tupo.vInfo[id].sationAt->text->setPlainText(name);
    // 更改信号
    setEdited(true);
}

void MyGraphicsView::setSationCenter(int id, QPointF center) {
    MySationItem* sation = tupo.vInfo[id].sationAt;
    sation->rePaint(center);
    // 更改信号
    setEdited(true);
}


void MyGraphicsView::setEdgeWeight(int id, qreal weight) {
    tupo.setEdgeWeidght(id, weight);
    tupo.eInfo[id].edgeAt->reSetPath();
    // 更改信号
    setEdited(true);
}

void MyGraphicsView::setEdgeStyle(int id, int style) {
    tupo.eInfo[id].edgeAt->style = (enum myShape)style;
    tupo.eInfo[id].edgeAt->reSetPath();
    // 更改信号
    setEdited(true);
}

void MyGraphicsView::replySave(QString filePath)
{
    tupo.save(filePath);
    setEdited(false);
}

void MyGraphicsView::replyOther(QString otherPath)
{
    tupo.save(otherPath);
}

void MyGraphicsView::replyRead(QString filePath)
{
    tupo.read(filePath);
}

void MyGraphicsView::replyPrintList()
{
    emit sendText("邻接表:\n" + tupo.printList());
}

void MyGraphicsView::replyTupoSort()
{
    if (SHOWING) {
        for (int e : showPath) {
            tupo.eInfo[e].edgeAt->setShowing(false);
        }
        showPath.clear();
        SHOWING = false;
    }

    // 伪入度初始化
    s.clear();
    for (vNode &v : tupo.vInfo) {
        if (v.isExist) {
            v.fackInDegree = v.inDegree;
            v.sationAt->setTextName(false);
            if (v.inDegree == 0) {
                s.push(v.sationAt->id);
                v.sationAt->setShowing(true);
            }
        }
    }

    //开始拓扑排序
    ansList.clear();
    emit sendText("拓扑排序开始");

    timer.start(1000);
}

void MyGraphicsView::oneTupoSort()
{
    if (s.isEmpty()) {
        timer.stop();
        endTupoSort();
    }
    else {
        int carry = s.top();
        s.pop();

        tupo.vInfo[carry].sationAt->setShowing(false);
        tupo.vInfo[carry].sationAt->setVisible(false);
        ansList.append(carry);

        for (int e = tupo.vInfo[carry].posFirst; e != -1; e = tupo.posList[e]) {
            --tupo.vInfo[tupo.eInfo[e].to].fackInDegree;
            tupo.vInfo[tupo.eInfo[e].to].sationAt->setTextName(false);
            tupo.eInfo[e].edgeAt->setVisible(false);

            if (tupo.vInfo[tupo.eInfo[e].to].fackInDegree == 0) {
                s.push(tupo.eInfo[e].to);
                tupo.vInfo[tupo.eInfo[e].to].sationAt->setShowing(true);
            }
        }
    }
}

void MyGraphicsView::replyAOE()
{
    if (SHOWING) {
        for (int e : showPath) {
            tupo.eInfo[e].edgeAt->setShowing(false);
        }
        showPath.clear();
        SHOWING = false;
    }

    int from, to;
    if (!tupo.checkOneFromTo(from, to)) {
        QMessageBox message;
        message.setWindowTitle("警告");
        message.setIconPixmap(QPixmap(":/icon/img/warn.png"));
        message.setText("必须只有一个源点(入度为0),只有一个汇点(出度为0)");
        message.exec();
        return;
    }

    showPath = tupo.AOE(from, to);
    if (!showPath.isEmpty() && showPath[0] == -1) {
        showPath.clear();
        QMessageBox message;
        message.setWindowTitle("警告");
        message.setIconPixmap(QPixmap(":/icon/img/warn.png"));
        message.setText("给定有向图存在环,无法计算");
        message.exec();
        return;
    }
    else {
        for (int e : showPath) {
            tupo.eInfo[e].edgeAt->setShowing(true);
        }
        SHOWING = true;
    }

    emit sendText("计算关键路径完成，已用红色标出，点击点或边查看相关信息");
}



void MyGraphicsView::endTupoSort()
{
    // 重新显示
    for (vNode v : tupo.vInfo) {
        if (v.isExist) {
            v.sationAt->setVisible(true);
            v.sationAt->setTextName(true);
        }
    }
    for (eNode e : tupo.eInfo) {
        if (e.isExist)
            e.edgeAt->setVisible(true);
    }

    //文本
    QString text;
    if (ansList.size() == tupo.vNum) {
        text += "点编号顺序为\n";
        bool first = true;
        for (int v : ansList) {
            if (first)
                first = false;
            else
                text += "->";
            text += QString::number(v);
        }
    }
    else {
        text += "图中存在环，无法继续排序";
    }

    emit sendUnSorting();
    emit sendText("拓扑排序完成\n" + text);
}

/*------------------------------MySationItem------------------------------*/

MySationItem::MySationItem(int id,
                           QPointF center,
                           QString name,
                           MyGraphicsView* view)
    : QGraphicsEllipseItem() {
    this->id = id;
    this->name = name;
    this->view = view;

    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsScenePositionChanges);

    setPen(myPen);
    // 画刷 - 背景色
    setBrush(QBrush(nullColor));

    setRect(QRect(center.x() - size, center.y() - size, 2 * size, 2 * size));
    // 文字
    this->text = new QGraphicsTextItem(name, this);
    text->setFont(myFont);
    text->setPos(this->rect().x() + 2 * size, this->rect().y() - size - fontSize - 2);
}

MySationItem::~MySationItem()
{
    if (text)
        delete text;
}

void MySationItem::rePaint(QPointF center) {
    if (SHOWING)
        setBrush(QBrush(showColor));
    else
        setBrush(QBrush(nullColor));

    setRect(QRect(-size, -size, 2 * size, 2 * size));
    setPos(center.x(), center.y());
    // 文字
    text->setPos(this->rect().x() + 2 * size, this->rect().y() - size - fontSize - 2);
    itemChange(ItemScenePositionHasChanged, QVariant());
}

QVariant MySationItem::itemChange(GraphicsItemChange change,
                                  const QVariant& value) {
    if (change == ItemScenePositionHasChanged) {
        for (int e = view->tupo.vInfo[id].posFirst; e != -1;
             e = view->tupo.posList[e])
            view->tupo.eInfo[e].edgeAt->reSetPath();
        for (int e = view->tupo.vInfo[id].invFirst; e != -1;
             e = view->tupo.invList[e])
            view->tupo.eInfo[e].edgeAt->reSetPath();
        // 更改信号
        view->setEdited(true);
    }
    return QGraphicsItem::itemChange(change, value);
}

QPointF MySationItem::getCenter() {
    return mapToScene(rect().center());
}

void MySationItem::setTextName(bool isName)
{
    if (isName) {
        text->setPlainText(name);
        text->setPos(this->rect().x() + 2 * size, this->rect().y() - size - fontSize - 2);
    }
    else {
        text->setPlainText(QString::number(view->tupo.vInfo[this->id].fackInDegree));
        text->setPos(this->rect().x() + 2 * size, this->rect().y() - size - fontSize - 2);
    }
}

void MySationItem::setShowing(bool showing)
{
    if (SHOWING ^ showing) {
        SHOWING = showing;
        if (SHOWING)
            setBrush(QBrush(showColor));
        else
            setBrush(QBrush(nullColor));
    }
}

/*------------------------------MyEdgeItem------------------------------*/
MyEdgeItem::MyEdgeItem(int id, enum myShape style, MyGraphicsView* view)
    : QGraphicsPathItem() {
    this->id = id;
    this->view = view;
    this->style = style;

    secondLine = new QGraphicsPathItem(this);
    text = new QGraphicsTextItem(this);
    text->setFont(myFont);
    text->setZValue(1);

    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable, false);

    reSetStyle();
    reSetPath();
}

MyEdgeItem::~MyEdgeItem()
{
    if (text)
        delete text;
}

void MyEdgeItem::reSetStyle() {
    // 颜色
    QColor color;
    if (SHOWING)
        color = showColor;
    else
        color = edgeColor;

    this->setPen(QPen(color, myPenWidth / 2));
    secondLine->setPen(QPen(color, myPenWidth / 2));
}

void MyEdgeItem::reSetPath() {
    // 获取起点和终点
    QPointF startCenter =
        view->tupo.vInfo[view->tupo.eInfo[id].from].sationAt->getCenter();
    QPointF endCenter =
        view->tupo.vInfo[view->tupo.eInfo[id].to].sationAt->getCenter();

    QPainterPath pathL;
    QPainterPath pathR;

    switch((int)style){
    case (int)myShape::straight:{
        // 线样式
        qreal len = sqrt(
            (startCenter.x() - endCenter.x()) * (startCenter.x() - endCenter.x()) +
            (startCenter.y() - endCenter.y()) * (startCenter.y() - endCenter.y()));
        qreal sina = (endCenter.x() - startCenter.x()) / len;
        qreal cosa = (endCenter.y() - startCenter.y()) / len;
        // 一直线
        QPointF startL = QPointF(startCenter.x() - edgeSpace * cosa,
                                 startCenter.y() + edgeSpace * sina);
        QPointF endL = QPointF(endCenter.x() - edgeSpace * cosa,
                               endCenter.y() + edgeSpace * sina);
        QPointF leftArrowPos = (startL + endL * 2) / 3;
        pathL.moveTo(startL);
        pathL.lineTo(endL);
        // 加左箭头
        QPointF leftArrowEnd =
            QPointF(leftArrowPos.x() - (sina * cos(arrowAngle) - cosa * sin(arrowAngle)) * arrowLength,
                    leftArrowPos.y() - (cosa * cos(arrowAngle) + sina * sin(arrowAngle)) * arrowLength);
        pathL.moveTo(leftArrowEnd);
        pathL.lineTo(leftArrowPos);
        // this->setPath(pathL);

        // 二直线
        QPointF startR =
            QPointF(startCenter.x() - (edgeSpace + myPenWidth / 2) * cosa,
                    startCenter.y() + (edgeSpace + myPenWidth / 2) * sina);
        QPointF endR = QPointF(endCenter.x() - (edgeSpace + myPenWidth / 2) * cosa,
                               endCenter.y() + (edgeSpace + myPenWidth / 2) * sina);
        QPointF rightArrowPos = (startR + endR * 2) / 3;
        pathR.moveTo(startR);
        pathR.lineTo(endR);
        // 加右箭头
        QPointF rightArrowEnd =
            QPointF(rightArrowPos.x() - (sina * cos(arrowAngle) + cosa * sin(arrowAngle)) * arrowLength,
                    rightArrowPos.y() - (cosa * cos(arrowAngle) - sina * sin(arrowAngle)) * arrowLength);
        pathR.moveTo(rightArrowEnd);
        pathR.lineTo(rightArrowPos);
        secondLine->setPath(pathR);

        // 碰撞范围
        pathL.addPath(pathR);
        this->setPath(pathL);

        // 文字
        text->setPos((startR + endR) / 2);
        text->setPlainText(QString::number(view->tupo.eInfo[id].weight));
    }
        break;

    case (int)myShape::cross_down: {
        //先横后竖
        // 一折线
        QPointF startL;
        if (startCenter.x() < endCenter.x())
            startL = QPointF(startCenter.x(), startCenter.y() + edgeSpace);
        else
            startL = QPointF(startCenter.x(), startCenter.y() - edgeSpace);

        QPointF endL;
        if (startCenter.y() < endCenter.y())
            endL = QPointF(endCenter.x() - edgeSpace, endCenter.y());
        else
            endL = QPointF(endCenter.x() + edgeSpace, endCenter.y());

        QPointF midL = QPointF(endL.x(), startL.y());

        QPointF leftArrowPos = (midL + endL) / 2;
        pathL.moveTo(startL);
        pathL.lineTo(midL);
        pathL.moveTo(midL);
        pathL.lineTo(endL);
        // 加左箭头
        qreal a;
        if (startCenter.y() < endCenter.y())
            a = M_PI / 2;
        else
            a = -M_PI / 2;

        QPointF leftArrowEnd =
            QPointF(leftArrowPos.x() - (cos(a) * cos(arrowAngle) - sin(a) * sin(arrowAngle)) * arrowLength,
                    leftArrowPos.y() - (sin(a) * cos(arrowAngle) + cos(a) * sin(arrowAngle)) * arrowLength);
        pathL.moveTo(leftArrowEnd);
        pathL.lineTo(leftArrowPos);
        // this->setPath(pathL);

        // 二折线
        QPointF startR;
        if (startCenter.x() < endCenter.x())
            startR = QPointF(startCenter.x(), startCenter.y() + (edgeSpace + myPenWidth / 2));
        else
            startR = QPointF(startCenter.x(), startCenter.y() - (edgeSpace + myPenWidth / 2));

        QPointF endR;
        if (startCenter.y() < endCenter.y())
            endR = QPointF(endCenter.x() - (edgeSpace + myPenWidth / 2), endCenter.y());
        else
            endR = QPointF(endCenter.x() + (edgeSpace + myPenWidth / 2), endCenter.y());

        QPointF midR = QPointF(endR.x(), startR.y());

        QPointF rightArrowPos = (midR + endR) / 2;
        rightArrowPos.setY(leftArrowPos.y());
        pathR.moveTo(startR);
        pathR.lineTo(midR);
        pathR.moveTo(midR);
        pathR.lineTo(endR);

        // 加右箭头
        QPointF rightArrowEnd =
            QPointF(rightArrowPos.x() - (cos(a) * cos(arrowAngle) + sin(a) * sin(arrowAngle)) * arrowLength,
                    rightArrowPos.y() - (sin(a) * cos(arrowAngle) - cos(a) * sin(arrowAngle)) * arrowLength);
        pathR.moveTo(rightArrowEnd);
        pathR.lineTo(rightArrowPos);
        secondLine->setPath(pathR);

        // 碰撞范围
        pathL.addPath(pathR);
        this->setPath(pathL);

        // 文字
        text->setPos(midR);
        text->setPlainText(QString::number(view->tupo.eInfo[id].weight));
    }
        break;

    case (int)myShape::down_cross: {
        //先横后竖
        // 一折线
        QPointF startL;
        if (startCenter.y() < endCenter.y())
            startL = QPointF(startCenter.x() - edgeSpace, startCenter.y());
        else
            startL = QPointF(startCenter.x() + edgeSpace, startCenter.y());

        QPointF endL;
        if (startCenter.x() < endCenter.x())
            endL = QPointF(endCenter.x(), endCenter.y() + edgeSpace);
        else
            endL = QPointF(endCenter.x(), endCenter.y() - edgeSpace);

        QPointF midL = QPointF(startL.x(), endL.y());

        QPointF leftArrowPos = (midL + endL) / 2;
        pathL.moveTo(startL);
        pathL.lineTo(midL);
        pathL.moveTo(midL);
        pathL.lineTo(endL);
        // 加左箭头
        qreal a;
        if (startCenter.x() < endCenter.x())
            a = 0;
        else
            a = M_PI;

        QPointF leftArrowEnd =
            QPointF(leftArrowPos.x() - (cos(a) * cos(arrowAngle) - sin(a) * sin(arrowAngle)) * arrowLength,
                    leftArrowPos.y() - (sin(a) * cos(arrowAngle) + cos(a) * sin(arrowAngle)) * arrowLength);
        pathL.moveTo(leftArrowEnd);
        pathL.lineTo(leftArrowPos);
        // this->setPath(pathL);

        // 二折线
        QPointF startR;
        if (startCenter.y() < endCenter.y())
            startR = QPointF(startCenter.x() - (edgeSpace + myPenWidth / 2), startCenter.y());
        else
            startR = QPointF(startCenter.x() + (edgeSpace + myPenWidth / 2), startCenter.y());

        QPointF endR;
        if (startCenter.x() < endCenter.x())
            endR = QPointF(endCenter.x(), endCenter.y() + (edgeSpace + myPenWidth / 2));
        else
            endR = QPointF(endCenter.x(), endCenter.y() - (edgeSpace + myPenWidth / 2));

        QPointF midR = QPointF(startR.x(), endR.y());

        QPointF rightArrowPos = (midR + endR) / 2;
        rightArrowPos.setX(leftArrowPos.x());
        pathR.moveTo(startR);
        pathR.lineTo(midR);
        pathR.moveTo(midR);
        pathR.lineTo(endR);
        // 加右箭头
        QPointF rightArrowEnd =
            QPointF(rightArrowPos.x() - (cos(a) * cos(arrowAngle) + sin(a) * sin(arrowAngle)) * arrowLength,
                    rightArrowPos.y() - (sin(a) * cos(arrowAngle) - cos(a) * sin(arrowAngle)) * arrowLength);
        pathR.moveTo(rightArrowEnd);
        pathR.lineTo(rightArrowPos);
        secondLine->setPath(pathR);

        // 碰撞范围
        pathL.addPath(pathR);
        this->setPath(pathL);

        // 文字
        text->setPos(midR);
        text->setPlainText(QString::number(view->tupo.eInfo[id].weight));
    }
        break;

    }
}

void MyEdgeItem::setShowing(bool showing)
{
    if (SHOWING ^ showing) {
        SHOWING = showing;
        reSetStyle();
    }
}
