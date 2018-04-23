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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_DriveDialog
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QCheckBox *doMeasurement;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *distance;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *driveSpeed;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *measurementSpeed;
    QLabel *label_3;
    QFormLayout *formLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *measurementTime;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_6;
    QDoubleSpinBox *acceleration;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_5;
    QDoubleSpinBox *deacceleration;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_7;
    QDoubleSpinBox *marge;
    QLabel *label_7;
    QDialogButtonBox *buttonBox;
    QCheckBox *Queue;

    void setupUi(QDialog *DriveDialog)
    {
        if (DriveDialog->objectName().isEmpty())
            DriveDialog->setObjectName(QStringLiteral("DriveDialog"));
        DriveDialog->resize(502, 191);
        gridLayout = new QGridLayout(DriveDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        doMeasurement = new QCheckBox(DriveDialog);
        doMeasurement->setObjectName(QStringLiteral("doMeasurement"));

        formLayout->setWidget(0, QFormLayout::LabelRole, doMeasurement);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        distance = new QDoubleSpinBox(DriveDialog);
        distance->setObjectName(QStringLiteral("distance"));

        horizontalLayout->addWidget(distance);

        label = new QLabel(DriveDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        driveSpeed = new QDoubleSpinBox(DriveDialog);
        driveSpeed->setObjectName(QStringLiteral("driveSpeed"));

        horizontalLayout_2->addWidget(driveSpeed);

        label_2 = new QLabel(DriveDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        measurementSpeed = new QDoubleSpinBox(DriveDialog);
        measurementSpeed->setObjectName(QStringLiteral("measurementSpeed"));

        horizontalLayout_3->addWidget(measurementSpeed);

        label_3 = new QLabel(DriveDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);


        formLayout->setLayout(3, QFormLayout::LabelRole, horizontalLayout_3);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        measurementTime = new QDoubleSpinBox(DriveDialog);
        measurementTime->setObjectName(QStringLiteral("measurementTime"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(measurementTime->sizePolicy().hasHeightForWidth());
        measurementTime->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(measurementTime);

        label_4 = new QLabel(DriveDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);


        formLayout_2->setLayout(0, QFormLayout::LabelRole, horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        acceleration = new QDoubleSpinBox(DriveDialog);
        acceleration->setObjectName(QStringLiteral("acceleration"));
        sizePolicy.setHeightForWidth(acceleration->sizePolicy().hasHeightForWidth());
        acceleration->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(acceleration);

        label_5 = new QLabel(DriveDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_6->addWidget(label_5);


        formLayout_2->setLayout(1, QFormLayout::LabelRole, horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        deacceleration = new QDoubleSpinBox(DriveDialog);
        deacceleration->setObjectName(QStringLiteral("deacceleration"));
        sizePolicy.setHeightForWidth(deacceleration->sizePolicy().hasHeightForWidth());
        deacceleration->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(deacceleration);

        label_6 = new QLabel(DriveDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_5->addWidget(label_6);


        formLayout_2->setLayout(2, QFormLayout::LabelRole, horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        marge = new QDoubleSpinBox(DriveDialog);
        marge->setObjectName(QStringLiteral("marge"));
        sizePolicy.setHeightForWidth(marge->sizePolicy().hasHeightForWidth());
        marge->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(marge);

        label_7 = new QLabel(DriveDialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);


        formLayout_2->setLayout(3, QFormLayout::LabelRole, horizontalLayout_7);


        gridLayout->addLayout(formLayout_2, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(DriveDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 2, 1, 1, 1);

        Queue = new QCheckBox(DriveDialog);
        Queue->setObjectName(QStringLiteral("Queue"));

        gridLayout->addWidget(Queue, 2, 0, 1, 1);


        retranslateUi(DriveDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), DriveDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DriveDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DriveDialog);
    } // setupUi

    void retranslateUi(QDialog *DriveDialog)
    {
        DriveDialog->setWindowTitle(QApplication::translate("DriveDialog", "Advanced drive command", nullptr));
        doMeasurement->setText(QApplication::translate("DriveDialog", "Measure", nullptr));
        label->setText(QApplication::translate("DriveDialog", "Distance (m)", nullptr));
        label_2->setText(QApplication::translate("DriveDialog", "Driving speed (m/s)", nullptr));
        label_3->setText(QApplication::translate("DriveDialog", "Measurement speed (m/s)", nullptr));
        label_4->setText(QApplication::translate("DriveDialog", "Measurement time (s)", nullptr));
        label_5->setText(QApplication::translate("DriveDialog", "Acceleration (m/s/s)", nullptr));
        label_6->setText(QApplication::translate("DriveDialog", "Deacceleration (m/s/s)", nullptr));
        label_7->setText(QApplication::translate("DriveDialog", "Marge (s)", nullptr));
        Queue->setText(QApplication::translate("DriveDialog", "Queue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DriveDialog: public Ui_DriveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRIVEDIALOG_H
