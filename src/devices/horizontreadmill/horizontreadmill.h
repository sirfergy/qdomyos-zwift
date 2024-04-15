#ifndef HORIZONTREADMILL_H
#define HORIZONTREADMILL_H

#include <QtBluetooth/qlowenergyadvertisingdata.h>
#include <QtBluetooth/qlowenergyadvertisingparameters.h>
#include <QtBluetooth/qlowenergycharacteristic.h>
#include <QtBluetooth/qlowenergycharacteristicdata.h>
#include <QtBluetooth/qlowenergycontroller.h>
#include <QtBluetooth/qlowenergydescriptordata.h>
#include <QtBluetooth/qlowenergyservice.h>
#include <QtBluetooth/qlowenergyservicedata.h>
//#include <QtBluetooth/private/qlowenergycontrollerbase_p.h>
//#include <QtBluetooth/private/qlowenergyserviceprivate_p.h>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QtCore/qbytearray.h>

#ifndef Q_OS_ANDROID
#include <QtCore/qcoreapplication.h>
#else
#include <QtGui/qguiapplication.h>
#endif
#include <QtCore/qlist.h>
#include <QtCore/qmutex.h>
#include <QtCore/qscopedpointer.h>
#include <QtCore/qtimer.h>

#include <QDateTime>
#include <QObject>
#include <QString>

#include "treadmill.h"

#ifdef Q_OS_IOS
#include "ios/lockscreen.h"
#endif

class horizontreadmill : public treadmill {
    Q_OBJECT
  public:
    horizontreadmill(bool noWriteResistance, bool noHeartService);
    bool connected() override;
    void forceSpeed(double requestSpeed);
    void forceIncline(double requestIncline);
    double minStepInclination() override;
    double minStepSpeed() override;

    bool autoPauseWhenSpeedIsZero() override;
    bool autoStartWhenSpeedIsGreaterThenZero() override;

  private:
    void writeCharacteristic(QLowEnergyService *service, QLowEnergyCharacteristic characteristic, uint8_t *data,
                             uint8_t data_len, QString info, bool disable_log = false, bool wait_for_response = false);
    void waitForAPacket();
    void startDiscover();
    void btinit();

    QTimer *refresh;

    QList<QLowEnergyService *> gattCommunicationChannelService;
    QLowEnergyCharacteristic gattWriteCharControlPointId;
    QLowEnergyService *gattFTMSService = nullptr;
    QLowEnergyCharacteristic gattWriteCharCustomService;
    QLowEnergyService *gattCustomService = nullptr;
    volatile int notificationSubscribed = 0;

    uint8_t sec1Update = 0;
    QByteArray lastPacket;
    QByteArray lastPacketComplete;
    QDateTime lastRefreshCharacteristicChanged = QDateTime::currentDateTime();
    bool firstDistanceCalculated = false;
    uint8_t firstStateChanged = 0;
    double lastSpeed = 0.0;
    double lastInclination = 0;
    int64_t lastStart = 0;
    int64_t lastStop = 0;
    bool horizonPaused = false;
    double lastHorizonForceSpeed = 0;
    double minInclination = 0.0;

    bool initDone = false;
    bool initRequest = false;
    bool initPacketRecv = false;

    bool noWriteResistance = false;
    bool noHeartService = false;

    int32_t customRecv = 0;
    int32_t messageID = 0;

    bool mobvoi_treadmill = false;
    bool kettler_treadmill = false;
    bool sole_tt8_treadmill = false;
    bool anplus_treadmill = false;
    bool tunturi_t60_treadmill = false;
    bool trx3500_treadmill = false;
    bool sole_f85_treadmill = false;
    bool sole_f89_treadmill = false;
    bool schwinn_810_treadmill = false;

    void testProfileCRC();
    void updateProfileCRC();
    int GenerateCRC_CCITT(uint8_t *PUPtr8, int PU16_Count, int crcStart = 65535);
    bool checkIfForceSpeedNeeding(double requestSpeed);
    float float_one_point_round(float value);

    // profiles
    uint8_t initData7[20] = {0x55, 0xaa, 0x02, 0x00, 0x01, 0x16, 0xdb, 0x02, 0xed, 0xc2,
                             0x00, 0x47, 0x75, 0x65, 0x73, 0x74, 0x00, 0x00, 0x00, 0x00};
    uint8_t initData8[20] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t initData9[20] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x05, 0xc2, 0x07};
    uint8_t initData10[20] = {0x01, 0x01, 0x00, 0xd3, 0x8a, 0x0c, 0x00, 0x01, 0x01, 0x02,
                              0x23, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};
    uint8_t initData11[20] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
                              0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};
    uint8_t initData12[20] = {0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
                              0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t initData13[20] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30,
                              0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};
    uint8_t initData14[1] = {0x30};

    uint8_t initData7_1[20] = {0x55, 0xaa, 0x03, 0x00, 0x01, 0x16, 0xdb, 0x02, 0xae, 0x2a,
                               0x01, 0x41, 0x69, 0x61, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t initData9_1[20] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0x06, 0xc4, 0x07};
    uint8_t initData10_1[20] = {0x09, 0x1c, 0x00, 0x9f, 0xef, 0x0c, 0x00, 0x01, 0x01, 0x02,
                                0x23, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};

    uint8_t initData7_2[20] = {0x55, 0xaa, 0x04, 0x00, 0x01, 0x16, 0xdb, 0x02, 0xae, 0x2a,
                               0x01, 0x41, 0x69, 0x61, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t initData9_2[20] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0x06, 0xc4, 0x07};
    uint8_t initData10_2[20] = {0x09, 0x1c, 0x00, 0x9f, 0xef, 0x0c, 0x00, 0x01, 0x01, 0x02,
                                0x23, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};

    uint8_t initData7_3[20] = {0x55, 0xaa, 0x05, 0x00, 0x01, 0x16, 0xdb, 0x02, 0xa9, 0xe7,
                               0x02, 0x4d, 0x65, 0x67, 0x68, 0x61, 0x00, 0x00, 0x00, 0x00};
    uint8_t initData9_3[20] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0x06, 0xc5, 0x07};
    uint8_t initData10_3[20] = {0x0b, 0x0f, 0x00, 0x4b, 0x40, 0x0c, 0x00, 0x01, 0x01, 0x02,
                                0x23, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};

    uint8_t initData7_4[20] = {0x55, 0xaa, 0x06, 0x00, 0x01, 0x16, 0xdb, 0x02, 0xbc, 0x76,
                               0x03, 0x44, 0x61, 0x72, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t initData9_4[20] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x07, 0xca, 0x07};
    uint8_t initData10_4[20] = {0x05, 0x1c, 0x00, 0x07, 0x25, 0x0c, 0x00, 0x01, 0x01, 0x02,
                                0x23, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};

    uint8_t initData7_5[20] = {0x55, 0xaa, 0x07, 0x00, 0x01, 0x16, 0xdb, 0x02, 0x7d, 0xeb,
                               0x04, 0x41, 0x68, 0x6f, 0x6e, 0x61, 0x00, 0x00, 0x00, 0x00};
    uint8_t initData9_5[20] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x04, 0xcc, 0x07};
    uint8_t initData10_5[20] = {0x01, 0x08, 0x00, 0xc2, 0x0f, 0x0c, 0x00, 0x01, 0x01, 0x02,
                                0x23, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};

    uint8_t initData7_6[20] = {0x55, 0xaa, 0x08, 0x00, 0x01, 0x16, 0xdb, 0x02, 0x03, 0x0d,
                               0x05, 0x55, 0x73, 0x65, 0x72, 0x20, 0x35, 0x00, 0x00, 0x00};
    uint8_t initData9_6[20] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdc, 0x05, 0xc2, 0x07};
    uint8_t initData10_6[20] = {0x01, 0x01, 0x00, 0x8e, 0x6a, 0x0c, 0x00, 0x01, 0x01, 0x02,
                                0x23, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30};
    // profiles end

#ifdef Q_OS_IOS
    lockscreen *h = 0;
#endif

  signals:
    void disconnected();
    void debug(QString string);
    void packetReceived();

  public slots:
    void deviceDiscovered(const QBluetoothDeviceInfo &device);

  private slots:

    void characteristicChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void characteristicWritten(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void descriptorWritten(const QLowEnergyDescriptor &descriptor, const QByteArray &newValue);
    void characteristicRead(const QLowEnergyCharacteristic &characteristic, const QByteArray &newValue);
    void descriptorRead(const QLowEnergyDescriptor &descriptor, const QByteArray &newValue);
    void stateChanged(QLowEnergyService::ServiceState state);
    void controllerStateChanged(QLowEnergyController::ControllerState state);

    void serviceDiscovered(const QBluetoothUuid &gatt);
    void serviceScanDone(void);
    void update();
    void error(QLowEnergyController::Error err);
    void errorService(QLowEnergyService::ServiceError);

    void changeInclinationRequested(double grade, double percentage);
};

#endif // HORIZONTREADMILL_H
