#include "tests.h"
#include <cassert>
#include "controller.h"
#include "csv_file.h"
#include "html_file.h"
#include "exceptions.h"
#include "action.h"


void Tests::test_domain() {
    this->message += "testing domain\n";
    Guardian_statue gs1{"name", "material", 100, "form"};
    assert(gs1.get_power_word_name() == "name");
    assert(gs1.get_material() == "material");
    assert(gs1.get_age() == 100);
    assert(gs1.get_corporeal_form() == "form");
}

void Tests::test_repository() {
    this->message += "testing repository\n";

    this->message += "\ttesting base repository\n";

    Repository repo{};
    Guardian_statue gs1{"name1", "material1", 100, "form1"};
    Guardian_statue gs2{"name2", "material1", 100, "form1"};
    Guardian_statue gs3{"name2", "updated_material", 100, "form1"};
    Guardian_statue gs4{"name3", "material2", 100, "form1"};
    repo.add(gs1);
    assert(repo.get_size() == 1);
    repo.add(gs2);
    assert(repo.get_size() == 2);
    try {
        repo.add(gs2);
        assert(false);
    } catch (Exception&) {
        assert(true);
    }
    assert(repo.get_size() == 2);
    repo.remove("name2");
    assert(repo.get_size() == 1);
    try {
        repo.remove(gs2.get_power_word_name());
        assert(false);
    } catch (Exception&) {
        assert(true);
    }
    repo.add(gs2);
    assert(repo.get_size() == 2);
    repo.update(gs3);
    assert(repo.get_size() == 2);
    std::vector<Guardian_statue> v = repo.get_all();
    assert(v[1].get_material() == "updated_material");
    try {
        repo.update(gs4);
        assert(false);
    } catch (Exception&) {
        assert(true);
    }

    this->message += "\ttesting csv_file repository\n";

    ////////////////////////////////////////////////////////////////////////////
    std::string filename = "test_csv_file.txt";
    ////////////////////////////////////////////////////////////////////////////
    Repository* csv_file = new Csv_file{filename};
    std::ofstream f{filename};
    f.close();
    csv_file->add(Guardian_statue{"name1", "material1", 1, "form1"});
    csv_file->add(Guardian_statue{"name2", "material2", 1, "form2"});
    csv_file->add(Guardian_statue{"name3", "material3", 1, "form3"});
    csv_file->add(Guardian_statue{"name4", "material4", 1, "form4"});
    csv_file->add(Guardian_statue{"name5", "material5", 1, "form5"});
    csv_file->add(Guardian_statue{"name6", "material6", 1, "form6"});
    csv_file->add(Guardian_statue{"name7", "material7", 1, "form7"});
    csv_file->add(Guardian_statue{"name8", "material8", 1, "form8"});
    csv_file->add(Guardian_statue{"name9", "material9", 1, "form9"});
    csv_file->add(Guardian_statue{"name10", "material10", 1, "form10"});
    assert(csv_file->get_size() == 10);
    csv_file->add(Guardian_statue{"name11","material11",11,"form11"});
    assert(csv_file->get_size() == 11);
    csv_file->remove("name11");
    assert(csv_file->get_size() == 10);
    csv_file->update(Guardian_statue{"name10", "updated_material", 10,"form10"});
    std::vector<Guardian_statue> v1 = csv_file->get_all();
    assert(v1[9].get_material() == "updated_material");
    csv_file->update(Guardian_statue{"name10", "material10", 10,"form10"});
    v1 = csv_file->get_all();
    assert(v1[9].get_material() == "material10");
    csv_file->remove("name1");
    csv_file->remove("name2");
    csv_file->remove("name3");
    csv_file->remove("name4");
    csv_file->remove("name5");
    csv_file->remove("name6");
    csv_file->remove("name7");
    csv_file->remove("name8");
    csv_file->remove("name9");
    csv_file->remove("name10");
    assert(csv_file->get_size() == 0);

    this->message += "\ttesting html_file repository\n";

    ////////////////////////////////////////////////////////////////////////////
    std::string filename1 = "test_html_file.txt";
    ////////////////////////////////////////////////////////////////////////////
    Repository* html_file = new Html_file{filename1};
    std::ofstream f1{filename1};
    f1.close();
    html_file->add(Guardian_statue{"name1", "material1", 1, "form1"});
    html_file->add(Guardian_statue{"name2", "material2", 2, "form2"});
    html_file->add(Guardian_statue{"name3", "material3", 3, "form3"});
    html_file->add(Guardian_statue{"name4", "material4", 4, "form4"});
    html_file->add(Guardian_statue{"name5", "material5", 5, "form5"});
    html_file->add(Guardian_statue{"name6", "material6", 6, "form6"});
    html_file->add(Guardian_statue{"name7", "material7", 7, "form7"});
    html_file->add(Guardian_statue{"name8", "material8", 8, "form8"});
    html_file->add(Guardian_statue{"name9", "material9", 9, "form9"});
    html_file->add(Guardian_statue{"name10", "material10", 10, "form10"});
    assert(html_file->get_size() == 10);
    html_file->add(Guardian_statue{"name11", "material11", 11, "form11"});
    assert(html_file->get_size() == 11);
    html_file->remove("name11");
    assert(html_file->get_size() == 10);
    html_file->update(Guardian_statue{"name10", "updated_material", 10,"form10"});
    std::vector<Guardian_statue> v2 = html_file->get_all();
    assert(v2[9].get_material() == "updated_material");
    html_file->update(Guardian_statue{"name10", "material10", 10,"form10"});
    v2 = html_file->get_all();
    assert(v2[9].get_material() == "material10");
    html_file->remove("name1");
    html_file->remove("name2");
    html_file->remove("name3");
    html_file->remove("name4");
    html_file->remove("name5");
    html_file->remove("name6");
    html_file->remove("name7");
    html_file->remove("name8");
    html_file->remove("name9");
    html_file->remove("name10");
    assert(html_file->get_size() == 0);
}

void Tests::test_controller() {
    this->message += "testing controller\n";

    this->message += "\ttesting basic operations\n";
    Repository* repo = new Repository{};
    Controller ctrl{repo, repo};
    ctrl.__admin_add_statue("name1", "material1", 1, "form1");
    assert(repo->get_size() == 1);
    ctrl.__admin_add_statue("name2", "material2", 2, "form2");
    assert(repo->get_size() == 2);
    ctrl.__admin_add_statue("name3", "material3", 3, "form3");
    assert(repo->get_size() == 3);
    try {
        ctrl.__admin_add_statue("name3", "material3", 3, "form3");
        assert(false);
    } catch (Exception&) {
        assert(true);
    }
    try {
        ctrl.__admin_add_statue("name4", "", -1, "");
        assert(false);
    } catch (Exception&) {
        assert(true);
    }
    ctrl.__admin_remove_statue("name3");
    assert(repo->get_size() == 2);
    ctrl.__admin_update_statue("name2", "update_material", 2, "form2");
    std::vector<Guardian_statue> v = ctrl.__admin_get_statues();
    assert(v[1].get_material() == "update_material");

    ////////////////////////////////////////////////////////////////////////////
    std::string filename = "test_csv_file.txt";
    ////////////////////////////////////////////////////////////////////////////
    Repository* csv_repo = new Csv_file{filename};
    Controller ctrl1{csv_repo, csv_repo};
    ctrl1.__admin_add_statue("name1", "material1", 1, "form1");
    assert(csv_repo->get_size() == 1);
    ctrl1.__admin_add_statue("name2", "material2", 2, "form2");
    assert(csv_repo->get_size() == 2);
    ctrl1.__admin_add_statue("name3", "material3", 3, "form3");
    assert(csv_repo->get_size() == 3);
    try {
        ctrl1.__admin_add_statue("name3", "material3", 3, "form3");
        assert(false);
    } catch (Exception&) {
        assert(true);
    }
    try {
        ctrl1.__admin_add_statue("name4", "", -1, "");
        assert(false);
    } catch (Exception&) {
        assert(true);
    }
    ctrl1.__admin_remove_statue("name3");
    assert(csv_repo->get_size() == 2);
    ctrl1.__admin_update_statue("name2", "update_material", 2, "form2");
    std::vector<Guardian_statue> v1 = ctrl1.__admin_get_statues();
    assert(v1[1].get_material() == "update_material");
    ctrl1.__admin_remove_statue("name1");
    ctrl1.__admin_remove_statue("name2");
    assert(csv_repo->get_size() == 0);
    ctrl1.__admin_set_file_path(filename);

    Repository* repo1 = new Repository{};
    Repository* repo2 = new Repository{};
    Controller ctrl2{repo1, repo2};
    ctrl2.__admin_add_statue("statue1", "material1", 1, "form1");
    ctrl2.__admin_add_statue("statue2", "material1", 2, "form1");
    ctrl2.__admin_add_statue("statue3", "material1", 4, "form1");
    ctrl2.__admin_add_statue("statue4", "material1", 8, "form1");
    ctrl2.__admin_add_statue("statue5", "material1", 16, "form1");
    ctrl2.__admin_add_statue("statue6", "material2", 32, "form1");
    ctrl2.__admin_add_statue("statue7", "material2", 64, "form1");
    ctrl2.__admin_add_statue("statue8", "material2", 128, "form1");
    ctrl2.__admin_add_statue("statue9", "material2", 256, "form1");
    ctrl2.__admin_add_statue("statue10", "material2", 512, "form1");
    assert(ctrl2.__user_get_statues().size() == 0);
    assert(ctrl2.__user_next_statue().get_power_word_name() == "statue1");
    assert(ctrl2.__user_next_statue().get_power_word_name() == "statue2");
    assert(ctrl2.__user_next_statue().get_power_word_name() == "statue3");
    assert(ctrl2.__user_next_statue().get_power_word_name() == "statue4");
    assert(ctrl2.__user_next_statue().get_power_word_name() == "statue5");
    assert(ctrl2.__user_next_statue().get_power_word_name() == "statue6");
    assert(ctrl2.__user_next_statue().get_power_word_name() == "statue7");
    assert(ctrl2.__user_next_statue().get_power_word_name() == "statue8");
    assert(ctrl2.__user_next_statue().get_power_word_name() == "statue9");
    assert(ctrl2.__user_next_statue().get_power_word_name() == "statue10");
    assert(ctrl2.__user_next_statue().get_power_word_name() == "statue1");
    ctrl2.__user_save_statue("statue1");
    assert(ctrl2.__user_get_statues().size() == 1);
    ctrl2.__user_save_statue("statue2");
    assert(ctrl2.__user_get_statues().size() == 2);
    ctrl2.__user_save_statue("statue3");
    assert(ctrl2.__user_get_statues().size() == 3);
    ctrl2.__user_save_statue("statue4");
    assert(ctrl2.__user_get_statues().size() == 4);
    ctrl2.__user_save_statue("statue5");
    assert(ctrl2.__user_get_statues().size() == 5);
    ctrl2.__user_save_statue("statue6");
    assert(ctrl2.__user_get_statues().size() == 6);
    ctrl2.__user_save_statue("statue7");
    assert(ctrl2.__user_get_statues().size() == 7);
    ctrl2.__user_save_statue("statue8");
    assert(ctrl2.__user_get_statues().size() == 8);
    ctrl2.__user_save_statue("statue9");
    assert(ctrl2.__user_get_statues().size() == 9);
    ctrl2.__user_save_statue("statue10");
    assert(ctrl2.__user_get_statues().size() == 10);
    assert(ctrl2.__user_filter_statues("material1", 16).size() == 4);
    assert(ctrl2.__user_filter_statues("material1", 17).size() == 5);
    assert(ctrl2.__user_filter_statues("material2", 512).size() == 4);
    assert(ctrl2.__user_filter_statues("material2", 513).size() == 5);
    ctrl2.__user_set_file_path(filename);

    this->message += "\ttesting undo/redo\n";
    Repository* repo3 = new Repository{};
    Controller ctrl3{repo3, repo3};
    ctrl3.__admin_add_statue("name1", "material1", 1, "form1");
    ctrl3.__admin_add_statue("name2", "material2", 2, "form2");
    ctrl3.__admin_add_statue("name3", "material3", 3, "form3");
    ctrl3.__admin_add_statue("name4", "material4", 4, "form4");
    ctrl3.__admin_add_statue("name5", "material5", 5, "form5");
    assert(repo3->get_size() == 5);
    ctrl3.undo();
    assert(repo3->get_size() == 4);
    ctrl3.redo();
    assert(repo3->get_size() == 5);
    try {
        ctrl3.redo();
        assert(false);
    } catch (Exception&) {
        assert(true);
    }
    ctrl3.undo();
    ctrl3.undo();
    ctrl3.undo();
    ctrl3.undo();
    ctrl3.undo();
    assert(repo3->get_size() == 0);
    try {
        ctrl3.undo();
        assert(false);
    } catch (Exception&) {
        assert(true);
    }
    ctrl3.redo();
    ctrl3.redo();
    ctrl3.redo();
    ctrl3.redo();
    ctrl3.redo();
    assert(repo3->get_size() == 5);
    ctrl3.__admin_update_statue("name4", "updated_material", 4, "form4");
    assert(repo3->get_all()[3].get_material() == "updated_material");
    ctrl3.undo();
    assert(repo3->get_all()[3].get_material() == "material4");
    ctrl3.redo();
    assert(repo3->get_all()[3].get_material() == "updated_material");
    try {
        ctrl3.redo();
        assert(false);
    } catch (Exception&) {
        assert(true);
    }
}

void Tests::test_action() {
    this->message += "testing action\n";

    this->message += "\ttesting action_add\n";
    Guardian_statue gs1{"name1", "material1", 1, "form1"};
    Repository* repo = new Repository{};
    repo->add(gs1);
    Action* action_add = new Action_add{gs1, repo};
    action_add->execute_undo();
    assert(repo->get_size() == 0);
    action_add->execute_redo();
    assert(repo->get_size() == 1);
    action_add->execute_undo();
    assert(repo->get_size() == 0);

    this->message += "\ttesting action_remove\n";
    Action* action_remove = new Action_remove{gs1, repo};
    action_remove->execute_undo();
    assert(repo->get_size() == 1);
    action_remove->execute_redo();
    assert(repo->get_size() == 0);
    action_remove->execute_undo();
    assert(repo->get_size() == 1);

    this->message += "\ttesting action_update\n";
    Guardian_statue gs2{"name1", "updated_material", 1, "form1"};
    Action* action_update = new Action_update{gs1, gs2, repo};
    repo->update(gs2);
    assert(repo->get_all()[0].get_material() == "updated_material");
    action_update->execute_undo();
    assert(repo->get_all()[0].get_material() == "material1");
    action_update->execute_redo();
    assert(repo->get_all()[0].get_material() == "updated_material");
}

void Tests::test_all() {
    this->test_domain();
    this->test_repository();
    this->test_controller();
    this->test_action();
    this->message += "all tests done!\n";
}
