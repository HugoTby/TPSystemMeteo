//*********************************************************************************************
//* Programme : TPSystemMeteo.cpp                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 17/11/2023
//*
//* Programmeurs : BOTEL Faustin                                               Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : R�cup�rer les data de la k8055, les convertir en degres et envoyer en BDD
//* Programmes associ�s : AUCUN
//*********************************************************************************************


#include "TPSytemeMeteo.h"
#include "K8055Adapter.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
#include <QDateTime>



TPSytemeMeteo::TPSytemeMeteo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("192.168.64.213");
	db.setDatabaseName("systemMeteo");
	db.setUserName("root");
	db.setPassword("root");

	// V�rifiez si la connexion est �tablie
	if (!db.open()) {
		ui.connectBDD->setText("Deconnecte");
	}
	else {
		ui.connectBDD->setText("Connecte");

	}


	// Initialiser la carte K8055
	K8055Adapter *carteES = K8055Adapter::getInstance();
	carteES->OpenDevice(0);
	long channel = 1;  // Remplacez par le num�ro de canal que vous souhaitez lire

	// Cr�er un QTimer pour actualiser la temp�rature toutes les 1000 millisecondes (1 seconde)
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, [this, carteES, channel, db]() {
		// Lire la tension
		long data = carteES->ReadAnalogChannel(channel);
		double voltage = (static_cast<double>(data) / 255.0) * 5.0;

		// Convertir la tension en temp�rature en utilisant une relation lin�aire
		double minVoltage = 0.0;   // Correspond � -30�C
		double maxVoltage = 5.0;   // Correspond � 60�C
		double minTemperature = -30.0;
		double maxTemperature = 60.0;

		double temperature = ((voltage - minVoltage) / (maxVoltage - minVoltage)) * (maxTemperature - minTemperature) + minTemperature;

		// Obtenir la date et l'heure actuelles
		QDateTime currentDateTime = QDateTime::currentDateTime();

		// Ins�rer les donn�es dans la base de donn�es
		QSqlQuery query(db);
		query.prepare("INSERT INTO temperature (degres, date, voltage) VALUES (?, ?, ?)");
		query.addBindValue(temperature);
		query.addBindValue(currentDateTime.toString("yyyy-MM-dd HH:mm:ss"));
		query.addBindValue(voltage);


		if (!query.exec()) {
			ui.erreurBDD->setText("Erreur lors de l'insertion des donn�es :");

		}

		// Convertir la temp�rature en QString
		QString temperatureString = QString::number(temperature, 'f', 2) + " C";

		// Mettre � jour le label avec la QString convertie
		ui.afficheTemp->setText(temperatureString);
	});

	timer->start(5000);  // D�marrer le QTimer avec une p�riode de 5000 ms (5 secondes)

}

TPSytemeMeteo::~TPSytemeMeteo()
{
	// Lib�rer les ressources lorsque la fen�tre est ferm�e
	K8055Adapter::freeInstance();
}

