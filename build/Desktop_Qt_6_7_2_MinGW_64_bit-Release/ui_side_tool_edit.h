/********************************************************************************
** Form generated from reading UI file 'side_tool_edit.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDE_TOOL_EDIT_H
#define UI_SIDE_TOOL_EDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideToolEdit
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *addEdgeGroup;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addEdgeButton;
    QComboBox *styleBox;
    QComboBox *directBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_13;
    QSpinBox *lengthSpinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *vexBox;
    QGroupBox *useBox;
    QVBoxLayout *verticalLayout_5;
    QPushButton *button_list;
    QPushButton *button_sort;
    QPushButton *button_aoe;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QPushButton *tipsButton;

    void setupUi(QWidget *SideToolEdit)
    {
        if (SideToolEdit->objectName().isEmpty())
            SideToolEdit->setObjectName("SideToolEdit");
        SideToolEdit->resize(334, 733);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SideToolEdit->sizePolicy().hasHeightForWidth());
        SideToolEdit->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(SideToolEdit);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(SideToolEdit);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 310, 709));
        verticalLayout_7 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_7->setObjectName("verticalLayout_7");
        groupBox = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(9);
        groupBox->setFont(font);
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setObjectName("verticalLayout_6");
        addEdgeGroup = new QGroupBox(groupBox);
        addEdgeGroup->setObjectName("addEdgeGroup");
        addEdgeGroup->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(addEdgeGroup->sizePolicy().hasHeightForWidth());
        addEdgeGroup->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(addEdgeGroup);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        addEdgeButton = new QPushButton(addEdgeGroup);
        addEdgeButton->setObjectName("addEdgeButton");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(addEdgeButton->sizePolicy().hasHeightForWidth());
        addEdgeButton->setSizePolicy(sizePolicy3);
        addEdgeButton->setFont(font);

        horizontalLayout_3->addWidget(addEdgeButton);

        styleBox = new QComboBox(addEdgeGroup);
        styleBox->addItem(QString());
        styleBox->addItem(QString());
        styleBox->addItem(QString());
        styleBox->setObjectName("styleBox");
        sizePolicy3.setHeightForWidth(styleBox->sizePolicy().hasHeightForWidth());
        styleBox->setSizePolicy(sizePolicy3);
        styleBox->setFont(font);

        horizontalLayout_3->addWidget(styleBox);

        directBox = new QComboBox(addEdgeGroup);
        directBox->addItem(QString());
        directBox->addItem(QString());
        directBox->setObjectName("directBox");
        sizePolicy3.setHeightForWidth(directBox->sizePolicy().hasHeightForWidth());
        directBox->setSizePolicy(sizePolicy3);
        directBox->setFont(font);

        horizontalLayout_3->addWidget(directBox);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_13 = new QLabel(addEdgeGroup);
        label_13->setObjectName("label_13");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy4);
        label_13->setFont(font);

        horizontalLayout_8->addWidget(label_13);

        lengthSpinBox = new QSpinBox(addEdgeGroup);
        lengthSpinBox->setObjectName("lengthSpinBox");

        horizontalLayout_8->addWidget(lengthSpinBox);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(addEdgeGroup);
        label->setObjectName("label");
        sizePolicy4.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy4);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        vexBox = new QSpinBox(addEdgeGroup);
        vexBox->setObjectName("vexBox");
        sizePolicy3.setHeightForWidth(vexBox->sizePolicy().hasHeightForWidth());
        vexBox->setSizePolicy(sizePolicy3);
        vexBox->setFont(font);
        vexBox->setMaximum(10000);

        horizontalLayout_2->addWidget(vexBox);


        verticalLayout_4->addLayout(horizontalLayout_2);


        verticalLayout_6->addWidget(addEdgeGroup);

        useBox = new QGroupBox(groupBox);
        useBox->setObjectName("useBox");
        sizePolicy3.setHeightForWidth(useBox->sizePolicy().hasHeightForWidth());
        useBox->setSizePolicy(sizePolicy3);
        verticalLayout_5 = new QVBoxLayout(useBox);
        verticalLayout_5->setObjectName("verticalLayout_5");
        button_list = new QPushButton(useBox);
        button_list->setObjectName("button_list");
        sizePolicy3.setHeightForWidth(button_list->sizePolicy().hasHeightForWidth());
        button_list->setSizePolicy(sizePolicy3);
        button_list->setFont(font);

        verticalLayout_5->addWidget(button_list);

        button_sort = new QPushButton(useBox);
        button_sort->setObjectName("button_sort");

        verticalLayout_5->addWidget(button_sort);

        button_aoe = new QPushButton(useBox);
        button_aoe->setObjectName("button_aoe");

        verticalLayout_5->addWidget(button_aoe);

        textEdit = new QTextEdit(useBox);
        textEdit->setObjectName("textEdit");
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        textEdit->setMaximumSize(QSize(16777215, 200));
        textEdit->setReadOnly(true);

        verticalLayout_5->addWidget(textEdit);


        verticalLayout_6->addWidget(useBox);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");

        verticalLayout_2->addWidget(widget);


        verticalLayout_6->addLayout(verticalLayout_2);

        tipsButton = new QPushButton(groupBox);
        tipsButton->setObjectName("tipsButton");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(tipsButton->sizePolicy().hasHeightForWidth());
        tipsButton->setSizePolicy(sizePolicy5);
        QFont font1;
        font1.setPointSize(12);
        tipsButton->setFont(font1);

        verticalLayout_6->addWidget(tipsButton);


        verticalLayout_7->addWidget(groupBox);

        scrollArea->setWidget(scrollAreaWidgetContents_3);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(SideToolEdit);

        QMetaObject::connectSlotsByName(SideToolEdit);
    } // setupUi

    void retranslateUi(QWidget *SideToolEdit)
    {
        SideToolEdit->setWindowTitle(QCoreApplication::translate("SideToolEdit", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SideToolEdit", "\345\267\245\345\205\267", nullptr));
        addEdgeGroup->setTitle(QCoreApplication::translate("SideToolEdit", "\346\267\273\345\212\240\350\276\271", nullptr));
        addEdgeButton->setText(QCoreApplication::translate("SideToolEdit", "\346\267\273\345\212\240", nullptr));
        styleBox->setItemText(0, QCoreApplication::translate("SideToolEdit", "\346\226\234", nullptr));
        styleBox->setItemText(1, QCoreApplication::translate("SideToolEdit", "\346\250\252\347\253\226", nullptr));
        styleBox->setItemText(2, QCoreApplication::translate("SideToolEdit", "\347\253\226\346\250\252", nullptr));

        directBox->setItemText(0, QCoreApplication::translate("SideToolEdit", "\345\207\272\350\276\271", nullptr));
        directBox->setItemText(1, QCoreApplication::translate("SideToolEdit", "\345\205\245\350\276\271", nullptr));

        label_13->setText(QCoreApplication::translate("SideToolEdit", "\350\276\271\346\235\203", nullptr));
        label->setText(QCoreApplication::translate("SideToolEdit", "\350\277\236\346\216\245\345\210\260\347\202\271", nullptr));
        useBox->setTitle(QCoreApplication::translate("SideToolEdit", "\345\212\237\350\203\275", nullptr));
        button_list->setText(QCoreApplication::translate("SideToolEdit", "\350\276\223\345\207\272\351\202\273\346\216\245\350\241\250", nullptr));
        button_sort->setText(QCoreApplication::translate("SideToolEdit", "\346\213\223\346\211\221\346\216\222\345\272\217", nullptr));
        button_aoe->setText(QCoreApplication::translate("SideToolEdit", "\350\256\241\347\256\227\345\205\263\351\224\256\350\267\257\345\276\204", nullptr));
        tipsButton->setText(QCoreApplication::translate("SideToolEdit", "\346\217\220\347\244\272\357\274\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SideToolEdit: public Ui_SideToolEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDE_TOOL_EDIT_H
