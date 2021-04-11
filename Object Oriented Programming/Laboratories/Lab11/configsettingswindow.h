#ifndef CONFIGSETTINGSWINDOW_H
#define CONFIGSETTINGSWINDOW_H

#include <QMainWindow>

namespace Ui {
class configSettingsWindow;
}

class configSettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit configSettingsWindow(QWidget *parent = nullptr);
    ~configSettingsWindow();

public slots:
    void update_line_edit();

private:

    bool settings_flag = false;

    void read_settings();
    void connect_signals_and_slots();

    void save_button_handler();

    Ui::configSettingsWindow *ui;
    void closeEvent(QCloseEvent* event);
};

#endif // CONFIGSETTINGSWINDOW_H
