#pragma once
#include "config.h"
#include "macro.h"

#ifdef GH_ESP_BUILD
#ifdef GH_NO_LOCAL
class HubWS {
   public:
};
#else

#include <Arduino.h>
#include <WebSocketsServer.h>

#include "utils/stats.h"

class HubWS {
    // ============ PROTECTED =============
   protected:
    HubWS() : ws(GH_WS_PORT, "", "hub") {}

    virtual void parse(char* url, GHconn_t conn) = 0;
    virtual void setStatus(GHstate_t state, GHconn_t conn) = 0;

    void beginWS() {
        ws.onEvent([this](uint8_t num, WStype_t type, uint8_t* data, size_t len) {
            switch (type) {
                case WStype_CONNECTED:
                    setStatus(GH_CONNECTED, GH_WS);
                    break;

                case WStype_DISCONNECTED:
                    setStatus(GH_DISCONNECTED, GH_WS);
                    break;

                case WStype_ERROR:
                    setStatus(GH_ERROR, GH_WS);
                    break;

                case WStype_TEXT: {
                    clientID = num;
                    /*char data_c[len + 1];
                    if (len) strcpy(data_c, (char*)data);
                    data_c[len] = 0;*/
                    parse((char*)data, GH_WS);
                } break;

                case WStype_BIN:
                case WStype_FRAGMENT_TEXT_START:
                case WStype_FRAGMENT_BIN_START:
                case WStype_FRAGMENT:
                case WStype_FRAGMENT_FIN:
                case WStype_PING:
                case WStype_PONG:
                    break;
            }
        });

        ws.begin();
    }

    void endWS() {
        ws.close();
    }

    void tickWS() {
        ws.loop();
    }

    void sendWS(const String& answ) {
        ws.broadcastTXT(answ.c_str(), answ.length());
    }

    void answerWS(const String& answ) {
        ws.sendTXT(clientID, answ.c_str(), answ.length());
    }

    // ============ PRIVATE =============
   private:
    WebSocketsServer ws;
    uint8_t clientID = 0;
};
#endif
#endif