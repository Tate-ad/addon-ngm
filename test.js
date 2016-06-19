var addon = require('./build/Release/addon');

var tt = new addon.Test(123);

console.log(tt.getName());
