# QUIK Auto Login
Плагин для QUIK, позволяющий делать автоматический вход по логину и паролю

## Требования
ОС Windows

## Установка
Скопировать файлы из bin/QUIKAutoLogin.dll и bin/QUIKAutoLogin.lua в папку QUIK.

В QUIKAutoLogin.lua прописать ваши логин и пароль

QUIKAutoLogin.lua:
```
package.path = ""
package.cpath = getScriptPath() .. "\\QUIKAutoLogin.dll"

require("AutoLogin")

function main()

	login =		"ваш логин"
	passwd =	"пароль"

	Auth(login, passwd)

end
```

В QUIK Меню -> Сервисы -> Lua скрипты... Добавить QUIKAutoLogin.lua и Запустить.
