var forml = ['id', 'ktype', 'key'];
var Mkey = require('../models/MSkey');

function parsingTool() {
};

parsingTool.prototype.parmod = function (data){
	var	ii = 0;
	var	jj;
	var	rt = [];
	var	tmps = {};
	var	tmpc = {
		'WIPO':0,
		'WIPF':0,
		'WIHO':0,
		'WIHF':0,
		'OFPP':0,
		'OFHS':0
	};

	var	tmpl = data.split('\n');
	while (ii < tmpl.length){
		rt.push(tmpl[ii].split(','));
		ii += 1;
	}
	ii = 0;
	var	timeStamp = this.getTms();
	while (ii < tmpl.length){
		jj = 1;
		if (rt[ii].length == 3 && ii !== 0){
			tmps = {};
			if (rt[ii][1] !== '' && rt[ii][2] !== ''){
				tmpc[rt[ii][1]] += 1;
				tmps[forml[0]] = timeStamp + tmpc[rt[ii][1]].toString().padStart(4, '0');

				tmps[forml[1]] = rt[ii][1];
				tmps[forml[2]] = rt[ii][2];
			}
			if (rt[ii][0] === 'a' || rt[ii][0] === 'A') Mkey.create(tmps);
//			else if (rt[ii][0] === 'd' || rt[ii][0] === 'D') Mkey.deleteByelem(tmps);
			console.log(tmps);
		}
		ii += 1;
	}
}

parsingTool.prototype.getTms = function () {
	let now = new Date();
	let rt = '';
	let tmp = 0;

	rt += now.getFullYear().toString();
	tmp = now.getMonth()+1;
	if (tmp < 10) rt += '0' + tmp.toString();
	else rt += tmp.toString();
	tmp = now.getDate();
	if (tmp < 10) rt += '0' + tmp.toString();
	else rt += tmp.toString();
	return rt;
}

module.exports = parsingTool;
