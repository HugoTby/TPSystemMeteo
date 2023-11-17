//*********************************************************************************************
//* Programme : main.cpp                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 17/11/2023
//*
//* Programmeurs : BOTEL Faustin                                               Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : initialiser l'interface graphique
//* Programmes associ�s : AUCUN
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
