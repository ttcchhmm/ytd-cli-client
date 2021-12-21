#include "main.h"

#include <QCoreApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    a.setApplicationName("ytd-cli-client");
    a.setApplicationVersion("1.0.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("A CLI client for ytd.");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("server address", "The address to the ytd server");
    parser.addPositionalArgument("port", "The port used by the ytd server");
    parser.addPositionalArgument("request", "The type of request to send to the server");
    parser.addPositionalArgument("argument", "The argument for the request if needed");

    parser.process(a);

    if(parser.positionalArguments().length() < 3) {
        Console::err << "Not enough arguments !" << Qt::endl;
        return 1;
    }

    QUrl serverUrl("ws://" + parser.positionalArguments()[0]); // Add ws:// as a prefix to use a websocket
    serverUrl.setPort(parser.positionalArguments()[1].toInt());

    request = parser.positionalArguments()[2];
    if(parser.positionalArguments().length() == 4) {
        argument = parser.positionalArguments()[3];
        hasArg = true;
    }

    Client *c = new Client(serverUrl);

    return a.exec();
}

Client::Client(QUrl server) {
    socket = new QWebSocket;
    socket->setParent(this);

    // Setup connection events
    connect(socket, &QWebSocket::connected, this, &Client::onConnected);
    connect(socket, &QWebSocket::disconnected, this, &Client::onDisconnected);

    // Setup messages from the server
    connect(socket, &QWebSocket::textMessageReceived, this, &Client::onTextMessageRecived);

    Console::out << "Connecting to " << server.toString() << Qt::endl;

    socket->open(server);
}

void Client::onConnected() {
    Console::out << "Connected." << Qt::endl;

    if(request != "watch") {
        // Send the request

        QString msg = request;

        if(hasArg) {
            msg += " " + argument;
        }

        socket->sendTextMessage(msg);
    }
}

// Quit on disconnect
void Client::onDisconnected() {
    Console::out << "Disconnected." << Qt::endl;
    qApp->quit();
}

// Just dump every incoming message into the console
void Client::onTextMessageRecived(QString message) {
    Console::out << message << Qt::endl;
}