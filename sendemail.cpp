/*
  Copyright (c) 2011 - Tőkés Attila

  This file is part of SmtpClient for Qt.

  SmtpClient for Qt is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  SmtpClient for Qt is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY.

  See the LICENSE file for more details.
*/

#include "sendemail.h"
#include "ui_sendemail.h"

#include <QFileDialog>
#include <QErrorMessage>
#include <QMessageBox>

#include <iostream>


#include "smtp_params.h"

using namespace std;

SendEmail::SendEmail(QWidget *parent) :
    QWidget(parent),
    generador(""),
    ui(new Ui::SendEmail)
{
    ui->setupUi(this);

    ui->host->setText(SMTP_SERVER);
    ui->port->setValue(465);
    ui->ssl->setChecked(true);
    ui->auth->setChecked(true);
    ui->username->setText(SENDER_EMAIL);
    ui->password->setText(SENDER_PASSWORD);

    ui->sender->setText(QString(SENDER_NAME) + "<" + SENDER_EMAIL + ">");
    // ui->recipients->setText(QString(RECIPIENT_NAME) + "<" + RECIPIENT_EMAIL + ">");

    // Connecta els botons als seus slots
    connect(ui->cmdLlegeixDades, &QPushButton::clicked, this, &SendEmail::llegeixDades);
    connect(ui->cmdLlegeixModel, &QPushButton::clicked, this, &SendEmail::llegeixModel);
    connect(ui->cmdAnt, &QPushButton::clicked, this, &SendEmail::missatgeAnt);
    connect(ui->cmdSeg, &QPushButton::clicked, this, &SendEmail::missatgeSeg);
}

SendEmail::~SendEmail()
{
    delete ui;
}

EmailAddress SendEmail::stringToEmail(const QString &str)
{
    int p1 = str.indexOf("<");
    int p2 = str.indexOf(">");

    if (p1 == -1)
    {
        // no name, only email address
        return EmailAddress(str);
    }
    else
    {
        return EmailAddress(str.mid(p1 + 1, p2 - p1 - 1), str.left(p1));
    }

}

void SendEmail::addAttachment()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        ui->attachments->addItems(dialog.selectedFiles());
}

void SendEmail::fesEnviament()
{
    QString host = ui->host->text();
    int port = ui->port->value();
    bool ssl = ui->ssl->isChecked();
    bool auth = ui->auth->isChecked();
    QString user = ui->username->text();
    QString password = ui->password->text();

    EmailAddress sender = stringToEmail(ui->sender->text());

    QStringList rcptStringList = ui->recipients->text().split(';');



    QString subject = ui->subject->text();
    QString html = ui->texteditor->toHtml();

    SmtpClient smtp (host, port, ssl ? SmtpClient::SslConnection : SmtpClient::TcpConnection);

    MimeMessage message;

    message.setSender(sender);
    message.setSubject(subject);

    for (int i = 0; i < rcptStringList.size(); ++i)
         message.addRecipient(stringToEmail(rcptStringList.at(i)));

    MimeHtml content;
    content.setHtml(html);

    message.addPart(&content);

    QList<QFile*> files;
    for (int i = 0; i < ui->attachments->count(); ++i)
    {
        QFile* file = new QFile(ui->attachments->item(i)->text());
        files.append(file);

        MimeAttachment* attachment = new MimeAttachment(file);

        message.addPart(attachment, true);
    }

    smtp.connectToHost();
    if (!smtp.waitForReadyConnected())
    {
        errorMessage("Connection Failed");
        return;
    }

    if (auth)
    {
        smtp.login(user, password);
        if (!smtp.waitForAuthenticated())
        {
            errorMessage("Authentification Failed");
            return;
        }
    }

    smtp.sendMail(message);
    if (!smtp.waitForMailSent())
    {
        errorMessage("Mail sending failed");
        return;
    }
    else
    {
        QMessageBox okMessage (this);
        okMessage.setText("The email was succesfully sent.");
        okMessage.exec();
    }

    smtp.quit();

    for (auto file : files) {
        delete file;
    }
}


void SendEmail::errorMessage(const QString &message)
{
    QErrorMessage err (this);

    err.showMessage(message);

    err.exec();
}


// Mètode que crida al lector del fitxer .csv que té les dades
void SendEmail::llegeixDades() {
    // Obrir un diàleg per seleccionar el fitxer CSV
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("Selecciona un fitxer CSV"),
                                                    QString(),
                                                    tr("Fitxers CSV (*.csv)"));

    // Si no s'ha seleccionat cap fitxer, sortir
    if (filePath.isEmpty()) {
        return;
    }

    try {
        // Cridar el mètode de l'objecte generador per llegir les dades
        generador.llegeixDades(filePath);
        if (generador.totOk()) {
            generador.genera();
            persActual = 0; // Poso l'index de personalitzaciona a 0
            personalitzacions = generador.missatges;
            ActualitzaUi();
        }
        persActual = 0; // Poso l'index de personalitzaciona a 0
        personalitzacions = generador.missatges;
        ActualitzaUi();
        QMessageBox::information(this, tr("Dades carregades"),
                                 tr("Les dades del fitxer han estat carregades correctament."));
    } catch (const std::exception &e) {
        // Mostrar un error en cas d'excepció
        errorMessage(tr("Error en carregar les dades: %1").arg(e.what()));
    }
}

// Mètode que crida al lector del fitxer .txt que és el model
void SendEmail::llegeixModel() {
    // Obrir un diàleg per seleccionar el fitxer de model
    QString filePath = QFileDialog::getOpenFileName(this,
                                                    tr("Selecciona un fitxer de model"),
                                                    QString(),
                                                    tr("Fitxers de model (*.txt)"));

    // Si no s'ha seleccionat cap fitxer, sortir
    if (filePath.isEmpty()) {
        return;
    }

    try {
        // Crear un nou model a partir del fitxer seleccionat
        envModel nouModel(filePath);

        // Assignar el model a l'objecte generador
        generador.model = nouModel;
        QMessageBox::information(this, tr("Model carregat"),
                                 tr("El model del fitxer ha estat carregat correctament."));
        ui->subject->setText(nouModel.assumpteTemplate);
        ui->texteditor->setText(nouModel.contingutTemplate);
        ui->recipients->setText(nouModel.destinatariTemplate);
    } catch (const std::exception &e) {
        // Mostrar un error en cas d'excepció
        errorMessage(tr("Error en carregar el model: %1").arg(e.what()));
    }
}

void SendEmail::ActualitzaUi() {
    ui->subject->setText(generador.model.assumpteTemplate);
    ui->texteditor->setText(generador.model.contingutTemplate);
    ui->recipients->setText(generador.model.destinatariTemplate);

    ui->subject_2->setText(personalitzacions[persActual].assumpte);
    ui->texteditor_2->setText(personalitzacions[persActual].contingut);
    ui->recipients_2->setText(personalitzacions[persActual].destinartari);
}

void SendEmail::missatgeSeg() {
    if (persActual<personalitzacions.size()-1 ) {
        persActual++;
        ActualitzaUi();
    }
}
void SendEmail::missatgeAnt() {
    if (persActual>0) {
        persActual--;
        ActualitzaUi();
    }
}
