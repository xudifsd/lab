//Date : 2011-04-19 Author : xudifsd
//this is a example to use right way of inputcheck and compatible
var init = function(){
	with (compatible){
		addcheckevent('textarea1','1','3','textarea1','tiparea1');	//this textarea don't lock submitButton
		addcheckevent('textarea2','1','3','textarea2','tiparea2','submitButton');
		addcheckevent('textarea3','1','3','textarea3','tiparea3','submitButton');
		addcheckevent('textarea4','1','20','textarea4','tiparea4','submitButton');
	}

	inputcheck.initlockbutton('submitButton', 'textarea2', 'textarea3', 'textarea4');
	//for ie
	with (compatible){
		if (isie){
			cleartiparea('tiparea1');
			cleartiparea('tiparea2');
			cleartiparea('tiparea3');
			cleartiparea('tiparea4');
		}
	}
}
