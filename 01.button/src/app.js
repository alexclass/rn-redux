// lession from stephengrider

// import a library to create Component
import React from 'react';
import { AppRegistry, View } from 'react-native';

import Header from './components/header.js';
import AlbumList from './components/AlbumList.js';
import WebView from './WebView.js';

export default function native() {
  // create a Component
  const App = () => (
      <View style={{ flex: 1 }}>
          <WebView />
      </View>
    );

  // render it to the screen
  AppRegistry.registerComponent('Pointlook', () => App);
}
