#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "envGenerador.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Classe principal de la finestra de l'aplicació.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief Gestiona l'acció de prémer el botó "Generar enviament".
     */
    void onGenerateClicked();

private:
    Ui::MainWindow *ui;

    // Atributs per gestionar l'enviament
    envGenerador *generador; ///< Instància per gestionar el procés de generació.
};

#endif // MAINWINDOW_H
