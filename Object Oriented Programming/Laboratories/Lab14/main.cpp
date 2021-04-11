#include "mainwindow.h"

#include <QApplication>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>
#include "Backend/controller.h"


Controller* load_settings();


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Controller* ctrl = load_settings();
    if (ctrl != nullptr) {
        MainWindow w{ctrl};
        w.test_backend();
        w.show();
        return a.exec();
    }

}

Controller* load_settings() {
    bool ok;
    QString text = QInputDialog::getText(NULL, ("Configure settings"),
                                         ("Config file path:"), QLineEdit::Normal,
                                         "config.txt", &ok);

    std::ifstream f{text.toStdString()};
    if (!ok || !f.is_open() || f.peek() == std::istream::traits_type::eof()) {
        QMessageBox::critical(NULL, ("Error"), ("Unable to load settings"));
        return nullptr;
    }
    std::string admin_repository_type;
    std::string user_repository_type;
    getline(f, admin_repository_type);
    getline(f, user_repository_type);

    std::string filename;
    if (admin_repository_type == "memory") {
        Repository* admin_repo = new Repository{};
        if (user_repository_type == "memory") {
            Repository* user_repo = new Repository{};
            Controller* ctrl = new Controller{admin_repo, user_repo};
            return ctrl;
        } else if (user_repository_type == "csv_file") {
            Repository* user_repo = new Csv_file{filename};
            Controller* ctrl = new Controller{admin_repo, user_repo};
            return ctrl;
        } else if (user_repository_type == "html_file") {
            Repository* user_repo = new Html_file{filename};
            Controller* ctrl = new Controller{admin_repo, user_repo};
            return ctrl;
        } else {
            return nullptr;
        }
    } else if (admin_repository_type == "csv_file") {
        Repository* admin_repo = new Csv_file{filename};
        if (user_repository_type == "memory") {
            Repository* user_repo = new Repository{};
            Controller* ctrl = new Controller{admin_repo, user_repo};
            return ctrl;
        } else if (user_repository_type == "csv_file") {
            Repository* user_repo = new Csv_file{filename};
            Controller* ctrl = new Controller{admin_repo, user_repo};
            return ctrl;
        } else if (user_repository_type == "html_file") {
            Repository* user_repo = new Html_file{filename};
            Controller* ctrl = new Controller{admin_repo, user_repo};
            return ctrl;
        } else {
            return nullptr;
        }
    } else if (admin_repository_type == "html_file") {
        Repository* admin_repo = new Html_file{filename};
        if (user_repository_type == "memory") {
            Repository* user_repo = new Repository{};
            Controller* ctrl = new Controller{admin_repo, user_repo};
            return ctrl;
        } else if (user_repository_type == "csv_file") {
            Repository* user_repo = new Csv_file{filename};
            Controller* ctrl = new Controller{admin_repo, user_repo};
            return ctrl;
        } else if (user_repository_type == "html_file") {
            Repository* user_repo = new Html_file{filename};
            Controller* ctrl = new Controller{admin_repo, user_repo};
            return ctrl;
        } else {
            return nullptr;
        }
    }
    return nullptr;
}
