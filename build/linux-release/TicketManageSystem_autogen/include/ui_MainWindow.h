/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *add;
    QPushButton *list;
    QPushButton *query;
    QPushButton *sell;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName("mainWindow");
        mainWindow->resize(201, 228);
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        add = new QPushButton(centralwidget);
        add->setObjectName("add");

        gridLayout->addWidget(add, 0, 0, 1, 1);

        list = new QPushButton(centralwidget);
        list->setObjectName("list");

        gridLayout->addWidget(list, 1, 0, 1, 1);

        query = new QPushButton(centralwidget);
        query->setObjectName("query");

        gridLayout->addWidget(query, 2, 0, 1, 1);

        sell = new QPushButton(centralwidget);
        sell->setObjectName("sell");

        gridLayout->addWidget(sell, 3, 0, 1, 1);

        mainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 201, 31));
        mainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(mainWindow);
        statusbar->setObjectName("statusbar");
        mainWindow->setStatusBar(statusbar);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QCoreApplication::translate("mainWindow", "\350\275\246\347\245\250\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        add->setText(QCoreApplication::translate("mainWindow", "\345\275\225\345\205\245\347\217\255\346\254\241\344\277\241\346\201\257", nullptr));
        list->setText(QCoreApplication::translate("mainWindow", "\346\265\217\350\247\210\347\217\255\346\254\241\344\277\241\346\201\257", nullptr));
        query->setText(QCoreApplication::translate("mainWindow", "\346\237\245\350\257\242\350\267\257\347\272\277", nullptr));
        sell->setText(QCoreApplication::translate("mainWindow", "\345\224\256\347\245\250\345\222\214\351\200\200\347\245\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
