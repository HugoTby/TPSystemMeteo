#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TPSytemeMeteo.h"

class TPSytemeMeteo : public QMainWindow
{
    Q_OBJECT

public:
    TPSytemeMeteo(QWidget *parent = nullptr);
    ~TPSytemeMeteo();
	void lireTemperature();

private:
    Ui::TPSytemeMeteoClass ui;
};
