//Date : 2011-04-18 Author : xudifsd
//this javascript is created for compatible with chrome, firefox and IE 6~8
//The main function of this class is compatible.addcheckevent, and IE need to invoke compatible.cleartiparea when init
var compatible = {};
compatible.browser = navigator.appName.toLowerCase();	//this function should be invoked firstly
compatible.debug = true;	//this is for alert for debug
compatible.isie = function(){
	//compatible.isie is not a function!!! It's true or false variable
	if (compatible.browser.indexOf('netscape') >= 0)
		return false;
	else if (compatible.browser.indexOf('microsoft internet explorer') >= 0)
		return true;
}();
compatible.addevent = function(node, eventname, eventfunction){
	if ((!node || !eventname || !eventfunction) && compatible.debug){
		alert('compatible.addevent:\nnode or eventname or eventfunction not assigned!');
		return;
	}
	if (compatible.isie){
		node.attachEvent(eventname, eventfunction);
	}
	else{
		node.addEventListener(eventname, eventfunction, false);
	}
};
compatible.checkeventfunctionliteral = function(min, max, textareaname, tipareaname, disabledTargetname){
	//this function use closure to create a non argument for setAttribute
	if (!inputcheck && compatible.debug){
		alert('compatible.checkeventfunctionliteral:\n inputcheck not found!');
		return;
	}
	return function(){
		inputcheck.check(min, max, textareaname, tipareaname, disabledTargetname);
	}
};
compatible.addcheckevent = function(nodename, min, max, textareaname, tipareaname, disabledTargetname){
	//this function is main function for compatible, it's add inputcheck.check to oninput or onpropertychange
	//disabledTargetname may not assigned
	if (!inputcheck && compatible.debug)
		alert('compatible.addcheck:\nThere are not a inputcheck, please add it to the page\ncompatible.addcheckevent need inputcheck');
	else {
		var eventname;
		var eventfunctionliteral;
		var node = document.getElementById(nodename);
		if (!node && compatible.debug){
			alert('compatible.addcheckevent:\nnodename is wrong!');
			return;
		}
		eventfunctionliteral = compatible.checkeventfunctionliteral(min, max, textareaname, tipareaname, disabledTargetname);
		if (compatible.isie){
			eventname = 'onpropertychange';
		}
		else{
			eventname = 'input';
		}
		compatible.addevent(node, eventname, eventfunctionliteral);
	}
};
compatible.cleartiparea = function(nodename){
   //this function is used to clear tiparea, because compatible.addcheckevent will fire onproperchange in ie, so this should be invoke at once, when DOM is ready
   var node = document.getElementById(nodename);
   if (!node && compatible.debug){
	   alert('compatible.cleartiparea:\nnodename is wrong!');
	   return;
   }
   node.innerHTML = '';
};
