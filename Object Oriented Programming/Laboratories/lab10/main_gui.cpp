#include "main_gui.h"
#include "admin_gui.h"
#include "user_gui.h"


MAIN_GUI::MAIN_GUI(Enchantment ctrl, QWidget* parent): QWidget{parent}, controller(ctrl) {
    this->init_main_gui();
    this->connect_signals_and_slots();
}

MAIN_GUI::~MAIN_GUI() {}

void MAIN_GUI::init_main_gui() {
    // main layout
    QVBoxLayout* layout = new QVBoxLayout {this};
    QFont f = {"Verdana", 15};

    // title layout
    this->title = new QLabel{this};
    this->title->setText("***RUNIC ALTAR***\nFirst Fire");
    this->title->setFont(f);
    this->title->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    // help text layout 1 and 2
    // 1
    this->help_text = new QLabel{this};
    this->help_text->setText("Are you a Mage or an Apprentice?\n"
                             "Press 'mode A' if you are an Archmages or an elder of the Spire.\n"
                             "Press 'mode B' if you are an Apprentice.");
    this->help_text->setFont(f);
    this->help_text->setAlignment(Qt::AlignHCenter);
    // 2
    this->help_text2 = new QLabel{this};
    this->help_text2->setText("You can set the path to the Archmage file and to the Apprentice file.");
    this->help_text2->setFont(f);
    this->help_text2->setAlignment(Qt::AlignHCenter);

    // buttons layout
    QWidget* buttons_widget = new QWidget{};
    QHBoxLayout* h_layout = new QHBoxLayout{buttons_widget};
    this->admin_mode_button = new QPushButton {"mode A"};
    this->admin_mode_button->setFont(f);
    this->user_mode_button = new QPushButton {"mode B"};
    this->user_mode_button->setFont(f);

    h_layout->addWidget(this->admin_mode_button);
    h_layout->addWidget(this->user_mode_button);

    // bottom part
    QWidget* bottom_part = new QWidget{};
    QVBoxLayout* v_layout = new QVBoxLayout{bottom_part};

    QWidget* files_path_widget = new QWidget{};
    QFormLayout* form_layout = new QFormLayout{files_path_widget};

    this->admin_file_path_edit = new QLineEdit{};
    this->user_file_path_edit = new QLineEdit{};

    QLabel* file_location_label = new QLabel{"File location:"};
    file_location_label->setBuddy(this->admin_file_path_edit);
    file_location_label->setFont(f);
    QLabel* myfile_location_label = new QLabel{"Myfile location:"};
    myfile_location_label->setBuddy(this->user_file_path_edit);
    myfile_location_label->setFont(f);

    this->admin_file_path_edit->setFont(f);
    this->user_file_path_edit->setFont(f);

    // add rows to form layout
    form_layout->addRow(file_location_label, this->admin_file_path_edit);
    form_layout->addRow(myfile_location_label, this->user_file_path_edit);

    // buttons for adding path
    QWidget* form_buttons = new QWidget{};
    QHBoxLayout* h_layout2 = new QHBoxLayout{form_buttons};
    this->set_admin_file_path_button = new QPushButton{"Save file location"};
    this->set_admin_file_path_button->setFont(f);
    this->set_user_file_path_button = new QPushButton{"Save myfile location"};
    this->set_user_file_path_button->setFont(f);

    // add buttons to the horizontal box
    h_layout2->addWidget(this->set_admin_file_path_button);
    h_layout2->addWidget(this->set_user_file_path_button);

    // add form and buttons to the vertical box
    v_layout->addWidget(this->help_text2);
    v_layout->addWidget(files_path_widget);
    v_layout->addWidget(form_buttons);

    // add to main layout
    layout->addWidget(this->title);
    layout->addWidget(this->help_text);
    layout->addWidget(buttons_widget);
    //layout->addWidget(this->help_text2);
    layout->addWidget(bottom_part);

    // set the layout for alignment
    this->setLayout(layout);
}

void MAIN_GUI::connect_signals_and_slots() {
    QObject::connect(this->admin_mode_button, &QPushButton::clicked, this, &MAIN_GUI::admin_mode_button_handler);
    QObject::connect(this->user_mode_button, &QPushButton::clicked, this, &MAIN_GUI::user_mode_button_handler);
    QObject::connect(this->set_admin_file_path_button, &QPushButton::clicked, this, &MAIN_GUI::set_admin_file_path_button_handler);
    QObject::connect(this->set_user_file_path_button, &QPushButton::clicked, this, &MAIN_GUI::set_user_file_path_button_handler);
}

void MAIN_GUI::admin_mode_button_handler() {
    //ADMIN_GUI admin_gui{};
    //admin_gui.show();
    auto admin_mode_gui = new ADMIN_GUI{this->controller};
    //int x = admin_mode_gui->width() * 0.6;
    //int y = admin_mode_gui->height() * 0.6;
    //admin_mode_gui->setFixedSize(x,y);
    //admin_mode_gui->setMinimumSize(1080,720);
    admin_mode_gui->setMinimumSize(1080, 820);
    admin_mode_gui->show();
    //this->close();
}

void MAIN_GUI::user_mode_button_handler() {
    auto user_mode_gui = new USER_GUI{this->controller};
    user_mode_gui->setMinimumSize(1080, 860);
    user_mode_gui->show();
    //this->close();
}

void MAIN_GUI::set_admin_file_path_button_handler() {
    QString path = this->admin_file_path_edit->text();
    std::string filepath = path.toStdString();

    std::ifstream test;
    test.open(filepath);
    if (test.is_open()) {
        this->controller.setFilePath(filepath);
        this->admin_file_path_edit->setStyleSheet("background-color:green");
    }
    else {
        this->admin_file_path_edit->setStyleSheet("background-color:red");
    }
}

void MAIN_GUI::set_user_file_path_button_handler() {
    QString path = this->user_file_path_edit->text();
    std::string filepath = path.toStdString();

    std::ifstream test;
    test.open(filepath);
    try {
        if (test.is_open()) {
            this->controller.setUserFilePath(filepath);
            this->controller.setUserFileType();
            this->user_file_path_edit->setStyleSheet("background-color:green");
        } else {
            this->user_file_path_edit->setStyleSheet("background-color:red");
        }
    } catch(std::exception&) {
        this->user_file_path_edit->setStyleSheet("background-color:red");
    }
}


