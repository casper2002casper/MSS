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
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_AutomaticMode
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout_2;
    QCheckBox *doMeasurement;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *distance;
    QLabel *label;
    QHBoxLayout *horizontalLayout_7;
    QDoubleSpinBox *measurementInterval;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *drivingSpeed;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *measurementSpeed;
    QLabel *label_3;
    QFormLayout *formLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_9;
    QDoubleSpinBox *measurementTime;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_5;
    QDoubleSpinBox *acceleration;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_6;
    QDoubleSpinBox *deacceleration;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_8;
    QDoubleSpinBox *Marge;
    QLabel *label_8;
    QDialogButtonBox *buttonBox;
    QProgressBar *sendingProgress;

    void setupUi(QDialog *AutomaticMode)
    {
        if (AutomaticMode->objectName().isEmpty())
            AutomaticMode->setObjectName(QStringLiteral("AutomaticMode"));
        AutomaticMode->resize(650, 238);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AutomaticMode->sizePolicy().hasHeightForWidth());
        AutomaticMode->setSizePolicy(sizePolicy);
        AutomaticMode->setMinimumSize(QSize(557, 188));
        gridLayout = new QGridLayout(AutomaticMode);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setVerticalSpacing(10);
        doMeasurement = new QCheckBox(AutomaticMode);
        doMeasurement->setObjectName(QStringLiteral("doMeasurement"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, doMeasurement);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        distance = new QDoubleSpinBox(AutomaticMode);
        distance->setObjectName(QStringLiteral("distance"));

        horizontalLayout->addWidget(distance);

        label = new QLabel(AutomaticMode);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        formLayout_2->setLayout(1, QFormLayout::LabelRole, horizontalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        measurementInterval = new QDoubleSpinBox(AutomaticMode);
        measurementInterval->setObjectName(QStringLiteral("measurementInterval"));

        horizontalLayout_7->addWidget(measurementInterval);

        label_7 = new QLabel(AutomaticMode);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);


        formLayout_2->setLayout(2, QFormLayout::LabelRole, horizontalLayout_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        drivingSpeed = new QDoubleSpinBox(AutomaticMode);
        drivingSpeed->setObjectName(QStringLiteral("drivingSpeed"));

        horizontalLayout_2->addWidget(drivingSpeed);

        label_2 = new QLabel(AutomaticMode);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);


        formLayout_2->setLayout(3, QFormLayout::LabelRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        measurementSpeed = new QDoubleSpinBox(AutomaticMode);
        measurementSpeed->setObjectName(QStringLiteral("measurementSpeed"));

        horizontalLayout_3->addWidget(measurementSpeed);

        label_3 = new QLabel(AutomaticMode);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);


        formLayout_2->setLayout(4, QFormLayout::LabelRole, horizontalLayout_3);


        gridLayout->addLayout(formLayout_2, 0, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setVerticalSpacing(10);
        verticalSpacer = new QSpacerItem(15, 22, QSizePolicy::Minimum, QSizePolicy::Fixed);

        formLayout->setItem(0, QFormLayout::LabelRole, verticalSpacer);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        measurementTime = new QDoubleSpinBox(AutomaticMode);
        measurementTime->setObjectName(QStringLiteral("measurementTime"));

        horizontalLayout_9->addWidget(measurementTime);

        label_4 = new QLabel(AutomaticMode);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_9->addWidget(label_4);


        formLayout->setLayout(1, QFormLayout::LabelRole, horizontalLayout_9);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        acceleration = new QDoubleSpinBox(AutomaticMode);
        acceleration->setObjectName(QStringLiteral("acceleration"));

        horizontalLayout_5->addWidget(acceleration);

        label_5 = new QLabel(AutomaticMode);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);


        formLayout->setLayout(2, QFormLayout::LabelRole, horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        deacceleration = new QDoubleSpinBox(AutomaticMode);
        deacceleration->setObjectName(QStringLiteral("deacceleration"));

        horizontalLayout_6->addWidget(deacceleration);

        label_6 = new QLabel(AutomaticMode);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);


        formLayout->setLayout(3, QFormLayout::LabelRole, horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        Marge = new QDoubleSpinBox(AutomaticMode);
        Marge->setObjectName(QStringLiteral("Marge"));

        horizontalLayout_8->addWidget(Marge);

        label_8 = new QLabel(AutomaticMode);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_8->addWidget(label_8);


        formLayout->setLayout(4, QFormLayout::LabelRole, horizontalLayout_8);


        gridLayout->addLayout(formLayout, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(AutomaticMode);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        buttonBox->setCenterButtons(true);

        gridLayout->addWidget(buttonBox, 0, 2, 1, 1);

        sendingProgress = new QProgressBar(AutomaticMode);
        sendingProgress->setObjectName(QStringLiteral("sendingProgress"));
        sizePolicy.setHeightForWidth(sendingProgress->sizePolicy().hasHeightForWidth());
        sendingProgress->setSizePolicy(sizePolicy);
        sendingProgress->setMinimumSize(QSize(550, 0));
        sendingProgress->setMinimum(0);
        sendingProgress->setValue(39);
        sendingProgress->setInvertedAppearance(false);

        gridLayout->addWidget(sendingProgress, 1, 0, 1, 3);


        retranslateUi(AutomaticMode);

        QMetaObject::connectSlotsByName(AutomaticMode);
    } // setupUi

    void retranslateUi(QDialog *AutomaticMode)
    {
        AutomaticMode->setWindowTitle(QApplication::translate("AutomaticMode", "Automatic Mode", nullptr));
        doMeasurement->setText(QApplication::translate("AutomaticMode", "Do measurement", nullptr));
        label->setText(QApplication::translate("AutomaticMode", "Total distance (m)", nullptr));
        label_7->setText(QApplication::translate("AutomaticMode", "Measurement distance (m)", nullptr));
        label_2->setText(QApplication::translate("AutomaticMode", "Driving speed (m/s)", nullptr));
        label_3->setText(QApplication::translate("AutomaticMode", "Measurement speed (m/s)", nullptr));
        label_4->setText(QApplication::translate("AutomaticMode", "Measurement time (s)", nullptr));
        label_5->setText(QApplication::translate("AutomaticMode", "Acceleratio0n (m/s/s)", nullptr));
        label_6->setText(QApplication::translate("AutomaticMode", "Deacceleration (m/s/s)", nullptr));
        label_8->setText(QApplication::translate("AutomaticMode", "Marge (s)", nullptr));
        sendingProgress->setFormat(QApplication::translate("AutomaticMode", "     %v / %m send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutomaticMode: public Ui_AutomaticMode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOMATICMODE_H
