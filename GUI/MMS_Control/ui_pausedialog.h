/********************************************************************************
** Form generated from reading UI file 'pausedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAUSEDIALOG_H
#define UI_PAUSEDIALOG_H

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

class Ui_PauseDialog
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *autoResume;
    QLabel *label;
    QDialogButtonBox *buttonBox;
    QCheckBox *Queue;

    void setupUi(QDialog *PauseDialog)
    {
        if (PauseDialog->objectName().isEmpty())
            PauseDialog->setObjectName(QStringLiteral("PauseDialog"));
        PauseDialog->resize(355, 89);
        PauseDialog->setContextMenuPolicy(Qt::PreventContextMenu);
        formLayout = new QFormLayout(PauseDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        autoResume = new QDoubleSpinBox(PauseDialog);
        autoResume->setObjectName(QStringLiteral("autoResume"));
        autoResume->setReadOnly(false);
        autoResume->setAccelerated(true);

        horizontalLayout->addWidget(autoResume);

        label = new QLabel(PauseDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        buttonBox = new QDialogButtonBox(PauseDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        formLayout->setWidget(1, QFormLayout::FieldRole, buttonBox);

        Queue = new QCheckBox(PauseDialog);
        Queue->setObjectName(QStringLiteral("Queue"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Queue);


        retranslateUi(PauseDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PauseDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PauseDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PauseDialog);
    } // setupUi

    void retranslateUi(QDialog *PauseDialog)
    {
        PauseDialog->setWindowTitle(QApplication::translate("PauseDialog", "Advanced pause comand", nullptr));
        label->setText(QApplication::translate("PauseDialog", "Auto resume (s)", nullptr));
        Queue->setText(QApplication::translate("PauseDialog", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PauseDialog: public Ui_PauseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAUSEDIALOG_H
