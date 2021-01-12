#ifndef QGAMECORE_H
#define QGAMECORE_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QNetworkProxy>
#include <QList>
#include <QPair>
#include <QUuid>
#include <math.h>

#include "qgamedictionary.h"

class QGameCore : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString proxyHost READ proxyHost NOTIFY proxyHostChanged)
    Q_PROPERTY(int proxyPort READ proxyPort NOTIFY proxyPortChanged)
    Q_PROPERTY(QString proxyUser READ proxyUser NOTIFY proxyUserChanged)
    Q_PROPERTY(QString proxyPass READ proxyPass NOTIFY proxyPassChanged)
    Q_PROPERTY(QString uuid READ uuid NOTIFY uuidChanged)
    Q_PROPERTY(int isLoading READ isLoading NOTIFY isLoadingChanged)

public:
    explicit QGameCore(QObject *parent = 0);
    ~QGameCore();

    QString proxyHost();
    int proxyPort();
    QString proxyUser();
    QString proxyPass();
    QString uuid();
    bool isLoading();


signals:
    void proxyHostChanged();
    void proxyPortChanged();
    void proxyUserChanged();
    void proxyPassChanged();
    void uuidChanged();
    void isLoadingChanged();

public slots:

    // NAT
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError error);
    void slotSslErrors(QList<QSslError> error_list);
protected slots:

protected:
    void init();
    void setProxySettings(QString IP, int Port, QString Username, QString Password);
    void setIsLoading(bool isLoading);

    void saveParameters(bool user = false, bool proxy = false, bool game = false, bool stats = false, bool options = false);
    virtual void loadParameters();
    virtual void saveUserParameters();
    virtual void saveProxyParameters();
    virtual void saveGameParameters();
    virtual void saveStatsParameters();
    virtual void saveOptionsParameters();
    virtual void loadUserParameters();
    virtual void loadProxyParameters();
    virtual void loadGameParameters();
    virtual void loadStatsParameters();
    virtual void loadOptionsParameters();
    virtual void setOrganization() = 0;

    QString _organizationName;
    QString _applicationName;
    QSettings *settings;
    // dictionary
    QGameDictionary *GameDictionary;

protected:

    // system
    QString _UUID;

    // proxy
    QString _proxyHost;
    int _proxyPort;
    QString _proxyUser;
    QString _proxyPass;

    // network
    bool _isLoading;
    int _requestIdx;
    QNetworkAccessManager _nam;
    QNetworkReply *_reply;
    QNetworkProxy _proxy;

    void applyProxySettings();
    void saveRequest(QString &data);
};

#endif // QGAMECORE_H
