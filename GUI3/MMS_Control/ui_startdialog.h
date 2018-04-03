/********************************************************************************
** Form generated from reading UI file 'startdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTDIALOG_H
#define UI_STARTDIALOG_H

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

class Ui_StartDialog
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *warmupTime;
    QLabel *label;
    QDialogButtonBox *buttonBox;
    QCheckBox *Queue;

    void setupUi(QDialog *StartDialog)
    {
        if (StartDialog->objectName().isEmpty())
            StartDialog->setObjectName(QStringLiteral("StartDialog"));
        StartDialog->resize(364, 81);
        formLayout = new QFormLayout(StartDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        warmupTime = new QDoubleSpinBox(StartDialog);
        warmupTime->setObjectName(QStringLiteral("warmupTime"));

        horizontalLayout->addWidget(warmupTime);

        label = new QLabel(StartDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        buttonBox = new QDialogButtonBox(StartDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(1, QFormLayout::FieldRole, buttonBox);

        Queue = new QCheckBox(StartDialog);
        Queue->setObjectName(QStringLiteral("Queue"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Queue);


        retranslateUi(StartDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), StartDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), StartDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(StartDialog);
    } // setupUi

    void retranslateUi(QDialog *StartDialog)
    {
        StartDialog->setWindowTitle(QApplication::translate("StartDialog", "Advanced start command", nullptr));
        label->setText(QApplication::translate("StartDialog", "Warm-up time (s)", nullptr));
        Queue->setText(QApplication::translate("StartDialog", "Queue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartDialog: public Ui_StartDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTDIALOG_H
