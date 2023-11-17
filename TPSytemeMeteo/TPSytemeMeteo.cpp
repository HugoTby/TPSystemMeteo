//*********************************************************************************************
//* Programme : TPSystemMeteo.cpp                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 17/11/2023
//*
//* Programmeurs : BOTEL Faustin                                               Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Récupérer les data de la k8055, les convertir en degres et envoyer en BDD
//* Programmes associés : AUCUN
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

	// Vérifiez si la connexion est établie
	if (!db.open()) {
		ui.connectBDD->setText("Deconnecte");
	}
	else {
		ui.connectBDD->setText("Connecte");

	}


	// Initialiser la carte K8055
	K8055Adapter *carteES = K8055Adapter::getInstance();
	carteES->OpenDevice(0);
	long channel = 1;  // Remplacez par le numéro de canal que vous souhaitez lire

	// Créer un QTimer pour actualiser la température toutes les 1000 millisecondes (1 seconde)
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, [this, carteES, channel, db]() {
		// Lire la tension
		long data = carteES->ReadAnalogChannel(channel);
		double voltage = (static_cast<double>(data) / 255.0) * 5.0;

		// Convertir la tension en température en utilisant une relation linéaire
		double minVoltage = 0.0;   // Correspond à -30°C
		double maxVoltage = 5.0;   // Correspond à 60°C
		double minTemperature = -30.0;
		double maxTemperature = 60.0;

		double temperature = ((voltage - minVoltage) / (maxVoltage - minVoltage)) * (maxTemperature - minTemperature) + minTemperature;

		// Obtenir la date et l'heure actuelles
		QDateTime currentDateTime = QDateTime::currentDateTime();

		// Insérer les données dans la base de données
		QSqlQuery query(db);
		query.prepare("INSERT INTO temperature (degres, date, voltage) VALUES (?, ?, ?)");
		query.addBindValue(temperature);
		query.addBindValue(currentDateTime.toString("yyyy-MM-dd HH:mm:ss"));
		query.addBindValue(voltage);


		if (!query.exec()) {
			ui.erreurBDD->setText("Erreur lors de l'insertion des données :");

		}

		// Convertir la température en QString
		QString temperatureString = QString::number(temperature, 'f', 2) + " C";

		// Mettre à jour le label avec la QString convertie
		ui.afficheTemp->setText(temperatureString);
	});

	timer->start(5000);  // Démarrer le QTimer avec une période de 5000 ms (5 secondes)

}

TPSytemeMeteo::~TPSytemeMeteo()
{
	// Libérer les ressources lorsque la fenêtre est fermée
	K8055Adapter::freeInstance();
}

