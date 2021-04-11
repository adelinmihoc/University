#ifndef MAIN_GUI_H
#define MAIN_GUI_H
#include <qwidget.h>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QFormLayout>
#include <lab9/Controller.h>


class MAIN_GUI : public QWidget {
    Q_OBJECT
public:
    MAIN_GUI(Enchantment ctrl, QWidget* parent = 0);
    ~MAIN_GUI();

private:
    Enchantment controller;


    // title
    QLabel* title;

    // help text
    QLabel* help_text;
    QLabel* help_text2;

    // buttons
    QPushButton* admin_mode_button;
    QPushButton* user_mode_button;

    // file paths
    QLineEdit* admin_file_path_edit;
    QLineEdit* user_file_path_edit;

    // file paths buttons
    QPushButton* set_admin_file_path_button;
    QPushButton* set_user_file_path_button;

    void init_main_gui();

    void connect_signals_and_slots();
    void admin_mode_button_handler();
    void user_mode_button_handler();
    void set_admin_file_path_button_handler();
    void set_user_file_path_button_handler();

};


#endif // MAIN_GUI_H
