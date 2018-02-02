fs = require('fs');
function addOne() {
	fs.readdir(process.argv[2], function readlist(err, list) {
		if (err)
			return console.log(err);
		for (let ii = 0; ii < list.length; ii++) {
			if (list[ii].split('.')[1] == 'md')
				console.log(list[ii]);
		}
	});
}
addOne();
		
