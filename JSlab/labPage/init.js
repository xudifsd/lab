//Date : 2011-04-19 Author : xudifsd
//this is a example to use right way of inputcheck and compatible
var init = function(){
	compatible.addcheckevent('textarea1','1','3','textarea1','tiparea1');	//this textarea don't lock submitButton
	compatible.addcheckevent('textarea2','1','3','textarea2','tiparea2','submitButton');
	compatible.addcheckevent('textarea3','1','3','textarea3','tiparea3','submitButton');
	compatible.addcheckevent('textarea4','1','20','textarea4','tiparea4','submitButton');

	inputcheck.initlockbutton('submitButton', 'textarea2', 'textarea3', 'textarea4');
	//for ie
	if (compatible.isie){
		compatible.cleartiparea('tiparea1');
		compatible.cleartiparea('tiparea2');
		compatible.cleartiparea('tiparea3');
		compatible.cleartiparea('tiparea4');
	}
}
