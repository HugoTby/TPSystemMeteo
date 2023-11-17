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
		// Lire la température
		long data = carteES->ReadAnalogChannel(channel);

		// Convertir le long en QString
		QString dataString = QString::number(data);

		// Mettre à jour le label avec la QString convertie
		ui.afficheTemp->setText(dataString);
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
