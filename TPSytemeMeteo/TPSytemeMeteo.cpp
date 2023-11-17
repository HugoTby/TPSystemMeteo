#include "TPSytemeMeteo.h"
#include "K8055Adapter.h"
#include <QTimer>


TPSytemeMeteo::TPSytemeMeteo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// Initialiser la carte K8055
	K8055Adapter *carteES = K8055Adapter::getInstance();
	carteES->OpenDevice(0);
	long channel = 1;  // Remplacez par le numéro de canal que vous souhaitez lire

	// Créer un QTimer pour actualiser la température toutes les 1000 millisecondes (1 seconde)
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, [this, carteES, channel]() {
		// Lire la tension
		long data = carteES->ReadAnalogChannel(channel);
		double voltage = (static_cast<double>(data) / 255.0) * 5.0;

		// Convertir la tension en température en utilisant une relation linéaire
		double minVoltage = 0.0;   // Correspond à -30°C
		double maxVoltage = 5.0;   // Correspond à 60°C
		double minTemperature = -30.0;
		double maxTemperature = 60.0;

		double temperature = ((voltage - minVoltage) / (maxVoltage - minVoltage)) * (maxTemperature - minTemperature) + minTemperature;

		// Convertir la température en QString
		QString temperatureString = QString::number(temperature, 'f', 2) + " °C";

		// Mettre à jour le label avec la QString convertie
		ui.afficheTemp->setText(temperatureString);
	});

	timer->start(1000);  // Démarrer le QTimer avec une période de 1000 ms (1 seconde)

}

TPSytemeMeteo::~TPSytemeMeteo()
{
	// Libérer les ressources lorsque la fenêtre est fermée
	K8055Adapter::freeInstance();
}

void TPSytemeMeteo::lireTemperature()
{
	
	
}
