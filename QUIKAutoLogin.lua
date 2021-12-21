package.path = ""
package.cpath = getScriptPath() .. "\\QUIKAutoLogin.dll"

require("AutoLogin")

function main()

	login =		"ваш логин"
	passwd =	"пароль"

	Auth(login, passwd)

	while not stopped do
	       sleep(100)
	end

end