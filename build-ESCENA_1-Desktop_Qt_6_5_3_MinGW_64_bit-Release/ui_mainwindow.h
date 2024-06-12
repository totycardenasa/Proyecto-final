/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *escenario;
    QLabel *mousePositionLabel;
    QGroupBox *groupBox;
    QLCDNumber *balas;
    QLCDNumber *barcos;
    QTextBrowser *textBrowser;
    QTextBrowser *textBrowser_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1366, 768);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        escenario = new QGraphicsView(centralwidget);
        escenario->setObjectName("escenario");
        escenario->setGeometry(QRect(0, 0, 1366, 768));
        mousePositionLabel = new QLabel(centralwidget);
        mousePositionLabel->setObjectName("mousePositionLabel");
        mousePositionLabel->setGeometry(QRect(160, 120, 49, 16));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(1208, 10, 150, 74));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    background-color: white;\n"
"}"));
        balas = new QLCDNumber(groupBox);
        balas->setObjectName("balas");
        balas->setGeometry(QRect(70, 40, 64, 23));
        balas->setStyleSheet(QString::fromUtf8("QLCDNumber {\n"
"    border: none;\n"
"	color: red;\n"
"}"));
        barcos = new QLCDNumber(groupBox);
        barcos->setObjectName("barcos");
        barcos->setEnabled(true);
        barcos->setGeometry(QRect(70, 10, 64, 23));
        QFont font;
        font.setKerning(true);
        barcos->setFont(font);
        barcos->setStyleSheet(QString::fromUtf8("QLCDNumber {\n"
"    border: none;\n"
"	color: red;\n"
"}"));
        textBrowser = new QTextBrowser(groupBox);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(30, 10, 71, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Palatino Linotype")});
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setItalic(false);
        textBrowser->setFont(font1);
        textBrowser->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	font: 9pt \"Palatino Linotype\";\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
""));
        textBrowser_2 = new QTextBrowser(groupBox);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setGeometry(QRect(30, 40, 71, 31));
        textBrowser_2->setFont(font1);
        textBrowser_2->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	font: 9pt \"Palatino Linotype\";\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        mousePositionLabel->setText(QString());
        groupBox->setTitle(QString());
        textBrowser->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Palatino Linotype'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">BARCOS:</span></p></body></html>", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Palatino Linotype'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">BALAS:</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
