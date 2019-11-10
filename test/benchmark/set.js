const crypto = require('crypto');
const { toBigIntBE } = require('bigint-buffer');
const { Suite } = require('benchmark');
const addon = require('bindings')('addon.node')

const BufferMap = addon.BufferMap;

const suite = new Suite();

const MAX_KEYS = 1000;
const BYTE_COUNT = 8;

const bufferMap = new BufferMap();
const stringMap = new Map();
const bigIntMap = new Map();

suite
  .add('BufferMap', function() {
    for (let i = 0; i < MAX_KEYS; i++) {
        const key = crypto.randomBytes(BYTE_COUNT);
        bufferMap.set(key, {});
    }
  })
  .add('StringMap', function() {
    for (let i = 0; i < MAX_KEYS; i++) {
        const key = crypto.randomBytes(BYTE_COUNT);
        stringMap.set(key.toString('hex'), {});
    }
  })
  .add('BigIntMap', function() {
    for (let i = 0; i < MAX_KEYS; i++) {
        const key = crypto.randomBytes(BYTE_COUNT);
        bigIntMap.set(toBigIntBE(key), {});
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