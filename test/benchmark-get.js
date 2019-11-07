const crypto = require('crypto');
const { Suite } = require('benchmark');
const addon = require('bindings')('addon.node')

const BufferMap = addon.BufferMap;

const suite = new Suite();

const MAX_KEYS = 1000;

const bufferMap = new BufferMap();
const map = new Map(); 

for (let i = 0; i < MAX_KEYS; i++) {
    const key = crypto.randomBytes(8);
    bufferMap.set(key, {});
    map.set(key.toString('hex'), {});
}

suite.add('BufferMap', function() {
    for (let i = 0; i < MAX_KEYS; i++) {
        const key = crypto.randomBytes(8);
        bufferMap.get(key, {});
    }
  })
  .add('Map', function() {
    for (let i = 0; i < MAX_KEYS; i++) {
        const key = crypto.randomBytes(8);
        map.get(key.toString('hex'), {});
    }
  })
  // add listeners
  .on('cycle', function(event) {
    console.log(String(event.target));
  })
  .on('complete', function() {
    console.log('Fastest is ' + this.filter('fastest').map('name'));
  })
  // run async
  .run({ 'async': true });