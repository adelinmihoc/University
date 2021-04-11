#include "admin_gui.h"
#include <QHBoxLayout>
//#include <lab9/Controller.h>


ADMIN_GUI::ADMIN_GUI(Enchantment ctrl, QWidget* parent) : QWidget{parent}, controller(ctrl) {
    this->init_admin_gui();
    this->connect_signals_and_slots();
    try {
        this->populate_statues_list();
    } catch(std::exception&) {

    }
}

ADMIN_GUI::~ADMIN_GUI() {}

void ADMIN_GUI::init_admin_gui() {
    // main layout
    QVBoxLayout* layout = new QVBoxLayout{};
    QFont f = {"Verdana", 15};

    // title
    this->title = new QLabel{this};
    this->title->setText("***ARCHMAGE MODE***");
    this->title->setFont(f);
    this->title->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    // stautes list
    this->statues_list = new QListWidget{this};
    this->statues_list->setSelectionMode(QAbstractItemView::SingleSelection);

    // middle part
    QWidget* middle_part = new QWidget{};
    QVBoxLayout* v_layout = new QVBoxLayout{middle_part};

    QWidget* statue_data_widget = new QWidget{};
    QFormLayout* form_layout = new QFormLayout{statue_data_widget};

    this->statue_name_edit = new QLineEdit{};
    this->statue_material_edit = new QLineEdit{};
    this->statue_age_edit = new QLineEdit{};
    this->statue_form_edit = new QLineEdit{};

    QLabel* statue_name_label = new QLabel{"Power Word Name:"};
    QLabel* statue_material_label = new QLabel{"Material:"};
    QLabel* statue_age_label = new QLabel{"Age:"};
    QLabel* statue_form_label = new QLabel{"Corporeal Form:"};

    statue_name_label->setBuddy(this->statue_name_edit);
    statue_material_label->setBuddy(this->statue_material_edit);
    statue_age_label->setBuddy(this->statue_age_edit);
    statue_form_label->setBuddy(this->statue_form_edit);

    statue_name_label->setFont(f);
    statue_material_label->setFont(f);
    statue_age_label->setFont(f);
    statue_form_label->setFont(f);

    this->statue_name_edit->setFont(f);
    this->statue_material_edit->setFont(f);
    this->statue_age_edit->setFont(f);
    this->statue_form_edit->setFont(f);

    form_layout->addRow(statue_name_label, this->statue_name_edit);
    form_layout->addRow(statue_material_label, this->statue_material_edit);
    form_layout->addRow(statue_age_label, this->statue_age_edit);
    form_layout->addRow(statue_form_label, this->statue_form_edit);

    // buttons from middle in a horizontal box
    QWidget* middle_buttons_widget = new QWidget{};
    QHBoxLayout* h_layout_middle = new QHBoxLayout{middle_buttons_widget};

    this->add_statue_button = new QPushButton{"Add"};
    this->delete_statue_button = new QPushButton{"Delete"};
    this->update_statue_button = new QPushButton{"Update"};

    this->add_statue_button->setFont(f);
    this->delete_statue_button->setFont(f);
    this->update_statue_button->setFont(f);

    h_layout_middle->addWidget(this->add_statue_button);
    h_layout_middle->addWidget(this->delete_statue_button);
    h_layout_middle->addWidget(this->update_statue_button);


    // add on vertical layout from middle
    v_layout->addWidget(statue_data_widget);
    v_layout->addWidget(middle_buttons_widget);


    // bottom part
    QWidget* bottom_part = new QWidget{};
    QHBoxLayout* h_layout_bottom = new QHBoxLayout{bottom_part};

    QWidget* bottom_left = new QWidget{};
    QVBoxLayout* v_layout_bottom_left = new QVBoxLayout{bottom_left};


    QWidget* file_location_data_widget = new QWidget{};
    QFormLayout* file_location_layout = new QFormLayout{file_location_data_widget};

    this->file_location_edit = new QLineEdit{};
    QLabel* file_path_label = new QLabel{"File Location:"};
    file_path_label->setBuddy(this->file_location_edit);
    file_path_label->setFont(f);
    this->file_location_edit->setFont(f);

    file_location_layout->addRow(file_path_label, this->file_location_edit);

    // button from bottom left bottom
    this->file_location_button = new QPushButton{"Save File Location"};
    this->file_location_button->setFont(f);
    this->file_location_button->setMaximumWidth(400);

    // add to bottom left vertical layout
    v_layout_bottom_left->addWidget(file_location_data_widget);
    v_layout_bottom_left->addWidget(this->file_location_button);

    // right bottom part
    // a button
    this->user_mode_button = new QPushButton{"Close"};
    this->user_mode_button->setFont(f);

    // add to bottom layout
    h_layout_bottom->addWidget(bottom_left);
    h_layout_bottom->addWidget(this->user_mode_button);

    // add to main layout
    layout->addWidget(this->title);
    layout->addWidget(this->statues_list);
    layout->addWidget(middle_part);
    layout->addWidget(bottom_part);

    // for alignment
    this->setLayout(layout);

    QTimer *timer = new QTimer{this};
    connect(timer, SIGNAL(timeout()), this, SLOT(update_buttons_colour()));
    timer->start(2000);
}

void ADMIN_GUI::connect_signals_and_slots() {
    QObject::connect(this, &ADMIN_GUI::statues_update_signal, this, &ADMIN_GUI::populate_statues_list);
    QObject::connect(this->user_mode_button, &QPushButton::clicked, this, &ADMIN_GUI::user_mode_button_handler);
    QObject::connect(this->add_statue_button, &QPushButton::clicked, this, &ADMIN_GUI::add_statue_button_handler);
    QObject::connect(this->delete_statue_button, &QPushButton::clicked, this, &ADMIN_GUI::delete_statue_button_handler);
    QObject::connect(this->update_statue_button, &QPushButton::clicked, this, &ADMIN_GUI::update_statue_button_handler);
    QObject::connect(this->file_location_button, &QPushButton::clicked, this, &ADMIN_GUI::file_location_button_handler);
    QObject::connect(this, SIGNAL(add_statue_signal(const std::string&, const std::string&, const int, const std::string&)),
                     this, SLOT(add_statue(const std::string&, const std::string&, const int, const std::string&)));
    QObject::connect(this->statues_list, &QListWidget::itemSelectionChanged, this, [this]() {this->list_item_changed();});
}

void ADMIN_GUI::user_mode_button_handler() {
    //auto user_mode_gui = new USER_GUI{};
    //user_mode_gui->setMinimumSize(1080, 820);
    //user_mode_gui->show();
    this->close();
}

void ADMIN_GUI::add_statue_button_handler() {
    QString name = this->statue_name_edit->text();
    QString material = this->statue_material_edit->text();
    QString age = this->statue_age_edit->text();
    QString form = this->statue_form_edit->text();

    emit add_statue_signal(name.toStdString(), material.toStdString(), age.toInt(), form.toStdString());
}

void ADMIN_GUI::delete_statue_button_handler() {
    QString name = this->statue_name_edit->text();
    std::string _name = name.toStdString();
    try {
        this->controller.deleteGuardianStatue(_name);
        this->delete_statue_button->setStyleSheet("background:green");
        emit statues_update_signal();
    } catch (std::exception&) {
        this->delete_statue_button->setStyleSheet("background:red");
    }
}

void ADMIN_GUI::list_item_changed() {
    int idx = this->get_selected_index();
    if (idx == -1) {
        return;
    }
    if (idx >= int(this->controller.getAllGuardianStatues().size())) {
        return;
    }
    GuardianStatue s = this->controller.getAllGuardianStatues()[idx];

    this->statue_name_edit->setText(QString::fromStdString(s.getPowerWordName()));
    this->statue_material_edit->setText(QString::fromStdString(s.getMaterial()));
    this->statue_age_edit->setText(QString::number(s.getAge()));
    this->statue_form_edit->setText(QString::fromStdString(s.getCorporealForm()));

}

int ADMIN_GUI::get_selected_index() {
    if (this->statues_list->count() == 0) {
        return -1;
    }

    QModelIndexList index = this->statues_list->selectionModel()->selectedIndexes();
    if (index.size() == 0) {
        this->statue_name_edit->clear();
        this->statue_material_edit->clear();
        this->statue_age_edit->clear();
        this->statue_form_edit->clear();
        return -1;
    }
    int idx = index.at(0).row();
    return idx;
}

void ADMIN_GUI::update_statue_button_handler() {
    QString name = this->statue_name_edit->text();
    QString material = this->statue_material_edit->text();
    QString age = this->statue_age_edit->text();
    QString form = this->statue_form_edit->text();

    std::string _name = name.toStdString();
    std::string _material = material.toStdString();
    int _age = age.toInt();
    std::string _form = form.toStdString();
    try {
        if (_age == 0 && age != "0") {
            throw std::exception();
        }
        this->controller.updateGuardianStatue(_name, _material, _age, _form);
        this->update_statue_button->setStyleSheet("background:green");
        emit statues_update_signal();
    } catch (std::exception&) {
        this->update_statue_button->setStyleSheet("background:red");
    }
}

void ADMIN_GUI::file_location_button_handler() {
    QString path = this->file_location_edit->text();
    std::string filepath = path.toStdString();

    std::ifstream test;
    test.open(filepath);
    if (test.is_open()) {
        this->controller.setFilePath(filepath);
        this->file_location_edit->setStyleSheet("background-color:green");
        emit statues_update_signal();
    }
    else {
        this->file_location_edit->setStyleSheet("background-color:red");
    }
}

void ADMIN_GUI::populate_statues_list() {
    if (this->statues_list->count() > 0) {
        this->statues_list->clear();
    }
    for (auto s : this->controller.getAllGuardianStatues()) {
        QString item_in_list = QString::fromStdString(s.to_string());
        QFont f = {"Verdana", 15};
        QListWidgetItem* item = new QListWidgetItem{item_in_list};
        item->setFont(f);
        this->statues_list->addItem(item);
    }
    if (this->controller.getAllGuardianStatues().size() > 0) {
        this->statues_list->setCurrentRow(0);
    }
}

void ADMIN_GUI::add_statue(const std::string& _name, const std::string& _material, const int _age, const std::string& _form) {
    try {
        if (_age == 0 && this->statue_age_edit->text() != "0") {
            throw std::exception();
        }
        this->controller.addGuardianStatue(_name, _material, _age, _form);
        this->add_statue_button->setStyleSheet("background-color:green");
        emit statues_update_signal();
    } catch (std::exception&) {
        this->add_statue_button->setStyleSheet("background-color:red");
    }
}

void ADMIN_GUI::update_buttons_colour() {
    this->add_statue_button->setStyleSheet("background-color:solid white");
    this->delete_statue_button->setStyleSheet("background-color:solid white");
    this->update_statue_button->setStyleSheet("background-color:solid white");
    this->file_location_edit->setStyleSheet("background-color:solid white");
    this->file_location_button->setStyleSheet("background-color:solid white");
}
