// lession from stephengrider

// import a library to create Component
import React, { Component } from 'react';
import { AppRegistry, View, Text } from 'react-native';
import firebase from 'firebase';

import { Header } from './components/common';
import LoginForm from './components/LoginForm';
import Home from './components/Home';

import { firebaseConfig } from '../config';

export default function native() {
  // create a Component
  class App extends Component {
    state= {
      appName: '',
      user: '',
      loggedIn: null
    }
    componentWillMount() {
      const app=firebase.initializeApp(firebaseConfig);
      this.setState({ appName: firebase.app().name });

      firebase.auth().onAuthStateChanged( (user) => {
        if(user) {
          this.setState({ loggedIn: true, user})
        } else {
          this.setState({ loggedIn: false, user: ''})
        }
      });
    }

    renderLoggedIn() {
      if(this.state.user) { 
        return (
          <Home user={this.state.user} />
        );
      } else {
        return (
          <LoginForm />
        );
      }
    }
    render() {
      console.log('1.App componentWillMount firebaseConfig: ', firebaseConfig);
      return (
        <View style={{ flex: 1 }}>
          <Header headerText="ALEX2006HW" />
          {this.renderLoggedIn()}
        </View>
      );
    }
  }

  // render it to the screen
  AppRegistry.registerComponent('auth', () => App);
}
