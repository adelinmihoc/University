#include "user_gui.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>


USER_GUI::USER_GUI(Enchantment ctrl, QWidget* parent) : QWidget{parent}, controller(ctrl) {
    this->init_user_gui();
    this->connect_signal_and_slots();
}

USER_GUI::~USER_GUI() {}

void USER_GUI::init_user_gui() {
    QVBoxLayout* layout = new QVBoxLayout{};
    QFont f = {"Verdana", 15};

    // title
    this->title = new QLabel{this};
    //this->title->setFrameStyle(QFrame::Panel);
    this->title->setText("***APPRENTICE MODE***");
    this->setFont(f);
    this->title->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    ///////////////// upper part
    QWidget* upper_part = new QWidget{};
    QVBoxLayout* v_layout_upper_part = new QVBoxLayout{upper_part};

    // label of Current Statue
    this->current_statue_text_label = new QLabel{this};
    this->current_statue_text_label->setText("Current Statue");
    this->current_statue_text_label->setFont(f);
    this->current_statue_text_label->setAlignment(Qt::AlignLeft);

    // the box with current statue
    this->current_statue_box_text_label = new QLabel{this};
    this->current_statue_box_text_label->setText("Uninitialized");
    this->current_statue_box_text_label->setFont(f);
    this->current_statue_box_text_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    this->current_statue_box_text_label->setStyleSheet("background-color:white");
    this->current_statue_box_text_label->setAlignment(Qt::AlignHCenter);

    // next button
    this->next_statue_button = new QPushButton{"Next"};
    this->next_statue_button->setFont(f);

    v_layout_upper_part->addWidget(this->current_statue_text_label);
    v_layout_upper_part->addWidget(this->current_statue_box_text_label);
    v_layout_upper_part->addWidget(this->next_statue_button);

    ///////////////// middle part
    QWidget* middle_part = new QWidget{};
    QHBoxLayout* h_layout_middle_part = new QHBoxLayout{middle_part};



    QWidget* middle_left_part = new QWidget{};
    QVBoxLayout* v_layout_middle_left = new QVBoxLayout{middle_left_part};

    this->mylist_button = new QPushButton{"Mylist"};
    this->mylist_button->setFont(f);


    ////
    QWidget* middle_left_top_part = new QWidget{};
    QVBoxLayout* v_layout_middle_left_top = new QVBoxLayout{middle_left_top_part};

    // middle left top area
    QWidget* statue_name_data_widget = new QWidget{};
    QFormLayout* statue_name_form_layout = new QFormLayout{statue_name_data_widget};
    this->statue_name_edit = new QLineEdit{};
    this->statue_name_edit->setFont(f);
    QLabel* statue_name_label = new QLabel{"Power Word Name:"};
    statue_name_label->setBuddy(this->statue_name_edit);
    statue_name_label->setFont(f);

    statue_name_form_layout->addRow(statue_name_label, this->statue_name_edit);

    // save botton
    this->save_statue_button = new QPushButton{"Save"};
    this->save_statue_button->setFont(f);
    //this->save_statue_button->

    // add to middle left top
    v_layout_middle_left_top->addWidget(statue_name_data_widget);
    v_layout_middle_left_top->addWidget(this->save_statue_button);
    ////


    ////
    QWidget* middle_left_bottom_part = new QWidget{};
    QVBoxLayout* v_layout_middle_left_bottom = new QVBoxLayout{middle_left_bottom_part};

    // middle left bottom area
    QWidget* statue_material_and_age_data_widget = new QWidget{};
    QFormLayout* statue_material_and_age_form_layout = new QFormLayout{statue_material_and_age_data_widget};
    this->statue_material_edit = new QLineEdit{};
    this->statue_material_edit->setFont(f);
    QLabel* statue_material_label = new QLabel{"Material:"};
    statue_material_label->setBuddy(this->statue_material_edit);
    statue_material_label->setFont(f);

    statue_material_and_age_form_layout->addRow(statue_material_label, this->statue_material_edit);

    this->statue_age_edit = new QLineEdit{};
    this->statue_age_edit->setFont(f);
    QLabel* statue_age_label = new QLabel{"Age:"};
    statue_age_label->setBuddy(this->statue_age_edit);
    statue_age_label->setFont(f);

    statue_material_and_age_form_layout->addRow(statue_age_label, this->statue_age_edit);

    // filter botton
    this->filer_statues_button = new QPushButton{"Filter"};
    this->filer_statues_button->setFont(f);

    // add to middle left bottom
    v_layout_middle_left_bottom->addWidget(statue_material_and_age_data_widget);
    v_layout_middle_left_bottom->addWidget(this->filer_statues_button);
    ////




    // add to middle left
    v_layout_middle_left->addWidget(this->mylist_button);
    v_layout_middle_left->addWidget(middle_left_top_part);
    v_layout_middle_left->addWidget(middle_left_bottom_part);



    // the middle right part with a list
    this->statues_list = new QListWidget{};
    this->statues_list->setSelectionMode(QAbstractItemView::SingleSelection);


    // add to middle part
    h_layout_middle_part->addWidget(middle_left_part);
    h_layout_middle_part->addWidget(this->statues_list);

    ///////////////// bottom part
    // bottom part
    QWidget* bottom_part = new QWidget{};
    QHBoxLayout* h_layout_bottom = new QHBoxLayout{bottom_part};

    QWidget* bottom_left = new QWidget{};
    QVBoxLayout* v_layout_bottom_left = new QVBoxLayout{bottom_left};


    QWidget* file_location_data_widget = new QWidget{};
    QFormLayout* file_location_layout = new QFormLayout{file_location_data_widget};

    this->myfile_location_edit = new QLineEdit{};
    QLabel* file_path_label = new QLabel{"Myfile Location:"};
    file_path_label->setBuddy(this->myfile_location_edit);
    file_path_label->setFont(f);
    this->myfile_location_edit->setFont(f);

    file_location_layout->addRow(file_path_label, this->myfile_location_edit);

    // button from bottom left bottom
    this->myfile_location_button = new QPushButton{"Save Myfile Location"};
    this->myfile_location_button->setFont(f);
    this->myfile_location_button->setMaximumWidth(400);

    // add to bottom left vertical layout
    v_layout_bottom_left->addWidget(file_location_data_widget);
    v_layout_bottom_left->addWidget(this->myfile_location_button);

    // right bottom part
    // a button
    this->admin_mode_button = new QPushButton{"Close"};
    this->admin_mode_button->setFont(f);

    // add to bottom layout
    h_layout_bottom->addWidget(bottom_left);
    h_layout_bottom->addWidget(this->admin_mode_button);


    // add to main layout
    layout->addWidget(this->title);
    layout->addWidget(upper_part);
    layout->addWidget(middle_part);
    layout->addWidget(bottom_part);

    // for alignment
    this->setLayout(layout);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_buttons_background()));
    timer->start(2000);
}

void USER_GUI::update_buttons_background() {
    this->next_statue_button->setStyleSheet("background-color:solid white");
    this->myfile_location_button->setStyleSheet("background-color:solid white");
    this->filer_statues_button->setStyleSheet("background-color:solid white");
    this->save_statue_button->setStyleSheet("background-color:solid white");
    this->myfile_location_button->setStyleSheet("background-color:solid white");
    this->myfile_location_edit->setStyleSheet("background-color:solid white");
}

void USER_GUI::connect_signal_and_slots() {
    QObject::connect(this->admin_mode_button, &QPushButton::clicked, this, &USER_GUI::admin_mode_button_handler);
    QObject::connect(this->next_statue_button, &QPushButton::clicked, this, &USER_GUI::next_statue_button_handler);
    QObject::connect(this->myfile_location_button, &QPushButton::clicked, this, &USER_GUI::myfile_location_button_handler);
    QObject::connect(this->mylist_button, &QPushButton::clicked, this, &USER_GUI::mylist_button_handler);
    QObject::connect(this, &USER_GUI::statues_updated_mylist_signal, this, &USER_GUI::populate_statues_list_mylist);
    QObject::connect(this, &USER_GUI::statues_uptade_filter_signal, this, &USER_GUI::populate_statues_list_filter);
    QObject::connect(this->filer_statues_button, &QPushButton::clicked, this, &USER_GUI::filter_statues_button_handler);
    QObject::connect(this,SIGNAL(add_statue_signal(const std::string&)),
                this, SLOT(add_statue(const std::string&)));
    QObject::connect(this->save_statue_button, &QPushButton::clicked, this, &USER_GUI::save_statue_button_handler);

}

void USER_GUI::admin_mode_button_handler() {
    this->close();
}

void USER_GUI::next_statue_button_handler() {
    try {
        GuardianStatue s = this->controller.nextGuardianStatues();
        this->current_statue_box_text_label->setText(QString::fromStdString(s.to_string()));
        this->next_statue_button->setStyleSheet("background-color:green");
    } catch(std::exception&) {
        this->next_statue_button->setStyleSheet("background-color:red");
    }
}

void USER_GUI::myfile_location_button_handler() {
    QString path = this->myfile_location_edit->text();
    std::string filepath = path.toStdString();

    std::ifstream test;
    test.open(filepath);
    if (test.is_open()) {
        this->controller.setUserFilePath(filepath);
        this->controller.setUserFileType();
        this->myfile_location_edit->setStyleSheet("background-color:green");
    } else {
        this->myfile_location_edit->setStyleSheet("background-color:red");
    }
}

void USER_GUI::mylist_button_handler() {
    emit statues_updated_mylist_signal();
}

void USER_GUI::filter_statues_button_handler() {
    emit statues_uptade_filter_signal();
}

void USER_GUI::populate_statues_list_mylist() {
    try {
        if (this->statues_list->count() > 0) {
            this->statues_list->clear();
        }
        for (auto s: this->controller.getAllApprenticeGuardianStatues()) {
            QString item_in_list = QString::fromStdString(s.to_string());
            QFont f{"Verdana", 15};
            QListWidgetItem* item = new QListWidgetItem{item_in_list};
            item->setFont(f);
            this->statues_list->addItem(item);
            this->mylist_button->setStyleSheet("background-color: green");
        }
    } catch(std::exception&) {
        this->mylist_button->setStyleSheet("background-color: red");
    }

    //if (this->controller.getAllApprenticeGuardianStatues().size() > 0) {
    //    this->statues_list->setCurrentRow(0);
    //}
}

void USER_GUI::populate_statues_list_filter() {
    try {
        if (this->statues_list->count() > 0) {
            this->statues_list->clear();
        }
        QString material = this->statue_material_edit->text();
        QString age = this->statue_age_edit->text();

        std::string _material = material.toStdString();
        int _age = age.toInt();
        if (_age == 0 && age != "0") {
            throw std::exception();
        }
        for (auto s: this->controller.getAllApprenticeStatuesByMaterialAndAge(_material, _age)) {
            QString item_in_list = QString::fromStdString(s.to_string());
            QFont f{"Verdana", 15};
            QListWidgetItem* item = new QListWidgetItem{item_in_list};
            item->setFont(f);
            this->statues_list->addItem(item);
        }
        this->filer_statues_button->setStyleSheet("background-color:green");

    } catch(std::exception&) {
        this->filer_statues_button->setStyleSheet("background-color:red");
    }
}

void USER_GUI::add_statue(const std::string& _name){
    try {
        this->controller.saveGuardianStatue(_name);
        this->save_statue_button->setStyleSheet("background-color:green");
        emit statues_updated_mylist_signal();
    } catch(std::exception&) {
        this->save_statue_button->setStyleSheet("background-color:red");
    }
}

void USER_GUI::save_statue_button_handler() {
    QString name = this->statue_name_edit->text();
    emit add_statue(name.toStdString());
}

