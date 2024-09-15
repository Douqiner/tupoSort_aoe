/********************************************************************************
** Form generated from reading UI file 'info_sation.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFO_SATION_H
#define UI_INFO_SATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfoSation
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *idLineEdit;
    QLabel *label_3;
    QLineEdit *nameLineEdit;
    QLabel *label_6;
    QDoubleSpinBox *xSpinBox;
    QLabel *label_8;
    QDoubleSpinBox *ySpinBox;
    QLabel *label;
    QSpinBox *spinBoxVe;
    QLabel *label_13;
    QSpinBox *spinBoxVl;
    QPushButton *deleteButton;

    void setupUi(QWidget *InfoSation)
    {
        if (InfoSation->objectName().isEmpty())
            InfoSation->setObjectName("InfoSation");
        InfoSation->resize(202, 310);
        verticalLayout = new QVBoxLayout(InfoSation);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(InfoSation);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        QFont font;
        font.setPointSize(9);
        label_2->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        idLineEdit = new QLineEdit(groupBox);
        idLineEdit->setObjectName("idLineEdit");
        sizePolicy.setHeightForWidth(idLineEdit->sizePolicy().hasHeightForWidth());
        idLineEdit->setSizePolicy(sizePolicy);
        idLineEdit->setFont(font);
        idLineEdit->setDragEnabled(false);
        idLineEdit->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, idLineEdit);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        nameLineEdit = new QLineEdit(groupBox);
        nameLineEdit->setObjectName("nameLineEdit");
        sizePolicy.setHeightForWidth(nameLineEdit->sizePolicy().hasHeightForWidth());
        nameLineEdit->setSizePolicy(sizePolicy);
        nameLineEdit->setFont(font);
        nameLineEdit->setDragEnabled(false);
        nameLineEdit->setReadOnly(false);

        formLayout->setWidget(1, QFormLayout::FieldRole, nameLineEdit);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_6);

        xSpinBox = new QDoubleSpinBox(groupBox);
        xSpinBox->setObjectName("xSpinBox");
        xSpinBox->setFont(font);
        xSpinBox->setMinimum(-10000.000000000000000);
        xSpinBox->setMaximum(10000.000000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, xSpinBox);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setFont(font);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_8);

        ySpinBox = new QDoubleSpinBox(groupBox);
        ySpinBox->setObjectName("ySpinBox");
        ySpinBox->setFont(font);
        ySpinBox->setMinimum(-10000.000000000000000);
        ySpinBox->setMaximum(10000.000000000000000);

        formLayout->setWidget(3, QFormLayout::FieldRole, ySpinBox);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        formLayout->setWidget(4, QFormLayout::LabelRole, label);

        spinBoxVe = new QSpinBox(groupBox);
        spinBoxVe->setObjectName("spinBoxVe");
        spinBoxVe->setReadOnly(true);
        spinBoxVe->setMinimum(-100000);
        spinBoxVe->setMaximum(100000);

        formLayout->setWidget(4, QFormLayout::FieldRole, spinBoxVe);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName("label_13");

        formLayout->setWidget(5, QFormLayout::LabelRole, label_13);

        spinBoxVl = new QSpinBox(groupBox);
        spinBoxVl->setObjectName("spinBoxVl");
        spinBoxVl->setReadOnly(true);
        spinBoxVl->setMinimum(-100000);
        spinBoxVl->setMaximum(100000);

        formLayout->setWidget(5, QFormLayout::FieldRole, spinBoxVl);


        verticalLayout_2->addLayout(formLayout);

        deleteButton = new QPushButton(groupBox);
        deleteButton->setObjectName("deleteButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(deleteButton->sizePolicy().hasHeightForWidth());
        deleteButton->setSizePolicy(sizePolicy1);
        deleteButton->setFont(font);

        verticalLayout_2->addWidget(deleteButton);


        verticalLayout->addWidget(groupBox);


        retranslateUi(InfoSation);

        QMetaObject::connectSlotsByName(InfoSation);
    } // setupUi

    void retranslateUi(QWidget *InfoSation)
    {
        InfoSation->setWindowTitle(QCoreApplication::translate("InfoSation", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("InfoSation", "\344\277\241\346\201\257", nullptr));
        label_2->setText(QCoreApplication::translate("InfoSation", "\347\274\226\345\217\267", nullptr));
        label_3->setText(QCoreApplication::translate("InfoSation", "\345\220\215\347\247\260", nullptr));
        label_6->setText(QCoreApplication::translate("InfoSation", "x\345\235\220\346\240\207", nullptr));
        label_8->setText(QCoreApplication::translate("InfoSation", "y\345\235\220\346\240\207", nullptr));
        label->setText(QCoreApplication::translate("InfoSation", "Ve", nullptr));
        label_13->setText(QCoreApplication::translate("InfoSation", "Vl", nullptr));
        deleteButton->setText(QCoreApplication::translate("InfoSation", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InfoSation: public Ui_InfoSation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_SATION_H
