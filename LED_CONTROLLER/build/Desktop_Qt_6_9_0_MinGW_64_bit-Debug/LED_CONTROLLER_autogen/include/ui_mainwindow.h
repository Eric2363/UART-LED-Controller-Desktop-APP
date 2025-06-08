/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *redButton;
    QPushButton *blueButton;
    QPushButton *cycleButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(462, 274);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 50, 221, 133));
        QFont font;
        font.setFamilies({QString::fromUtf8("Terminal")});
        font.setPointSize(32);
        label->setFont(font);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 180, 441, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        redButton = new QPushButton(horizontalLayoutWidget);
        redButton->setObjectName("redButton");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Terminal")});
        redButton->setFont(font1);

        horizontalLayout->addWidget(redButton);

        blueButton = new QPushButton(horizontalLayoutWidget);
        blueButton->setObjectName("blueButton");
        blueButton->setFont(font1);

        horizontalLayout->addWidget(blueButton);

        cycleButton = new QPushButton(horizontalLayoutWidget);
        cycleButton->setObjectName("cycleButton");
        cycleButton->setFont(font1);

        horizontalLayout->addWidget(cycleButton);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "THIS IS MY LED APP :D", nullptr));
        redButton->setText(QCoreApplication::translate("MainWindow", "Red LED", nullptr));
        blueButton->setText(QCoreApplication::translate("MainWindow", "Blue LED", nullptr));
        cycleButton->setText(QCoreApplication::translate("MainWindow", "Cycle LED", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
