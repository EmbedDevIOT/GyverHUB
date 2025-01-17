[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverHUB.svg?color=brightgreen)](https://github.com/GyverLibs/GyverHUB/releases/latest/download/GyverHUB.zip)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverHUB?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverHUB
Система взаимодействия с микроконтроллером из приложения и веб-сервиса GyverHUB, конструктор интерфейса

## Документация
Находится в [Wiki репозитория](https://github.com/GyverLibs/GyverHUB/wiki)
> [English docs](https://github-com.translate.goog/GyverLibs/GyverHUB/wiki?_x_tr_sl=ru&_x_tr_tl=en)

## Бета-версия
**Проект пока что тестируется.** Особенности, обсуждение и всё остальное - тут https://github.com/GyverLibs/GyverHUB/issues/3

![promo](/docs/promo.jpg)

GyverHUB - это программный комплекс, включающий в себя библиотеку для микроконтроллеров и программу для управления. Программа написана на JavaScript и по сути является сайтом, что позволяет ей работать:
- С официального сайта [hub.gyver.ru](http://hub.gyver.ru/)
- Сайт можно установить как веб-приложение (PWA) на любое устройство (Android/iOS/Windows...)
- Файлы сайта можно скачать и использовать локально с компьютера
- Отдельное Android приложение (в разработке)

Микроконтроллер и приложение обмениваются данными по своему протоколу (см. API) через различные интерфейсы связи: 
- MQTT (через Интернет)
- WebSocket (в локальной сети)
- Serial (проводное подключение) (в разработке)
- Bluetooth (в разработке)
- В ручном режиме - любой символьный интерфейс (GSM, GPRS, радио...)

Основные моменты:
- Приложение может обнаруживать устройства в своей "сети"
- В программе для микроконтроллера "собирается" графический интерфейс, который отправляется в приложение
- Можно управлять микроконтроллером с полученного интерфейса в приложении или с сайта
- В случае с ESP8266/ESP32 это работает через Интернет
- Библиотека реализована таким образом, что помимо использования в паре с родным приложением можно очень просто и быстро интегрировать свою самоделку в любую систему умного дома, которая поддерживает MQTT (Алиса, Home Assistant...)

Особенности:
- Библиотека невероятно проста в использовании
- Стильный дизайн ;) светлая и тёмная темы
- Удобный парсинг действий с приложения/сайта или сервера умного дома
- Более 20 активных компонентов интерфейса (кнопки, слайдеры, выбор...) + блоки оформления и навигации
- Настраиваемые модули: загрузка и скачивание файлов, информация о плате, OTA обновление, защита паролем, интерфейс командной строки...
- 1000 FontAwesome иконок оформления для кнопок и списка устройств
- Библиотека асинхронная (опционально для ESP8266/ESP32)
- Оптимальное использование памяти для работы на слабых МК

Ближайшие аналоги:
- Приложение RemoteXY
- Сервис Blynk

В отличие от них GyverHUB полностью бесплатный, безопасный, не имеет ограничений и не нуждается в локальном сервере

### Совместимость
- Все Arduino: Serial, Bluetooth (Serial) и ручной режим
- ESP8266 и ESP32: + WebSocket и MQTT

### Зависимости
Общие:
- [Stamp](https://github.com/GyverLibs/Stamp)

Для синхронной работы (ESP8266/ESP32):
- [PubSubClient](https://github.com/knolleary/pubsubclient)
- [arduinoWebSockets](https://github.com/Links2004/arduinoWebSockets)

Для асинхронной работы (ESP8266/ESP32):
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)
- [async-mqtt-client](https://github.com/marvinroger/async-mqtt-client)

## Содержание
- [Установка](#install)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GyverHUB** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GyverHUB/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


<a id="versions"></a>
## Версии
- v1.0

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!

При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
