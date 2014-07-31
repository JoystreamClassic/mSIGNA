///////////////////////////////////////////////////////////////////////////////
//
// CoinVault
//
// txmodel.h
//
// Copyright (c) 2013-2014 Eric Lombrozo
//
// All Rights Reserved.

#pragma once

#include <QStandardItemModel>

#include <CoinDB/Vault.h>

namespace CoinDB
{
    class SynchedVault;
}

class TxModel : public QStandardItemModel
{
    Q_OBJECT

public:
    TxModel(QObject* parent = nullptr);
    TxModel(CoinDB::Vault* vault, const QString& accountName, QObject* parent = nullptr);

    void setVault(CoinDB::Vault* vault);
    CoinDB::Vault* getVault() const { return vault; }
    void setAccount(const QString& accountName);
    void update();

    bytes_t getTxHash(int row) const;

    void signTx(int row);
    void sendTx(int row, CoinDB::SynchedVault* synchedVault);
    std::shared_ptr<CoinDB::Tx> getTx(int row);
    void deleteTx(int row);

    // Overridden methods
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;

signals:
    void txSigned(const QString& keychainNames);
    void txDeleted();

private:
    unsigned char base58_versions[2];
    QString currencySymbol;

    void setColumns();

    CoinDB::Vault* vault;
    QString accountName; // empty when not loaded
    uint64_t confirmedBalance;
    uint64_t pendingBalance;
};

