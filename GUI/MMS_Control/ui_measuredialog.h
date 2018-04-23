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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_MeasureDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *Maxmeasure;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *Minmeasure;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *continues;
    QDialogButtonBox *buttonBox;
    QCheckBox *Queue;

    void setupUi(QDialog *MeasureDialog)
    {
        if (MeasureDialog->objectName().isEmpty())
            MeasureDialog->setObjectName(QStringLiteral("MeasureDialog"));
        MeasureDialog->resize(517, 168);
        gridLayout = new QGridLayout(MeasureDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Maxmeasure = new QDoubleSpinBox(MeasureDialog);
        Maxmeasure->setObjectName(QStringLiteral("Maxmeasure"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Maxmeasure->sizePolicy().hasHeightForWidth());
        Maxmeasure->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(Maxmeasure);

        label = new QLabel(MeasureDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Minmeasure = new QDoubleSpinBox(MeasureDialog);
        Minmeasure->setObjectName(QStringLiteral("Minmeasure"));
        sizePolicy.setHeightForWidth(Minmeasure->sizePolicy().hasHeightForWidth());
        Minmeasure->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(Minmeasure);

        label_2 = new QLabel(MeasureDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_2);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        continues = new QCheckBox(MeasureDialog);
        continues->setObjectName(QStringLiteral("continues"));

        horizontalLayout_3->addWidget(continues);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        buttonBox = new QDialogButtonBox(MeasureDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 0, 1, 1, Qt::AlignRight);

        Queue = new QCheckBox(MeasureDialog);
        Queue->setObjectName(QStringLiteral("Queue"));
        Queue->setMinimumSize(QSize(495, 0));

        gridLayout->addWidget(Queue, 5, 0, 1, 1);


        retranslateUi(MeasureDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MeasureDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MeasureDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(MeasureDialog);
    } // setupUi

    void retranslateUi(QDialog *MeasureDialog)
    {
        MeasureDialog->setWindowTitle(QApplication::translate("MeasureDialog", "Advanced measurement command", nullptr));
        label->setText(QApplication::translate("MeasureDialog", "Max measure time (s)", nullptr));
        label_2->setText(QApplication::translate("MeasureDialog", "Min measure time (s)", nullptr));
        continues->setText(QApplication::translate("MeasureDialog", "Continues measurement", nullptr));
        Queue->setText(QApplication::translate("MeasureDialog", "Queue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeasureDialog: public Ui_MeasureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASUREDIALOG_H
