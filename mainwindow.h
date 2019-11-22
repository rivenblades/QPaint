// ---------- mainwindow.h ----------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

#include "layeritem.h"

// ScribbleArea used to paint the image
class ScribbleArea;
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    // Declares our class as a QObject which is the base class
    // for all Qt objects
    // QObjects handle events
    Q_OBJECT

public:
    MainWindow();
    Ui::MainWindow *ui;
protected:
    // Function used to close an event
    void closeEvent(QCloseEvent *event) override;

// The events that can be triggered
private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_valueChanged(int value);


    void on_checkBox_2_toggled(bool checked);

    void on_checkBox_3_toggled(bool checked);

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

private:
    // Will tie user actions to functions
    void createActions();
    void createMenus();

    // Will check if changes have occurred since last save
    bool maybeSave();

    // Opens the Save dialog and saves
    bool saveFile(const QByteArray &fileFormat);

    // What we'll draw on
    ScribbleArea *scribbleArea;

    // The menu widgets
    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    // All the actions that can occur
    QAction *openAct;

    // Actions tied to specific file formats
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
};

#endif

// ---------- END mainwindow.h ----------
