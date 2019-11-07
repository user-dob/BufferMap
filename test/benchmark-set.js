const { Suite } = require('benchmark');
const addon = require('bindings')('addon.node')

const BufferMap = addon.BufferMap;

const suite = new Suite();

const MAX_KEYS = 1000;

const bufferMap = new BufferMap();
const map = new Map(); 

suite.add('BufferMap', function() {
    for (let i = 0; i < MAX_KEYS; i++) {
        const key = Buffer.from(String(i));
        bufferMap.set(key, {});
    }
  })
  .add('Map', function() {
    for (let i = 0; i < MAX_KEYS; i++) {
        const key = Buffer.from(String(i));
        map.set(key.toString('hex'), {});
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