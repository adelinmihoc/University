#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Backend/controller.h"
#include "general_listview_model.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Controller* _c, QWidget *parent = nullptr);
    ~MainWindow();
    void test_backend();

private:
    Ui::MainWindow *ui;
    Controller* controller;
    General_listView_model* model;

    void connect_signals_and_slots();
    void admin_mode_button_handler();
    void user_mode_button_handler();
    void set_file_extensions_in_lineEdit();
    void file_location_button_handler();
    void myfile_location_button_handler();

public slots:
    void reset_button_color();

};
#endif // MAINWINDOW_H
