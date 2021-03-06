/*
    Copyright (C) 2020 Sebastian J. Wolf

    This file is part of Fernschreiber.

    Fernschreiber is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Fernschreiber is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Fernschreiber. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QObject>
#include <QMutex>
#include <ngf-qt5/NgfClient>
#include "tdlibwrapper.h"

class NotificationManager : public QObject
{
    Q_OBJECT
public:
    explicit NotificationManager(TDLibWrapper *tdLibWrapper, QObject *parent = nullptr);
    ~NotificationManager() override;

signals:

public slots:

    void handleUpdateActiveNotifications(const QVariantList notificationGroups);
    void handleUpdateNotificationGroup(const QVariantMap notificationGroupUpdate);
    void handleUpdateNotification(const QVariantMap updatedNotification);
    void handleChatDiscovered(const QString &chatId, const QVariantMap &chatInformation);
    void handleNgfConnectionStatus(const bool &connected);
    void handleNgfEventFailed(const quint32 &eventId);
    void handleNgfEventCompleted(const quint32 &eventId);
    void handleNgfEventPlaying(const quint32 &eventId);
    void handleNgfEventPaused(const quint32 &eventId);

private:

    TDLibWrapper *tdLibWrapper;
    Ngf::Client *ngfClient;
    QVariantMap chatMap;
    QVariantMap notificationGroups;
    QMutex chatListMutex;

    QVariantMap sendNotification(const QString &chatId, const QVariantMap &notificationInformation, const QVariantMap &activeNotifications);
    void removeNotification(const QVariantMap &notificationInformation);
    QString getNotificationText(const QVariantMap &notificationContent);
    void controlLedNotification(const bool &enabled);

};

#endif // NOTIFICATIONMANAGER_H
