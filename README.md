# QUIK Auto Login
Плагин для QUIK, позволяющий делать автоматический вход по логину и паролю

## Установка
Скопировать bin/QUIKAutoLogin.dll и bin/QUIKAutoLogin.lua в папку QUIK
В QUIKAutoLogin.lua установить логин/пароль
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