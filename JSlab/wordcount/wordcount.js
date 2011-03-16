
function wordcount(){
	var start = (new Date()).getTime();	//time of start
	var text = document.getElementById('source')
	var datapool = {};	//this variable is only store data , has no method!!!

	var insert = function (depository,word){
		if ( depository[word] === undefined )
			depository[word] = 1;
		else
			depository[word] += 1;
	}

	var literal = function(depository){
		var result='';
		for (var i in depository){
			result += i+' : '+depository[i]+'<br/>';
		}
		return result;
	}

	var getTop10 = function(depository){
		var times = 0;
		var top10 = {};	//this variable is only store data , has no method!!!
		for ( var i in depository ){
			if (times < 10){
				top10[i] = depository[i];	//fill up top10 first
				times += 1;
			}
			else{
				var min = {'word' : '' , 'count' : Infinity}	//find the min in top10
				for (var j in top10){	//find the min in top10
					if (min['count'] > top10[j]){
						min['word'] = j;
						min['count'] = top10[j];
					}
				}
				if (min['count'] < depository[i]){
					delete top10[min['word']];
					top10[i] = depository[i];
				}
			}
		}
		return top10;
	}

	var wordPattern = /\b[a-zA-Z]+\b/g;

	var words = text.value.match(wordPattern);

	for (var i = 0 ; i<words.length ; i++)
		insert(datapool,words[i]);

	var top10 = getTop10(datapool)

	var result = document.getElementById("result");
	result.innerHTML=literal(top10);

	var end = (new Date()).getTime();	//time of end

	var time = document.getElementById("time");
	time.innerHTML = "time consumed:"+(end - start)+"ms";
}

