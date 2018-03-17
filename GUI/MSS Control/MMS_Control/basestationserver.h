#ifndef BASESTATIONSERVER_H
#define BASESTATIONSERVER_H

class basestationServer {

public:
    basestationServer();
    int makeConnection();
    int writeToFile(char filename[], char text[]);
    void Connect();
    void sendCommand();

private:

    int getNum(char array[]);


};
#endif // BASESTATIONSERVER_H
