#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "envGenerador.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , generador(nullptr) // Inicialitzem el punter
{
    ui->setupUi(this);

    // Connectem el botó "Generar enviament" amb la funció onGenerateClicked
    connect(ui->cmdGenerar, &QPushButton::clicked, this, &MainWindow::onGenerateClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete generador; // Alliberem memòria
}

void MainWindow::onGenerateClicked()
{
    // Selecció del fitxer de personalitzacions
    QString dadesPath = QFileDialog::getOpenFileName(this, "Selecciona el fitxer de dades", "", "CSV Files (*.csv)");
    if (dadesPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "No s'ha seleccionat cap fitxer de dades.");
        return;
    }

    // Selecció del fitxer de model
    QString modelPath = QFileDialog::getOpenFileName(this, "Selecciona el fitxer de model", "", "Text Files (*.txt)");
    if (modelPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "No s'ha seleccionat cap fitxer de model.");
        return;
    }

    // Ruta de sortida
    QString sortidaPath = QFileDialog::getSaveFileName(this, "Selecciona el fitxer de sortida", "", "CSV Files (*.csv)");
    if (sortidaPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "No s'ha seleccionat cap fitxer de sortida.");
        return;
    }

    // Creem i inicialitzem el generador
    delete generador; // Assegurem que no hi ha fugues de memòria
    generador = new envGenerador(modelPath);

    // Carreguem les dades i generem l'enviament
    try {
        generador->llegeixDades(dadesPath);
        generador->genera(sortidaPath);

        QMessageBox::information(this, "Èxit", "L'enviament s'ha generat correctament!");
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "Error", QString("Error durant el procés: %1").arg(e.what()));
    }
}
