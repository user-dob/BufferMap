const addon = require('bindings')('addon.node')

const BufferMap = addon.BufferMap;

const bufferMap = new BufferMap();

for (let i = 0; i < 10; i++) {
    const key = Buffer.from(String(i));
    bufferMap.set(key, {'i': i});
}

const key = Buffer.from(String(5));
console.log( bufferMap.get(key) );

bufferMap.set(Buffer.from([1,2,3,4,5,6,7]), {'i': 100});
console.log( bufferMap.get(Buffer.from([1,2,3,4,5,6,7])) );
