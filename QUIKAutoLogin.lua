package.path = ""
package.cpath = getScriptPath() .. "\\QUIKAutoLogin.dll"

require("AutoLogin")

function main()

	login =		"��� �����"
	passwd =	"������"

	Auth(login, passwd)

end