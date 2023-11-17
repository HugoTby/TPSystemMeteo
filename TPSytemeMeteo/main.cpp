//*********************************************************************************************
//* Programme : main.cpp                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 17/11/2023
//*
//* Programmeurs : BOTEL Faustin                                               Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : initialiser l'interface graphique
//* Programmes associés : AUCUN
//*********************************************************************************************



#include "TPSytemeMeteo.h"
#include <QtWidgets/QApplication>
#include "K8055Adapter.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TPSytemeMeteo w;
    w.show();
    return a.exec();
}
