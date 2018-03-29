/********************************************************************************
** Form generated from reading UI file 'automaticmode.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOMATICMODE_H
#define UI_AUTOMATICMODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout_2;
    QCheckBox *doMeasurement;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *distance;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *drivingSpeed;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *measurmentSpeed;
    QLabel *label_3;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *measurementTime;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_5;
    QDoubleSpinBox *acceleration;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_6;
    QDoubleSpinBox *deacceleration;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_7;
    QDoubleSpinBox *measurementInterval;
    QLabel *label_7;
    QPushButton *pushButton;
    QProgressBar *sendingProgress;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(557, 188);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Dialog->sizePolicy().hasHeightForWidth());
        Dialog->setSizePolicy(sizePolicy);
        Dialog->setMinimumSize(QSize(557, 188));
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetFixedSize);
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setVerticalSpacing(10);
        doMeasurement = new QCheckBox(Dialog);
        doMeasurement->setObjectName(QStringLiteral("doMeasurement"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, doMeasurement);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        distance = new QDoubleSpinBox(Dialog);
        distance->setObjectName(QStringLiteral("distance"));

        horizontalLayout->addWidget(distance);

        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        formLayout_2->setLayout(1, QFormLayout::LabelRole, horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        drivingSpeed = new QDoubleSpinBox(Dialog);
        drivingSpeed->setObjectName(QStringLiteral("drivingSpeed"));

        horizontalLayout_2->addWidget(drivingSpeed);

        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);


        formLayout_2->setLayout(2, QFormLayout::LabelRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        measurmentSpeed = new QDoubleSpinBox(Dialog);
        measurmentSpeed->setObjectName(QStringLiteral("measurmentSpeed"));

        horizontalLayout_3->addWidget(measurmentSpeed);

        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);


        formLayout_2->setLayout(3, QFormLayout::LabelRole, horizontalLayout_3);


        gridLayout->addLayout(formLayout_2, 0, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setVerticalSpacing(10);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        measurementTime = new QDoubleSpinBox(Dialog);
        measurementTime->setObjectName(QStringLiteral("measurementTime"));

        horizontalLayout_4->addWidget(measurementTime);

        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        acceleration = new QDoubleSpinBox(Dialog);
        acceleration->setObjectName(QStringLiteral("acceleration"));

        horizontalLayout_5->addWidget(acceleration);

        label_5 = new QLabel(Dialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        deacceleration = new QDoubleSpinBox(Dialog);
        deacceleration->setObjectName(QStringLiteral("deacceleration"));

        horizontalLayout_6->addWidget(deacceleration);

        label_6 = new QLabel(Dialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        measurementInterval = new QDoubleSpinBox(Dialog);
        measurementInterval->setObjectName(QStringLiteral("measurementInterval"));

        horizontalLayout_7->addWidget(measurementInterval);

        label_7 = new QLabel(Dialog);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);


        formLayout->setLayout(3, QFormLayout::LabelRole, horizontalLayout_7);


        gridLayout->addLayout(formLayout, 0, 1, 1, 1);

        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        sendingProgress = new QProgressBar(Dialog);
        sendingProgress->setObjectName(QStringLiteral("sendingProgress"));
        sizePolicy.setHeightForWidth(sendingProgress->sizePolicy().hasHeightForWidth());
        sendingProgress->setSizePolicy(sizePolicy);
        sendingProgress->setMinimumSize(QSize(520, 0));
        sendingProgress->setMinimum(0);
        sendingProgress->setValue(39);
        sendingProgress->setInvertedAppearance(false);

        gridLayout->addWidget(sendingProgress, 1, 0, 1, 3);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Automatic Mode", nullptr));
        doMeasurement->setText(QApplication::translate("Dialog", "Do measurement", nullptr));
        label->setText(QApplication::translate("Dialog", "Distance", nullptr));
        label_2->setText(QApplication::translate("Dialog", "Driving speed", nullptr));
        label_3->setText(QApplication::translate("Dialog", "Measurement speed", nullptr));
        label_4->setText(QApplication::translate("Dialog", "Measurement time", nullptr));
        label_5->setText(QApplication::translate("Dialog", "Acceleration", nullptr));
        label_6->setText(QApplication::translate("Dialog", "Deacceleration", nullptr));
        label_7->setText(QApplication::translate("Dialog", "Measurement interval", nullptr));
        pushButton->setText(QApplication::translate("Dialog", "Create commands", nullptr));
        sendingProgress->setFormat(QApplication::translate("Dialog", "     %v / %m send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOMATICMODE_H
