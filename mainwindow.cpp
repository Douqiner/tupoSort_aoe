#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //切换两大模式
    QObject::connect(ui->action_use, &QAction::triggered, this, &MainWindow::setSideToolView);
    QObject::connect(ui->action_edit, &QAction::triggered, this, &MainWindow::setSideToolEdit);
    //发出信息更新需求
    QObject::connect(ui->myGraphicsView, &MyGraphicsView::showSationInfo, ui->sideToolEdit, &SideToolEdit::setInfoSation);
    QObject::connect(ui->myGraphicsView, &MyGraphicsView::showEdgeInfo, ui->sideToolEdit, &SideToolEdit::setInfoEdge);
    QObject::connect(ui->myGraphicsView, &MyGraphicsView::unshow, ui->sideToolEdit, &SideToolEdit::setInfoClose);
    //添加边
    QObject::connect(ui->sideToolEdit, &SideToolEdit::sendAddEdge, ui->myGraphicsView, &MyGraphicsView::checkAddEdge);
    //信息修改
    QObject::connect(ui->sideToolEdit->infoSation, &InfoSation::sendSetVexName, ui->myGraphicsView, &MyGraphicsView::setSationName);
    QObject::connect(ui->sideToolEdit->infoSation, &InfoSation::sendSetVexCenter, ui->myGraphicsView, &MyGraphicsView::setSationCenter);
    QObject::connect(ui->sideToolEdit->infoSation, &InfoSation::sendDeleteVex, ui->myGraphicsView, &MyGraphicsView::deleteSation);

    QObject::connect(ui->sideToolEdit->infoEdge, &InfoEdge::sendSetEdgeWeight, ui->myGraphicsView, &MyGraphicsView::setEdgeWeight);
    QObject::connect(ui->sideToolEdit->infoEdge, &InfoEdge::sendSetEdgeStyle, ui->myGraphicsView, &MyGraphicsView::setEdgeStyle);
    QObject::connect(ui->sideToolEdit->infoEdge, &InfoEdge::sendDeleteEdge, ui->myGraphicsView, &MyGraphicsView::deleteEdge);

    //是否编辑过
    QObject::connect(ui->myGraphicsView, &MyGraphicsView::sendSetTitleEdited, this, &MainWindow::setTitleEdited);
    //文件
    QObject::connect(ui->action_save, &QAction::triggered, this, &MainWindow::askSave);
    QObject::connect(ui->action_other, &QAction::triggered, this, &MainWindow::askOther);
    QObject::connect(this, &MainWindow::sendAskSave, ui->myGraphicsView, &MyGraphicsView::replySave);
    QObject::connect(this, &MainWindow::sendAskOther, ui->myGraphicsView, &MyGraphicsView::replyOther);
    QObject::connect(this, &MainWindow::sendAskRead, ui->myGraphicsView, &MyGraphicsView::replyRead);
    //--使用
    //拓扑禁断
    QObject::connect(ui->sideToolEdit, &SideToolEdit::sendTupoSort, this, &MainWindow::setSorting);
    QObject::connect(ui->myGraphicsView, &MyGraphicsView::sendUnSorting, ui->sideToolEdit, &SideToolEdit::setUnSorting);
    QObject::connect(ui->myGraphicsView, &MyGraphicsView::sendUnSorting, this, &MainWindow::setUnSorting);
    //你问我答
    QObject::connect(ui->sideToolEdit, &SideToolEdit::sendPrintList, ui->myGraphicsView, &MyGraphicsView::replyPrintList);
    QObject::connect(ui->sideToolEdit, &SideToolEdit::sendTupoSort, ui->myGraphicsView, &MyGraphicsView::replyTupoSort);
    QObject::connect(ui->sideToolEdit, &SideToolEdit::sendAOE, ui->myGraphicsView, &MyGraphicsView::replyAOE);
    QObject::connect(ui->myGraphicsView, &MyGraphicsView::sendText, ui->sideToolEdit, &SideToolEdit::setText);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::askRead()
{
    emit sendAskRead(filePath);
}

void MainWindow::setSideToolView()
{
    ui->action_use->setDisabled(true);
    ui->action_edit->setDisabled(false);
    //切换工作
    //view进行切换
    ui->myGraphicsView->changeToUse();
    //side_tool进行切换
    ui->sideToolEdit->setModeUse();
}

void MainWindow::setSideToolEdit()
{
    ui->action_use->setDisabled(false);
    ui->action_edit->setDisabled(true);
    //切换工作
    //view进行切换
    ui->myGraphicsView->changeToEdit();
    //side_tool进行切换
    ui->sideToolEdit->setModeEdit();
}

void MainWindow::setTitleEdited(bool edited)
{
    if (edited) {
        if (filePath.isEmpty())
            this->setWindowTitle("无标题*");
        else
            this->setWindowTitle(filePath + "*");
    }
    else {
        if (filePath.isEmpty())
            this->setWindowTitle("无标题");
        else
            this->setWindowTitle(filePath);
    }
}

void MainWindow::setSorting()
{
    ui->action_edit->setEnabled(false);
    ui->action_save->setEnabled(false);
    ui->action_other->setEnabled(false);
}

void MainWindow::setUnSorting()
{
    ui->action_edit->setEnabled(true);
    ui->action_save->setEnabled(true);
    ui->action_other->setEnabled(true);
}

void MainWindow::askSave()
{
    if (ui->myGraphicsView->EDITED) {
        if (filePath.isEmpty()) {
            QFileDialog f(this);
            filePath =  QFileDialog::getSaveFileName(this, "保存文件位置", QString(), "有向图文件 (*.dgh)");
            if (!filePath.isEmpty()) {
                emit sendAskSave(filePath);
            }
        }
        else
            emit sendAskSave(filePath);
    }
}

void MainWindow::askOther()
{
    QFileDialog f(this);
    QString otherPath =  QFileDialog::getSaveFileName(this, "另存文件位置", QString(), "有向图文件 (*.dgh)");
    if (!filePath.isEmpty()) {
        emit sendAskOther(otherPath);
    }
}
