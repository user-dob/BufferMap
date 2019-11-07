const addon = require('bindings')('addon.node')

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
