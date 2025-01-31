/*
  Copyright (c) 2011 - Tőkés Attila

  This file is part of SmtpClient for Qt.

  SmtpClient for Qt is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  SmtpClient for Qt is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY.

  See the LICENCE file for more details.
*/

#ifndef SENDEMAIL_H
#define SENDEMAIL_H

#include <QWidget>

#include <SmtpMime>

#include "envGenerador.h"
#include "envModel.h"
#include "msgDades.h"
#include "msgPers.h"


namespace Ui {
    class SendEmail;
}

/**
 * @class SendEmail
 * @brief Classe que gestiona l'enviament d'emails mitjançant una interfície Qt. *
 */
class SendEmail : public QWidget
{
    Q_OBJECT

public:
    explicit SendEmail(QWidget *parent = 0);
    ~SendEmail();

    static EmailAddress stringToEmail(const QString & str);

    envGenerador generador;

    QList<msgPers> personalitzacions;
    /*@brief És un índex al missatge personalitzat que s'està veient
     * Va des de 0 fins a personalitzacions.size()
     */
    int persActual;

    /*@brief Mètode que actualitza les dades que es veuen a pantalla
     */
    void ActualitzaUi();


private slots:

    /*@brief Mètode que adjunta un arxiu a tots els missatges
     */
    void addAttachment();

    /*@brief Mètode fa l'enviament de tots els missatges
     */
    void fesEnviament();


    //*@brief Mètode que crida al lector del fitxer .csv que té les dades
    //  */
    void llegeixDades();

    // /*@brief Mètode que crida al lector del fitxer .txt que és el model
    //  */
    void llegeixModel();

    // /*@brief Incrementa el comptador que diu quin missatge personalitzat s'està mostrant
    //  */
    void missatgeSeg();

    // /*@brief Decrementa el comptador que diu quin missatge personalitzat s'està mostrant
    //  */
    void missatgeAnt();

private:
    Ui::SendEmail *ui;

    void errorMessage(const QString & message);
};

#endif // SENDEMAIL_H
