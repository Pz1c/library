#include "qcore.h"

QGameCore::QGameCore(QObject *parent) :
    QObject(parent)
{
    _requestIdx = 0;
}

QGameCore::~QGameCore() {
    settings->sync();
}

void QGameCore::init() {
    settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, _organizationName, _applicationName);
    loadParameters();
    applyProxySettings();
    GameDictionary = QGameDictionary::getInstance();
}


void QGameCore::saveRequest(QString &data) {
    qDebug() << "QGameCore::saveRequest" << data.length();
#ifdef QT_DEBUG
    QString file_name = QString("dda_request_%1.html").arg(QString::number(++_requestIdx));
    QFile file(file_name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << data;
    file.close();
    qDebug() << "data stored into " << file_name;
#endif
}

bool QGameCore::isLoading(){
    return _isLoading;
}


void QGameCore::slotReadyRead() {
    QNetworkReply *reply = (QNetworkReply *)sender();

    if (reply->error() != QNetworkReply::NoError) {
        return;
    }
	
    QString url = reply->url().toString();
    QString data = reply->readAll();
    qDebug() << "from url: " << url << " slotReadyRead";
    if (!data.isEmpty()) {
        saveRequest(data);
    }

}

void QGameCore::slotError(QNetworkReply::NetworkError error) {
    qDebug() << "slotError" << error << _reply->errorString();
}

void QGameCore::slotSslErrors(QList<QSslError> error_list) {
    qDebug() << "slotSslErrors " << error_list;
}
/*
void QGameCore::setOrganization() {
    qDebug() << "QGameCore::setOrganization()";
    _organizationName = "Steel Programming";
    _applicationName = "Game";
}
*/
void QGameCore::setProxySettings(QString IP, int Port, QString Username, QString Password) {
    _proxyHost = IP;
    _proxyPort = Port;
    _proxyUser = Username;
    _proxyPass = Password;
    saveParameters(false, true);
}

void QGameCore::saveParameters(bool user, bool proxy, bool game, bool stats, bool options) {
    if (user) {
        settings->beginGroup("User");
        saveUserParameters();
        settings->endGroup();
    }

    if (proxy) {
        settings->beginGroup("Proxy");
        saveProxyParameters();
        settings->endGroup();
    }

    if (game) {
        settings->beginGroup("Game");
        saveGameParameters();
        settings->endGroup();
    }

    if (stats) {
        settings->beginGroup("Statistic");
        saveStatsParameters();
        settings->endGroup();
    }

    if (options) {
        settings->beginGroup("Options");
        saveOptionsParameters();
        settings->endGroup();
    }
}

void QGameCore::loadParameters() {
    settings->beginGroup("User");
    loadUserParameters();
    settings->endGroup();

    settings->beginGroup("Proxy");
    loadProxyParameters();
    settings->endGroup();

    settings->beginGroup("Game");
    loadGameParameters();
    settings->endGroup();

    settings->beginGroup("Statistic");
    loadStatsParameters();
    settings->endGroup();

    settings->beginGroup("Options");
    loadOptionsParameters();
    settings->endGroup();
}

void QGameCore::saveUserParameters() {
    settings->setValue("uuid", _UUID);
}

void QGameCore::saveProxyParameters() {
    settings->setValue("host", _proxyHost);
    settings->setValue("port", _proxyPort);
    settings->setValue("user", _proxyUser);
    settings->setValue("password", _proxyPass);
}

void QGameCore::saveGameParameters() {

}

void QGameCore::saveStatsParameters() {

}

void QGameCore::saveOptionsParameters() {

}

void QGameCore::loadUserParameters() {
    _UUID = settings->value("uuid", QUuid::createUuid().toString().replace("{", "").replace("}", "").replace("-", "")).toString();
}

void QGameCore::loadProxyParameters() {
    _proxyHost = settings->value("host", "").toString();
    _proxyPort = settings->value("port", "").toInt();
    _proxyUser = settings->value("user", "").toString();
    _proxyPass = settings->value("password", "").toString();
}

void QGameCore::loadGameParameters() {

}

void QGameCore::loadStatsParameters() {

}

void QGameCore::loadOptionsParameters() {

}

void QGameCore::setIsLoading(bool isLoading)
{
    bool changed = _isLoading != isLoading;
    _isLoading = isLoading;
    if (changed) {
        qDebug() << "QGameCore::setIsLoading" << isLoading <<"emit isLoadingChanged()";
        emit isLoadingChanged();
    }
}

void QGameCore::applyProxySettings() {
    if (_proxyHost.isEmpty()) {
        _nam.setProxy(QNetworkProxy::NoProxy);
    } else {
        _proxy.setType(QNetworkProxy::HttpProxy);
        _proxy.setHostName(_proxyHost);
        _proxy.setPort(static_cast<quint16>(_proxyPort));
        if (!_proxyUser.isEmpty()) {
            _proxy.setUser(_proxyUser);
        }
        if (!_proxyPass.isEmpty()) {
            _proxy.setPassword(_proxyPass);
        }
        _nam.setProxy(_proxy);
    }
}

QString QGameCore::proxyHost() {
    return _proxyHost;
}

int QGameCore::proxyPort() {
    return _proxyPort;
}

QString QGameCore::proxyUser() {
    return _proxyUser;
}

QString QGameCore::proxyPass() {
    return _proxyPass;
}

QString QGameCore::uuid() {
    return _UUID;
}