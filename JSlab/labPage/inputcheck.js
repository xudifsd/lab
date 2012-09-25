//Date : 2011-04-17 Author : xudifsd
//This class use a concept that use locallock and globallock to lock a button. Locallock's name is element's id that invoke disable function, because element's id is universal unique, so this won't collision with other locallock, but id must not be same with button element's other tag attribute, locallock's value is 1 or 0, indicate local locked or not. Global lock's name is inputcheck. Globaldisablename, it's value is sum of locallock's value.

//IMPORTANT this class should be initialized by inputcheck.initlockbutton(), it's arguments should be (id_of_button_that_will_be_locked, ids_of_elements_that_invoke_inputcheck.check, etc)
var inputcheck = {
	//Main program is inputcheck.check()
	tips : {
		inputLengthInvalid : function(min, max){
			return 'You should input at least '+min+' character and '+max+' at most!';
		}
	},
	debug : true,	//debug or not
	globaldisablename : 'globaldisabledtimes',
	disable : function(node, hint){
		//this function use hint to local lock an element and plus 1 to global lock
		if ((!node || typeof hint !== 'string' )&& inputcheck.debug)
			alert('inputcheck.disable:\nSomething wrong in javascript');
		else{
			node.disabled = true;
			var localdisabledtimes = parseInt(node.getAttribute(hint)) || 0;	//localdisabledtimes is either 0 or 1
			var globaldisabledtimes = parseInt(node.getAttribute(inputcheck.globaldisablename)) || 0;	//the number is 0 ~ i(numbers of tags that use check())
			if (localdisabledtimes === 0){
				localdisabledtimes = 1;
				globaldisabledtimes += 1;
				node.setAttribute(hint, localdisabledtimes);
				node.setAttribute(inputcheck.globaldisablename, globaldisabledtimes);
			}
		}
	},
	enable : function(node,hint){
		//this function use hint to local unlock an element : decrease 1 to global lock, if global lock is 0, this function unlock element
		if ((!node || typeof hint !== 'string' )&& inputcheck.debug)
			alert('inputcheck.enable:\nSomething wrong in javascript');
		else{
			var localdisabledtimes = parseInt(node.getAttribute(hint)) || 0;	//either 0 or 1
			var globaldisabledtimes = parseInt(node.getAttribute(inputcheck.globaldisablename)) || 0;	//the number is 0 ~ i(numbers of tags that use check())
			if (globaldisabledtimes === 0){
				node.disabled = false;
			}
			else if (localdisabledtimes === 1){
				localdisabledtimes = 0;
				globaldisabledtimes -= 1;
				node.setAttribute(hint,localdisabledtimes);
				node.setAttribute(inputcheck.globaldisablename,globaldisabledtimes);
				if (globaldisabledtimes === 0){
					node.disabled = false;
				}
			}
		}
	},
	check : function(min, max, textarea, tiparea, disabledTarget){
		//this function is main function of inputcheck, disabledTarget may not assigned, but textarea, tiparea must be assigned
		//the type of textarea, disabledTarget and tiparea must be string
		min = min;
		max = max;
		var lockname = textarea;
		textarea = document.getElementById(textarea);
		tiparea = document.getElementById(tiparea);
		disabledTarget = document.getElementById(disabledTarget);
		if (!(textarea && tiparea) && inputcheck.debug)	//must have textarea and tiparea
			alert('inputcheck.check:\nSomething wrong in this page.\nPlease contact the writer of this page');
		else{
			if (textarea.value.length < min || textarea.value.length > max){
				if (disabledTarget)
					inputcheck.disable(disabledTarget, lockname);
				if (tiparea)
					tiparea.innerHTML = inputcheck.tips.inputLengthInvalid(min, max);
			}
			else{
				if (disabledTarget)
					inputcheck.enable(disabledTarget, lockname);
				if (tiparea)
					tiparea.innerHTML = '';
			}
		}
	},
	initlockbutton : function(buttonid){
		//this function will lock button at init, extra arguments will be treated as local lock name
		if (!buttonid && inputcheck.debug){
			alert('inputcheck.initlockbutton:\n buttonid is wrong');
			return;
		}
		var i;
		var button = document.getElementById(buttonid);
		for (i = 1; i < arguments.length; i+=1)	//local lock
			button.setAttribute(arguments[i], "1");
		button.setAttribute(inputcheck.globaldisablename, i-1);	//global lock
		if (i > 1)
			button.disabled = true;
	}
};
