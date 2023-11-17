#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
#include <QProcess>
#include <QTimer>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /* functionality */
    void createButtons();
    void disableOtherButtons(QPushButton *exclude);
    void enableAllButtons();
    void createTimers();

    /* tool operations */
    void returnHome();
    void cutPipe();
    void writeDoe();
    void getMarker();
    void returnMarker();
    void getGrinder();
    void returnGrinder();

    /* push buttons */
    QPushButton *m_buttonReturnHome;
    QPushButton *m_buttonCutPipe;
    QPushButton *m_buttonWriteDoe;
    QPushButton *m_buttonGetMarker;
    QPushButton *m_buttonReturnMarker;
    QPushButton *m_buttonGetGrinder;
    QPushButton *m_buttonReturnGrinder;

    QProcess *m_process;

    QTimer *m_timeout;
};

#endif // MAINWINDOW_H
