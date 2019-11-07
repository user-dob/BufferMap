const addon = require('bindings')('addon.node');
const crypto = require('crypto');

const BufferMap = addon.BufferMap;

const bufferMap = new BufferMap();

for (let i = 0; i < 10; i++) {
    const key = Buffer.from(String(i));
    bufferMap.set(key, {'i': i});
}

for (let i = 0; i < 10; i++) {
    const key = Buffer.from(String(i));
    console.log( bufferMap.get(key) );
}

const key = crypto.randomBytes(8);
bufferMap.set(key, {'i': 'randomBytes'});
console.log( bufferMap.get(key) );
