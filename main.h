#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QTextStream>
#include <QString>
#include <QWebSocket>
#include <QUrl>
#include <QByteArray>

namespace Console {
    inline QTextStream out = QTextStream(stdout);
    inline QTextStream err = QTextStream(stderr);
}

class Client : public QObject {
    Q_OBJECT

    public:
        Client(QUrl server);

    private slots:
        void onConnected();
        void onDisconnected();
        void onTextMessageRecived(QString message);

    private:
        QWebSocket *socket;
};

int main(int argc, char *argv[]);

inline QString request;
inline QString argument;
inline bool hasArg = false;

#endif // MAIN_H