const addon = require('bindings')('addon.node')

const BufferMap = addon.BufferMap;

const map = new BufferMap();

const key = Buffer.from([1, 2, 3]);
const key1 = Buffer.from([1, 2, 3]);

map.set(key, {1: 1})
map.set(Buffer.from([5]), {1: 100})

console.log( map.get(key1) )
console.log( map.get(Buffer.from([5])) )
