//*********************************************************************************************
//* Programme : TPSystemMeteo.h                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 17/11/2023
//*
//* Programmeurs : BOTEL Faustin                                               Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Récupérer les data de la k8055, les convertir en degres et envoyer en BDD
//* Programmes associés : AUCUN
//*********************************************************************************************


#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TPSytemeMeteo.h"

class TPSytemeMeteo : public QMainWindow
{
    Q_OBJECT

public:
    TPSytemeMeteo(QWidget *parent = nullptr);
    ~TPSytemeMeteo();

private:
    Ui::TPSytemeMeteoClass ui;
};
