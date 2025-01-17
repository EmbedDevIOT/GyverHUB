#include "misc.h"

String _GH_empty_str;

char* GHsplitter(char* list, char div) {
    static uint8_t prev, end;
    if (list == NULL) prev = end = 0;
    else {
        if (prev) *(list + prev - 1) = div;
        char* cur = strchr(list + prev, div);
        if (cur) {
            *cur = '\0';
            uint8_t b = prev;
            prev = cur - list + 1;
            return list + b;
        } else if (!end) {
            end = 1;
            return list + prev;
        }
    }
    return NULL;
}

String GH_uptime() {
    uint32_t sec = millis() / 1000ul;
    uint8_t second = sec % 60ul;
    sec /= 60ul;
    uint8_t minute = sec % 60ul;
    sec /= 60ul;
    uint16_t hour = sec % 24ul;
    sec /= 24ul;
    String s;
    s.reserve(10);
    s += sec;  // day
    s += ':';
    s += hour / 10;
    s += hour % 10;
    s += ':';
    s += minute / 10;
    s += minute % 10;
    s += ':';
    s += second / 10;
    s += second % 10;
    return s;
}

void GH_escapeChar(String* s, char c) {
    if (c <= 13) {
        *s += '\\';
        switch (c) {
            case '\r':
                *s += 'r';
                break;
            case '\n':
                *s += 'n';
                break;
            case '\t':
                *s += 't';
                break;
        }
    } else {
        *s += c;
    }
}

// ========================== FS ==========================
#ifdef GH_ESP_BUILD
#ifndef GH_NO_FS
void showFiles(String& answ, const String& path, GH_UNUSED uint8_t levels, uint16_t* count) {
#ifdef ESP8266
    Dir dir = GH_FS.openDir(path);
    while (dir.next()) {
        if (dir.isDirectory()) {
            String p(path);
            p += dir.fileName();
            p += '/';
            answ += '\'';
            answ += p;
            answ += "':0,";
            if (count) {
                *count += answ.length();
                answ = "";
            }
            Dir sdir = GH_FS.openDir(p);
            showFiles(answ, p);
        }
        if (dir.isFile() && dir.fileName().length()) {
            answ += '\'';
            answ += path;
            answ += dir.fileName();
            answ += "':";
            answ += dir.fileSize();
            answ += ',';
            if (count) {
                *count += answ.length();
                answ = "";
            }
        }
    }

#else  // ESP32
    File root = GH_FS.open(path.c_str());
    if (!root || !root.isDirectory()) return;
    File file;
    while (file = root.openNextFile()) {
        if (file.isDirectory()) {
            answ += '\'';
            answ += file.path();
            answ += "/':0,";
            if (count) {
                *count += answ.length();
                answ = "";
            }
            if (levels) showFiles(answ, file.path(), levels - 1);
        } else {
            answ += '\'';
            if (levels != GH_FS_DEPTH) answ += path;
            answ += '/';
            answ += file.name();
            answ += "':";
            answ += file.size();
            answ += ',';
            if (count) {
                *count += answ.length();
                answ = "";
            }
        }
    }
#endif
}

void fileToB64(File& file, String& str) {
    int16_t len = 0;
    uint16_t slen = 0;
    int val = 0, valb = -6;
    while (file.available()) {
        val = (val << 8) + file.read();
        valb += 8;
        while (valb >= 0) {
            str += GH_b64v((val >> valb) & 0x3F);
            slen++;
            valb -= 6;
        }
        if (++len > GH_DOWN_CHUNK_SIZE) {
            if (slen % 4 == 0) break;
        }
    }
    if (valb > -6) {
        str += GH_b64v(((val << 8) >> (valb + 8)) & 0x3F);
        slen++;
    }
    while (slen % 4) {
        str += '=';
        slen++;
    }
}

void B64toFile(File& file, const char* str) {
    uint16_t len = strlen(str);
    if (len < 4) return;
    int padd = 0;
    if (str[len - 2] == '=') padd = 2;
    else if (str[len - 1] == '=') padd = 1;

    int val = 0, valb = -8;
    for (uint16_t i = 0; i < len - padd; i++) {
        uint8_t b = GH_b64i(str[i]);
        val = (val << 6) + b;
        valb += 6;
        if (valb >= 0) {
            file.write(uint8_t((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
}
#endif

#ifndef GH_NO_OTA
void B64toUpdate(const char* str) {
    uint16_t len = strlen(str);
    if (len < 4) return;
    int padd = 0;
    if (str[len - 2] == '=') padd = 2;
    else if (str[len - 1] == '=') padd = 1;
    int blen = ((len + 3) / 4) * 3 - padd;  // byte length
    uint8_t data[blen];

    int val = 0, valb = -8, idx = 0;
    for (uint16_t i = 0; i < len - padd; i++) {
        uint8_t b = GH_b64i(str[i]);
        val = (val << 6) + b;
        valb += 6;
        if (valb >= 0) {
            data[idx++] = (uint8_t)((val >> valb) & 0xFF);
            valb -= 8;
        }
    }
    Update.write(data, blen);
}
#endif
#endif