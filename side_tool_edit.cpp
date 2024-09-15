#include "side_tool_edit.h"
#include "ui_side_tool_edit.h"

SideToolEdit::SideToolEdit(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SideToolEdit)
{
    ui->setupUi(this);

    //信息栏
    information = new QStackedWidget(this);
    infoSation = new InfoSation(information);
    infoEdge = new InfoEdge(information);

    information->addWidget(infoSation);
    information->addWidget(infoEdge);

    ui->verticalLayout_2->addWidget(information);
    information->hide();

    //添加边
    connect(ui->addEdgeButton, &QPushButton::clicked, this, &SideToolEdit::addEdge);
    //查询请求
    connect(ui->button_list, &QPushButton::clicked, this, &SideToolEdit::sendPrintList);
    connect(ui->button_sort, &QPushButton::clicked, this, &SideToolEdit::setSorting);
    connect(ui->button_aoe, &QPushButton::clicked, this, &SideToolEdit::sendAOE);
    //提示
    connect(ui->tipsButton, &QPushButton::clicked, this, &SideToolEdit::showTips);
}

SideToolEdit::~SideToolEdit()
{
    delete ui;
}

void SideToolEdit::setModeEdit()
{
    ui->useBox->setVisible(false);
    ui->addEdgeGroup->setVisible(true);

    //信息栏
    infoSation->setModeEdit();
    infoEdge->setModeEdit();
}

void SideToolEdit::setModeUse()
{
    ui->addEdgeGroup->setVisible(false);
    ui->useBox->setVisible(true);

    //信息栏
    infoSation->setModeUse();
    infoEdge->setModeUse();
}

void SideToolEdit::setInfoSation(int id, QString name, QPointF center, int Vl, int Ve)
{
    infoSation->setInfo(id, name, center, Vl, Ve);
    information->setCurrentIndex(0);
    information->show();
    ui->addEdgeButton->setEnabled(true);
}

void SideToolEdit::setInfoEdge(int id, int weight, int style, int from, int to, int l, int e, int le)
{
    infoEdge->setInfo(id, weight, style, from, to, l, e, le);
    information->setCurrentIndex(1);
    information->show();
    ui->addEdgeButton->setEnabled(false);
}

void SideToolEdit::setInfoClose()
{
    information->hide();
    ui->addEdgeButton->setEnabled(false);
}

void SideToolEdit::setSorting()
{
    ui->useBox->setEnabled(false);
    emit sendTupoSort();
}

void SideToolEdit::setUnSorting()
{
    ui->useBox->setEnabled(true);
}


void SideToolEdit::setText(QString way)
{
    ui->textEdit->setPlainText(way);
}

void SideToolEdit::showTips()
{
    QMessageBox message(this);
    message.setWindowTitle("提示");
    message.setIconPixmap(QPixmap(":/icon/img/tips.png"));
    message.setText("模式：编辑模式和使用模式\n\n"
                    "操作：左键单击空白添加站点，点或边则选中查看信息\n"
                    "可以修改部分信息；左键拖动站点，滚轮放缩，右键拖动界面\n"
                    "选中点时，才可以根据此点添加边\n"
                    "使用模式下，点击计算关键路径后才可以正确查看相关信息\n\n"
                    "注意：直接关闭不会提示未保存\n"
                    "重边设置不同边形避免图形重叠");
    message.exec();
}

void SideToolEdit::addEdge()
{
    if(!(information->isVisible() && information->currentIndex() == 0))
        return;

    int from, to;
    if (ui->directBox->currentIndex() == 0) {
        from = infoSation->id;
        to = ui->vexBox->value();
    }
    else {
        from = ui->vexBox->value();
        to = infoSation->id;
    }

    emit sendAddEdge(from, to, ui->styleBox->currentIndex(), ui->lengthSpinBox->value());
}

