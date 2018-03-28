/********************************************************************************
** Form generated from reading UI file 'measuredialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASUREDIALOG_H
#define UI_MEASUREDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_MeasureDialog
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *measureTime;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *MeasureDialog)
    {
        if (MeasureDialog->objectName().isEmpty())
            MeasureDialog->setObjectName(QStringLiteral("MeasureDialog"));
        MeasureDialog->resize(222, 85);
        formLayout = new QFormLayout(MeasureDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        measureTime = new QDoubleSpinBox(MeasureDialog);
        measureTime->setObjectName(QStringLiteral("measureTime"));

        horizontalLayout->addWidget(measureTime);

        label = new QLabel(MeasureDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);

        buttonBox = new QDialogButtonBox(MeasureDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(1, QFormLayout::LabelRole, buttonBox);


        retranslateUi(MeasureDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MeasureDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MeasureDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(MeasureDialog);
    } // setupUi

    void retranslateUi(QDialog *MeasureDialog)
    {
        MeasureDialog->setWindowTitle(QApplication::translate("MeasureDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("MeasureDialog", "Measure time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeasureDialog: public Ui_MeasureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASUREDIALOG_H
