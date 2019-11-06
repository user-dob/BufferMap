const addon = require('bindings')('addon.node')

const BufferMap = addon.BufferMap;

const map = new BufferMap();

const key = Buffer.from([1, 2, 3]);
const key1 = Buffer.from(key);

console.log( map.set(key, {1: 1}) )

console.log( map.get(key) )
