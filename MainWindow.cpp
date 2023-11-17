#include "MainWindow.h"

#include <QFrame>
#include <QIcon>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createButtons();

    m_process = new QProcess(this);

    /* draws vertical line in menu */
    QFrame *vLine = new QFrame();
    vLine->setFrameShape(QFrame::VLine);
    vLine->setFrameShadow(QFrame::Sunken);

    /* draws horizontal line in menu */
    QFrame *hLine = new QFrame();
    hLine->setFrameShape(QFrame::HLine);
    hLine->setFrameShadow(QFrame::Sunken);

    /* layout for the main tool operation buttons */
    QHBoxLayout *topButtonLayout = new QHBoxLayout();
    topButtonLayout->addWidget(m_buttonCutPipe);
    topButtonLayout->addWidget(m_buttonWriteDoe);

    /* layout for marker/grinder get/return operation buttons */
    QHBoxLayout *bottomButtonLayout = new QHBoxLayout();
    bottomButtonLayout->addWidget(m_buttonGetMarker);
    bottomButtonLayout->addWidget(m_buttonReturnMarker);
    bottomButtonLayout->addWidget(vLine);
    bottomButtonLayout->addWidget(m_buttonGetGrinder);
    bottomButtonLayout->addWidget(m_buttonReturnGrinder);

    /* special layout for the "return home" button */
    QHBoxLayout *homeButtonLayout = new QHBoxLayout();
    homeButtonLayout->addWidget(m_buttonReturnHome);

    /* aggregates all layouts into a central widget */
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addLayout(topButtonLayout);
    mainLayout->addLayout(bottomButtonLayout);
    mainLayout->addWidget(hLine);
    mainLayout->addLayout(homeButtonLayout);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() { }

void MainWindow::createButtons() {
    int iconWidth = 50;
    int iconHeight = 50;

    /* return home button */
    m_buttonReturnHome = new QPushButton("Return Home", this);
    QIcon iconReturnHome("icons/returnhome-icon.png");
    m_buttonReturnHome->setIcon(iconReturnHome);
    m_buttonReturnHome->setIconSize(QSize(iconWidth, iconHeight));

    /* cut pipe button */
    m_buttonCutPipe = new QPushButton("Cut Pipe", this);
    QIcon iconCutPipe("icons/cutpipe-icon.png");
    m_buttonCutPipe->setIcon(iconCutPipe);
    m_buttonCutPipe->setIconSize(QSize(iconWidth, iconHeight));

    /* write DOE button */
    m_buttonWriteDoe = new QPushButton("Write DOE", this);
    QIcon iconWriteDoe("icons/writedoe-icon.png");
    m_buttonWriteDoe->setIcon(iconWriteDoe);
    m_buttonWriteDoe->setIconSize(QSize(iconWidth, iconHeight));

    /* get marker button */
    m_buttonGetMarker = new QPushButton("Get Marker", this);
    QIcon iconGetMarker("icons/getmarker-icon.png");
    m_buttonGetMarker->setIcon(iconGetMarker);
    m_buttonGetMarker->setIconSize(QSize(iconWidth, iconHeight));

    /* return marker button */
    m_buttonReturnMarker = new QPushButton("Return Marker", this);
    QIcon iconReturnMarker("icons/returnmarker-icon.png");
    m_buttonReturnMarker->setIcon(iconReturnMarker);
    m_buttonReturnMarker->setIconSize(QSize(iconWidth, iconHeight));

    /* get grinder button */
    m_buttonGetGrinder = new QPushButton("Get Grinder", this);
    QIcon iconGetGrinder("icons/getgrinder-icon.png");
    m_buttonGetGrinder->setIcon(iconGetGrinder);
    m_buttonGetGrinder->setIconSize(QSize(iconWidth, iconHeight));

    /* return grinder button */
    m_buttonReturnGrinder = new QPushButton("Return Grinder", this);
    QIcon iconReturnGrinder("icons/returngrinder-icon.png");
    m_buttonReturnGrinder->setIcon(iconReturnGrinder);
    m_buttonReturnGrinder->setIconSize(QSize(iconWidth, iconHeight));
}

/* disables buttons while performing tool operations */
void MainWindow::disableOtherButtons(QPushButton *exclude) {
    m_buttonReturnHome->setEnabled(m_buttonReturnHome == exclude);
    m_buttonCutPipe->setEnabled(m_buttonCutPipe == exclude);
    m_buttonWriteDoe->setEnabled(m_buttonWriteDoe == exclude);
    m_buttonGetMarker->setEnabled(m_buttonGetMarker == exclude);
    m_buttonReturnMarker->setEnabled(m_buttonReturnMarker == exclude);
    m_buttonGetGrinder->setEnabled(m_buttonGetGrinder == exclude);
    m_buttonReturnGrinder->setEnabled(m_buttonReturnGrinder == exclude);
}

/* enables all buttons once tool operation has completed */
void MainWindow::enableAllButtons() {
    m_buttonReturnHome->setEnabled(true);
    m_buttonCutPipe->setEnabled(true);
    m_buttonWriteDoe->setEnabled(true);
    m_buttonGetMarker->setEnabled(true);
    m_buttonReturnMarker->setEnabled(true);
    m_buttonGetGrinder->setEnabled(true);
    m_buttonReturnGrinder->setEnabled(true);
}

/* creates the timer(s) */
void MainWindow::createTimers() {
    /* initializes the timeout timer */
    m_timeout = new QTimer(this);
    connect(m_timeout, &QTimer::timeout, this, &MainWindow::enableAllButtons);
}

/* returns arm to its home position */
void MainWindow::returnHome() {
    QObject::connect(m_buttonReturnHome, &QPushButton::clicked, this, [this]() {
        QStringList args;
        args << "doeDemo.py" << "home(urx.Robot('10.0.0.12'))";
        m_process->start("python3", args);
        disableOtherButtons(m_buttonReturnHome);
        m_timeout->start(30000);
    });
}

/* executes the cut pipe tool operation */
void MainWindow::cutPipe() {
    QObject::connect(m_buttonCutPipe, &QPushButton::clicked, this, [this]() {
        QStringList args;
        args << "doeDemo.py" << "cutPipe(0.05, 0.05, urx.Robot('10.0.0.12'))";
        // args << "doeDemo.py" << "cutPipe(acc, vel, robot)";
        m_process->start("python3", args);
        disableOtherButtons(m_buttonCutPipe);
        m_timeout->start(30000);
    });
}

/* executes the write DOE tool operation */
void MainWindow::writeDoe() {
    QObject::connect(m_buttonWriteDoe, &QPushButton::clicked, this, [this]() {
        QStringList args;
        args << "doeDemo.py" << "writeDoe(0.05, 0.05, urx.Robot('10.0.0.12'))";
        m_process->start("python3", args);
        disableOtherButtons(m_buttonWriteDoe);
        m_timeout->start(30000);
    });
}

/* retrieves marker attachment from tool rack */
void MainWindow::getMarker() {
    QObject::connect(m_buttonGetMarker, &QPushButton::clicked, this, [this]() {
        QStringList args;
        args << "doeDemo.py" << "getMarker(0.05, 0.05, urx.Robot('10.0.0.12'), board.get_pin(f'd:{8}:o'))";
        m_process->start("python3", args);
        disableOtherButtons(m_buttonGetMarker);
        m_timeout->start(30000);
    });
}

/* returns marker attachment to tool rack */
void MainWindow::returnMarker() {
    QObject::connect(m_buttonReturnMarker, &QPushButton::clicked, this, [this]() {
        QStringList args;
        args << "doeDemo.py" << "returnMarker(0.05, 0.05, urx.Robot('10.0.0.12'), board.get_pin(f'd:{8}:o'))";
        m_process->start("python3", args);
        disableOtherButtons(m_buttonReturnMarker);
        m_timeout->start(30000);
    });
}

/* retrieves grinder attachment from tool rack */
void MainWindow::getGrinder() {
    QObject::connect(m_buttonGetGrinder, &QPushButton::clicked, this, [this]() {
        QStringList args;
        args << "doeDemo.py" << "getGrinder(0.05, 0.05, urx.Robot('10.0.0.12'), board.get_pin(f'd:{8}:o'))";
        m_process->start("python3", args);
        disableOtherButtons(m_buttonGetGrinder);
        m_timeout->start(30000);
    });
}

/* returns grinder attachment to tool rack */
void MainWindow::returnGrinder() {
    QObject::connect(m_buttonReturnGrinder, &QPushButton::clicked, this, [this]() {
        QStringList args;
        args << "doeDemo.py" << "returnGrinder(0.05, 0.05, urx.Robot('10.0.0.12'), board.get_pin(f'd:{8}:o'))";
        m_process->start("python3", args);
        disableOtherButtons(m_buttonReturnGrinder);
        m_timeout->start(30000);
    });
}
