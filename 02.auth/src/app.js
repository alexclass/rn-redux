// lession from stephengrider

// import a library to create Component
import React, { Component } from 'react';
import { AppRegistry, View, Text } from 'react-native';
import firebase from 'firebase';

import { Header } from './components/common';
import LoginForm from './components/LoginForm';

export default function native() {
  // create a Component
  class App extends Component {
    componentWillMount() {
      firebase.initializeApp({
        apiKey: 'AIzaSyBtxMY4K6uHxv_2e3GD-FWAD2ACX6lPVRE',
        authDomain: 'authentication-70a18.firebaseapp.com',
        databaseURL: 'https://authentication-70a18.firebaseio.com',
        storageBucket: 'authentication-70a18.appspot.com',
        messagingSenderId: '682333809338'
      });
    }
    render() {
      return (
        <View style={{ flex: 1 }}>
          <Header headerText="Authentication" />
          <LoginForm />
        </View>
      );
    }
  }

  // render it to the screen
  AppRegistry.registerComponent('auth', () => App);
}
