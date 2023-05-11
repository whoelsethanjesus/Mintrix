/* * * * * * * * * * * * * * * *
 * Mintrix              v1.0.2 *
 *                             *
 *                Janik Heiler *
 * GitHub:   @whoelsethanjesus *
 * * * * * * * * * * * * * * * */

#ifndef MINTRIX_WEBFILES_H
#define MINTRIX_WEBFILES_H
namespace MintrixWeb {

WebPage HelloWorld = {
	R"=====(<h1>Hello World!</h1>)=====",
	R"=====()=====",
	R"=====()====="
};

WebPage Input_InputText = {
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

}
#endif