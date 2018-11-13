'use strict';

var React = require('react-native');
var JitPushNative = React.NativeModules.JitPush;

type Props = {
  isVisible: boolean;
}

module.exports = {
  jsCodeVersion: function() {
  	return JitPushNative.jsCodeVersion;
  }
};