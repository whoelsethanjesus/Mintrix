/* * * * * * * * * * * * * * * * * * * *
 *                                     *
 *            M I N T R I X            *
 *           by Janik Heiler           *
 *                                     *
 * * * * * * * * * * * * * * * * * * * */

#ifndef MINTRIX_WEBFILES_H
#define MINTRIX_WEBFILES_H
namespace MintrixWeb {

#ifdef MINTRIX_HelloWorld
WebPage HelloWorld = {
	R"=====(<h1>Hello World!</h1>)=====",
	R"=====()=====",
	R"=====()====="
};
#endif

#ifdef MINTRIX_InputText
WebPage InputText = {
	R"=====(<input onchange="send('text=' + this.value)"/>)=====",
	R"=====()=====",
	R"=====(
	function send(d) {
		xhr = new XMLHttpRequest();
		xhr.open("POST", "/data/?" + d);
		xhr.setRequestHeader("Content-Type", "text/plain");
		xhr.send();
	}
	)====="
};
#endif

}
#endif
