/********************************************************************************
** Form generated from reading UI file 'drivedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRIVEDIALOG_H
#define UI_DRIVEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DriveDialog
{
public:
    QFormLayout *formLayout;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *doubleSpinBox_4;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_5;
    QDoubleSpinBox *doubleSpinBox_5;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *doubleSpinBox_3;
    QLabel *label_3;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout_6;
    QDoubleSpinBox *doubleSpinBox_6;
    QLabel *label_5;

    void setupUi(QDialog *DriveDialog)
    {
        if (DriveDialog->objectName().isEmpty())
            DriveDialog->setObjectName(QStringLiteral("DriveDialog"));
        DriveDialog->resize(566, 180);
        formLayout = new QFormLayout(DriveDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        checkBox = new QCheckBox(DriveDialog);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, checkBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        doubleSpinBox = new QDoubleSpinBox(DriveDialog);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        horizontalLayout->addWidget(doubleSpinBox);

        label = new QLabel(DriveDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        doubleSpinBox_4 = new QDoubleSpinBox(DriveDialog);
        doubleSpinBox_4->setObjectName(QStringLiteral("doubleSpinBox_4"));

        horizontalLayout_4->addWidget(doubleSpinBox_4);

        label_4 = new QLabel(DriveDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        doubleSpinBox_2 = new QDoubleSpinBox(DriveDialog);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));

        horizontalLayout_2->addWidget(doubleSpinBox_2);

        label_2 = new QLabel(DriveDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        doubleSpinBox_5 = new QDoubleSpinBox(DriveDialog);
        doubleSpinBox_5->setObjectName(QStringLiteral("doubleSpinBox_5"));

        horizontalLayout_5->addWidget(doubleSpinBox_5);

        label_6 = new QLabel(DriveDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_5->addWidget(label_6);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        doubleSpinBox_3 = new QDoubleSpinBox(DriveDialog);
        doubleSpinBox_3->setObjectName(QStringLiteral("doubleSpinBox_3"));

        horizontalLayout_3->addWidget(doubleSpinBox_3);

        label_3 = new QLabel(DriveDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);


        formLayout->setLayout(3, QFormLayout::LabelRole, horizontalLayout_3);

        buttonBox = new QDialogButtonBox(DriveDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(5, QFormLayout::SpanningRole, buttonBox);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        doubleSpinBox_6 = new QDoubleSpinBox(DriveDialog);
        doubleSpinBox_6->setObjectName(QStringLiteral("doubleSpinBox_6"));

        horizontalLayout_6->addWidget(doubleSpinBox_6);

        label_5 = new QLabel(DriveDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);


        formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayout_6);


        retranslateUi(DriveDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), DriveDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DriveDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DriveDialog);
    } // setupUi

    void retranslateUi(QDialog *DriveDialog)
    {
        DriveDialog->setWindowTitle(QApplication::translate("DriveDialog", "Dialog", nullptr));
        checkBox->setText(QApplication::translate("DriveDialog", "do-measurement", nullptr));
        label->setText(QApplication::translate("DriveDialog", "Distance", nullptr));
        label_4->setText(QApplication::translate("DriveDialog", "Measurement time", nullptr));
        label_2->setText(QApplication::translate("DriveDialog", "Drive speed", nullptr));
        label_6->setText(QApplication::translate("DriveDialog", "Deacceleration", nullptr));
        label_3->setText(QApplication::translate("DriveDialog", "Measurement speed", nullptr));
        label_5->setText(QApplication::translate("DriveDialog", "Acceleration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DriveDialog: public Ui_DriveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRIVEDIALOG_H
