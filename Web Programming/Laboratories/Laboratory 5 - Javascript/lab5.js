function show(className) {
	var elements = document.getElementsByClassName(className);
	for(var i=0; i<elements.length; i++) {
		elements[i].style.visibility="visible";
	}
}

function hide(className) {
	var elements = document.getElementsByClassName(className);
	for(var i=0; i<elements.length; i++) {
		elements[i].style.visibility="hidden";
	}
}
