#include "configsettingswindow.h"
#include "ui_configsettingswindow.h"
#include "main_gui.h"
#include <QTimer>
#include <QMessageBox>


configSettingsWindow::configSettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::configSettingsWindow)
{
    ui->setupUi(this);
    this->connect_signals_and_slots();
}

configSettingsWindow::~configSettingsWindow()
{
    delete ui;
}

void configSettingsWindow::connect_signals_and_slots() {
    QObject::connect(this->ui->save_path_button, &QPushButton::clicked, this, &configSettingsWindow::save_button_handler);
}

void configSettingsWindow::closeEvent(QCloseEvent *event) {
    // this->start_main();
    if (this->settings_flag == false) {
        QMessageBox mssg_box{};
        mssg_box.setWindowTitle("Error");
        mssg_box.setText("Couldn't load settings!");
        mssg_box.exec();
    }
    QWidget::closeEvent(event);
}

void configSettingsWindow::save_button_handler() {
    std::string file_path = this->ui->file_path_line_edit->text().toStdString();
    std::ifstream settings(file_path);
    if (!settings.is_open()) {
        this->ui->file_path_line_edit->setStyleSheet("background-color:red");
        QTimer::singleShot(1500, this, SLOT(update_line_edit()));
    } else {
        if (settings.peek() == std::ifstream::traits_type::eof()) {
            this->ui->file_path_line_edit->setStyleSheet("background-color:red");
            QTimer::singleShot(1500, this, SLOT(update_line_edit()));
        } else {
            std::string admin_line;
            //std::string user_line;
            getline(settings, admin_line);
            //getline(settings, user_line);
            if (admin_line == "file") {
                this->settings_flag = true;
                ArchmageEncyclopedia* repo = new  ArchmageEncyclopedia();
                Enchantment* controller = new Enchantment(*repo, "file");
                MAIN_GUI* main_gui = new MAIN_GUI{*controller};

                main_gui->setMinimumSize(1080, 720);
                main_gui->show();
            } else if (admin_line == "memory") {
                this->settings_flag = true;
                ArchmageEncyclopedia* repo = new  ArchmageEncyclopedia();
                Enchantment* controller = new Enchantment(*repo, "memory");
                MAIN_GUI* main_gui = new MAIN_GUI{*controller};

                main_gui->setMinimumSize(1080, 720);
                main_gui->show();
            }
            this->close();
        }
    }
}

void configSettingsWindow::update_line_edit() {
    this->ui->file_path_line_edit->setStyleSheet("background-color:solid white");
}


